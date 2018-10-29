#include <jni.h>
#include <memory>
#include <string>
#include <android/asset_manager_jni.h>
#include "AudioEngine.h"


extern "C" {
AudioEngine* audioEngine;


JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_DrumMachine_playSound(
        JNIEnv *env,
        jobject instance,
        jint soundId) {

    if (audioEngine != nullptr) {
        audioEngine->playSound(soundId);
    }
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_DrumMachine_onCreate(JNIEnv *env, jobject instance,
                                                          jobject jAssetManager) {

    AAssetManager *assetManager = AAssetManager_fromJava(env, jAssetManager);

    audioEngine = new AudioEngine(assetManager);
    audioEngine->start();
}


}



