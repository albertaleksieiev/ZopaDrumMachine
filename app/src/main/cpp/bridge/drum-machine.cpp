//
// Created by Albert on 11/13/18.
//

#include <jni.h>
#include <android/asset_manager_jni.h>
#include "../instruments/DrumMachine.h"


extern "C" {

JNIEXPORT jint JNICALL
Java_alfacerpro_com_zopadrammachine_core_DrumMachine_currentStep(JNIEnv *env,
                                                                 jobject instance) {
    auto drumMachine = getNativeObject<DrumMachine>(env, instance);

    if (drumMachine != nullptr) {
        return drumMachine->currentStep();
    }

    return 0;
}


JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_DrumMachine_addPattern(
        JNIEnv *env,
        jobject instance,
        jint soundId,
        jint patternIndex) {
    auto drumMachine = getNativeObject<DrumMachine>(env, instance);

    if (drumMachine != nullptr) {
        drumMachine->addPattern(soundId, patternIndex);
    }
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_DrumMachine_removePattern(
        JNIEnv *env,
        jobject instance,
        jint soundId,
        jint patternIndex) {
    auto drumMachine = getNativeObject<DrumMachine>(env, instance);

    if (drumMachine != nullptr) {
        drumMachine->removePattern(soundId, patternIndex);
    }
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_DrumMachine_setPatternForSound(
        JNIEnv *env,
        jobject instance,
        jint soundId,
        jintArray patternArray) {
    auto drumMachine = getNativeObject<DrumMachine>(env, instance);

    if (drumMachine == nullptr) {
        return;
    }

    std::vector<int> patternAsVector;
    auto size = env->GetArrayLength(patternArray);

    auto patternArrayAsCArray = env->GetIntArrayElements(patternArray, nullptr);
    for (int i = 0; i < size; ++i) {
        patternAsVector.push_back(patternArrayAsCArray[i]);
    }

    env->ReleaseIntArrayElements(patternArray, patternArrayAsCArray, 0);

    drumMachine->setPatternForSound(soundId, patternAsVector);
}

JNIEXPORT jintArray JNICALL
Java_alfacerpro_com_zopadrammachine_core_DrumMachine_getPatternForSound(
        JNIEnv *env,
        jobject instance,
        jint soundId) {
    auto drumMachine = getNativeObject<DrumMachine>(env, instance);

    if (drumMachine == nullptr) {
        return nullptr;
    }

    auto pattern = drumMachine->getPatternForSound(soundId);

    // Fill it
    const auto arraySize = pattern.size();
    auto cArray = new int[arraySize];
    for (int i = 0; i < pattern.size(); ++i) {
        cArray[i] = pattern[i];
    }

    // Create JNI instance
    jintArray result;
    result = env->NewIntArray(static_cast<jsize>(arraySize));

    if (result == nullptr) {
        delete[] cArray;
        return nullptr; /* out of memory error thrown */
    }

    // Convert and delete
    env->SetIntArrayRegion(result, 0, (jsize) arraySize, cArray);
    delete[] cArray;

    return result;
}

JNIEXPORT jlong JNICALL
Java_alfacerpro_com_zopadrammachine_core_DrumMachine_init(JNIEnv *env, jobject instance,
                                                          jobject jAssetManager) {

    AAssetManager *assetManager = AAssetManager_fromJava(env, jAssetManager);

    return (jlong) new DrumMachine(assetManager);
}

}



