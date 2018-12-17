//
// Created by Albert on 11/17/18.
//

#include "Piano.h"

void Piano::renderAudio(int16_t *targetData, int32_t numFrames) {
    audioOscillator.renderAudio(targetData, numFrames);
}

void Piano::setNotes(std::vector<int> notes) {
    std::vector<double > freqs;
    for (auto note: notes) {
        freqs.emplace_back(pow(2, (note - 49.0)/12.) * 440.0);
    }

    audioOscillator.setFrequencies(freqs);
}
