//
// Created by Albert on 10/28/18.
//

#ifndef ZOPADRAMMACHINE_AUDIOENGINE_H
#define ZOPADRAMMACHINE_AUDIOENGINE_H

#include <oboe/Oboe.h>
#include <vector>
#include "google/SoundRecording.h"
#include "google/Mixer.h"
#include "effects/SimpleDelay.h"

#include "const.h"


constexpr int kBeatMultiplier = static_cast<const int>((float) kSampleRateHz / (BPM / 60.0));
constexpr int kMaxWindowHZ = kBeatMultiplier * 16;

using namespace oboe;

class DrumMachine : public AudioStreamCallback {
public:
    DrumMachine(AAssetManager *mAssetManager);

    void start();

    void stop();

    void addPattern(int idSound, int patternIndex);

    void removePattern(int idSound, int patternIndex);

    std::vector<int> getPatternForSound(int idSound);

    void setPatternForSound(int idSound, std::vector<int> pattern);

    int currentStep();

    DataCallbackResult onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

private:
    std::vector<bool> *getPatternBank(int idSound);

    SoundRecording *mClap = nullptr;
    SoundRecording *mSnaire = nullptr;
    SoundRecording *mKick = nullptr;

    AAssetManager *mAssetManager = nullptr;
    Mixer mMixer;

    AudioStream *mAudioStream = nullptr;

    //                                                   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
    std::vector<bool> clapEvents = makeVector((bool[])  {0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1});
    std::vector<bool> snareEvents = makeVector((bool[]) {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0});
    std::vector<bool> kickEvents = makeVector((bool[])  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0});

    //std::vector<bool> clapEvents = std::vector<bool>(kSteps, false);
    //std::vector<bool> snareEvents = std::vector<bool>(kSteps, false);
    //std::vector<bool> kickEvents = std::vector<bool>(kSteps, false);


    std::atomic<int> mCurrentFrame{0};
};


#endif //ZOPADRAMMACHINE_AUDIOENGINE_H
