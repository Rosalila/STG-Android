#include "Enemy.h"

Enemy::Enemy(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name,Player*player)
{
    //Setting up the other variables
    this->name=name;
    this->directory="stages/"+name+"/Enemy/";
    this->sonido=sonido;
    this->painter=painter;
    this->receiver=receiver;
    this->player=player;
    this->active_patterns=new std::list<Pattern*>;
    this->shooting=true;
    this->orientation="idle";
    this->current_type="";
    this->visible=true;

    //Enemy variables
    this->angle=180;
    this->velocity=0;
    this->angle_change=0;


    //Sprites animation
    this->animation_velocity=4;
    this->animation_iteration=0;
    this->current_sprite=0;

    this->iteration=0;

    this->score_upload_message="";
    bool flag_begin_upload=false;

    loadFromXML();

    loadModifiersFromXML();
    life_bar=painter->getTexture(directory+"life_bar.png");
}

void Enemy::modifiersControl()
{
    bool flag_iterator_change=false;

    vector<Modifier*>* current_modifiers = this->modifiers[iteration];
    if(current_modifiers!=NULL)
    {
        for(int i=0;i<(int)current_modifiers->size();i++)
        {
            Modifier* modifier=(*current_modifiers)[i];
            if(modifier->variable=="velocity")
            {
                this->velocity=atoi(modifier->value.c_str());
            }
            if(modifier->variable=="angle")
            {
                this->angle=atoi(modifier->value.c_str());
            }
            if(modifier->variable=="angle_change")
            {
                this->angle_change=atoi(modifier->value.c_str());
            }
            if(modifier->variable=="iterator")
            {
                this->iteration=atoi(modifier->value.c_str());
                flag_iterator_change=true;
            }
            if(modifier->variable=="pattern_type")
            {
                this->current_type=modifier->value;
            }
        }
    }

    if(!flag_iterator_change && getIterateSlowdownFlag())
        iteration++;
}

void Enemy::logic(int stage_velocity, string stage_name, int global_iteration, string username)
{
    animationControl();
    spellControl(stage_velocity);

    for (std::list<Pattern*>::iterator pattern = active_patterns->begin(); pattern != active_patterns->end(); pattern++)
        if(((Pattern*)*pattern)->getAimPlayer())
        {
            double distance_x=player->x-((Pattern*)*pattern)->getX();
            double distance_y=player->y-((Pattern*)*pattern)->getY();
            ((Pattern*)*pattern)->setAngle(((Pattern*)*pattern)->getAngle()-atan2(distance_y,distance_x)*180/PI);
        }

    if(this->hp>0)
	{
        modifiersControl();
	}
    else
    {
        if(orientation!="destroyed" && flag_begin_upload)
        {
            orientation="destroyed";
            if(this->sonido->soundExists(name+".destroyed"))
                this->sonido->playSound(name+".destroyed");

            this->hitbox.setValues(0,0,0,0,0);

            //Delete bullets
            std::list<Pattern*>* active_patterns=getActivePatterns();
            std::list<Pattern*>::iterator i = active_patterns->begin();
            while (i != active_patterns->end())
            {
                Pattern*p=(Pattern*)*i;
                active_patterns->erase(i++);
                delete p;
            }

            RosalilaNetwork network(painter);
            //score_upload_message = network.runTcpClientSendScore(31716, "108.59.1.187",stage_name, username, global_iteration);
            score_upload_message = network.runTcpClientSendScore(31716, "localhost",stage_name, username, global_iteration);
        }
    }

    this->angle+=this->angle_change / getSlowdown();

    this->x += cos (angle*PI/180) * velocity / getSlowdown() + stage_velocity;
    this->y -= sin (angle*PI/180) * velocity / getSlowdown();

    getIterateSlowdownFlag();
}

