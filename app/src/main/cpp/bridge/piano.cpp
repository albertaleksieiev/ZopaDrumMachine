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
Java_alfacerpro_com_zopadrammachine_core_Piano_setNote(JNIEnv *env, jobject instance, jint note) {
    auto piano = getNativeObject<Piano>(env, instance);
    piano->setNote(note);
}



}
