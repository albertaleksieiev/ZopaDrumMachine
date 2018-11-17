#include <jni.h>
#include <android/asset_manager_jni.h>
#include "AudioEngine.h"


extern "C" {
AudioEngine engine;

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_AudioEngine_start(JNIEnv *env,
                                                           jobject thiz) {
    engine.start();
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_AudioEngine_stop(JNIEnv *env,
                                                          jobject thiz) {
    engine.stop();
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_AudioEngine_pause(JNIEnv *env,
                                                          jobject thiz) {
    engine.pause();
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_AudioEngine_resume(JNIEnv *env,
                                                           jobject thiz) {
    engine.resume();
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_AudioEngine_setIsPlaying(JNIEnv *env,
                                                            jobject thiz,
                                                            jboolean isPlaying) {
    engine.setIsPlaying(isPlaying);
}

JNIEXPORT jint JNICALL
Java_alfacerpro_com_zopadrammachine_core_AudioEngine_getOboeAudioStreamState(JNIEnv *env,
                                                           jobject thiz) {
    return engine.getState();
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_AudioEngine_addInstrument(JNIEnv *env,
                                                           jobject thiz,
                                                           jlong instrument) {
    engine.renderableAudios.push_back((RenderableAudio *) instrument);
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_AudioEngine_clearInstruments(JNIEnv *env,
                                                          jobject thiz) {
    engine.renderableAudios.clear();
}


}



