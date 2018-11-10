#include <jni.h>
#include <android/asset_manager_jni.h>
#include "DrumMachine.h"


extern "C" {
DrumMachine *drumMachine;

JNIEXPORT jint JNICALL
Java_alfacerpro_com_zopadrammachine_DrumMachine_currentStep(JNIEnv *env,
                                                            jobject thiz) {
    if (drumMachine != nullptr) {
        return drumMachine->currentStep();
    }

    return 0;
}


JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_DrumMachine_addPattern(
        JNIEnv *env,
        jobject instance,
        jint soundId,
        jint patternIndex) {

    if (drumMachine != nullptr) {
        drumMachine->addPattern(soundId, patternIndex);
    }
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_DrumMachine_removePattern(
        JNIEnv *env,
        jobject instance,
        jint soundId,
        jint patternIndex) {

    if (drumMachine != nullptr) {
        drumMachine->removePattern(soundId, patternIndex);
    }
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_DrumMachine_setPatternForSound(
        JNIEnv *env,
        jobject instance,
        jint soundId,
        jintArray patternArray) {
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
Java_alfacerpro_com_zopadrammachine_DrumMachine_getPatternForSound(
        JNIEnv *env,
        jobject instance,
        jint soundId) {

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
    env->SetIntArrayRegion(result, 0, arraySize, cArray);
    delete[] cArray;

    return result;
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_DrumMachine_onCreate(JNIEnv *env, jobject instance,
                                                         jobject jAssetManager) {

    AAssetManager *assetManager = AAssetManager_fromJava(env, jAssetManager);

    drumMachine = new DrumMachine(assetManager);
    drumMachine->start();
}
JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_DrumMachine_stop(JNIEnv *env, jobject instance) {
    if (drumMachine == nullptr) {
        return;
    }

    drumMachine->stop();
}

}



