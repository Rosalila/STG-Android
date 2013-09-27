#include "RosalilaGraphics/Explosion2.h"

Explosion2::Explosion2(int x, int y)
{
    iteration=0;
    duration=100;
    pos_x=0;
    pos_y=0;

    fuel = 0;                /* "fuel" of the explosion */

    angle = 0.0;             /* camera rotation angle */

    wantNormalize = 0;   /* Speed vector normalization flag */
    wantPause = 0;       /* Pause flag */


    /* Light sources and material */
//
    light0Amb[0]=1.0;
    light0Amb[1]=1.0;
    light0Amb[2]=1.0;
    light0Amb[3]=1.0;

    light0Dif[0]=1.0;
    light0Dif[1]=1.0;
    light0Dif[2]=1.0;
    light0Dif[3]=1.0;

    light0Spec[0]=1.0;
    light0Spec[1]=1.0;
    light0Spec[2]=1.0;
    light0Spec[3]=1.0;

    light0Pos[0]=1.0;
    light0Pos[1]=1.0;
    light0Pos[2]=1.0;
    light0Pos[3]=1.0;

    light1Amb[0]=1.0;
    light1Amb[1]=1.0;
    light1Amb[2]=1.0;
    light1Amb[3]=1.0;

    light1Dif[0]=1.0;
    light1Dif[1]=0.0;
    light1Dif[2]=0.0;
    light1Dif[3]=1.0;

    light1Spec[0]=1.0;
    light1Spec[1]=1.0;
    light1Spec[2]=1.0;
    light1Spec[3]=1.0;

    light1Pos[0]=0.0;
    light1Pos[1]=5.0;
    light1Pos[2]=5.0;
    light1Pos[3]=0.0;

    materialAmb[0]=255.0/255.0;
    materialAmb[1]=0.0/255.0;
    materialAmb[2]=0.0/255.0;
    materialAmb[3]=128.0/255.0;

    materialDif[0]=255.0/255.0;
    materialDif[1]=0.0/255.0;
    materialDif[2]=0.0/255.0;
    materialDif[3]=128.0/255.0;

    materialSpec[0]=255.0/255.0;
    materialSpec[1]=0.0/255.0;
    materialSpec[2]=0.0/255.0;
    materialSpec[3]=128.0/255.0;

    materialShininess = 10.0;

    newExplosion(x,y);
}

void Explosion2::setMaterialColor(float r,float g,float b,float a)
{
    materialAmb[0]=r/255.0;
    materialAmb[1]=g/255.0;
    materialAmb[2]=b/255.0;
    materialAmb[3]=a/255.0;

    materialDif[0]=r/255.0;
    materialDif[1]=g/255.0;
    materialDif[2]=b/255.0;
    materialDif[3]=a/255.0;

    materialSpec[0]=r/255.0;
    materialSpec[1]=g/255.0;
    materialSpec[2]=b/255.0;
    materialSpec[3]=a/255.0;
}

