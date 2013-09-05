#include "Player.h"

Player::Player(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name)
{
    //Setting up the other variables
    this->name=name;
    this->directory="chars/"+name+"/";
    this->sonido=sonido;
    this->painter=painter;
    this->receiver=receiver;
    this->active_patterns=new std::list<Pattern*>;
    this->shooting=true;
    this->orientation="idle";
    this->current_type="o";
    this->visible=true;

    //Sprites animation
    this->animation_velocity=4;
    this->animation_iteration=0;
    this->current_sprite=0;

    this->iteration=0;

    this->slow_in_cooldown=false;

    life_bar=painter->getTexture(directory+"life_bar.png");

    hitbox_sprites.push_back(painter->getTexture(directory+"sprites/hitbox/1.png"));
    hitbox_sprites.push_back(painter->getTexture(directory+"sprites/hitbox/2.png"));
    hitbox_sprites.push_back(painter->getTexture(directory+"sprites/hitbox/3.png"));
    hitbox_sprites.push_back(painter->getTexture(directory+"sprites/hitbox/4.png"));
	current_hitbox_sprite=0;

    loadPlayerFromXML();

	shadow_x.push_back(this->x);
	shadow_y.push_back(this->y);
	shadow_x.push_back(this->x);
	shadow_y.push_back(this->y);
	shadow_x.push_back(this->x);
	shadow_y.push_back(this->y);
	shadow_x.push_back(this->x);
	shadow_y.push_back(this->y);


	shadow_orientation.push_back(this->orientation);
	shadow_orientation.push_back(this->orientation);
	shadow_orientation.push_back(this->orientation);
	shadow_orientation.push_back(this->orientation);

	shadow_current_sprite.push_back(this->current_sprite);
	shadow_current_sprite.push_back(this->current_sprite);
	shadow_current_sprite.push_back(this->current_sprite);
	shadow_current_sprite.push_back(this->current_sprite);

	shadow_effect_green.push_back(false);
	shadow_effect_green.push_back(false);
	shadow_effect_green.push_back(false);
	shadow_effect_green.push_back(false);

	shadow_effect_red.push_back(false);
	shadow_effect_red.push_back(false);
	shadow_effect_red.push_back(false);
	shadow_effect_red.push_back(false);
}

void Player::loadPlayerFromXML()
{
    loadFromXML();


    this->current_slow=750;
    this->max_slow=750;

    this->slow_decrement=3;


    this->slow_increment=1;


    this->slow_cooldown_increment=2;

    this->slow_bar_x=85;
    this->slow_bar_y=77;
    this->slow_bar_rect_offset_x=0;
    this->slow_bar_rect_offset_y=0;
    this->slow_bar_rect_width=186;
    this->slow_bar_rect_height=5;
    this->slow_bar_color.red=0;
    this->slow_bar_color.green=64;
    this->slow_bar_color.blue=128;
    this->slow_bar_color.alpha=255;
    this->slow_bar_cooldown_color.red=50;
    this->slow_bar_cooldown_color.green=50;
    this->slow_bar_cooldown_color.blue=50;
    this->slow_bar_cooldown_color.alpha=255;

}

