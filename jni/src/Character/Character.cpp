#include "Character.h"

extern "C" JNIEXPORT jint JNICALL Java_org_libsdl_app_SDLMain_cFunction(JNIEnv* env, jobject o)
{
    return (jint) 2;
}

Character::Character(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name)
{
    //Setting up the other variables
    this->name=name;
    this->directory="";
    this->sonido=sonido;
    this->painter=painter;
    this->receiver=receiver;
    this->active_patterns=new std::list<Pattern*>;
    this->x=500;
    this->y=500;
    this->shooting=false;
    this->orientation="idle";
    this->current_type="o";
    this->visible=true;

    //Sprites animation
    this->animation_iteration=0;
    this->current_sprite=0;

    this->life_bar_x=0;
    this->life_bar_y=0;

    this->iteration=0;

    loadFromXML();
}

void Character::loadFromXML()
{
    loadMainXML();

    loadBulletsXML();

    loadPatternsXML();
}

void Character::loadMainXML()
{

    //Loading attributes
    this->velocity=5;
    this->animation_velocity=2;

    this->max_hp=100;
    this->hp=this->max_hp;

    this->max_hp=1;
    this->hp=this->max_hp;

    this->x=100;
    this->y=500;

    this->life_bar_x=0;
    this->life_bar_y=0;
    this->life_bar_rect_offset_x=0;
    this->life_bar_rect_offset_y=0;
    this->life_bar_rect_height=0;
    this->life_bar_rect_width=0;
    this->color.red=0;
    this->color.green=0;
    this->color.blue=0;
    this->color.alpha=255;



	if(directory=="chars/Iguro/")
	{
	    this->velocity=10;

	    this->shooting=false;

	    /*
		TiXmlDocument docTemp;
		const string strData = "<?xml version=\"1.0\" ?><Hello velocity=\"60\">World</Hello>";
		const char* pTest = docTemp.Parse(strData.c_str(), 0 , TIXML_ENCODING_UTF8);
		this->velocity=atoi(docTemp.FirstChild("Hello")->ToElement()->Attribute("velocity"));
		*/

		this->max_hp=200;
		this->hp=this->max_hp;

		this->life_bar_x=50;
		this->life_bar_y=50;
		this->life_bar_rect_offset_x=35;
		this->life_bar_rect_offset_y=18;
		this->life_bar_rect_width=186;
		this->life_bar_rect_height=16;

		this->color.red=0;
		this->color.green=128;
		this->color.blue=0;
		this->color.alpha=255;

		int hitbox_x=-15;
		int hitbox_y=-15;
		int hitbox_width=30;
		int hitbox_height=30;
		int hitbox_angle=0;
		this->hitbox.setValues(hitbox_x,hitbox_y,hitbox_width,hitbox_height,hitbox_angle);


        std::vector<Image*>sprites_vector;
		sprites_vector.push_back(painter->getTexture("chars/Iguro/sprites/nuevas/1iddle.png"));
		sprites_vector.push_back(painter->getTexture("chars/Iguro/sprites/nuevas/2iddle.png"));

        std::vector<Image*>vector_down;
		vector_down.push_back(painter->getTexture("chars/Iguro/sprites/nuevas/1down.png"));
		vector_down.push_back(painter->getTexture("chars/Iguro/sprites/nuevas/2down.png"));

        std::vector<Image*>vector_up;
		vector_up.push_back(painter->getTexture("chars/Iguro/sprites/nuevas/1up.png"));
		vector_up.push_back(painter->getTexture("chars/Iguro/sprites/nuevas/2up.png"));

        std::vector<Image*>vector_forward;
		vector_forward.push_back(painter->getTexture("chars/Iguro/sprites/nuevas/1forward.png"));
		vector_forward.push_back(painter->getTexture("chars/Iguro/sprites/nuevas/2forward.png"));

        std::vector<Image*>vector_back;
		vector_back.push_back(painter->getTexture("chars/Iguro/sprites/nuevas/1back.png"));
		vector_back.push_back(painter->getTexture("chars/Iguro/sprites/nuevas/2back.png"));

        std::vector<Image*>vector_destroyed;
		vector_destroyed.push_back(painter->getTexture("chars/Iguro/sprites/destroyed/1.png"));
		vector_destroyed.push_back(painter->getTexture("chars/Iguro/sprites/destroyed/2.png"));
		vector_destroyed.push_back(painter->getTexture("chars/Iguro/sprites/destroyed/3.png"));
		vector_destroyed.push_back(painter->getTexture("chars/Iguro/sprites/destroyed/4.png"));
		vector_destroyed.push_back(painter->getTexture("chars/Iguro/sprites/destroyed/5.png"));
		vector_destroyed.push_back(painter->getTexture("chars/Iguro/sprites/destroyed/6.png"));
		vector_destroyed.push_back(painter->getTexture("chars/Iguro/sprites/destroyed/7.png"));
		vector_destroyed.push_back(painter->getTexture("chars/Iguro/sprites/destroyed/8.png"));

		sprites["idle"]=sprites_vector;

		sprites["up"]=vector_up;
		sprites["down"]=vector_down;
		sprites["left"]=vector_back;
		sprites["right"]=vector_forward;

		sprites["destroyed"]=vector_destroyed;
	}else
	{
	    this->velocity=0;

		this->x=1000;
		this->y=300;

		this->max_hp=6500;
		this->hp=this->max_hp;

		this->life_bar_x=50;
		this->life_bar_y=600;
		this->life_bar_rect_offset_x=35;
		this->life_bar_rect_offset_y=18;
		this->life_bar_rect_width=186;
		this->life_bar_rect_height=16;

		this->color.red=128;
		this->color.green=0;
		this->color.blue=0;
		this->color.alpha=255;

		//this->iteration=100;//initiald
		//this->iteration=550;//crazy eyes
		//this->iteration=1200;//happy meal
		//this->iteration=2075;//rockets
		//this->iteration=2375;//feminst laser
		//this->iteration=4275;//kowaii

		int hitbox_x=-100;
		int hitbox_y=-250;
		int hitbox_width=200;
		int hitbox_height=500;
		int hitbox_angle=0;
		this->hitbox.setValues(hitbox_x,hitbox_y,hitbox_width,hitbox_height,hitbox_angle);

        std::vector<Image*>sprites_vector;
		sprites_vector.push_back(painter->getTexture("stages/FeministKillBot_normal/Enemy/sprites/idle/1.png"));
		sprites_vector.push_back(painter->getTexture("stages/FeministKillBot_normal/Enemy/sprites/idle/2.png"));
		sprites_vector.push_back(painter->getTexture("stages/FeministKillBot_normal/Enemy/sprites/idle/3.png"));

        std::vector<Image*>vector_destroyed;
		vector_destroyed.push_back(painter->getTexture("stages/FeministKillBot_normal/Enemy/sprites/destroyed/1.png"));
		vector_destroyed.push_back(painter->getTexture("stages/FeministKillBot_normal/Enemy/sprites/destroyed/2.png"));
		vector_destroyed.push_back(painter->getTexture("stages/FeministKillBot_normal/Enemy/sprites/destroyed/3.png"));
		vector_destroyed.push_back(painter->getTexture("stages/FeministKillBot_normal/Enemy/sprites/destroyed/4.png"));
		vector_destroyed.push_back(painter->getTexture("stages/FeministKillBot_normal/Enemy/sprites/destroyed/5.png"));
		vector_destroyed.push_back(painter->getTexture("stages/FeministKillBot_normal/Enemy/sprites/destroyed/6.png"));
		vector_destroyed.push_back(painter->getTexture("stages/FeministKillBot_normal/Enemy/sprites/destroyed/7.png"));
		vector_destroyed.push_back(painter->getTexture("stages/FeministKillBot_normal/Enemy/sprites/destroyed/8.png"));

		sprites["idle"]=sprites_vector;
		sprites["destroyed"]=vector_destroyed;
	}
}

