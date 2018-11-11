//
// Created by Albert on 11/11/18.
//

#include "SimpleOscillator.h"

using namespace oscillator;
namespace oscillator {
    double sine_wave(double phase) {
        return sin(phase);
    }

    double square_wave(double phase) {
        return phase <= M_PI ? 1 : -1;
    }

    double downward_sawtooth_wave(double phase) {
        return 1.0 - 2.0 * (phase / M_TWO_PI);
    }

    double upward_sawtooth_wave(double phase) {
        return 2.0 * (phase / M_TWO_PI) - 1.0;
    }

    double triangle_wave(double phase) {
        double result = upward_sawtooth_wave(phase);
        if (result < 0.0)
            result = -result;
        return 2.0 * (result - 0.5);
    }

    void SimpleOscillator::renderAudio(int16_t *targetData, int32_t numFrames) {
        for (int i = 0; i < numFrames; i++) {
            double value = waveFunc(phase) * kMaxSoundValue * volume;

            for (int j = 0; j < mChannelCount; ++j) {
                targetData[(i * mChannelCount) + j] = static_cast<int16_t>(value);
            }

            // Increment phase
            phase += increment;

            // Wrap phase to the 0-2PI range
            if (phase >= M_TWO_PI)
                phase -= M_TWO_PI;
        }
    }

    SimpleOscillator::SimpleOscillator() : phase(0.0), volume(0.7) {
        setFrequency(440); // 440hz aka note A4
    }

    void SimpleOscillator::setFrequency(double frequency) {
        increment = frequency / kSampleRateHz * M_TWO_PI;
    }
}