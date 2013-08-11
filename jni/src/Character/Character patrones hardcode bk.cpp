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
    this->current_type="1";
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

		//this->iteration=6700;

		int hitbox_x=-100;
		int hitbox_y=-100;
		int hitbox_width=200;
		int hitbox_height=200;
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
		addBullet(sonido,painter,receiver,"lazor",3,-120,-10,240,20,0,2);

		addBullet(sonido,painter,receiver,"machinegun",3,-10,-10,20,20,0,2);

		sonido->addSound("bullet.lazor",directory+string("sounds/lazor.ogg"));
	}else
	{
		addBullet(sonido,painter,receiver,"Eye Lazor",3,-50,-3,100,6,0,20);
		addBullet(sonido,painter,receiver,"Feminist Laser startup",
											11,-1,-1,-1,-1,0,0);
		addBullet(sonido,painter,receiver,"Feminist Laser cooldown",
											11,-1,-1,-1,-1,0,0);
		addBullet(sonido,painter,receiver,"Feminist Laser active",
											4,-600,-120,1200,240,0,60);
		addBullet(sonido,painter,receiver,"Rocket",
											2,-10,-10,20,20,0,20);
	}
}

void Character::addPattern(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name,int velocity,int max_velocity,int acceleration,int a_frequency,float angle,int angle_change,int stop_ac_at,int ac_frequency,int animation_velocity,std::string bullet,int offset_x,int offset_y,int startup,int cooldown,int duration,int random_angle,bool aim_player,float bullet_rotation, float br_change, bool independent_br)
{
	//32 frames converter
	/**/
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
	/**/
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
					/*name*/"1",
					/*velocity*/0,
					/*max_velocity*/99999,
					/*acceleration*/10,
					/*a_frequency*/1,
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
					/*name*/"1",
					/*velocity*/20,
					/*max_velocity*/80,
					/*acceleration*/1,
					/*a_frequency*/2,
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
					/*name*/"1",
					/*velocity*/20,
					/*max_velocity*/50,
					/*acceleration*/2,
					/*a_frequency*/2,
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
	}else
	{
		std::map<int, vector<Modifier*>* >*pattern_modifiers=new std::map<int, vector<Modifier*>* >();

////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////InitialD//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/20,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-15,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",0,20, "angle", "0");
		addModifier("InitialD",0,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/16,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-10,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",1,20, "angle", "0");
		addModifier("InitialD",1,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/20,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-5,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",2,20, "angle", "0");
		addModifier("InitialD",2,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/16,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",3,20, "angle", "0");
		addModifier("InitialD",3,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/20,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/5,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",4,20, "angle", "0");
		addModifier("InitialD",4,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/16,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/10,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",5,20, "angle", "0");
		addModifier("InitialD",5,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/20,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/15,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",6,20, "angle", "0");
		addModifier("InitialD",6,20, "aim_player", "yes");

///
///Set 2
///


		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/20,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-15,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",7,20, "angle", "0");
		addModifier("InitialD",7,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/16,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-10,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",8,20, "angle", "0");
		addModifier("InitialD",8,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/20,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-5,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",9,20, "angle", "0");
		addModifier("InitialD",9,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/16,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",10,20, "angle", "0");
		addModifier("InitialD",10,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/20,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/5,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",11,20, "angle", "0");
		addModifier("InitialD",11,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/16,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/10,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",12,20, "angle", "0");
		addModifier("InitialD",12,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"InitialD",
					/*velocity*/20,
					/*max_velocity*/20,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/15,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("InitialD",13,20, "angle", "0");
		addModifier("InitialD",13,20, "aim_player", "yes");



////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Crazy eyes////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);


		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/10,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/20,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/30,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/40,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/50,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/60,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/70,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/80,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/100,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/110,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/120,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/130,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/140,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/150,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/160,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/170,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/190,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/200,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/210,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/220,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/230,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/240,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/250,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/260,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/270,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/280,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/290,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/300,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/310,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/320,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/330,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/4,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/340,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Crazy eyes",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/350,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-45,
					/*offset_y*/145,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Happy meal////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",0,20, "angle", "180");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",1,25, "angle", "180");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",2,30, "angle", "180");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",3,35, "angle", "180");


		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",4,20, "angle", "180");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",5,25, "angle", "180");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",6,30, "angle", "180");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",7,35, "angle", "180");

///
///Set 2
///
		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",8,0, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",9,5, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",10,10, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",11,15, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",12,20, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",13,25, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",14,30, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",15,35, "angle", "0");

///

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",16,5, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",17,10, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",18,15, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",19,20, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",20,25, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",21,30, "angle", "0");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/10,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/-90,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/20,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",22,35, "angle", "0");

///
/// Set 3
///

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/0,
					/*max_velocity*/8,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-55,
					/*offset_y*/157,
					/*startup*/0,
					/*cooldown*/10,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",23,20, "angle", "135");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/0,
					/*max_velocity*/8,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-55,
					/*offset_y*/157,
					/*startup*/0,
					/*cooldown*/10,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",24,20, "angle", "135");
		addModifier("Happy meal",24,60, "angle", "225");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/0,
					/*max_velocity*/8,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-55,
					/*offset_y*/157,
					/*startup*/0,
					/*cooldown*/10,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",25,20, "angle", "135");
		addModifier("Happy meal",25,60, "angle", "225");
		addModifier("Happy meal",25,100, "angle", "135");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/0,
					/*max_velocity*/8,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-55,
					/*offset_y*/157,
					/*startup*/0,
					/*cooldown*/10,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",26,20, "angle", "135");
		addModifier("Happy meal",26,60, "angle", "225");
		addModifier("Happy meal",26,100, "angle", "135");
		addModifier("Happy meal",26,140, "angle", "225");

///

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/0,
					/*max_velocity*/8,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-55,
					/*offset_y*/157,
					/*startup*/0,
					/*cooldown*/10,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",27,20, "angle", "225");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/0,
					/*max_velocity*/8,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-55,
					/*offset_y*/157,
					/*startup*/0,
					/*cooldown*/10,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",28,20, "angle", "225");
		addModifier("Happy meal",28,60, "angle", "135");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/0,
					/*max_velocity*/8,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-55,
					/*offset_y*/157,
					/*startup*/0,
					/*cooldown*/10,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",29,20, "angle", "225");
		addModifier("Happy meal",29,60, "angle", "135");
		addModifier("Happy meal",29,100, "angle", "225");

		addPattern(sonido,painter,receiver,
					/*name*/"Happy meal",
					/*velocity*/0,
					/*max_velocity*/8,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/-55,
					/*offset_y*/157,
					/*startup*/0,
					/*cooldown*/10,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("Happy meal",30,20, "angle", "225");
		addModifier("Happy meal",30,60, "angle", "135");
		addModifier("Happy meal",30,100, "angle", "225");
		addModifier("Happy meal",30,140, "angle", "135");


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Rockets///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

		addPattern(sonido,painter,receiver,
					/*name*/"Rockets",
					/*velocity*/3,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/0,
					/*offset_y*/0,
					/*startup*/0,
					/*cooldown*/60,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

///
///Set 2
///

		addPattern(sonido,painter,receiver,
					/*name*/"Rockets",
					/*velocity*/-1,
					/*max_velocity*/30,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/120,
					/*ac_frequency*/60,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-70,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Rockets",
					/*velocity*/-1,
					/*max_velocity*/30,
					/*acceleration*/1,
					/*a_frequency*/20,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/120,
					/*ac_frequency*/60,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/10,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Rockets",
					/*velocity*/-1,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/120,
					/*ac_frequency*/60,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-30,
					/*offset_y*/184,
					/*startup*/20,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

//
//Set 3
//

		addPattern(sonido,painter,receiver,
					/*name*/"Rockets",
					/*velocity*/-1,
					/*max_velocity*/30,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/120,
					/*ac_frequency*/60,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/70,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Rockets",
					/*velocity*/-1,
					/*max_velocity*/30,
					/*acceleration*/1,
					/*a_frequency*/20,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/120,
					/*ac_frequency*/60,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/10,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Rockets",
					/*velocity*/-1,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/120,
					/*ac_frequency*/60,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/30,
					/*offset_y*/184,
					/*startup*/20,
					/*cooldown*/80,
					/*duration*/600,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Feminist Laser////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

		addPattern(sonido,painter,receiver,
					/*name*/"Feminist Laser",
					/*velocity*/0,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Feminist Laser startup",
					/*offset_x*/-933,
					/*offset_y*/110,
					/*startup*/0,
					/*cooldown*/200,
					/*duration*/60,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Feminist Laser",
					/*velocity*/0,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Feminist Laser active",
					/*offset_x*/-933,
					/*offset_y*/110,
					/*startup*/55,
					/*cooldown*/200,
					/*duration*/100,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"Feminist Laser",
					/*velocity*/0,
					/*max_velocity*/30,
					/*acceleration*/0,
					/*a_frequency*/10,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Feminist Laser cooldown",
					/*offset_x*/-933,
					/*offset_y*/110,
					/*startup*/150,
					/*cooldown*/200,
					/*duration*/55,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////KowaiiDesu////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/0,
					/*max_velocity*/15,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/20,
					/*offset_y*/155,
					/*startup*/0,
					/*cooldown*/5,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("KowaiiDesu",0,20, "angle", "-30");
		addModifier("KowaiiDesu",0,20, "aim_player", "yes");
		addModifier("KowaiiDesu",0,30, "angle", "30");
		addModifier("KowaiiDesu",0,30, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/0,
					/*max_velocity*/15,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/20,
					/*offset_y*/155,
					/*startup*/0,
					/*cooldown*/5,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("KowaiiDesu",1,20, "angle", "30");
		addModifier("KowaiiDesu",1,20, "aim_player", "yes");
		addModifier("KowaiiDesu",1,30, "angle", "-30");
		addModifier("KowaiiDesu",1,30, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/0,
					/*max_velocity*/15,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/20,
					/*offset_y*/155,
					/*startup*/0,
					/*cooldown*/5,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("KowaiiDesu",2,20, "angle", "-70");
		addModifier("KowaiiDesu",2,20, "aim_player", "yes");
		addModifier("KowaiiDesu",2,30, "angle", "70");
		addModifier("KowaiiDesu",2,30, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/0,
					/*max_velocity*/15,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/20,
					/*offset_y*/155,
					/*startup*/0,
					/*cooldown*/5,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("KowaiiDesu",3,20, "angle", "70");
		addModifier("KowaiiDesu",3,20, "aim_player", "yes");
		addModifier("KowaiiDesu",3,30, "angle", "-70");
		addModifier("KowaiiDesu",3,30, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/0,
					/*max_velocity*/15,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/20,
					/*offset_y*/155,
					/*startup*/0,
					/*cooldown*/5,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("KowaiiDesu",4,20, "angle", "-110");
		addModifier("KowaiiDesu",4,20, "aim_player", "yes");
		addModifier("KowaiiDesu",4,30, "angle", "110");
		addModifier("KowaiiDesu",4,30, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/0,
					/*max_velocity*/15,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/20,
					/*offset_y*/155,
					/*startup*/0,
					/*cooldown*/5,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("KowaiiDesu",5,20, "angle", "110");
		addModifier("KowaiiDesu",5,20, "aim_player", "yes");
		addModifier("KowaiiDesu",5,30, "angle", "-110");
		addModifier("KowaiiDesu",5,30, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/0,
					/*max_velocity*/15,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/20,
					/*offset_y*/155,
					/*startup*/0,
					/*cooldown*/5,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("KowaiiDesu",6,20, "angle", "-150");
		addModifier("KowaiiDesu",6,20, "aim_player", "yes");
		addModifier("KowaiiDesu",6,30, "angle", "150");
		addModifier("KowaiiDesu",6,30, "aim_player", "yes");

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/0,
					/*max_velocity*/15,
					/*acceleration*/1,
					/*a_frequency*/2,
					/*angle*/180,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Eye Lazor",
					/*offset_x*/20,
					/*offset_y*/155,
					/*startup*/0,
					/*cooldown*/5,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);
		addModifier("KowaiiDesu",7,20, "angle", "150");
		addModifier("KowaiiDesu",7,20, "aim_player", "yes");
		addModifier("KowaiiDesu",7,30, "angle", "-150");
		addModifier("KowaiiDesu",7,30, "aim_player", "yes");

///
///Set 2
///

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/-50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);


///
///Set 3
///

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/10,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/-4,
					/*stop_ac_at*/-1,
					/*ac_frequency*/3,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/0,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/360,
					/*aim_player*/false,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

///
///Set 5
///

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/5,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/10,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

		addPattern(sonido,painter,receiver,
					/*name*/"KowaiiDesu",
					/*velocity*/2,
					/*max_velocity*/5,
					/*acceleration*/1,
					/*a_frequency*/10,
					/*angle*/0,
					/*angle_change*/0,
					/*stop_ac_at*/-1,
					/*ac_frequency*/0,
					/*animation_velocity*/5,
					/*bullet*/"Rocket",
					/*offset_x*/50,
					/*offset_y*/184,
					/*startup*/20,
					/*cooldown*/80,
					/*duration*/-1,
					/*random_angle*/0,
					/*aim_player*/true,
					/*bullet_rotation*/0,
					/*br_change*/0,
					/*independent_br*/false);

/*

		addPattern(sonido,painter,receiver,"Crazy eyes",4,30,0,10,0,0,99999,0,2,
		"Eye Lazor",80,18,25,4,99999,0,false,0,0,false);
		addModifier("Crazy eyes",0,20, "angle", "0");
		addModifier("Crazy eyes",0,20, "aim_player", "yes");

		addPattern(sonido,painter,receiver,"Crazy eyes",4,30,0,10,0,0,99999,0,2,
		"Eye Lazor",80,18,25,4,99999,0,false,0,0,false);
		addModifier("Crazy eyes",1,20, "angle", "10");
		addModifier("Crazy eyes",1,20, "aim_player", "yes");

//		addPattern(sonido,painter,receiver,"Crazy eyes",4,30,0,10,0,0,99999,0,2,
//		"Eye Lazor",80,18,25,4,99999,0,false,0,0,false);

		//addPattern(sonido,painter,receiver,"InitialD",4,30,0,10,0,0,99999,0,2,
		//"Feminist Laser startup",80,18,25,4,99999,0,false,0,0,false,pattern_modifiers);
*/
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

/*
    if(receiver->IsKeyDownn(SDLK_h))
    {
        painter->drawRectangle(this->getHitbox().getX(),
                               this->getHitbox().getY(),
                               hitbox.getWidth(),hitbox.getHeight(),
                               hitbox.getAngle(),100,0,0,100,true);
    }
*/
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
