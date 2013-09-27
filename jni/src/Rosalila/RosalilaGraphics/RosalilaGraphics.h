#ifndef GRAFICO_H
#define GRAFICO_H

/*


#include <iostream>
#include <list>
#include "SDL_image.h"
//#include "SDL/SDL_ttf.h"
#include "TinyXml/tinyxml.h"





//
#include <stdlib.h>

#include <iostream>
#include <fstream>

*/
#include <android/log.h>
//#include "RosalilaGraphics/smpeg.h"
#include "RosalilaGraphics/Image.h"
#include "RosalilaGraphics/Timer.h"
//#include "RosalilaGraphics/Explosion.h"
//#include "RosalilaGraphics/Explosion2.h"
//#include "RosalilaGraphics/Cube.h"
//#include "RosalilaGraphics/Object3D.h"
#include "RosalilaUtility/RosalilaUtility.h"
#include "STGUtility/STGUtility.h"
using namespace std;
 
#define WINDOW_W 1920
#define WINDOW_H 1080
 
#ifdef __ANDROID__
    #include <android/log.h>
        #include <GLES/gl.h>
        #define DIR_SEP "/"
        #define DIR_CUR "/sdcard/"
        #define glOrtho(a,b,c,d,e,f) glOrthof(a,b,c,d,e,f) ///FIXME
#else
        #include <stdio.h>
        #include <GL/gl.h>
        #include <GL/glu.h>
        #define DIR_CUR ""
        #define DIR_SEP "/"
#endif
 
#define PATH(filename) DIR_CUR "data" DIR_SEP filename
#define ISPWR2(n) !(n&(n-1))
 
#include "SDL.h"
#include "SDL_image.h"
//
typedef float vector4[4];


class Color
{
public:
    int red;
    int green;
    int blue;
    int alpha;

    Color()
    {
        this->red=0;
        this->green=0;
        this->blue=0;
        this->alpha=255;
    }

    Color(int red,int green,int blue,int alpha)
    {
        this->red=red;
        this->green=green;
        this->blue=blue;
        this->alpha=alpha;
    }

    int getRed()
    {
        return red;
    }

    int getGreen()
    {
        return green;
    }

    int getBlue()
    {
        return blue;
    }

    int getAlpha()
    {
        return alpha;
    }
};

class RosalilaGraphics
{
    public:
    SDL_Window *window;
    SDL_Renderer *renderer;
	SDL_GLContext context;

int iterations;

    SDL_Surface* screen;
    //TTF_Font* font;
    SDL_Color textColor;
    int screen_width;
    int screen_height;
    bool fullscreen;
    int screen_bpp;
    int camera_x,camera_y;
    SDL_Joystick *joystick_1;
    SDL_Joystick *joystick_2;

    //Set fps
    int frames_per_seccond;
    int frame;
    Timer *fps;
    Timer *update;

	//effects
	int transparency_effect;

    //3D
//    list<Explosion*> explosions;
//    list<Explosion2*> explosions2;
//    Cube cube;

    RosalilaGraphics();
    ~RosalilaGraphics();
    Image* getTexture(std::string filename);
    void draw2DImage(
	             Image* texture,
				 int size_x,int size_y,
				 int position_x,int position_y,
				 float scale,
				 float rotation,
				 bool flipHorizontally,
				 int depth_effect_x,
				 int depth_effect_y,
				 Color color_effects,
				 bool camera_align);

    void draw2DImage(
	             Image* texture,
				 int size_x,int size_y,
				 int position_x,int position_y,
				 float scale,
				 float rotation,
				 bool flipHorizontally,
				 int depth_effect_x,
				 int depth_effect_y,
				 Color color_effects,
				 bool camera_align,
				 bool allow_alpha);

    void draw2DImageBatch(
	             Image* texture,
				 int size_x,int size_y,
				 vector<int> position_x,vector<int> position_y,
				 float scale,
				 vector<float> rotation,
				 bool flipHorizontally,
				 int depth_effect_x,
				 int depth_effect_y,
				 Color color_effects,
				 bool camera_align);

    void drawText(std::string text,int position_x,int position_y);
    void drawRectangle(int x,int y,int width,int height,float rotation,int red,int green,int blue,int alpha,bool camera_align);
    void draw3D();
    void draw3DCube(int x,int y,float size,Color color);
    void explode(float pos_x,float pos_y);
    void addExplosion(int x,int y);
    void drawObject();
    void updateScreen();
    void frameCap();
    void resetScreen();
    void video(RosalilaGraphics*painter);
    void resetFpsCount();
};
#endif
