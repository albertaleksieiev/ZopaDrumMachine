//
// Created by Albert on 11/11/18.
//

#ifndef ZOPADRAMMACHINE_SIMPLEOSCILLATOR_H
#define ZOPADRAMMACHINE_SIMPLEOSCILLATOR_H

#include "../google/RenderableAudio.h"
#include "../const.h"
#include <functional>

namespace oscillator {
    // Waves
    double sine_wave(double phase);

    double square_wave(double phase);

    double downward_sawtooth_wave(double phase);

    double upward_sawtooth_wave(double phase);

    double triangle_wave(double phase);
}

namespace oscillator {
    class SimpleOscillator : public RenderableAudio {
    public:
        SimpleOscillator();

        void setVolume(double value) { volume = value; }

        void setWaveFunc(std::function<double(double)> waveFunc) {
            this->waveFunc = std::move(waveFunc);
        }

        void setFrequency(double frequency);

        void renderAudio(int16_t *targetData, int32_t numFrames) override;

    private:
        double phase;
        double increment;
        double volume;

        std::function<double(double)> waveFunc = sine_wave;
    };
}


#endif //ZOPADRAMMACHINE_SIMPLEOSCILLATOR_H
