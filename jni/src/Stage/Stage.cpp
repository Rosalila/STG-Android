#include "Stage.h"

Stage::Stage(RosalilaGraphics* painter,Sound* sonido,Receiver*receiver)
{
    this->painter=painter;
    this->sonido=sonido;
    this->receiver=receiver;
    this->iterator=0;
    //this->dialogue_bg=painter->getTexture("misc/dialogue_bg.png");

    //slow extra control
    this->iterate_slowdown_flag=false;
    this->current_slowdown_iteration=0;

	//effects
	this->transparency_effect=255;
}

void Stage::drawLayer(Layer* layer,bool alpha_enabled)
{
    //Animation speed
    if(layer->time_elapsed>layer->frame_duration)
    {
        layer->current_frame++;
        layer->time_elapsed=0;
    }

    //Loop animation
    if(getIterateSlowdownFlag())
        layer->time_elapsed++;

    if(layer->current_frame>=(int)layer->textures.size())
        layer->current_frame=0;

    //Get current image
    Image* texture=layer->textures[layer->current_frame];

    //Paint
    int size_x=layer->textures_size_x[layer->current_frame];
    int size_y=layer->textures_size_y[layer->current_frame];

    int pos_x=layer->alignment_x;
    int pos_y=painter->screen_height-size_y-layer->alignment_y;


	if(isSlowActive())
	{
		transparency_effect--;
	}else
	{
		transparency_effect++;
	}

	if(transparency_effect>255)
		transparency_effect=255;

	if(isSlowActive()
		&& receiver->isOuyaDown('m') && receiver->isOuyaDown('s'))
	{
		if(transparency_effect<64)
		{
			transparency_effect=64;
		}
	}else if(transparency_effect<128)
	{
		transparency_effect=128;
	}
/**/

    for(int i=0;i<painter->screen_width/(size_x+layer->separation_x)+2;i++)
    {
        painter->draw2DImage
        (   texture,
            size_x,size_y,
            pos_x+i*(size_x+layer->separation_x),pos_y,
            1.0,
            0.0,
            false,
            layer->depth_effect_x,
            layer->depth_effect_y,
            Color(255,255,255,transparency_effect),
            false,
            alpha_enabled);
    }

    if(layer->depth_effect_x>0)
    {
        if(painter->camera_x/layer->depth_effect_x>size_x+layer->separation_x+layer->alignment_x)
        {
            layer->alignment_x+=size_x+layer->separation_x;
        }
    }else if(layer->depth_effect_x<0)
    {
        if(painter->camera_x-layer->depth_effect_x>size_x+layer->alignment_x)
        {
            layer->alignment_x+=size_x;
        }
    }

}

void Stage::dibujarBack()
{
    for(int i=0;i<(int)back.size();i++)
    {
        Layer* layer=back[i];
        //if(i%2!=0)
        //	continue;
        drawLayer(layer,i!=0);
    }
}

void Stage::dibujarFront()
{
    for(int i=0;i<(int)front.size();i++)
    {
        Layer* layer=front[i];
        drawLayer(layer,true);
    }

    for (std::list<Dialogue*>::iterator dialogue = active_dialogues.begin(); dialogue != active_dialogues.end(); dialogue++)
    {
        painter->draw2DImage
        (   dialogue_bg,
            dialogue_bg->getWidth(),dialogue_bg->getHeight(),
            dialogue_x,dialogue_y,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            false);
        ((Dialogue*)*dialogue)->render(this->dialogue_x+this->dialogue_padding_x,this->dialogue_y+this->dialogue_padding_y);
    }
}

void Stage::loadDialogues(std::string file)
{
    writeLogLine("Loading dialogues from XML.");

    char *archivo=new char[255];
    strcpy(archivo,"stages/");
    strcat(archivo,file.c_str());
    strcat(archivo,"/dialogues.xml");
    TiXmlDocument doc_t( archivo );
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode *dialogues_file=doc->FirstChild("DialoguesFile");

    if(dialogues_file==NULL)
        return;

    for(TiXmlNode *dialogue_node=dialogues_file->FirstChild("dialogue");
            dialogue_node!=NULL;
            dialogue_node=dialogue_node->NextSibling("dialogue"))
    {
        int frame=atoi(dialogue_node->ToElement()->Attribute("frame"));
        std::string text=dialogue_node->ToElement()->Attribute("text");
        std::string path=dialogue_node->ToElement()->Attribute("path");

        dialogues[frame]=new Dialogue(painter,sonido,receiver,text,painter->getTexture("stages/"+file+"/"+path));
    }
}

void Stage::addLayer(string layer_name,int sprite_amount,int frame_duration,int depth_effect_x,int depth_effect_y,int alignment_x,int alignment_y,int separation_x)
{
    std::vector <Image*> textures;

    std::vector <int> textures_size_x;
    std::vector <int> textures_size_y;

	for(int i=1;i<=sprite_amount;i++)
	{
	    Image *image_temp=painter->getTexture("stages/"+name+"/images/"+layer_name+"/"+toString(i)+".png");
		int size_x=image_temp->getWidth();
		int size_y=image_temp->getHeight();
		textures.push_back(image_temp);
		textures_size_x.push_back(size_x);
		textures_size_y.push_back(size_y);
	}

    back.push_back(new Layer(textures,textures_size_x,textures_size_y,
		frame_duration,depth_effect_x,depth_effect_y,
		alignment_x,alignment_y,separation_x));
//(textures,textures_size_x,textures_size_y,40,0,0,0,0,0));
}