void Explosion2::logic()
{
//        for (int i = 0; i < NUM_PARTICLES; i++)
//        {
//            this->particles[i].position[0] += this->particles[i].speed[0] * 0.2;
//            this->particles[i].position[1] += this->particles[i].speed[1] * 0.2;
//            this->particles[i].position[2] += this->particles[i].speed[2] * 0.2;
//
//            this->particles[i].color[0] -= 1.0 / 500.0;
//            if (this->particles[i].color[0] < 0.0)
//            {
//                this->particles[i].color[0] = 0.0;
//            }
//
//            this->particles[i].color[1] -= 1.0 / 100.0;
//            if (this->particles[i].color[1] < 0.0)
//            {
//                this->particles[i].color[1] = 0.0;
//            }
//
//            this->particles[i].color[2] -= 1.0 / 50.0;
//            if (this->particles[i].color[2] < 0.0)
//            {
//                this->particles[i].color[2] = 0.0;
//            }
//        }
//
//        for (int i = 0; i < NUM_DEBRIS; i++)
//        {
//            this->debris[i].position[0] += this->debris[i].speed[0] * 0.5;
//            this->debris[i].position[1] += this->debris[i].speed[1] * 0.5;
//            this->debris[i].position[2] += this->debris[i].speed[2] * 0.5;
//
//            this->debris[i].orientation[0] += this->debris[i].orientationSpeed[0] * 10;
//            this->debris[i].orientation[1] += this->debris[i].orientationSpeed[1] * 10;
//            this->debris[i].orientation[2] += this->debris[i].orientationSpeed[2] * 10;
//        }
//
//        --this->fuel;
//
//    this->angle += 0.7;  /* Always continue to rotate the camera */

 //    if (this->fuel > 0)
//    {
        for (int i = 0; i < NUM_PARTICLES; i++)
        {
            //Set the color of the current particle
/*
            glColor3f (Particle[i].Red, Particle[i].Green, Particle[i].Blue);
*/

            //Move the particle on the Y axes, adding on the amount of acceleration
            //and then subtracting the rate of deceleration
            Particle[i].Ypos = Particle[i].Ypos + Particle[i].Acceleration - Particle[i].Deceleration;
            //Increase the deceleration rate so the particle falls gaining speed
            Particle[i].Deceleration = Particle[i].Deceleration + 0.001;
            //Move the particle on the X axis
            Particle[i].Xpos = Particle[i].Xpos + Particle[i].Xmov;
            //Move the particle on the Z axis
            Particle[i].Zpos = Particle[i].Zpos + Particle[i].Zmov;

            //Rotate the particle
            Particle[i].Direction = Particle[i].Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1);

//            Now here I am saying that if the particle goes beneath its initial height
//            which I set earlier to -5, then it will restart the particle changing some
//            of the variables.
//            if (Particle[i].Ypos < -15)
//            {
//                //Set the X position
//                Particle[i].Xpos = 10;
//                //Set the Y position
//                Particle[i].Ypos = 10;
//                //Set the Z position
//                Particle[i].Zpos = -50;
//                //Set the amount of Red
//                Particle[i].Red = 1;
//                //Set the amount of Green
//                Particle[i].Green = 200;
//                //Set the amount of Blue
//                Particle[i].Blue = 1;
//                //Set the angle of rotation
//                Particle[i].Direction = 0;
//                //Adjust the Acceleration rate to another random number
//                Particle[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.02;
//                //Reset the Deceleration rate
//                Particle[i].Deceleration = 0.025;
//            }

//            this->particles[i].position[0] += this->particles[i].speed[0] * 0.2;
//            this->particles[i].position[1] += this->particles[i].speed[1] * 0.2;
//            this->particles[i].position[2] += this->particles[i].speed[2] * 0.2;
//
//            this->particles[i].color[0] -= 1.0 / 500.0;
//            if (this->particles[i].color[0] < 0.0)
//            {
//                this->particles[i].color[0] = 0.0;
//            }
//
//            this->particles[i].color[1] -= 1.0 / 100.0;
//            if (this->particles[i].color[1] < 0.0)
//            {
//                this->particles[i].color[1] = 0.0;
//            }
//
//            this->particles[i].color[2] -= 1.0 / 50.0;
//            if (this->particles[i].color[2] < 0.0)
//            {
//                this->particles[i].color[2] = 0.0;
//            }
        }

//        for (int i = 0; i < NUM_DEBRIS; i++)
//        {
//            this->debris[i].position[0] += this->debris[i].speed[0] * 0.5;
//            this->debris[i].position[1] += this->debris[i].speed[1] * 0.5;
//            this->debris[i].position[2] += this->debris[i].speed[2] * 0.5;
//
//            this->debris[i].orientation[0] += this->debris[i].orientationSpeed[0] * 10;
//            this->debris[i].orientation[1] += this->debris[i].orientationSpeed[1] * 10;
//            this->debris[i].orientation[2] += this->debris[i].orientationSpeed[2] * 10;
//        }

//        --this->fuel;
//    }

    this->angle += 0.7;  /* Always continue to rotate the camera */


    iteration++;
}

