//
// Created by Albert on 1/27/19.
//

//
// Created by Albert on 11/17/18.
//

#include <jni.h>
#include <android/asset_manager_jni.h>
#include "../instruments/MediaPlayer.h"

extern "C" {


JNIEXPORT jlong JNICALL
Java_alfacerpro_com_zopadrammachine_core_MediaPlayer_init(JNIEnv *env, jobject instance, jobject jAssetManager) {
    AAssetManager *assetManager = AAssetManager_fromJava(env, jAssetManager);

    return (jlong) new MediaPlayer(assetManager);
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_MediaPlayer_setProgress(JNIEnv *env, jobject instance, jfloat progress) {
    auto mediaPlayer = getNativeObject<MediaPlayer>(env, instance);
    mediaPlayer->setProgress(progress);
}

JNIEXPORT jfloat JNICALL
Java_alfacerpro_com_zopadrammachine_core_MediaPlayer_getProgress(JNIEnv *env, jobject instance) {
    auto mediaPlayer = getNativeObject<MediaPlayer>(env, instance);
    return mediaPlayer->getProgress();
}


JNIEXPORT jfloatArray JNICALL
Java_alfacerpro_com_zopadrammachine_core_MediaPlayer_getAnalyzedFrequencies(JNIEnv *env, jobject instance) {
    auto mediaPlayer = getNativeObject<MediaPlayer>(env, instance);

    std::vector<float> volume = mediaPlayer->getAnalyzedFrequencies();
// Fill it
    const auto arraySize = volume.size();
    auto cArray = new float[arraySize];
    for (int i = 0; i < volume.size(); ++i) {
        cArray[i] = volume[i];
    }

// Create JNI instance
    jfloatArray result;
    result = env->NewFloatArray(static_cast<jsize>(arraySize));

    if (result == nullptr) {
        delete[] cArray;
        return nullptr; /* out of memory error thrown */
    }

// Convert and delete
    env->SetFloatArrayRegion(result, 0, (jsize) arraySize, cArray);
    delete[] cArray;

    return result;
}

JNIEXPORT jfloatArray JNICALL
Java_alfacerpro_com_zopadrammachine_core_MediaPlayer_getWaveform(JNIEnv *env, jobject instance) {
    auto mediaPlayer = getNativeObject<MediaPlayer>(env, instance);

    std::vector<float> volume = mediaPlayer->getWaveform();
    // Fill it
    const auto arraySize = volume.size();
    auto cArray = new float[arraySize];
    for (int i = 0; i < volume.size(); ++i) {
        cArray[i] = volume[i];
    }

    // Create JNI instance
    jfloatArray result;
    result = env->NewFloatArray(static_cast<jsize>(arraySize));

    if (result == nullptr) {
        delete[] cArray;
        return nullptr; /* out of memory error thrown */
    }

    // Convert and delete
    env->SetFloatArrayRegion(result, 0, (jsize) arraySize, cArray);
    delete[] cArray;

    return result;
}


}
