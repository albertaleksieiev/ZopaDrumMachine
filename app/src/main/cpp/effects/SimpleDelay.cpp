//
// Created by Albert on 10/31/18.
//

#include "SimpleDelay.h"

SimpleDelay::SimpleDelay(float timeSec, float decay): decay(decay) {
    this->size = static_cast<size_t>(timeSec * kSampleRateHz) ;

    buffer = new int16_t[size];
    memset(buffer, 0, size);
}

void SimpleDelay::renderAudio(int16_t *targetData, int32_t numFrames) {
    for(auto i = 0; i < numFrames;i++) {
        targetData[i] += buffer[i] * decay;
        buffer[position] = targetData[i];

        ++position %= size;
    }
}