void Explosion2::newExplosion (float pos_x,float pos_y)
{
    this->pos_x=pos_x;
    this->pos_y=pos_y;
    this->pos_x+=650.0;
    this->pos_y+=400.0;
    //(-((screen_width-pos_x)/2.0)/5.0, ((screen_height-pos_y)/2.0)/5.0, -100.0)
  int    i;

  for (i = 0; i < NUM_PARTICLES; i++)
  {
        //Set the inital X position to 0
        Particle[i].Xpos = -((1366/2-pos_x)/2.0)/5.0;
        //Set the inital Y position to -5
        Particle[i].Ypos = ((768/2-pos_y)/2.0)/5.0;
        //Set the inital Z position to -5
        Particle[i].Zpos = -100;
        //Set the amount of movement on the X axis to a random number, we dont want
        //all our particles doing the same thing
        Particle[i].Xmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
        //Set the amount of movement on the Z axis to a random number, as above, we dont
        //want all our particles doing the same thing
        Particle[i].Zmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
        //Set the amount of Red to 1
        Particle[i].Red = 1;
        //Set the amount of Green to 1
        Particle[i].Green = 200;
        //Set the amount of Blue to 1
        Particle[i].Blue = 1;
        //Scale the particle to 1 quarter of its original size
        Particle[i].Scalez = 0.50;
        //Set the initial rotation angle to 0
        Particle[i].Direction = 0;
        //Set the amount of acceleration to a random number so they climb to different
        //heights
        Particle[i].Acceleration = ((((((8 - 5 + 2) * rand ()%11) + 5) - 1 + 1) * rand ()%11) + 1) * 0.02;
        //Decrease their acceleration by 0.0025. They will slow down at a constant
        //rate but you will not see a difference
        Particle[i].Deceleration = 0.0025;

    }
  fuel = 100;
}

void Explosion2::newSpeed (float dest[3])
{
  float    x;
  float    y;
  float    z;
  float    len;

  x = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  y = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  z = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

  /*
   * Normalizing the speed vectors gives a "fireball" effect
   *
   */

  if (wantNormalize)
    {
      len = sqrt (x * x + y * y + z * z);

      if (len)
	{
	  x = x / len;
	  y = y / len;
	  z = z / len;
	}
    }

  dest[0] = x;
  dest[1] = y;
  dest[2] = z;
}

void Explosion2::render(int screen_width, int screen_height)
{
    ///////////////////////////////////////////////////////////////////

    //  glViewport (0.0, 0.0, (GLfloat) screen_width, (GLfloat) screen_height);
    //glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
/*
    gluPerspective (45.0, (GLfloat) screen_width / (GLfloat) screen_height, 0.1, 100.0);
*/
    glMatrixMode (GL_MODELVIEW);

    glEnable (GL_LIGHT0);
    glEnable (GL_LIGHT1);
    glLightfv (GL_LIGHT0, GL_AMBIENT, light0Amb);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light0Dif);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light0Spec);
    glLightfv (GL_LIGHT0, GL_POSITION, light0Pos);
//    glLightfv (GL_LIGHT1, GL_AMBIENT, light1Amb);
//    glLightfv (GL_LIGHT1, GL_DIFFUSE, light1Dif);
//    glLightfv (GL_LIGHT1, GL_SPECULAR, light1Spec);
//    glLightfv (GL_LIGHT1, GL_POSITION, light1Pos);
    glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, materialAmb);
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, materialDif);
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
    glEnable (GL_NORMALIZE);

    this->logic();


    //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity ();

    ////////////////////////////////////////////////////////////////////
    float pos_x=this->pos_x;
    float pos_y=this->pos_y;
    //camera align
//    pos_x-=camera_x;
//    pos_y+=camera_y;

    pos_x+=650.0;
    pos_y+=400.0;

    /* If no explosion, draw cube */

    if (this->fuel > 0)
    {
        glPushMatrix ();

        glDisable (GL_LIGHTING);
        glDisable (GL_DEPTH_TEST);

/*
        glBegin (GL_POINTS);

        for (int i = 0; i < NUM_PARTICLES; i++)
        {
//            glColor3fv (this->particles[i].color);
//            glVertex3fv (this->particles[i].position);




            glPushMatrix();

//            glTranslatef (-((screen_width-pos_x)/2.0)/5.0, ((screen_height-pos_y)/2.0)/5.0, -100.0);
//            glRotatef (this->angle, 0.0, 1.0, 0.0);

//            //Translate the particle on the X, Y and Z axis accordingly
            glTranslatef (Particle[i].Xpos, Particle[i].Ypos, Particle[i].Zpos);
//
//            //Rotate the particle
            glRotatef (Particle[i].Direction - 90, 0, 0, 1);
//            //Scale the particle
            glScalef (Particle[i].Scalez, Particle[i].Scalez, Particle[i].Scalez);

            //Disable Depth Testing so our masking appears as one
            glDisable (GL_DEPTH_TEST);
            //Enable blending
            //glEnable (GL_BLEND);

            //Set the blending function to Take our Destination Colour and combine it with
            //Zero which is Black
            //glBlendFunc (GL_DST_COLOR, GL_ZERO);
            //Bind our mask
            //glBindTexture (GL_TEXTURE_2D, texture[0]);

            //Draw our shape

            glBegin (GL_QUADS);
            glTexCoord2d (0, 0);
            glVertex3f (-1, -1, 0);
            glTexCoord2d (1, 0);
            glVertex3f (1, -1, 0);
            glTexCoord2d (1, 1);
            glVertex3f (1, 1, 0);
            glTexCoord2d (0, 1);
            glVertex3f (-1, 1, 0);
            glEnd();

            //Re-enable Depth Testing
            glEnable(GL_DEPTH_TEST);

            //End the changes to the current object
            glPopMatrix();
        }
*/
    }

    glPopMatrix();












