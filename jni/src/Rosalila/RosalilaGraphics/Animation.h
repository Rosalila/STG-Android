//#include "SDL/SDL_image.h"

/*
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
*/

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

#include "TinyXml/tinyxml.h"
#include "RosalilaGraphics/RosalilaGraphics.h"
#include "RosalilaSound/RosalilaSound.h"
#include "RosalilaInputs/RosalilaInputs.h"

class Animation
{
    RosalilaGraphics*painter;

    std::vector <Image*> images;
    int x,y;
    int animation_velocity;
    int animation_iteration;
    int current_frame;
public:
    Animation(){}
    Animation(int x,int y,int animation_velocity,RosalilaGraphics* painter);
    void addImage(Image*image);
    void render();
};
