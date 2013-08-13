#include "Character.h"

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
    this->shooting=true;
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

    this->max_hp=6500;
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

		this->max_hp=100000;
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

		int hitbox_x=10;
		int hitbox_y=10;
		int hitbox_width=100;
		int hitbox_height=10;
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

		sprites["idle"]=sprites_vector;

		sprites["up"]=vector_up;
		sprites["down"]=vector_down;
		sprites["left"]=vector_back;
		sprites["right"]=vector_forward;
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

		//this->iteration=1200;

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

		sprites["idle"]=sprites_vector;
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
						/*damage*/2);

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
	}else
	{
		addBullet(sonido,painter,receiver,
						/*name*/"Eye Lazor",
						/*sprites_amount*/3,
						/*hitbox_x*/-70,
						/*hitbox_y*/0,
						/*hitbox_w*/140,
						/*hitbox_h*/6,
						/*hitbox_angle*/0,
						/*damage*/20);

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
						/*hitbox_x*/-10,
						/*hitbox_y*/-10,
						/*hitbox_w*/20,
						/*hitbox_h*/20,
						/*hitbox_angle*/0,
						/*damage*/20);
	}
}

void Character::addPattern(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name,int velocity,int max_velocity,int acceleration,int a_frequency,float angle,int angle_change,int stop_ac_at,int ac_frequency,int animation_velocity,std::string bullet,int offset_x,int offset_y,int startup,int cooldown,int duration,int random_angle,bool aim_player,float bullet_rotation, float br_change, bool independent_br)
{
	//32 frames converter
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
	//32 frames converter
	/*
	at/=2;
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
					/*offset_x*/120,
					/*offset_y*/-17,
					/*startup*/4,
					/*cooldown*/22,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"o",
					/*velocity*/20,
					/*max_velocity*/120,
					/*acceleration*/1,
					/*a_frequency*/1,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/2,
					/*bullet*/"machinegun",
					/*offset_x*/80,
					/*offset_y*/25,
					/*startup*/25,
					/*cooldown*/4,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"o",
					/*velocity*/20,
					/*max_velocity*/90,
					/*acceleration*/2,
					/*a_frequency*/1,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/99999,
					/*ac_frequency*/0,
					/*animation_velocity*/2,
					/*bullet*/"machinegun",
					/*offset_x*/80,
					/*offset_y*/18,
					/*startup*/25,
					/*cooldown*/4,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

////////////////////////////////////U////////////////////////////////////
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
					/*offset_x*/120,
					/*offset_y*/-17,
					/*startup*/4,
					/*cooldown*/22,
					/*duration*/99999,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

////////////////////////////////////Y////////////////////////////////////
		addPattern(sonido,painter,receiver,
					/*name*/"y",
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
					/*offset_x*/120,
					/*offset_y*/-17,
					/*startup*/4,
					/*cooldown*/22,
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
					/*animation_velocity*/2,
					/*bullet*/"lazor",
					/*offset_x*/120,
					/*offset_y*/-17,
					/*startup*/4,
					/*cooldown*/22,
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


    if(/*receiver->IsKeyDownn(SDLK_h) || */
		receiver->isOuyaDown('a'))
    {
        painter->drawRectangle(this->getHitbox().getX(),
                               this->getHitbox().getY(),
                               hitbox.getWidth(),hitbox.getHeight(),
                               hitbox.getAngle(),100,0,0,100,true);
    }
}

void Character::renderPatterns()
{
    for (std::list<Pattern*>::iterator pattern = active_patterns->begin(); pattern != active_patterns->end(); pattern++)
        ((Pattern*)*pattern)->render();
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