void Enemy::render()
{
    painter->drawRectangle(life_bar_x+life_bar_rect_offset_x,life_bar_y+life_bar_rect_offset_y,(life_bar_rect_width*hp)/max_hp,life_bar_rect_height,0,this->color.getRed(),this->color.getGreen(),this->color.getBlue(),this->color.getAlpha(),false);
    parrentRender();

    painter->draw2DImage
    (   life_bar,
        life_bar->getWidth(),life_bar->getHeight(),
        painter->camera_x+life_bar_x,life_bar_y,
        1.0,
        0.0,
        false,
        0,0,
        Color(255,255,255,255),
        true);
    if(this->hp<=0)
    {
        painter->drawText("Uploading score.",0,80);
        painter->drawText(score_upload_message,0,95);
        flag_begin_upload = true;
    }
}

void Enemy::addModifier(int at,std::string variable,std::string value)
{
	//Create new if not exists
	std::map<int, vector<Modifier*>* >::const_iterator it = modifiers.find(at);
	if(it==modifiers.end())
	{
		vector<Modifier*>* temp_modifiers=new vector<Modifier*>();
		modifiers[at]=temp_modifiers;
	}

	this->modifiers[at]->push_back(new Modifier(variable,value));
}

void Enemy::loadModifiersFromXML()
{
	addModifier(0,"velocity","1");
	addModifier(0,"angle_change","5");

	addModifier(100,"pattern_type","InitialD");
	addModifier(1000,"pattern_type","");

	addModifier(1100,"pattern_type","Crazy eyes");
	addModifier(2950,"pattern_type","");
	addModifier(2950,"velocity","0");
	addModifier(2950,"angle_change","0");

	addModifier(3100,"pattern_type","Happy meal");
	addModifier(3100,"velocity","0");

	for(int i=0;i<4;i++)
	{
		addModifier(3300+i*100,"velocity","2");
		addModifier(3300+i*100,"angle","180");
	}

	for(int i=0;i<4;i++)
	{
		addModifier(3350+i*100,"angle","0");
	}

	for(int i=0;i<4;i++)
	{
		addModifier(3800+i*150,"angle","180");
	}

	for(int i=0;i<4;i++)
	{
		addModifier(3850+i*150,"angle","-60");
	}

	for(int i=0;i<4;i++)
	{
		addModifier(3900+i*150,"angle","60");
	}

	addModifier(4550,"pattern_type","");
	addModifier(4550,"velocity","5");
	addModifier(4550,"angle","-90");

	addModifier(4600,"pattern_type","Rockets");
	addModifier(4600,"velocity","5");
	addModifier(4600,"angle","90");
	addModifier(4700,"angle","-90");
	addModifier(4800,"angle","90");

	addModifier(4900,"pattern_type","Feminist Laser");
	addModifier(4900,"velocity","0");
	addModifier(5100,"pattern_type","");

	addModifier(5200,"pattern_type","Rockets");
	addModifier(5200,"velocity","5");
	addModifier(5200,"angle","-90");
	addModifier(5300,"angle","90");
	addModifier(5400,"angle","-90");
	addModifier(5500,"angle","90");
	addModifier(5600,"angle","-90");
	addModifier(5700,"angle","90");

	addModifier(5800,"pattern_type","Feminist Laser");
	addModifier(5800,"velocity","0");
	addModifier(6000,"pattern_type","");

	addModifier(6100,"pattern_type","Rockets");
	addModifier(6100,"velocity","5");
	addModifier(6100,"angle","-90");
	addModifier(6200,"angle","90");
	addModifier(6300,"angle","-90");
	addModifier(6400,"angle","90");
	addModifier(6500,"angle","-90");
	addModifier(6600,"pattern_type","");
	addModifier(6600,"angle","90");

	addModifier(6700,"velocity","0");
	addModifier(6700,"pattern_type","KowaiiDesu");
/**/
}

void Enemy::addActivePattern(Pattern* pattern)
{
    Pattern* pattern_temp=new Pattern(pattern,this->x,this->y);
    float angle=pattern_temp->getAngle();
    angle+=pattern_temp->getRandomAngle();

    pattern_temp->setAngle(angle);

    if(pattern_temp->getAimPlayer())
    {
        double distance_x=player->x-pattern_temp->getX();
        double distance_y=player->y-pattern_temp->getY();
        pattern_temp->setAngle(pattern_temp->getAngle()-atan2(distance_y,distance_x)*180/PI);
    }

    active_patterns->push_back(pattern_temp);
}
