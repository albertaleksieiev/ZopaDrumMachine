//
// Created by Albert on 10/28/18.
//

#ifndef ZOPADRAMMACHINE_AUDIOENGINE_H
#define ZOPADRAMMACHINE_AUDIOENGINE_H
#include <oboe/Oboe.h>
#include "google/SoundRecording.h"


constexpr int kSampleRateHz = 48000; // Fixed sample rate, see README
constexpr int kBufferSizeInBursts = 2; // Use 2 bursts as the buffer size (double buffer)
constexpr int kMaxQueueItems = 4; // Must be power of 2



using namespace oboe;
class AudioEngine: public AudioStreamCallback {
public:
    AudioEngine(AAssetManager *mAssetManager);

    void start();
    void playSound(int id);
    DataCallbackResult onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

private:
    SoundRecording *mClap = nullptr;
    SoundRecording *mSnaire = nullptr;
    SoundRecording *mKick = nullptr;

    AAssetManager *mAssetManager = nullptr;


    AudioStream *mAudioStream = nullptr;

    SoundRecording *mCurrentlyPlaying = nullptr;
};


#endif //ZOPADRAMMACHINE_AUDIOENGINE_H
