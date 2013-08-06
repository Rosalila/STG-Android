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
    this->animation_velocity=5;

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
	    this->velocity=5;

		this->max_hp=100;
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

		this->x=950;
		this->y=500;

		this->max_hp=6500;
		this->hp=this->max_hp;

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

void Character::addPattern(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name,int velocity,int max_velocity,int acceleration,int a_frequency,float angle,int angle_change,int stop_ac_at,int ac_frequency,int animation_velocity,std::string bullet,int offset_x,int offset_y,int startup,int cooldown,int duration,int random_angle,bool aim_player,float bullet_rotation, float br_change, bool independent_br, std::map<int, vector<Modifier*>* >*modifiers)
{

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
bullet_rotation,br_change,independent_br,modifiers,&bullets));

}

void Character::loadPatternsXML()
{
	if(directory=="chars/Iguro/")
	{
		std::map<int, vector<Modifier*>* >*pattern_modifiers=new std::map<int, vector<Modifier*>* >();

		addPattern(sonido,painter,receiver,"1",0,99999,10,1,0,0,99999,0,2,
		"lazor",120,-17,4,22,99999,0,false,0,0,false,pattern_modifiers);

		addPattern(sonido,painter,receiver,"1",20,80,1,2,0,0,99999,0,2,
		"machinegun",80,25,25,4,99999,0,false,0,0,false,pattern_modifiers);

		addPattern(sonido,painter,receiver,"1",10,50,2,2,0,0,99999,0,2,
		"machinegun",80,18,25,4,99999,0,false,0,0,false,pattern_modifiers);
	}else
	{
		std::map<int, vector<Modifier*>* >*pattern_modifiers=new std::map<int, vector<Modifier*>* >();

		addPattern(sonido,painter,receiver,"Crazy eyes",4,30,0,10,0,0,99999,0,2,
		"Eye Lazor",80,18,25,4,99999,0,false,0,0,false,pattern_modifiers);

		//addPattern(sonido,painter,receiver,"InitialD",4,30,0,10,0,0,99999,0,2,
		//"Feminist Laser startup",80,18,25,4,99999,0,false,0,0,false,pattern_modifiers);
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
