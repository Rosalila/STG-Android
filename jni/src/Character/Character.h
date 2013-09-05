#ifndef CHARACTER_H
#define CHARACTER_H

#include <map>
#include <list>
#include <vector>

#include "TinyXml/tinyxml.h"
#include "RosalilaGraphics/RosalilaGraphics.h"
#include "RosalilaSound/RosalilaSound.h"
#include "RosalilaInputs/RosalilaInputs.h"
#include "../Spells/Bullet.h"
#include "../Spells/Pattern.h"
#include "RosalilaUtility/RosalilaUtility.h"
#include "Modifier.h"
#include "RosalilaNetwork/RosalilaNetwork.h"
#include <jni.h>

class Character
{
protected:
    Sound* sonido;
    RosalilaGraphics* painter;
    Receiver* receiver;

    std::string name;
    std::string directory;
    int hp;
    int max_hp;
    int iteration;
    bool visible;

    int velocity;
    Hitbox hitbox;
    bool shooting;
    std::string orientation;
    std::string current_type;

    //Life bar variables
    int current_slow;
    int max_slow;
    int life_bar_x;
    int life_bar_y;
    int life_bar_rect_offset_x;
    int life_bar_rect_offset_y;
    int life_bar_rect_height;
    int life_bar_rect_width;
    Color color;

    //Sprites animation
    int animation_velocity;
    int animation_iteration;
    int current_sprite;
    std::map< std::string,std::vector<Image*> >sprites;

    //Patterns and bullets
    std::map<std::string,Bullet*> bullets;
    std::map<std::string, std::vector<Pattern*> > type;
    std::list<Pattern*>* active_patterns;

public:

double x,y;
    Character(){}
    Character(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name);
	void addBullet(Sound* sonido,RosalilaGraphics* painter,Receiver*receiver, std::string name,int sprites_amount,
int hitbox_x,int hitbox_y,int hitbox_w,int hitbox_h,int hitbox_angle,
int damage);

    void addPattern(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name,int velocity,int max_velocity,int acceleration,int a_frequency,float angle,int angle_change,int stop_ac_at,int ac_frequency,int animation_velocity,std::string bullet,int offset_x,int offset_y,int startup,int cooldown,int duration,int random_angle,bool aim_player,float bullet_rotation, float br_change, bool independent_br);

	void addModifier(string type,int pattern_pos,int at, string variable, string value);

    void loadFromXML();
    void loadMainXML();
    void loadBulletsXML();
    void loadPatternsXML();
    void logic(int stage_velocity);
    //logic sub functions
    void animationControl();
    void spellControl(int stage_velocity);
    virtual void addActivePattern(Pattern* pattern);

    void parrentRender();
	void renderPatterns();
    void render();
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    int getHP();
    int getIteration();
    Hitbox getHitbox();
    void setType(std::string type);
    std::list<Pattern*>* getActivePatterns();
    bool collides(Hitbox hitbox,int hitbox_x,int hitbox_y,float hitbox_angle);
    void hit(int damage);
	~Character();
};

#endif