void Player::inputControl()
{
    if(receiver->IsKeyDownn(SDLK_DOWN)
       || receiver->IsJoyDown(-2,0)
	   || receiver->isOuyaDown(2))
    {
        if(orientation!="down" && this->sonido->soundExists(name+".down"))
            this->sonido->playSound(name+".down");
        orientation="down";
    }
    else if(receiver->IsKeyDownn(SDLK_UP)
       || receiver->IsJoyDown(-8,0)
	   || receiver->isOuyaDown(8))
    {
        if(orientation!="up" && this->sonido->soundExists(name+".up"))
            this->sonido->playSound(name+".up");
        orientation="up";
    }
    else if(receiver->IsKeyDownn(SDLK_LEFT)
       || receiver->IsJoyDown(-4,0)
	   || receiver->isOuyaDown(4))
    {
        if(orientation!="left" && this->sonido->soundExists(name+".left"))
            this->sonido->playSound(name+".left");
        orientation="left";
    }
    else if(receiver->IsKeyDownn(SDLK_RIGHT)
       || receiver->IsJoyDown(-6,0)
	   || receiver->isOuyaDown(6))
    {
        if(orientation!="right" && this->sonido->soundExists(name+".right"))
            this->sonido->playSound(name+".right");
        orientation="right";
    }
    else
    {
        if(orientation!="idle" && this->sonido->soundExists(name+".idle"))
            this->sonido->playSound(name+".idle");
        orientation="idle";
    }

    if((receiver->IsKeyDownn(SDLK_DOWN) && receiver->IsKeyDownn(SDLK_LEFT))
       || (receiver->IsJoyDown(-2,0) && receiver->IsJoyDown(-4,0))
	   || (receiver->isOuyaDown(2) && receiver->isOuyaDown(4)))
    {
		double delta = sqrt(pow(velocity/getSlowdown(),2)/2);
		if(receiver->isOuyaDown('l'))
			delta/=2;
		if(receiver->isOuyaDown('r'))
			delta*=2;
        this->y+=delta;
        this->x-=delta;
	}else if((receiver->IsKeyDownn(SDLK_DOWN) && receiver->IsKeyDownn(SDLK_RIGHT))
       || (receiver->IsJoyDown(-2,0) && receiver->IsJoyDown(-6,0))
	   || (receiver->isOuyaDown(2) && receiver->isOuyaDown(6)))
    {
		double delta = sqrt(pow(velocity/getSlowdown(),2)/2);
		if(receiver->isOuyaDown('l'))
			delta/=2;
		if(receiver->isOuyaDown('r'))
			delta*=2;
        this->y+=delta;
        this->x+=delta;
	}else if((receiver->IsKeyDownn(SDLK_UP) && receiver->IsKeyDownn(SDLK_LEFT))
       || (receiver->IsJoyDown(-8,0) && receiver->IsJoyDown(-4,0))
	   || (receiver->isOuyaDown(8) && receiver->isOuyaDown(4)))
    {
		double delta = sqrt(pow(velocity/getSlowdown(),2)/2);
		if(receiver->isOuyaDown('l'))
			delta/=2;
		if(receiver->isOuyaDown('r'))
			delta*=2;
        this->y-=delta;
        this->x-=delta;
	}else if((receiver->IsKeyDownn(SDLK_UP) && receiver->IsKeyDownn(SDLK_RIGHT))
       || (receiver->IsJoyDown(-8,0) && receiver->IsJoyDown(-6,0))
	   || (receiver->isOuyaDown(8) && receiver->isOuyaDown(6)))
    {
		double delta = sqrt(pow(velocity/getSlowdown(),2)/2);
		if(receiver->isOuyaDown('l'))
			delta/=2;
		if(receiver->isOuyaDown('r'))
			delta*=2;
        this->y-=delta;
        this->x+=delta;
	}else
    if(receiver->IsKeyDownn(SDLK_DOWN)
       || receiver->IsJoyDown(-2,0)
	   || receiver->isOuyaDown(2))
    {
		double delta = velocity/getSlowdown();
		if(receiver->isOuyaDown('l'))
			delta/=2;
		if(receiver->isOuyaDown('r'))
			delta*=2;
        this->y+=delta;
    }else
    if(receiver->IsKeyDownn(SDLK_UP)
       || receiver->IsJoyDown(-8,0)
	   || receiver->isOuyaDown(8))
    {
		double delta = velocity/getSlowdown();
		if(receiver->isOuyaDown('l'))
			delta/=2;
		if(receiver->isOuyaDown('r'))
			delta*=2;
        this->y-=delta;
    }else
    if(receiver->IsKeyDownn(SDLK_LEFT)
       || receiver->IsJoyDown(-4,0)
	   || receiver->isOuyaDown(4))
    {
		double delta = velocity/getSlowdown();
		if(receiver->isOuyaDown('l'))
			delta/=2;
		if(receiver->isOuyaDown('r'))
			delta*=2;
        this->x-=delta;
    }else
    if(receiver->IsKeyDownn(SDLK_RIGHT)
       || receiver->IsJoyDown(-6,0)
	   || receiver->isOuyaDown(6))
    {
		double delta = velocity/getSlowdown();
		if(receiver->isOuyaDown('l'))
			delta/=2;
		if(receiver->isOuyaDown('r'))
			delta*=2;
       this->x+=delta;
    }

    if(receiver->IsKeyDownn(SDLK_z)
		|| receiver->IsJoyDown(0,0)
		|| receiver->isOuyaDown('o')
		|| receiver->isOuyaDown('u')
		|| receiver->isOuyaDown('y')
		|| receiver->isOuyaDown('a'))
    {
        this->shooting=true;
    }
    else
    {
        this->shooting=false;
    }
}

