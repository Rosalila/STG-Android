/*

*/

#include "RosalilaGraphics/RosalilaGraphics.h"

#include <jni.h>





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



#include "android_rwops.h"
#include <android/asset_manager_jni.h>



#include <errno.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android/asset_manager.h>

#include <iostream>
using namespace std;


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "wikibooks-android_wrapper", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "wikibooks-android_wrapper", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "wikibooks-android_wrapper", __VA_ARGS__))

#include "RosalilaGraphics/RosalilaGraphics.h"
#include "Rosalila/RosalilaInputs/RosalilaInputs.h"
#include "RosalilaSound/RosalilaSound.h"
#include "RosalilaUtility/RosalilaUtility.h"
#include "STGUtility/STGUtility.h"
#include "STGMenu/STGMenu.h"








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
__android_log_print(ANDROID_LOG_DEBUG, "CHUUUY", "AAAAAAAAAAAAAAAAAAA");
    RosalilaGraphics*painter=new RosalilaGraphics();
__android_log_print(ANDROID_LOG_DEBUG, "CHUUUY", "AAAAAAAAAAAAAAAAAAA2");

//    painter->video(painter);

    Sound*sonido = new Sound();

std::vector<Elemento*> elementos;
            Image* image=painter->getTexture("menu/selection_bg.png");
            elementos.push_back((Elemento*)new MenuImagen(painter,0,0,0,0,0,0,-1,0,
                                                          2048,2048,image,""
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

    menu->playMusic();

    LOGI("Ready to loopp");

    menu->loopMenu();

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "ASDF");	

    return 0;
}
