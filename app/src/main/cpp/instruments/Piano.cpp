//
// Created by Albert on 11/17/18.
//

#include "Piano.h"

void Piano::renderAudio(int16_t *targetData, int32_t numFrames) {
    simpleOscillator.renderAudio(targetData, numFrames);
}

void Piano::setNote(int note) {
    simpleOscillator.setFrequency(pow(2, (note - 49.0)/12.) * 440.0);
}
