#ifndef EXPLOSION2_H
#define EXPLOSION2_H

//#include "SDL/SDL_image.h"

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>

#define NUM_PARTICLES    50          /* Number of particles  */
#define NUM_DEBRIS       50            /* Number of debris     */

/* GLUT menu entries */

#define PAUSE              0
#define NORMALIZE_SPEED    1
#define QUIT               2

class Explosion2
{
public:
    /* A particle */

    typedef struct
    {
    //The X position
    double Xpos;
    //The Y position
    double Ypos;
    //The Z position
    double Zpos;
    //The movement on the X axis while being displayed
    double Xmov;
    //The movement on the Z axis while being displayed
    double Zmov;
    //The amount of Red within the object
    double Red;
    //The amount of Green within the object
    double Green;
    //The amount of Blue within the object
    double Blue;
    //The angle of rotation
    double Direction;
    //How fast it accelerates upwards
    double Acceleration;
    //How fast it decelerates downwards
    double Deceleration;
    //How much we wish to scale it
    double Scalez;
    }PARTICLES;

    struct particleData
    {
      float   position[3];
      float   speed[3];
      float   color[3];
    };
    typedef struct particleData    particleData;


    /* A piece of debris */

    struct debrisData
    {
      float   position[3];
      float   speed[3];
      float   orientation[3];        /* Rotation angles around x, y, and z axes */
      float   orientationSpeed[3];
      float   color[3];
      float   scale[3];
    };
    typedef struct debrisData    debrisData;


    /* Globals */

    int iteration;
    int duration;

    float pos_x;
    float pos_y;

    PARTICLES        Particle[NUM_PARTICLES];
    particleData     particles[NUM_PARTICLES];
    debrisData       debris[NUM_DEBRIS];
    int fuel;                /* "fuel" of the explosion */

    float angle;             /* camera rotation angle */

    int wantNormalize;   /* Speed vector normalization flag */
    int wantPause;       /* Pause flag */


    /* Light sources and material */

    GLfloat  light0Amb[4];
    GLfloat  light0Dif[4];
    GLfloat  light0Spec[4];
    GLfloat  light0Pos[4];

    GLfloat  light1Amb[4];
    GLfloat  light1Dif[4];
    GLfloat  light1Spec[4];
    GLfloat  light1Pos[4];

    GLfloat  materialAmb[4];
    GLfloat  materialDif[4];
    GLfloat  materialSpec[4];
    GLfloat  materialShininess;

    Explosion2(int x,int y);

    void render(int screen_width, int screen_height);

    void setMaterialColor(float r,float g,float b,float a);

//    GLfloat  light0Amb[4] =  { 1.0, 0.6, 0.2, 1.0 };
//    GLfloat  light0Dif[4] =  { 1.0, 0.6, 0.2, 1.0 };
//    GLfloat  light0Spec[4] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat  light0Pos[4] =  { 0.0, 0.0, 0.0, 1.0 };
//
//    GLfloat  light1Amb[4] =  { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat  light1Dif[4] =  { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat  light1Spec[4] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat  light1Pos[4] =  { 0.0, 5.0, 5.0, 0.0 };
//
//    GLfloat  materialAmb[4] = { 0.25, 0.22, 0.26, 1.0 };
//    GLfloat  materialDif[4] = { 0.63, 0.57, 0.60, 1.0 };
//    GLfloat  materialSpec[4] = { 0.99, 0.91, 0.81, 1.0 };
//    GLfloat  materialShininess = 27.8;

    void logic();
    void newExplosion (float pos_x,float pos_y);
    void newSpeed (float dest[3]);
};

#endif
