//
// Created by Albert on 10/28/18.
//

#ifndef ZOPADRAMMACHINE_AUDIOENGINE_H
#define ZOPADRAMMACHINE_AUDIOENGINE_H

#include <oboe/Oboe.h>
#include <vector>
#include "../google/SoundRecording.h"
#include "../google/Mixer.h"
#include "../effects/SimpleDelay.h"
#include "../const.h"
#include "../../../../../../../android/oboe/src/common/OboeDebug.h"

constexpr int kBeatMultiplier = static_cast<const int>((float) kSampleRateHz / (BPM / 60.0));
constexpr int kMaxWindowHZ = kBeatMultiplier * 16;

using namespace oboe;

class DrumMachine : public RenderableAudio {
public:
    DrumMachine(AAssetManager *mAssetManager);

    void addPattern(int idSound, int patternIndex);

    void removePattern(int idSound, int patternIndex);

    std::vector<int> getPatternForSound(int idSound);

    void setPatternForSound(int idSound, std::vector<int> pattern);

    int currentStep();

    void renderAudio(int16_t *targetData, int32_t numFrames) override;

private:
    std::vector<bool> *getPatternBank(int idSound);

    SoundRecording *mClap = nullptr;
    SoundRecording *mSnaire = nullptr;
    SoundRecording *mKick = nullptr;

    AAssetManager *mAssetManager = nullptr;
    Mixer mMixer;

    std::vector<bool> clapEvents = std::vector<bool>(kSteps, false);
    std::vector<bool> snareEvents = std::vector<bool>(kSteps, false);
    std::vector<bool> kickEvents = std::vector<bool>(kSteps, false);

    std::atomic<int> mCurrentFrame{0};
};


#endif //ZOPADRAMMACHINE_AUDIOENGINE_H
