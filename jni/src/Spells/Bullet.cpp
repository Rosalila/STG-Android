#include "Bullet.h"

Bullet::Bullet(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name,vector<Image*>sprites,vector<Image*>sprites_on_hit,vector<Hitbox*> hitboxes,int damage)
{
    this->sonido=sonido;
    this->painter=painter;
    this->receiver=receiver;
    this->sprites=sprites;
    this->sprites_on_hit=sprites_on_hit;
    this->hitboxes=hitboxes;
    this->damage=damage;
    this->name=name;
}

void Bullet::logic()
{
}

void Bullet::render()
{

}

Image* Bullet::getImage(int position)
{
    if(position>=(int)sprites.size())
        return NULL;
    return sprites[position];
}

Image* Bullet::getOnHitImage(int position)
{
    if(position>=(int)sprites_on_hit.size())
        return NULL;
    return sprites_on_hit[position];
}

int Bullet::spritesSize()
{
    return sprites.size();
}

int Bullet::spritesOnHitSize()
{
    return sprites_on_hit.size();
}

vector<Hitbox*> Bullet::getHitboxes()
{
    return hitboxes;
}

int Bullet::getDamage()
{
    return damage;
}

string Bullet::getName()
{
    return name;
}

void Bullet::playSound()
{
    if(sonido->soundExists("bullet."+name))
    {
        sonido->playSound("bullet."+name);
    }
}

void Bullet::playHitSound()
{
    if(sonido->soundExists("bullet_hit."+name))
    {
        sonido->playSound("bullet_hit."+name);
    }
}

Bullet::~Bullet()
{
	for(;!sprites.empty();)
	{
	    Image*image=sprites.back();
	    sprites.pop_back();
	    delete image;
	}

	for(;!sprites_on_hit.empty();)
	{
	    Image*image=sprites_on_hit.back();
	    sprites_on_hit.pop_back();
	    delete image;
	}

	for(;!hitboxes.empty();)
	{
	    Hitbox*hitbox=hitboxes.back();
	    hitboxes.pop_back();
	    delete hitbox;
	}
}
