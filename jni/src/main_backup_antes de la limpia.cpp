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

AAssetManager * get_asset_manager()
{
	jclass sdlClass = mEnv->FindClass("org/libsdl/app/SDLActivity");

	if (sdlClass == 0)
	{
		//fatal("org/libsdl/app/SDLActivity not found.");
		return NULL;
	}

	jfieldID assman = mEnv->GetStaticFieldID(sdlClass, 
                          "mAssetMgr", "Landroid/content/res/AssetManager;");

	if (assman == 0)
	{
		//fatal("Could not find mAssetMgr.");
		return NULL;
	}

	jobject assets = mEnv->GetStaticObjectField(sdlClass, assman);

	if (assets == 0)
	{
		//fatal("Could not get mAssetMgr.");
		return NULL;
	}

	return AAssetManager_fromJava(mEnv, assets);
}

extern "C" JNIEXPORT jint JNICALL Java_org_libsdl_app_SDLMain_cFunction(JNIEnv* env, jobject o)
{
    return (jint) 2;
}

extern "C" JNIEXPORT jint JNICALL Java_org_libsdl_app_SDLMain_classParam(JNIEnv* env, jobject o)
{
	jclass sdlMain = env->GetObjectClass(o);

    return (jint) 2;
}

extern "C" JNIEXPORT jint JNICALL Java_org_libsdl_app_SDLMain_loadAssets(JNIEnv* env, jobject o)
{
	jclass sdlMain = env->GetObjectClass(o);




__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "LOAAAAD");
    
    // Make sure glue isn't stripped.
    app_dummy();

    //state = state_param;


    // Get usable JNI context

//    JNIEnv* env = mEnv;
    JavaVM* vm = mJavaVM;
    vm->AttachCurrentThread(&env, NULL);

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "QQQQQQ5");

    // Get a handle on our calling NativeActivity instance
    //jclass activityClass = env->GetObjectClass(state_param->activity->clazz);
	jclass activityClass = sdlMain;

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "WWWWWWW");

    // Get path to cache dir (/data/data/org.wikibooks.OpenGL/cache)
	jmethodID getCacheDir = env->GetMethodID(activityClass, "getCacheDir", "()Ljava/io/File;");

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "EEEEEEE");

	//jobject file = env->CallObjectMethod(state_param->activity->clazz, getCacheDir);
    jobject file = env->CallObjectMethod(activityClass, getCacheDir);

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "RRRRRRR");

    jclass fileClass = env->FindClass("java/io/File");

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "TTTTTTT");

    jmethodID getAbsolutePath = env->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "YYYYYYY");

    jstring jpath = (jstring)env->CallObjectMethod(file, getAbsolutePath);
    const char* app_dir = env->GetStringUTFChars(jpath, NULL);

    // chdir in the application cache directory
    LOGI("app_dir: %s", app_dir);
    chdir(app_dir);
    env->ReleaseStringUTFChars(jpath, app_dir);
//    print_info_paths(state_param);

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "RRRRRRRR");

    // Pre-extract assets, to avoid Android-specific file opening
    //AAssetManager* mgr = state_param->activity->assetManager;
	AAssetManager* mgr = get_asset_manager();
    AAssetDir* assetDir = AAssetManager_openDir(mgr, "");
    const char* filename = (const char*)NULL;
    while ((filename = AAssetDir_getNextFileName(assetDir)) != NULL) {
        AAsset* asset = AAssetManager_open(mgr, filename, AASSET_MODE_STREAMING);
        char buf[BUFSIZ];
        int nb_read = 0;
        FILE* out = fopen(filename, "w");
        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
            fwrite(buf, nb_read, 1, out);
        fclose(out);
        AAsset_close(asset);
    }
    AAssetDir_close(assetDir);

    // Call user's main
    char progname[5] = "self";
    char* argv[] = {progname};
    main(1, argv);

    LOGI("android_main: end");

    return (jint) 2;
}

extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved)
{

//	jclass sdlClass = mEnv->FindClass("org/libsdl/app/SDLActivity");
//	jfieldID field_int = mEnv->GetStaticFieldID(sdlClass,"int_test", "I");
//__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "2222222222222222222%i",(int)field_int);
//__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "3333333333333333333%i",(int)field_int);

//exit(0);


    mJavaVM = vm;
    LOGI("JNI_OnLoad calle!!!!!!!!!!!!!!");
    if (mJavaVM->GetEnv((void**) &mEnv, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("Failed to get the environment using GetEnv()");
        return -1;
    }

    return JNI_VERSION_1_4;
}


// This function retrieves a static member of SDLActivity called mAssetMgr
// which is initialized in the onCreate() method like so:
// ...
//   mAssetMgr = getAssets();
// ...
// You can also call the getAssets() method from the native code.


void android_main(struct android_app* state_param)
{
}

void myLoadFiles()//(struct android_app* state_param)
{
__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "LOAAAAD");
    
    // Make sure glue isn't stripped.
    app_dummy();

    //state = state_param;


    // Get usable JNI context

    JNIEnv* env = mEnv;
    JavaVM* vm = mJavaVM;
    vm->AttachCurrentThread(&env, NULL);

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "QQQQQQ5");

    // Get a handle on our calling NativeActivity instance
    //jclass activityClass = env->GetObjectClass(state_param->activity->clazz);
	jclass activityClass = mEnv->FindClass("org/libsdl/app/SDLActivity");

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "WWWWWWW");

    // Get path to cache dir (/data/data/org.wikibooks.OpenGL/cache)
	jmethodID getCacheDir = env->GetMethodID(activityClass, "getCacheDir", "()Ljava/io/File;");

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "EEEEEEE");

	//jobject file = env->CallObjectMethod(state_param->activity->clazz, getCacheDir);
    jobject file = env->CallObjectMethod(activityClass, getCacheDir);

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "RRRRRRR");

    jclass fileClass = env->FindClass("java/io/File");

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "TTTTTTT");

    jmethodID getAbsolutePath = env->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "YYYYYYY");

    jstring jpath = (jstring)env->CallObjectMethod(file, getAbsolutePath);
    const char* app_dir = env->GetStringUTFChars(jpath, NULL);

    // chdir in the application cache directory
    LOGI("app_dir: %s", app_dir);
    chdir(app_dir);
    env->ReleaseStringUTFChars(jpath, app_dir);
//    print_info_paths(state_param);

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "RRRRRRRR");

    // Pre-extract assets, to avoid Android-specific file opening
    //AAssetManager* mgr = state_param->activity->assetManager;
	AAssetManager* mgr = get_asset_manager();
    AAssetDir* assetDir = AAssetManager_openDir(mgr, "");
    const char* filename = (const char*)NULL;
    while ((filename = AAssetDir_getNextFileName(assetDir)) != NULL) {
        AAsset* asset = AAssetManager_open(mgr, filename, AASSET_MODE_STREAMING);
        char buf[BUFSIZ];
        int nb_read = 0;
        FILE* out = fopen(filename, "w");
        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
            fwrite(buf, nb_read, 1, out);
        fclose(out);
        AAsset_close(asset);
    }
    AAssetDir_close(assetDir);

    // Call user's main
    char progname[5] = "self";
    char* argv[] = {progname};
    main(1, argv);

    LOGI("android_main: end");
}

int main(int argc, char *argv[])
{

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "2222222222222222222");
__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "BBBBBBBBBBBBBBBBBB");
__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "BBBBBBBBBBBBBBBBBB");
__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "BBBBBBBBBBBBBBBBBB");
//myLoadFiles();
__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "BBBBBBBBBBBBBBBBBB");
__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "BBBBBBBBBBBBBBBBBB");



__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "fff");

    //Creadas abierto
    setReceiver(new Receiver());

    RosalilaGraphics*painter=new RosalilaGraphics();

//    painter->video(painter);

    Sound*sonido = new Sound();

    Menu* menu=new Menu(painter,getReceiver(),sonido,(char*)"menu/main_menu.svg");
/*
    menu->playMusic();
*/
    menu->loopMenu();

__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "ASDF");	

    return 0;
}
