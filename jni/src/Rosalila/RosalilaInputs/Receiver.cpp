#include "RosalilaInputs/RosalilaInputs.h"

Receiver::Receiver()
{
    for(int i = 0; i < 322; i++) { // init them all to false
       KEYS[i] = false;
    }

    for(int i = 0; i < max_joystick_inputs; i++) { // init them all to false
       JOYKEYS_player1[i] = false;
    }
    for(int i = 0; i < max_joystick_inputs; i++) { // init them all to false
       JOYKEYS_player2[i] = false;
    }

    joy_up_pressed_player_1=false;
    joy_down_pressed_player_1=false;
    joy_left_pressed_player_1=false;
    joy_right_pressed_player_1=false;
    joy_up_pressed_player_2=false;
    joy_down_pressed_player_2=false;
    joy_left_pressed_player_2=false;
    joy_right_pressed_player_2=false;

for(int i=0;i<14;i++)
	is_ouya_down.push_back(false);
for(int i=0;i<14;i++)
	is_ouya_pressed.push_back(false);

//    SDL_EnableKeyRepeat(0,0);
}

bool Receiver::IsKeyPressed(int keycode)
{
//__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "B111111");
/*
  if(KEYS[keycode])
  {
__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "B222222");
      KEYS[keycode]=false;
      return true;
  }
*/
  return false;
}

bool Receiver::IsKeyDownn(int keycode)
{
  return false;
  if(KEYS[keycode])
  {
      //KEYS[keycode]=false;
      return true;
  }
  return false;
//  if (keystates[keycode])
//  {
//     return true;
//  }
//  else
//  {
//     return false;
//  }
}

bool Receiver::IsJoyDown(int joyCode,int joystick)
{
	return false;
    if(joystick==0)
    {
        if(joyCode==-1)
            return joy_down_pressed_player_1 && joy_left_pressed_player_1;
        if(joyCode==-3)
            return joy_down_pressed_player_1 && joy_right_pressed_player_1;
        if(joyCode==-7)
            return joy_up_pressed_player_1 && joy_left_pressed_player_1;
        if(joyCode==-9)
            return joy_up_pressed_player_1 && joy_right_pressed_player_1;
        if(joyCode==-2)
            return joy_down_pressed_player_1;
        if(joyCode==-4)
            return joy_left_pressed_player_1;
        if(joyCode==-6)
            return joy_right_pressed_player_1;
        if(joyCode==-8)
            return joy_up_pressed_player_1;
        if(JOYKEYS_player1[joyCode])
        {
          return true;
        }
        return false;
    }
    if(joystick==1)
    {
        if(joyCode==-1)
            return joy_down_pressed_player_2 && joy_left_pressed_player_2;
        if(joyCode==-3)
            return joy_down_pressed_player_2 && joy_right_pressed_player_2;
        if(joyCode==-7)
            return joy_up_pressed_player_2 && joy_left_pressed_player_2;
        if(joyCode==-9)
            return joy_up_pressed_player_2 && joy_right_pressed_player_2;
        if(joyCode==-2)
            return joy_down_pressed_player_2;
        if(joyCode==-4)
            return joy_left_pressed_player_2;
        if(joyCode==-6)
            return joy_right_pressed_player_2;
        if(joyCode==-8)
            return joy_up_pressed_player_2;
        if(JOYKEYS_player2[joyCode])
        {
          return true;
        }
        return false;
    }
    return false;
}

bool Receiver::IsJoyPressed(int joyCode,int joystick)
{
//__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "C1111111");
/*
    if(joystick==0)
    {
        if(joyCode==-1)
        {
            if(joy_down_pressed_player_1 && joy_left_pressed_player_1)
            {
                joy_down_pressed_player_1 = false;
                joy_left_pressed_player_1 = false;
                return true;
            }
        }
        if(joyCode==-3 && joy_down_pressed_player_1 && joy_right_pressed_player_1)
        {
            joy_down_pressed_player_1 = false;
            joy_right_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-7 && joy_up_pressed_player_1 && joy_left_pressed_player_1)
        {
            joy_up_pressed_player_1 = false;
            joy_left_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-9 && joy_up_pressed_player_1 && joy_right_pressed_player_1)
        {
            joy_up_pressed_player_1 = false;
            joy_right_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-2 && joy_down_pressed_player_1)
        {
            joy_down_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-4 && joy_left_pressed_player_1)
        {
            joy_left_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-6 && joy_right_pressed_player_1)
        {
            joy_right_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-8 && joy_up_pressed_player_1)
        {
            joy_up_pressed_player_1 = false;
            return true;
        }
        if(JOYKEYS_player1[joyCode])
        {
            JOYKEYS_player1[joyCode] = false;
            return true;
        }
        return false;
    }
    if(joystick==1)
    {
        if(joyCode==-1)
        {
            if(joy_down_pressed_player_2 && joy_left_pressed_player_2)
            {
                joy_down_pressed_player_2 = false;
                joy_left_pressed_player_2 = false;
                return true;
            }
        }
        if(joyCode==-3 && joy_down_pressed_player_2 && joy_right_pressed_player_2)
        {
            joy_down_pressed_player_2 = false;
            joy_right_pressed_player_2 = false;
            return true;
        }
        if(joyCode==-7 && joy_up_pressed_player_2 && joy_left_pressed_player_2)
        {
            joy_up_pressed_player_2 = false;
            joy_left_pressed_player_2 = false;
            return true;
        }
        if(joyCode==-9 && joy_up_pressed_player_2 && joy_right_pressed_player_2)
        {
            joy_up_pressed_player_2 = false;
            joy_right_pressed_player_2 = false;
            return true;
        }
        if(joyCode==-2 && joy_down_pressed_player_2)
        {
            joy_down_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-4 && joy_left_pressed_player_2)
        {
            joy_left_pressed_player_2 = false;
            return true;
        }
        if(joyCode==-6 && joy_right_pressed_player_2)
        {
            joy_right_pressed_player_2 = false;
            return true;
        }
        if(joyCode==-8 && joy_up_pressed_player_2)
        {
            joy_up_pressed_player_2 = false;
            return true;
        }
        if(JOYKEYS_player2[joyCode])
        {
            JOYKEYS_player2[joyCode] = false;
            return true;
        }
        return false;
    }
*/
    return false;
}