/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////






//    //  glViewport (0.0, 0.0, (GLfloat) screen_width, (GLfloat) screen_height);
//    //glDisable(GL_BLEND);
//    glDisable(GL_TEXTURE_2D);
//    glEnable(GL_BLEND);
//    glMatrixMode (GL_PROJECTION);
//    glLoadIdentity ();
//    gluPerspective (45.0, (GLfloat) screen_width / (GLfloat) screen_height, 0.1, 100.0);
//    glMatrixMode (GL_MODELVIEW);
//
//    glEnable (GL_LIGHT0);
//    glEnable (GL_LIGHT1);
//    glLightfv (GL_LIGHT0, GL_AMBIENT, cube.light0Amb);
//    glLightfv (GL_LIGHT0, GL_DIFFUSE, cube.light0Dif);
//    glLightfv (GL_LIGHT0, GL_SPECULAR, cube.light0Spec);
//    glLightfv (GL_LIGHT0, GL_POSITION, cube.light0Pos);
////    glLightfv (GL_LIGHT1, GL_AMBIENT, cube.light1Amb);
////    glLightfv (GL_LIGHT1, GL_DIFFUSE, cube.light1Dif);
////    glLightfv (GL_LIGHT1, GL_SPECULAR, cube.light1Spec);
////    glLightfv (GL_LIGHT1, GL_POSITION, cube.light1Pos);
//    glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
//    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, cube.materialAmb);
//    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, cube.materialDif);
//    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, cube.materialSpec);
//    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, cube.materialShininess);
//    glEnable (GL_NORMALIZE);
//
//    cube.logic();
//
//
//    //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glLoadIdentity ();
//
//    for (int i = 0; i < NUM_PARTICLES; i++)
//    {
//        if (cube.fuel == 0)
//        {
//
//        }
//
////        if (cube.fuel > 0)
////        {
//            //Distinguish the start of our current particle, we do not wish for them
//            //all to be affected by the ones prior
//
//            glPushMatrix();
//
//            //Translate the particle on the X, Y and Z axis accordingly
//            glTranslatef (cube.Particle[i].Xpos, cube.Particle[i].Ypos, cube.Particle[i].Zpos);
//
//            //Rotate the particle
//            glRotatef (cube.Particle[i].Direction - 90, 0, 0, 1);
//            //Scale the particle
//            glScalef (cube.Particle[i].Scalez, cube.Particle[i].Scalez, cube.Particle[i].Scalez);
//
//            //Disable Depth Testing so our masking appears as one
//            glDisable (GL_DEPTH_TEST);
//            //Enable blending
//            //glEnable (GL_BLEND);
//
//            //Set the blending function to Take our Destination Colour and combine it with
//            //Zero which is Black
//            //glBlendFunc (GL_DST_COLOR, GL_ZERO);
//            //Bind our mask
//            //glBindTexture (GL_TEXTURE_2D, texture[0]);
//
//            //Draw our shape
//
//            glBegin (GL_QUADS);
//            glTexCoord2d (0, 0);
//            glVertex3f (-1, -1, 0);
//            glTexCoord2d (1, 0);
//            glVertex3f (1, -1, 0);
//            glTexCoord2d (1, 1);
//            glVertex3f (1, 1, 0);
//            glTexCoord2d (0, 1);
//            glVertex3f (-1, 1, 0);
//            glEnd();
//
//            //Re-enable Depth Testing
//            glEnable(GL_DEPTH_TEST);
//
//            //End the changes to the current object
//            glPopMatrix();
////        }
//    }




}
