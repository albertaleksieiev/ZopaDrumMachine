//
// Created by Albert on 11/25/18.
//

#include "MultiFrequencyOscillator.h"

oscillator::MultiFrequencyOscillator::MultiFrequencyOscillator() {

}

void oscillator::MultiFrequencyOscillator::renderAudio(int16_t *targetData, int32_t numFrames) {
    mtx.lock();
    for (int i = 0; i < numFrames; i++) {
        double value = 0;

        for (int j = 0; j < this->freqs.size(); j++) {
            value += waveFunc(freqs[j].phase) * kMaxSoundValue;

            // Increment phase
            freqs[j].incrementPhase();
        }

        value /= freqs.size();

        for (int j = 0; j < kChannelCount; ++j) {
            targetData[(i * kChannelCount) + j] = static_cast<int16_t>(value);
        }
    }
    mtx.unlock();
}

void oscillator::MultiFrequencyOscillator::setFrequencies(std::vector<double> frequencies) {
    std::vector<Frequency> freqs;
    for (double frequency: frequencies) {
        freqs.emplace_back(M_PI, frequency / kSampleRateHz * M_TWO_PI);
    }

    mtx.lock();
    this->freqs = freqs;
    mtx.unlock();
}
