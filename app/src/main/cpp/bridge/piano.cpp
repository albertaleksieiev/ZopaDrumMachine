//
// Created by Albert on 11/17/18.
//

#include <jni.h>
#include <android/asset_manager_jni.h>
#include "../instruments/Piano.h"

extern "C" {


JNIEXPORT jlong JNICALL
Java_alfacerpro_com_zopadrammachine_core_Piano_init(JNIEnv *env, jobject instance) {


    return (jlong) new Piano();
}

JNIEXPORT void JNICALL
Java_alfacerpro_com_zopadrammachine_core_Piano_setNotes(JNIEnv *env, jobject instance, jintArray jIntNotes) {
    auto piano = getNativeObject<Piano>(env, instance);

    std::vector<int> notes;
    auto size = env->GetArrayLength(jIntNotes);

    auto patternArrayAsCArray = env->GetIntArrayElements(jIntNotes, nullptr);
    for (int i = 0; i < size; ++i) {
        notes.push_back(patternArrayAsCArray[i]);
    }
    env->ReleaseIntArrayElements(jIntNotes, patternArrayAsCArray, 0);

    piano->setNotes(notes);
}

}
