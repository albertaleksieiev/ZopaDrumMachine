//
// Created by Albert on 11/17/18.
//

#ifndef ZOPADRAMMACHINE_PIANO_H
#define ZOPADRAMMACHINE_PIANO_H

#include "../google/RenderableAudio.h"
#include "../const.h"
#include <functional>
#include "./MultiFrequencyOscillator.h"
#include <cmath>

class Piano : public RenderableAudio {
public:
    void setNotes(std::vector<int> notes); // [1..88]

private:
    oscillator::MultiFrequencyOscillator audioOscillator;
    void renderAudio(int16_t *targetData, int32_t numFrames) override;

};


#endif //ZOPADRAMMACHINE_PIANO_H
