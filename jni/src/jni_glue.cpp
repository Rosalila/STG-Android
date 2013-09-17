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
