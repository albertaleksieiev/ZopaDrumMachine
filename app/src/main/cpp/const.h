//
// Created by Albert on 11/9/18.
//

#ifndef ZOPADRAMMACHINE_CONST_H
#define ZOPADRAMMACHINE_CONST_H
#include <algorithm>

constexpr int kSampleRateHz = 48000; //
constexpr int kBufferSizeInBursts = 2; // Use 2 bursts as the buffer size (double buffer)
constexpr int kSteps = 16; // Must be multiplied of 2
constexpr int BPM = 155; // TODO fix bpm

template<typename T, size_t N>
std::vector<T> makeVector(const T (&data)[N]) {
    return std::vector<T>(data, data + N);
}
#endif //ZOPADRAMMACHINE_CONST_H


