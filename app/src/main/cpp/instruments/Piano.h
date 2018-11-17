//
// Created by Albert on 11/17/18.
//

#ifndef ZOPADRAMMACHINE_PIANO_H
#define ZOPADRAMMACHINE_PIANO_H

#include "../google/RenderableAudio.h"
#include "../const.h"
#include <functional>
#include "./SimpleOscillator.h"
#include <cmath>

class Piano : public RenderableAudio {
public:
    void setNote(int note); // [1..88]

private:
    oscillator::SimpleOscillator simpleOscillator;
    void renderAudio(int16_t *targetData, int32_t numFrames) override;

};


#endif //ZOPADRAMMACHINE_PIANO_H