void Character::addBullet(Sound* sonido,RosalilaGraphics* painter,Receiver*receiver, std::string name,int sprites_amount,
int hitbox_x,int hitbox_y,int hitbox_w,int hitbox_h,int hitbox_angle,
int damage)
{

    vector<Image*>sprites_temp;
	for(int i=1;i<=sprites_amount;i++)
	    sprites_temp.push_back(painter->getTexture(directory+"sprites/"+name+"/"+toString(i)+".png"));

    vector<Image*>sprites_onhit_temp;
    sprites_onhit_temp.push_back(painter->getTexture(directory+"sprites/hit1.png"));
    sprites_onhit_temp.push_back(painter->getTexture(directory+"sprites/hit2.png"));
    sprites_onhit_temp.push_back(painter->getTexture(directory+"sprites/hit3.png"));
    sprites_onhit_temp.push_back(painter->getTexture(directory+"sprites/hit4.png"));
    sprites_onhit_temp.push_back(painter->getTexture(directory+"sprites/hit5.png"));

    vector<Hitbox*>hitboxes_temp;
	hitboxes_temp.push_back(new Hitbox(hitbox_x,hitbox_y,hitbox_w,hitbox_h,hitbox_angle));
	bullets[name]=new Bullet(sonido,painter,receiver,name,sprites_temp,sprites_onhit_temp,hitboxes_temp,damage);

}