bool Receiver::isOuyaDown(char key)
{
	if(key=='o')
		return is_ouya_down[0];
	if(key=='u')
		return is_ouya_down[1];
	if(key=='y')
		return is_ouya_down[2];
	if(key=='a')
		return is_ouya_down[3];

	if(key=='l')
		return is_ouya_down[4];
	if(key=='m')
		return is_ouya_down[5];

	if(key=='r')
		return is_ouya_down[6];
	if(key=='s')
		return is_ouya_down[7];

	if(key=='j')
		return is_ouya_down[8];
	if(key=='k')
		return is_ouya_down[9];

	if(key==8)
		return is_ouya_down[10];
	if(key==2)
		return is_ouya_down[11];
	if(key==4)
		return is_ouya_down[12];
	if(key==6)
		return is_ouya_down[13];
}


bool Receiver::isOuyaPressed(char key)
{
	if(key=='o')
		return is_ouya_pressed[0];
	if(key=='u')
		return is_ouya_pressed[1];
	if(key=='y')
		return is_ouya_pressed[2];
	if(key=='a')
		return is_ouya_pressed[3];

	if(key=='l')
		return is_ouya_pressed[4];
	if(key=='m')
		return is_ouya_pressed[5];

	if(key=='r')
		return is_ouya_pressed[6];
	if(key=='s')
		return is_ouya_pressed[7];

	if(key=='j')
		return is_ouya_pressed[8];
	if(key=='k')
		return is_ouya_pressed[9];

	if(key==8)
		return is_ouya_pressed[10];
	if(key==2)
		return is_ouya_pressed[11];
	if(key==4)
		return is_ouya_pressed[12];
	if(key==6)
		return is_ouya_pressed[13];
}

