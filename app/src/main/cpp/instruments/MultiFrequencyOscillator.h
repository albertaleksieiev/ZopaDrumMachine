//
// Created by Albert on 11/25/18.
//

#ifndef ZOPADRAMMACHINE_MULTIPLEPHASEOSCILLATOR_H
#define ZOPADRAMMACHINE_MULTIPLEPHASEOSCILLATOR_H

#include "./SimpleOscillator.h"
#include <mutex>
#include "../const.h"
#include <vector>

namespace oscillator {
    struct Frequency {
        Frequency(double phase, double increment) : phase(phase), increment(increment) {}
        double phase;
        double increment;

        void incrementPhase() {
            phase += increment;

            if (phase >= M_TWO_PI)
                phase -= M_TWO_PI;
        }
    };

    class MultiFrequencyOscillator : public RenderableAudio {
    public:
        MultiFrequencyOscillator();

        void setVolume(double value) { volume = value; }

        void setWaveFunc(std::function<double(double)> waveFunc) {
            this->waveFunc = std::move(waveFunc);
        }

        void setFrequencies(std::vector<double> frequencies);

        void renderAudio(int16_t *targetData, int32_t numFrames) override;

    private:
        std::vector<Frequency> freqs;
        double volume;
        std::function<double(double)> waveFunc = sine_wave;

        std::mutex mtx;
    };
}

#endif //ZOPADRAMMACHINE_MULTIPLEPHASEOSCILLATOR_H