void Character::loadBulletsXML()
{
	if(directory=="chars/Iguro/")
	{
		addBullet(sonido,painter,receiver,
						/*name*/"lazor",
						/*sprites_amount*/3,
						/*hitbox_x*/-120,
						/*hitbox_y*/-10,
						/*hitbox_w*/240,
						/*hitbox_h*/20,
						/*hitbox_angle*/0,
						/*damage*/10);

		addBullet(sonido,painter,receiver,
						/*name*/"machinegun",
						/*sprites_amount*/3,
						/*hitbox_x*/-10,
						/*hitbox_y*/-10,
						/*hitbox_w*/20,
						/*hitbox_h*/20,
						/*hitbox_angle*/0,
						/*damage*/2);

		sonido->addSound("bullet.lazor",directory+string("sounds/lazor.ogg"));
		//sonido->addSound("bullet.machinegun",directory+string("sounds/machinegun.ogg"));
	}else
	{
		addBullet(sonido,painter,receiver,
						/*name*/"Eye Lazor",
						/*sprites_amount*/3,
						/*hitbox_x*/-40,
						/*hitbox_y*/0,
						/*hitbox_w*/80,
						/*hitbox_h*/6,
						/*hitbox_angle*/0,
						/*damage*/20);
		sonido->addSound("bullet.Eye Lazor",directory+string("sounds/Eye Lazor.ogg"));

		addBullet(sonido,painter,receiver,
						/*name*/"Feminist Laser startup",
						/*sprites_amount*/11,
						/*hitbox_x*/-1,
						/*hitbox_y*/-1,
						/*hitbox_w*/-1,
						/*hitbox_h*/-1,
						/*hitbox_angle*/0,
						/*damage*/0);

		addBullet(sonido,painter,receiver,
						/*name*/"Feminist Laser cooldown",
						/*sprites_amount*/11,
						/*hitbox_x*/-1,
						/*hitbox_y*/-1,
						/*hitbox_w*/-1,
						/*hitbox_h*/-1,
						/*hitbox_angle*/0,
						/*damage*/0);

		addBullet(sonido,painter,receiver,
						/*name*/"Feminist Laser active",
						/*sprites_amount*/4,
						/*hitbox_x*/-800,
						/*hitbox_y*/-120,
						/*hitbox_w*/1600,
						/*hitbox_h*/240,
						/*hitbox_angle*/0,
						/*damage*/60);

		addBullet(sonido,painter,receiver,
						/*name*/"Rocket",
						/*sprites_amount*/2,
						/*hitbox_x*/-8,
						/*hitbox_y*/-8,
						/*hitbox_w*/16,
						/*hitbox_h*/16,
						/*hitbox_angle*/0,
						/*damage*/20);
		sonido->addSound("bullet.Rocket",directory+string("sounds/Rocket.ogg"));
	}
}

void Character::addPattern(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name,int velocity,int max_velocity,int acceleration,int a_frequency,float angle,int angle_change,int stop_ac_at,int ac_frequency,int animation_velocity,std::string bullet,int offset_x,int offset_y,int startup,int cooldown,int duration,int random_angle,bool aim_player,float bullet_rotation, float br_change, bool independent_br)
{
	//30 frames converter
	/*
	velocity*=2;
	max_velocity*=2;
	acceleration*=2;
	a_frequency/=2;
	angle_change*=2;
	if(stop_ac_at!=-1)
		stop_ac_at*=2;
	ac_frequency/=2;
	animation_velocity/=2;
	startup/=2;
	cooldown/=2;
	if(duration!=-1)
		duration/=2;
	br_change*=2;
	/**/

	//60 frames converter
	velocity=ceil(velocity/2.0);
	max_velocity=ceil(max_velocity/2.0);
	acceleration=ceil(acceleration/2.0);
	a_frequency*=2;
	angle_change=ceil(angle_change/2.0);
	if(stop_ac_at!=-1)
		stop_ac_at=ceil(stop_ac_at/2.0);
	ac_frequency*=2;
	animation_velocity*=2;
	startup*=2;
	cooldown*=2;
	if(duration!=-1)
		duration*=2;
	br_change=ceil(br_change/2.0);
	/**/

	//Create new if not exists
	std::map<std::string, std::vector<Pattern*> >::const_iterator it = type.find(name);
	if(it==type.end())
	{
		std::vector<Pattern*> patterns;
		type[name]=patterns;
	}

	//Push new pattern
	type[name].push_back(new Pattern(sonido,painter,receiver,velocity,max_velocity,acceleration,a_frequency,angle,angle_change,
stop_ac_at,ac_frequency,animation_velocity,bullets[bullet],offset_x,offset_y,startup,cooldown,duration,random_angle,aim_player,
bullet_rotation,br_change,independent_br,new std::map<int, vector<Modifier*>* >(),&bullets));

}


