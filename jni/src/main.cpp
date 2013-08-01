#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <android_native_app_glue.h>

#include "SDL.h"
#include "SDL_image.h"

#include "RosalilaGraphics/RosalilaGraphics.h"

#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sstream>

//SDL
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
//#include "SDL_mixer.h"
#include <string>

#include "Rosalila/RosalilaInputs/RosalilaInputs.h"
#include "RosalilaGraphics/RosalilaGraphics.h"
#include "RosalilaSound/RosalilaSound.h"
#include "STGMenu/STGMenu.h"
#include "RosalilaUtility/RosalilaUtility.h"
#include "STGUtility/STGUtility.h"

#include "android_rwops.h"
#include <android/asset_manager_jni.h>


#include <jni.h>
#include <errno.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android/asset_manager.h>

#include <iostream>
using namespace std;

#include <EGL/egl.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "wikibooks-android_wrapper", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "wikibooks-android_wrapper", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "wikibooks-android_wrapper", __VA_ARGS__))

struct android_app* state;

static JNIEnv* mEnv = NULL;
static JNIEnv* mAudioEnv = NULL;
static JavaVM* mJavaVM;

extern "C" JNIEXPORT jint JNICALL Java_org_libsdl_app_SDLMain_cFunction(JNIEnv* env, jobject o)
{
    return (jint) 2;
}

extern "C" JNIEXPORT jint JNICALL Java_org_libsdl_app_SDLMain_classParam(JNIEnv* env, jobject o)
{
	jclass sdlMain = env->GetObjectClass(o);

    return (jint) 2;
}

int main(int argc, char *argv[])
{
//myLoadFiles();

    //Creadas abierto
    setReceiver(new Receiver());

    RosalilaGraphics*painter=new RosalilaGraphics();

//    painter->video(painter);

    Sound*sonido = new Sound();

std::vector<Elemento*> elementos;
            Image* image=painter->getTexture("menu/selection_bg.png");
            elementos.push_back((Elemento*)new MenuImagen(painter,0,0,0,0,0,0,-1,0,
                                                          1920,1080,image,""
                                                          ));
std::vector<Elemento*>elementos_contenedor;

std::vector<Elemento*>elem_lista;
elementos_contenedor.push_back((Elemento*)new MenuLista(painter,0,0,
0,0, NULL,
0,0, NULL,
0,0, NULL,
0,0,NULL,
elem_lista,"start"));

MenuContenedor*selectables_container;
selectables_container=new MenuContenedor(painter,elementos_contenedor);


    Menu* menu=new Menu(painter,new Receiver,sonido,(char*)"menu/main_menu.svg");
menu->elementos=elementos;
menu->selectables_container=selectables_container;
/*
    menu->playMusic();
*/

    LOGI("Ready to loop");

    menu->loopMenu();

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "ASDF");	

    return 0;
}

/*
    <image
       sodipodi:absref="/home/turupawn/Chicas del espacio demo - Linux 64 bit/menu/selection_bg.png"
       xlink:href="selection_bg.png"
       y="0"
       x="0"
       id="image2992"
       height="768"
       width="1366" />
    <rect
       style="fill:#ff0000;fill-opacity:1;stroke:#000000;stroke-width:0;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none;stroke-dashoffset:0"
       id="rect2983"
       width="465.27094"
       height="180.16872"
       x="853.10522"
       y="550.15326"
       type="char_select"
       chars_player2="0"
       size_x="4"
       size_y="1"
       box_separation_x="15"
       preview_player1_x="70"
       preview_player1_y="30" />
    <rect
       style="fill:#ff0000;fill-opacity:1;stroke:#000000;stroke-width:0;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none;stroke-dashoffset:0"
       id="rect2985"
       width="500"
       height="252"
       x="825.11334"
       y="44.808998"
       type="stage_select" />
*/
