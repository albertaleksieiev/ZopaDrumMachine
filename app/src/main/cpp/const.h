//
// Created by Albert on 11/9/18.
//

#ifndef ZOPADRAMMACHINE_CONST_H
#define ZOPADRAMMACHINE_CONST_H

#include <algorithm>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include <jni.h>
#include <vector>

constexpr int kSampleRateHz = 48000; //
constexpr int kBufferSizeInBursts = 1; // Use 2 bursts as the buffer size (double buffer)
constexpr int kSteps = 16; // Must be multiplied of 2
constexpr int BPM = 155; // TODO fix bpm
constexpr int16_t kMaxSoundValue = 32767;

constexpr int32_t kChannelCount = 2; // TODO: move this into a constant and maybe add as parameter to ctor
constexpr auto M_TWO_PI = M_PI * 2;

template<typename T, size_t N>
std::vector<T> makeVector(const T (&data)[N]) {
    return std::vector<T>(data, data + N);
}

template<typename T>
std::string toString(const std::vector<T> &vec) {
    std::string res = "[";
    for (auto element: vec) {
        res += std::to_string(element) + ",";
    }
    res += "]";

    return res;
}

template<typename T>
T* getNativeObject(JNIEnv *env,
                   jobject jobj) {
    jclass DrumMachineClass = env->GetObjectClass(jobj);

    jfieldID fieldId = env->GetFieldID(DrumMachineClass, "nativePointer", "J");

    return (T*) env->GetLongField(jobj, fieldId);
}

#endif //ZOPADRAMMACHINE_CONST_H


