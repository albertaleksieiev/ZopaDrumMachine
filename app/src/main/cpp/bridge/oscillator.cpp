//
// Created by Albert on 11/13/18.
//

#include <jni.h>
#include <android/asset_manager_jni.h>
#include "../instruments/SimpleOscillator.h"

extern "C" {


JNIEXPORT jlong JNICALL
Java_alfacerpro_com_zopadrammachine_core_SimpleOscillator_init(JNIEnv *env, jobject instance) {
    return (jlong) new oscillator::SimpleOscillator();
}


}