void Character::addModifier(string type_param,int pattern_pos,int at, string variable, string value)
{
	//30 frames converter
	/*
	at/=2;
	/**/

	//60 frames converter
	at*=2;
	/**/

	//Create new if not exists
	std::vector<Pattern*> type_temp = type[type_param];
	Pattern* pattern_temp = type_temp[pattern_pos];

	std::map<int, vector<Modifier*>* >::const_iterator it = pattern_temp->modifiers->find(at);

	if(it==pattern_temp->modifiers->end())
	{
		vector<Modifier*>* modifiers_temp = new vector<Modifier*>();
		(*pattern_temp->modifiers)[at]=modifiers_temp;
	}
	(*pattern_temp->modifiers)[at]->push_back(new Modifier(variable,value));
}



void Character::loadPatternsXML()
{
	if(directory=="chars/Iguro/")
	{
		addPattern(sonido,painter,receiver,
					/*name*/"o",
					/*velocity*/0,
					/*max_velocity*/99999,
					/*acceleration*/10,
					/*a_frequency*/0,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/2,
					/*bullet*/"lazor",
					/*offset_x*/65,
					/*offset_y*/-44,
					/*startup*/0,
					/*cooldown*/11,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"o",
					/*velocity*/40,
					/*max_velocity*/120,
					/*acceleration*/1,
					/*a_frequency*/0,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/2,
					/*bullet*/"machinegun",
					/*offset_x*/85,
					/*offset_y*/4,
					/*startup*/0,
					/*cooldown*/2,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"o",
					/*velocity*/40,
					/*max_velocity*/90,
					/*acceleration*/2,
					/*a_frequency*/0,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/2,
					/*bullet*/"machinegun",
					/*offset_x*/75,
					/*offset_y*/-4,
					/*startup*/0,
					/*cooldown*/2,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

////////////////////////////////////U////////////////////////////////////
if(false)
{
		addPattern(sonido,painter,receiver,
					/*name*/"u",
					/*velocity*/0,
					/*max_velocity*/99999,
					/*acceleration*/10,
					/*a_frequency*/0,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/2,
					/*bullet*/"lazor",
					/*offset_x*/65,
					/*offset_y*/-44,
					/*startup*/0,
					/*cooldown*/11,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
}
		addPattern(sonido,painter,receiver,
					/*name*/"u",
					/*velocity*/20,
					/*max_velocity*/120,
					/*acceleration*/1,
					/*a_frequency*/1,
					/*angle*/-30,
					/*angle_change*/0,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/2,
					/*bullet*/"machinegun",
					/*offset_x*/85,
					/*offset_y*/4,
					/*startup*/0,
					/*cooldown*/2,
					/*duration*/99999,
					/*random_angle*/60,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"u",
					/*velocity*/20,
					/*max_velocity*/90,
					/*acceleration*/2,
					/*a_frequency*/1,
					/*angle*/-30,
					/*angle_change*/0,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/2,
					/*bullet*/"machinegun",
					/*offset_x*/75,
					/*offset_y*/-4,
					/*startup*/0,
					/*cooldown*/2,
					/*duration*/99999,
					/*random_angle*/60,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		//addModifier("u",2,20, "aim_player", "yes");

////////////////////////////////////Y////////////////////////////////////

		addPattern(sonido,painter,receiver,
					/*name*/"y",
					/*velocity*/70,
					/*max_velocity*/99999,
					/*acceleration*/0,
					/*a_frequency*/0,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/2,
					/*bullet*/"lazor",
					/*offset_x*/65,
					/*offset_y*/-44,
					/*startup*/0,
					/*cooldown*/4,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

////////////////////////////////////A////////////////////////////////////

		addPattern(sonido,painter,receiver,
					/*name*/"a",
					/*velocity*/0,
					/*max_velocity*/99999,
					/*acceleration*/10,
					/*a_frequency*/0,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/4,
					/*bullet*/"lazor",
					/*offset_x*/65,
					/*offset_y*/-44,
					/*startup*/0,
					/*cooldown*/22,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"a",
					/*velocity*/20,
					/*max_velocity*/120,
					/*acceleration*/1,
					/*a_frequency*/1,
					/*angle*/-45,
					/*angle_change*/2,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/4,
					/*bullet*/"machinegun",
					/*offset_x*/85,
					/*offset_y*/4,
					/*startup*/0,
					/*cooldown*/4,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"a",
					/*velocity*/20,
					/*max_velocity*/90,
					/*acceleration*/2,
					/*a_frequency*/1,
					/*angle*/45,
					/*angle_change*/-2,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/3,
					/*bullet*/"machinegun",
					/*offset_x*/75,
					/*offset_y*/-4,
					/*startup*/0,
					/*cooldown*/4,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
	}else
	{
	}
}

void Character::logic(int stage_velocity)
{
    animationControl();
    spellControl(stage_velocity);
}

void Character::animationControl()
{
    if(animation_iteration>=animation_velocity)
    {
        current_sprite++;
        if(current_sprite>=(int)sprites[orientation].size())
        {
            current_sprite=0;
            if(orientation=="destroyed")
                visible=false;
        }
        animation_iteration=0;
    }
animation_iteration++;
    //if(getIterateSlowdownFlag())
    //    animation_iteration++;
}

void Character::spellControl(int stage_velocity)
{
    std::vector<Pattern*> patterns=type[current_type];
    for(int i=0;i<(int)patterns.size();i++)
    {
        if(shooting && this->hp!=0)
        {
            patterns[i]->updateStateShouting();
            if(patterns[i]->isReady())
            {
                patterns[i]->getBullet()->playSound();
                this->addActivePattern(patterns[i]);
            }
        }else
        {
            patterns[i]->updateStateNotShouting();
        }
    }

    if((current_type!="o" || !shooting ) && type.find("o") != type.end())
    {
        std::vector<Pattern*> patterns_o=type["o"];
        for(int i=0;i<(int)patterns_o.size();i++)
        {
            patterns_o[i]->updateCooldownNotShouting();
        }
    }

    if((current_type!="u" || !shooting ) && type.find("u") != type.end())
    {
        std::vector<Pattern*> patterns_o=type["u"];
        for(int i=0;i<(int)patterns_o.size();i++)
        {
        	patterns_o[i]->updateCooldownNotShouting();
        }
    }

    if((current_type!="y" || !shooting ) && type.find("y") != type.end())
    {
        std::vector<Pattern*> patterns_o=type["y"];
        for(int i=0;i<(int)patterns_o.size();i++)
        {
        	patterns_o[i]->updateCooldownNotShouting();
        }
    }

    if((current_type!="a" || !shooting ) && type.find("a") != type.end())
    {
        std::vector<Pattern*> patterns_o=type["a"];
        for(int i=0;i<(int)patterns_o.size();i++)
        {
        	patterns_o[i]->updateCooldownNotShouting();
        }
    }

    for (std::list<Pattern*>::iterator pattern = active_patterns->begin(); pattern != active_patterns->end(); pattern++)
        ((Pattern*)*pattern)->logic(stage_velocity);
}

void Character::parrentRender()
{
/*
    if(!visible)
        return;
*/
    painter->draw2DImage
    (   sprites[orientation][current_sprite],
        sprites[orientation][current_sprite]->getWidth(),sprites[orientation][current_sprite]->getHeight(),
        this->x-sprites[orientation][current_sprite]->getWidth()/2,this->y-sprites[orientation][current_sprite]->getHeight()/2,
        1.0,
        0.0,
        false,
        0,0,
        Color(255,255,255,255),
        true);

/*
    if(receiver->IsKeyDownn(SDLK_h) ||
		receiver->isOuyaDown('a'))
    {
        painter->drawRectangle(this->getHitbox().getX(),
                               this->getHitbox().getY(),
                               hitbox.getWidth(),hitbox.getHeight(),
                               hitbox.getAngle(),100,0,0,100,true);
    }
*/
}

void Character::renderPatterns()
{
	    for (std::list<Pattern*>::iterator pattern = active_patterns->begin(); pattern != active_patterns->end(); pattern++)
	        ((Pattern*)*pattern)->render();
/*
	for(std::map<std::string,Bullet* >::iterator bullet_iterator = bullets.begin(); bullet_iterator != bullets.end(); ++bullet_iterator)
    {
    	Bullet* bullet=(*bullet_iterator).second;

    	for(int current_image=0;current_image<bullet->spritesSize();current_image++)
    	{
			vector<int> position_x;
			vector<int> position_y;
			vector<float> rotation;
			Image* image=bullet->getImage(current_image);

			for (std::list<Pattern*>::iterator pattern_iterator = active_patterns->begin(); pattern_iterator != active_patterns->end(); pattern_iterator++)
			{
				Pattern* pattern=(Pattern*)*pattern_iterator;
				if(bullet->getName()==pattern->getBullet()->getName()
				   && pattern->getCurrentSprite()==current_image
				   && !pattern->isHit())
				{
					//pattern->render();
					position_x.push_back(pattern->getX()-image->getWidth()/2);
					position_y.push_back(pattern->getY()-image->getHeight()/2);
					rotation.push_back(pattern->getAngle());
				}
			}

			painter->draw2DImageBatch
			(   image,
				image->getWidth(),image->getHeight(),
				position_x,position_y,
				1.0,
				rotation,//getBulletAngle(),
				false,
				0,0,
				Color(255,255,255,255),
				true);
    	}

    	//On hit draw
    	for(int current_image=0;current_image<bullet->spritesOnHitSize();current_image++)
    	{
			vector<int> position_x;
			vector<int> position_y;
			vector<float> rotation;
			Image* image=bullet->getOnHitImage(current_image);

			for (std::list<Pattern*>::iterator pattern_iterator = active_patterns->begin(); pattern_iterator != active_patterns->end(); pattern_iterator++)
			{
				Pattern* pattern=(Pattern*)*pattern_iterator;
				if(bullet->getName()==pattern->getBullet()->getName()
				   && pattern->getCurrentSprite()==current_image
				   && pattern->isHit())
				{
					//pattern->render();
					position_x.push_back(pattern->getX()-image->getWidth()/2);
					position_y.push_back(pattern->getY()-image->getHeight()/2);
					rotation.push_back(pattern->getAngle());
				}
			}

			painter->draw2DImageBatch
			(   image,
				image->getWidth(),image->getHeight(),
				position_x,position_y,
				1.0,
				rotation,//getBulletAngle(),
				false,
				0,0,
				Color(255,255,255,255),
				true);
    	}
    }
	/**/
}

void Character::render()
{
    parrentRender();
}

int Character::getX()
{
    return this->x;
}

int Character::getY()
{
    return this->y;
}

int Character::getHP()
{
    return this->hp;
}

int Character::getIteration()
{
    return iteration;
}

void Character::setX(int x)
{
    this->x=x;
}

void Character::setY(int y)
{
    this->y=y;
}

std::list<Pattern*>* Character::getActivePatterns()
{
    return active_patterns;
}

void Character::setType(std::string type)
{
    this->current_type=type;
}

bool Character::collides(Hitbox hitbox,int hitbox_x,int hitbox_y,float hitbox_angle)
{
    return this->hitbox.getPlacedHitbox(Point(this->x,this->y),0).collides(hitbox,0,0,0);
}

void Character::hit(int damage)
{
    this->hp-=damage;
    if(hp<0)
        hp=0;
}

Hitbox Character::getHitbox()
{
    return hitbox.getPlacedHitbox(Point(this->x,this->y),0);
}


void Character::addActivePattern(Pattern* pattern)
{
    Pattern* pattern_temp=new Pattern(pattern,this->x,this->y);
    float angle=pattern_temp->getAngle();
    angle+=pattern_temp->getRandomAngle();
    pattern_temp->setAngle(angle);

    active_patterns->push_back(pattern_temp);

    painter->addExplosion(pattern_temp->getX()-pattern_temp->getBullet()->getImage(0)->getWidth()/2,pattern_temp->getY());
}

Character::~Character()
{
	for(std::map<std::string,std::vector<Image*> >::iterator MapItor = sprites.begin(); MapItor != sprites.end(); ++MapItor)
	{
		std::vector<Image*> Value = (*MapItor).second;

		for(;!Value.empty();)
		{
		    Image*image=Value.back();
		    Value.pop_back();
		    delete image;
		}
	}



	for(std::map<std::string,Bullet* >::iterator MapItor = bullets.begin(); MapItor != bullets.end(); ++MapItor)
	{
		Bullet* Value = (*MapItor).second;
		delete Value;
	}

}
