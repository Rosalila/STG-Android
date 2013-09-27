//#include "SDL_image.h"
#include <stdlib.h>
 
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
/*
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
*/

class Image
{
public:
    GLuint texture;
	SDL_Surface *surface;
	SDL_Texture *sdl_texture;
    int width;
    int height;

    Image();
    ~Image();
    int getWidth();
    int getHeight();
    GLuint getTexture();
    void setTexture(GLuint texture);
	void setSdlTexture(SDL_Texture *sdl_texture);
    void setWidth(int width);
    void setHeight(int height);
};