void Stage::addLayer(string layer_name,int sprite_amount,int frame_duration,int depth_effect_x,int depth_effect_y,int alignment_x,int alignment_y,int separation_x, int width, int height)
{
    std::vector <Image*> textures;

    std::vector <int> textures_size_x;
    std::vector <int> textures_size_y;

	for(int i=1;i<=sprite_amount;i++)
	{
	    Image *image_temp=painter->getTexture("stages/"+name+"/images/"+layer_name+"/"+toString(i)+".png");
		textures.push_back(image_temp);
		textures_size_x.push_back(width);
		textures_size_y.push_back(height);
	}

    back.push_back(new Layer(textures,textures_size_x,textures_size_y,
		frame_duration,depth_effect_x,depth_effect_y,
		alignment_x,alignment_y,separation_x));
//(textures,textures_size_x,textures_size_y,40,0,0,0,0,0));
}

void Stage::loadFromXML(std::string name)
{
    this->name=name;

    //Load settings
    char *music=new char[255];
    strcpy(music,"stages/");
    strcat(music,name.c_str());
    strcat(music,"/music.ogg");
    music_path=(std::string)music;

    this->dialogue_x=0;
    this->dialogue_y=0;
    this->dialogue_padding_x=0;
    this->dialogue_padding_y=0;


    this->bound_x1=0;
    this->bound_y1=0;
    this->bound_x2=painter->screen_width;
    this->bound_y2=painter->screen_height;


    this->velocity=20;

    writeLogLine("Loading stage's BackLayers.");


	addLayer("fondo",1,40,0,0,0,0,0);
	addLayer("planetaguerra",1,40,120,0,300,350,2000-256+32);
	addLayer("explosion",7,5,120,0,300,350,2000);
	addLayer("explosion",7,3,120,0,350,375,2000);
	addLayer("explosion",7,4,120,0,400,445,2000);
	addLayer("explosion",7,9,120,0,450,415,2000);
	addLayer("explosion",7,7,120,0,350,405,2000);
	addLayer("explosion",7,4,120,0,320,410,2000);
	addLayer("explosion",7,8,120,0,463,423,2000);
	addLayer("explosion",7,5,120,0,435,395,2000);
	addLayer("explosion",7,7,120,0,427,393,2000);
	addLayer("explosion",7,9,120,0,421,405,2000);
	addLayer("explosion",7,4,120,0,413,403,2000);
	addLayer("restosbrillantes",1,5,3,0,300,440,0,3500,75);
	addLayer("city",3,21,80,0,900,350,1300);
	addLayer("restosnegros",1,2,10,0,100,575,0);
	addLayer("restosnegros",1,2,25,0,300,450,0);
	//addLayer("restosnegros",1,2,30,0,600,300,0);
	//addLayer("plataforma",1,100,1,0,0,0,0);


/*
    //Load back layer
    for(TiXmlNode *nodo_back=stage_file->FirstChild("BackLayer");
            nodo_back!=NULL;
            nodo_back=nodo_back->NextSibling("BackLayer"))
    {
        int frame_duration=0;
        if(nodo_back->ToElement()->Attribute("frame_duration")!=NULL)
            frame_duration=atoi(nodo_back->ToElement()->Attribute("frame_duration"));

        int depth_effect_x=0;
        if(nodo_back->ToElement()->Attribute("depth_effect_x")!=NULL)
            depth_effect_x=atoi(nodo_back->ToElement()->Attribute("depth_effect_x"));

        int depth_effect_y=0;
        if(nodo_back->ToElement()->Attribute("depth_effect_y")!=NULL)
            depth_effect_y=atoi(nodo_back->ToElement()->Attribute("depth_effect_y"));

        int align_x=0;
        if(nodo_back->ToElement()->Attribute("align_x")!=NULL)
            align_x=atoi(nodo_back->ToElement()->Attribute("align_x"));

        int align_y=0;
        if(nodo_back->ToElement()->Attribute("align_y")!=NULL)
            align_y=atoi(nodo_back->ToElement()->Attribute("align_y"));

        int separation_x=0;
        if(nodo_back->ToElement()->Attribute("separation_x")!=NULL)
            separation_x=atoi(nodo_back->ToElement()->Attribute("separation_x"));

        std::vector <Image*> textures;
        std::vector <int> textures_size_x;
        std::vector <int> textures_size_y;

        for(TiXmlNode* layer=nodo_back->FirstChild("frame");
                layer!=NULL;
                layer=layer->NextSibling("frame"))
        {
            char *image=new char[255];
            strcpy(image,"stages/");
            strcat(image,name.c_str());
            strcat(image,"/images/");
            strcat(image,layer->ToElement()->Attribute("image_path"));

            Image *image_temp=painter->getTexture(image);

            int size_x=image_temp->getWidth();
            int size_y=image_temp->getHeight();

            if(layer->ToElement()->Attribute("width")!=NULL)
                size_x=atoi(layer->ToElement()->Attribute("width"));
            if(layer->ToElement()->Attribute("height")!=NULL)
                size_y=atoi(layer->ToElement()->Attribute("height"));

            textures.push_back(image_temp);
            textures_size_x.push_back(size_x);
            textures_size_y.push_back(size_y);
        }

        back.push_back(new Layer(textures,textures_size_x,textures_size_y,frame_duration,depth_effect_x,depth_effect_y,align_x,align_y,separation_x));
    }

    writeLogLine("Loading stage's FrontLayers.");

    //Load front layer
    for(TiXmlNode *nodo_back=stage_file->FirstChild("FrontLayer");
            nodo_back!=NULL;
            nodo_back=nodo_back->NextSibling("FrontLayer"))
    {
        int frame_duration=0;
        if(nodo_back->ToElement()->Attribute("frame_duration")!=NULL)
            frame_duration=atoi(nodo_back->ToElement()->Attribute("frame_duration"));

        int depth_effect_x=0;
        if(nodo_back->ToElement()->Attribute("depth_effect_x")!=NULL)
            depth_effect_x=atoi(nodo_back->ToElement()->Attribute("depth_effect_x"));

        int depth_effect_y=0;
        if(nodo_back->ToElement()->Attribute("depth_effect_y")!=NULL)
            depth_effect_y=atoi(nodo_back->ToElement()->Attribute("depth_effect_y"));

        int align_x=0;
        if(nodo_back->ToElement()->Attribute("align_x")!=NULL)
            align_x=atoi(nodo_back->ToElement()->Attribute("align_x"));

        int align_y=0;
        if(nodo_back->ToElement()->Attribute("align_y")!=NULL)
            align_y=atoi(nodo_back->ToElement()->Attribute("align_y"));

        int separation_x=0;
        if(nodo_back->ToElement()->Attribute("separation_x")!=NULL)
            separation_x=atoi(nodo_back->ToElement()->Attribute("separation_x"));

        std::vector <Image*> textures;
        std::vector <int> textures_size_x;
        std::vector <int> textures_size_y;

        for(TiXmlNode* layer=nodo_back->FirstChild("frame");
                layer!=NULL;
                layer=layer->NextSibling("frame"))
        {
            char *image=new char[255];
            strcpy(image,"stages/");
            strcat(image,name.c_str());
            strcat(image,"/images/");
            strcat(image,layer->ToElement()->Attribute("image_path"));

            Image *image_temp=painter->getTexture(image);

            int size_x=image_temp->getWidth();
            int size_y=image_temp->getHeight();

            if(layer->ToElement()->Attribute("width")!=NULL)
                size_x=atoi(layer->ToElement()->Attribute("width"));
            if(layer->ToElement()->Attribute("height")!=NULL)
                size_y=atoi(layer->ToElement()->Attribute("height"));

            textures.push_back(image_temp);
            textures_size_x.push_back(size_x);
            textures_size_y.push_back(size_y);
        }

        front.push_back(new Layer(textures,textures_size_x,textures_size_y,frame_duration,depth_effect_x,depth_effect_y,align_x,align_y,separation_x
                                  ));
    }
    writeLogLine("Stage loaded succesfully from XML.");

    loadDialogues(name);
*/
}

