/*

*/

#include "RosalilaGraphics/RosalilaGraphics.h"

#include <jni.h>





#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//#include <android_native_app_glue.h>
#include <nv_and_util/nv_native_app_glue.h>
#include <nv_egl_util/nv_egl_util.h>

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

//!//

#include "jni.h"
#include "SDL_config.h"
#include "SDL_stdinc.h"
 
//static float fLastAccelerometer[3];
extern "C" {
    void Java_org_libsdl_app_SDLActivity_nativeRunAudioThread(JNIEnv* env, jclass cls);
    void Java_org_libsdl_app_SDLActivity_onNativeResize(
                                    JNIEnv* env, jclass jcls,
                                    jint width, jint height, jint format);
    void Java_org_libsdl_app_SDLActivity_onNativeKeyDown(
                                    JNIEnv* env, jclass jcls, jint keycode);
    void Java_org_libsdl_app_SDLActivity_onNativeKeyUp(
                                    JNIEnv* env, jclass jcls, jint keycode);
    void Java_org_libsdl_app_SDLActivity_onNativeTouch(
                                    JNIEnv* env, jclass jcls,
                                    jint touch_device_id_in, jint pointer_finger_id_in,
                                    jint action, jfloat x, jfloat y, jfloat p);
    void Java_org_libsdl_app_SDLActivity_onNativeAccel(
                                    JNIEnv* env, jclass jcls,
                                    jfloat x, jfloat y, jfloat z);
    void Java_org_libsdl_app_SDLActivity_nativeQuit(
                                    JNIEnv* env, jclass cls);
    void Java_org_libsdl_app_SDLActivity_nativeRunAudioThread(
                                    JNIEnv* env, jclass cls);
    void Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject obj);
};
 
// Resize
extern "C" void Java_rosalila_studio_shooter_SDLActivity_onNativeResize(
                                    JNIEnv* env, jclass jcls,
                                    jint width, jint height, jint format)
{
    Java_org_libsdl_app_SDLActivity_onNativeResize(env, jcls, width, height, format);
}
 
// Keydown
extern "C" void Java_rosalila_studio_shooter_SDLActivity_onNativeKeyDown(
                                    JNIEnv* env, jclass jcls, jint keycode)
{
    Java_org_libsdl_app_SDLActivity_onNativeKeyDown(env, jcls, keycode);
}
 
// Keyup
extern "C" void Java_rosalila_studio_shooter_SDLActivity_onNativeKeyUp(
                                    JNIEnv* env, jclass jcls, jint keycode)
{
    Java_org_libsdl_app_SDLActivity_onNativeKeyUp(env, jcls, keycode);
}
 
// Touch
extern "C" void Java_rosalila_studio_shooter_SDLActivity_onNativeTouch(
                                    JNIEnv* env, jclass jcls,
                                    jint touch_device_id_in, jint pointer_finger_id_in,
                                    jint action, jfloat x, jfloat y, jfloat p)
{
    Java_org_libsdl_app_SDLActivity_onNativeTouch(env, jcls, touch_device_id_in, pointer_finger_id_in, action, x, y, p);
}
 
// Accelerometer
extern "C" void Java_rosalila_studio_shooter_SDLActivity_onNativeAccel(
                                    JNIEnv* env, jclass jcls,
                                    jfloat x, jfloat y, jfloat z)
{
     Java_org_libsdl_app_SDLActivity_onNativeAccel(env, jcls, x, y, z);
}
 
// Quit
extern "C" void Java_rosalila_studio_shooter_SDLActivity_nativeQuit(
                                    JNIEnv* env, jclass cls)
{
    Java_org_libsdl_app_SDLActivity_nativeQuit(env, cls);
}
 
extern "C" void Java_rosalila_studio_shooter_SDLActivity_nativeRunAudioThread(
                                    JNIEnv* env, jclass cls)
{
    Java_org_libsdl_app_SDLActivity_nativeRunAudioThread(env, cls);
}
 
extern "C" void Java_rosalila_studio_shooter_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject obj) {
    Java_org_libsdl_app_SDLActivity_nativeInit(env, cls, obj);
}

//!//








struct android_app* state;

static JNIEnv* mEnv = NULL;
static JNIEnv* mAudioEnv = NULL;
static JavaVM* mJavaVM;

/*
extern "C" JNIEXPORT jint JNICALL Java_org_libsdl_app_SDLMain_cFunction(JNIEnv* env, jobject o)
{
    return (jint) 2;
}
*/

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
            elementos.push_back((Elemento*)new MenuImagen(painter,0,0,0,0,0,0,255,0,
                                                          2048,1024,image,""
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

setReceiver(new Receiver);

    Menu* menu=new Menu(painter,getReceiver(),sonido,(char*)"menu/main_menu.svg");
menu->elementos=elementos;
menu->selectables_container=selectables_container;

    menu->playMusic();

    LOGI("Ready to loopp");

    menu->loopMenu();

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "ASDF");	

    return 0;
}