void Receiver::updateInputs()
{

	for(int i=0;i<14;i++)
		is_ouya_pressed[i]=false;

	SDL_Event event;
    while(SDL_PollEvent(&event))
	{
        if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == 'o')
			{
				is_ouya_down[0]=true;
				is_ouya_pressed[0]=true;
			}
			if(event.key.keysym.sym == 'u')
			{
				is_ouya_down[1]=true;
				is_ouya_pressed[1]=true;
			}
			if(event.key.keysym.sym == 'y')
			{
				is_ouya_down[2]=true;
				is_ouya_pressed[2]=true;
			}
			if(event.key.keysym.sym == 'a')
			{
				is_ouya_down[3]=true;
				is_ouya_pressed[3]=true;
			}

			if(event.key.keysym.sym == 'l')//l
			{
				is_ouya_down[4]=true;
				is_ouya_pressed[4]=true;
			}
			if(event.key.keysym.sym == 'm')//l2
			{
				is_ouya_down[5]=true;
				is_ouya_pressed[5]=true;
			}

			if(event.key.keysym.sym == 'r')//lt
			{
				is_ouya_down[6]=true;
				is_ouya_pressed[6]=true;
			}
			if(event.key.keysym.sym == 's')//rt
			{
				is_ouya_down[7]=true;
				is_ouya_pressed[7]=true;
			}

			if(event.key.keysym.sym == 'j')//lpad
			{
				is_ouya_down[8]=true;
				is_ouya_pressed[8]=true;
			}
			if(event.key.keysym.sym == 'k')//rpad
			{
				is_ouya_down[9]=true;
				is_ouya_pressed[9]=true;
			}

			if(event.key.keysym.sym == SDLK_UP)
			{
				is_ouya_down[10]=true;
				is_ouya_pressed[10]=true;
			}
			if(event.key.keysym.sym == SDLK_DOWN)
			{
				is_ouya_down[11]=true;
				is_ouya_pressed[11]=true;
			}
			if(event.key.keysym.sym == SDLK_LEFT)
			{
				is_ouya_down[12]=true;
				is_ouya_pressed[12]=true;
			}
			if(event.key.keysym.sym == SDLK_RIGHT)
			{
				is_ouya_down[13]=true;
				is_ouya_pressed[13]=true;
			}
        }

        if(event.type == SDL_KEYUP)
		{
			if(event.key.keysym.sym == 'o')
			{
				is_ouya_down[0]=false;
			}
			if(event.key.keysym.sym == 'u')
			{
				is_ouya_down[1]=false;
			}
			if(event.key.keysym.sym == 'y')
			{
				is_ouya_down[2]=false;
			}
			if(event.key.keysym.sym == 'a')
			{
				is_ouya_down[3]=false;
			}
			if(event.key.keysym.sym == 'l')
			{
				is_ouya_down[4]=false;
			}
			if(event.key.keysym.sym == 'm')
			{
				is_ouya_down[5]=false;
			}
			if(event.key.keysym.sym == 'r')
			{
				is_ouya_down[6]=false;
			}
			if(event.key.keysym.sym == 's')
			{
				is_ouya_down[7]=false;
			}
			if(event.key.keysym.sym == 'j')
			{
				is_ouya_down[8]=false;
			}
			if(event.key.keysym.sym == 'k')
			{
				is_ouya_down[9]=false;
			}

			if(event.key.keysym.sym == SDLK_UP)
			{
				is_ouya_down[10]=false;
			}
			if(event.key.keysym.sym == SDLK_DOWN)
			{
				is_ouya_down[11]=false;
			}
			if(event.key.keysym.sym == SDLK_LEFT)
			{
				is_ouya_down[12]=false;
			}
			if(event.key.keysym.sym == SDLK_RIGHT)
			{
				is_ouya_down[13]=false;
			}
		}
    }

/*
    //While there's events to handle
    SDL_Event event;
    while( SDL_PollEvent( &event ) )
    {
        //If the user has Xed out the window
        if( event.type == SDL_QUIT )
        {
            exit(0);
        }
        if( event.type == SDL_KEYDOWN )
        {
            KEYS[event.key.keysym.sym] = true;
        }
        if( event.type == SDL_KEYUP )
        {
            KEYS[event.key.keysym.sym] = false;
        }
        if( event.type == SDL_JOYBUTTONDOWN )
        {
            for(int i=0;i<max_joystick_inputs;i++)
            {
                if ( event.jbutton.button == i
                    && event.jbutton.which==0)
                {
                    JOYKEYS_player1[i]=true;
                }
            }
            for(int i=0;i<max_joystick_inputs;i++)
            {
                if ( event.jbutton.button == i
                    && event.jbutton.which==1)
                {
                    JOYKEYS_player2[i]=true;
                }
            }
        }
        if( event.type == SDL_JOYBUTTONUP )
        {
            for(int i=0;i<max_joystick_inputs;i++)
            {
                if ( event.jbutton.button == i
                    && event.jbutton.which==0)
                {
                    JOYKEYS_player1[i]=false;
                }
            }
            for(int i=0;i<max_joystick_inputs;i++)
            {
                if ( event.jbutton.button == i
                    && event.jbutton.which==1)
                {
                    JOYKEYS_player2[i]=false;
                }
            }
        }
        if( event.type == SDL_JOYAXISMOTION )
        {
            //If joystick 0 has moved
            if( event.jaxis.which == 0 )
            {
                if( event.jaxis.axis == 0 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_left_pressed_player_1=false;
                        joy_right_pressed_player_1=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_left_pressed_player_1=true;
                        }
                        else
                        {
                            joy_right_pressed_player_1=true;
                        }
                    }
                }
                //If the Y axis changed
                else if( event.jaxis.axis == 1 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_up_pressed_player_1=false;
                        joy_down_pressed_player_1=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_up_pressed_player_1=true;
                        }
                        else
                        {
                            joy_down_pressed_player_1=true;
                        }
                    }
                }
            }




            if( event.jaxis.which == 1 )
            {
                if( event.jaxis.axis == 0 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_left_pressed_player_2=false;
                        joy_right_pressed_player_2=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_left_pressed_player_2=true;
                            joy_right_pressed_player_2=false;
                        }
                        else
                        {
                            joy_left_pressed_player_2=false;
                            joy_right_pressed_player_2=true;
                        }
                    }
                }
                //If the Y axis changed
                else if( event.jaxis.axis == 1 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_up_pressed_player_2=false;
                        joy_down_pressed_player_2=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_up_pressed_player_2=true;
                            joy_down_pressed_player_2=false;
                        }
                        else
                        {
                            joy_up_pressed_player_2=false;
                            joy_down_pressed_player_2=true;
                        }
                    }
                }
            }



        }
    }
//    keystates = SDL_GetKeyState( NULL );
*/
}