Stage::~Stage()
{
    writeLogLine("Deleting stage.");
    for(;!back.empty();)
    {
        Layer*layer=back.back();
        back.pop_back();
        delete layer;
    }
    for(;!front.empty();)
    {
        Layer*layer=front.back();
        front.pop_back();
        delete layer;
    }
}

int Stage::getBoundX1()
{
    return bound_x1;
}
int Stage::getBoundY1()
{
    return bound_y1;
}
int Stage::getBoundX2()
{
    return bound_x2;
}
int Stage::getBoundY2()
{
    return bound_y2;
}
int Stage::getVelocity()
{
    return velocity;
}
string Stage::getName()
{
    return name;
}
void Stage::setVelocity(int velocity)
{
    this->velocity=velocity;
}

void Stage::render()
{
//    for (std::list<Character*>::iterator character = active_enemies->begin(); character != active_enemies->end(); character++)
//        ((Character*)*character)->render();
}

void Stage::logic()
{
    if(getIterateSlowdownFlag())
        iterator++;

    if(dialogues.find(iterator)!=dialogues.end())
    {
        active_dialogues.push_back(dialogues[iterator]);
    }

    std::list<Dialogue*>::iterator i = active_dialogues.begin();
    while (i != active_dialogues.end())
    {
        Dialogue*d=(Dialogue*)*i;
        d->logic();
        if (d->destroyFlag())
        {
            active_dialogues.erase(i++);
        }
        else
        {
            ++i;
        }
    }
}

void Stage::playMusic()
{
    sonido->playMusic(this->music_path);
}
