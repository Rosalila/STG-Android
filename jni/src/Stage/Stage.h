#ifndef STAGE_H
#define STAGE_H

#include "TinyXml/tinyxml.h"
#include "RosalilaGraphics/RosalilaGraphics.h"
#include "RosalilaSound/RosalilaSound.h"
#include "../Character/Character.h"
#include "Layer.h"
#include "Dialogue.h"
#include "../STGUtility/STGUtility.h"
#include <map>

class Stage
{
private:
    std::vector<Layer*> back,front;
    std::map<int,Dialogue*>dialogues;
    std::list<Dialogue*>active_dialogues;
    std::string music_path;
    RosalilaGraphics* painter;
    Sound* sonido;
    Receiver*receiver;
    int dialogue_x;
    int dialogue_y;
    int dialogue_padding_x;
    int dialogue_padding_y;
    Image* dialogue_bg;
    int bound_x1,bound_y1,bound_x2,bound_y2;
    int velocity;
    int iterator;
    string name;

    //slow extra control
    bool iterate_slowdown_flag;
    int current_slowdown_iteration;

public:
    Stage(RosalilaGraphics* painter,Sound* sonido,Receiver*receiver);
	void addLayer(string layer_name,int sprite_amount,int frame_duration,int depth_effect_x,int depth_effect_y,int alignment_x,int alignment_y,int separation_x);
	void addLayer(string layer_name,int sprite_amount,int frame_duration,int depth_effect_x,int depth_effect_y,int alignment_x,int alignment_y,int separation_x,int width,int height);
    void dibujarBack();
    void dibujarFront();
    void drawLayer(Layer*layer);
    void loadFromXML(std::string name);
    void loadDialogues(std::string file);
    int getBoundX1();
    int getBoundY1();
    int getBoundX2();
    int getBoundY2();
    int getVelocity();
    string getName();
    void logic();
    void render();
    void setVelocity(int velocity);
    void playMusic();
    ~Stage();
};

#endif
