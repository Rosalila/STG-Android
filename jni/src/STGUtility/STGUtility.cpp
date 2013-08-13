#include "STGUtility.h"

int iterate_slowdown_flag=0;
int current_slowdown_iteration=0;
bool slow_enabled=false;
Receiver* receiver = new Receiver();

bool getIterateSlowdownFlag()
{
    return !isSlowActive() || iterate_slowdown_flag;
}

void slowExtraControl()
{
    //slow extra control
    if(isSlowActive())
    {
        iterate_slowdown_flag=false;
        current_slowdown_iteration++;
        if(current_slowdown_iteration>=3)
        {
            current_slowdown_iteration=0;
            iterate_slowdown_flag=true;
        }
    }
}

void setReceiver(Receiver*receiver_param)
{
    receiver=receiver;
}

Receiver* getReceiver()
{
    return receiver;
}

bool isSlowPressed()
{
    return receiver->IsKeyDownn(SDLK_x) || receiver->IsJoyDown(5,0) || receiver->isOuyaDown('m') || receiver->isOuyaDown('s');
}

void disableSlow()
{
    slow_enabled=false;
}
void enableSlow()
{
    slow_enabled=true;
}
bool isSlowEnabled()
{
    return slow_enabled;
}
bool isSlowActive()
{
    return isSlowEnabled() && isSlowPressed();
}

double getSlowdown()
{
    if(receiver->isOuyaDown('m') && receiver->isOuyaDown('s') && isSlowEnabled())
        return 4.0;
    if(isSlowPressed() && isSlowEnabled())
		return 2.0;
    return 1.0;
}