void Player::logic(int stage_velocity)
{
    animationControl();

	if(receiver->isOuyaDown('o'))
		current_type="o";
	if(receiver->isOuyaDown('u'))
		current_type="u";
	if(receiver->isOuyaDown('y'))
		current_type="y";
	if(receiver->isOuyaDown('a'))
		current_type="a";

    if(this->hp!=0)
    {
        inputControl();
    }else
    {
        if(orientation!="destroyed" && this->sonido->soundExists(name+".destroyed"))
            this->sonido->playSound(name+".destroyed");
        orientation="destroyed";
        this->hitbox.setValues(0,0,0,0,0);
    }



    //Enable or disable slow
    if(isSlowPressed() && !slow_in_cooldown)
    {
        enableSlow();
        current_slow-=slow_decrement;
		if(receiver->isOuyaDown('x') && receiver->isOuyaDown('z'))//double
			current_slow-=slow_decrement;
    }else
    {
        disableSlow();
        if(slow_in_cooldown)
            current_slow+=slow_cooldown_increment;
        else
            current_slow+=slow_increment;
    }

    //Check max and min slow
    if(current_slow<=0)
    {
        current_slow=0;
    }
    if(current_slow>max_slow)
    {
        current_slow=max_slow;
    }

    //Slow cooldown
    if(slow_in_cooldown && current_slow>=max_slow)
    {
        slow_in_cooldown=false;
    }
    if(!slow_in_cooldown && current_slow<=0)
    {
        slow_in_cooldown=true;
    }

    spellControl(stage_velocity);

	this->setX(this->getX()+stage_velocity);

	//shadow control
	if(iteration%1==0)
	{
		for(int i=shadow_x.size()-1;i>=1;i--)
		{
			shadow_x[i]=shadow_x[i-1];
			shadow_y[i]=shadow_y[i-1];

			shadow_orientation[i]=shadow_orientation[i-1];
			shadow_current_sprite[i]=shadow_current_sprite[i-1];
			shadow_effect_green[i]=shadow_effect_green[i-1];
			shadow_effect_red[i]=shadow_effect_red[i-1];
		}

		shadow_x[0]=this->x-painter->camera_x;
		shadow_y[0]=this->y;

		shadow_orientation[0]=this->orientation;
		shadow_current_sprite[0]=this->current_sprite;
		shadow_effect_green[0]=receiver->isOuyaDown('l');
		shadow_effect_red[0]=receiver->isOuyaDown('r');
	}

    iteration++;
}

void Player::render()
{

for(int i=1;i<shadow_x.size();i++)
{
	int shadow_x_int=shadow_x[i];
	int shadow_y_int=shadow_y[i];

	int effect_red=0;
	int effect_green=0;

	if(shadow_effect_red[i])
		effect_red=128;

	if(shadow_effect_green[i])
		effect_green=128;

    painter->draw2DImage
    (   sprites[shadow_orientation[0]][shadow_current_sprite[0]],
        sprites[shadow_orientation[0]][shadow_current_sprite[0]]->getWidth(),sprites[shadow_orientation[0]][shadow_current_sprite[0]]->getHeight(),
        shadow_x_int-sprites[shadow_orientation[0]][shadow_current_sprite[0]]->getWidth()/2,shadow_y_int-sprites[shadow_orientation[0]][shadow_current_sprite[0]]->getHeight()/2,
        1.0,
        0.0,
        false,
        0,0,
        Color(effect_red,effect_green,128,255/(i+1)),
        false);
}

    parrentRender();

        painter->draw2DImage
        (   hitbox_sprites[current_hitbox_sprite],
        		hitbox_sprites[current_hitbox_sprite]->getWidth(),hitbox_sprites[current_hitbox_sprite]->getHeight(),
        		this->x-hitbox_sprites[current_hitbox_sprite]->getWidth()/2,this->y-hitbox_sprites[current_hitbox_sprite]->getHeight()/2,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            true);

        if(this->iteration%2==0)
        	current_hitbox_sprite++;
        if(current_hitbox_sprite>=hitbox_sprites.size())
        	current_hitbox_sprite=0;
/*
    if(isSlowActive())
    {
        painter->draw3DCube(this->getHitbox().getX(),this->getHitbox().getY(),2.0,Color(255,0,0,180));
    }else
    {
        painter->draw3DCube(this->getHitbox().getX(),this->getHitbox().getY(),2.0,Color(255,0,0,100));
    }

//    if(shooting)
//    {
//        if(iteration%10==0)
//            painter->addExplosion(this->x,this->y);
//    }
    painter->draw3D();
*/
}
void Player::renderHUD()
{
    //HP
    painter->drawRectangle(life_bar_x+life_bar_rect_offset_x,life_bar_y+life_bar_rect_offset_y,(life_bar_rect_width*hp)/max_hp,life_bar_rect_height,0,this->color.getRed(),this->color.getGreen(),this->color.getBlue(),this->color.getAlpha(),false);
    if(!slow_in_cooldown)
        painter->drawRectangle(slow_bar_x+slow_bar_rect_offset_x,slow_bar_y+slow_bar_rect_offset_y,(slow_bar_rect_width*current_slow)/max_slow,slow_bar_rect_height,0,this->slow_bar_color.getRed(),this->slow_bar_color.getGreen(),this->slow_bar_color.getBlue(),this->slow_bar_color.getAlpha(),false);
    else
        painter->drawRectangle(slow_bar_x+slow_bar_rect_offset_x,slow_bar_y+slow_bar_rect_offset_y,(slow_bar_rect_width*current_slow)/max_slow,slow_bar_rect_height,0,this->slow_bar_cooldown_color.getRed(),this->slow_bar_cooldown_color.getGreen(),this->slow_bar_cooldown_color.getBlue(),this->slow_bar_cooldown_color.getAlpha(),false);

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
}
