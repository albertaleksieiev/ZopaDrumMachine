//
// Created by Albert on 11/13/18.
//

#ifndef ZOPADRAMMACHINE_AUDIOENGINE_H
#define ZOPADRAMMACHINE_AUDIOENGINE_H
#include <oboe/Oboe.h>
#include <vector>
#include <google/RenderableAudio.h>

#include <oboe/Oboe.h>
#include <vector>
#include <array>
#include "google/Mixer.h"
#include "effects/SimpleDelay.h"
#include "const.h"
#include "../../../../../android/oboe/src/common/OboeDebug.h"
using namespace oboe;

class AudioEngine : public AudioStreamCallback {
public:
    AudioEngine() {
        releaseDataList = new int16_t[releaseDataSize];
    }
    void start();
    void pause();
    void stop();
    aaudio_stream_state_t getState();
    std::vector<RenderableAudio*> renderableAudios;

    DataCallbackResult onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

    void resume();

    void setIsPlaying(bool i);

private:
    int release = 200; //300 ms
    int releaseDataSize = static_cast<int>((double)release / 1000 * kSampleRateHz);
    int releaseDataPointer = 0;
    int releaseDataPointerNext = -1;
    int releaseDataPointerUntil = -1; // after release we use this pointer


    int16_t* releaseDataList;
    bool skipAllFrames = false;//if false we will skip all frames


    AudioStream *audioStream = nullptr;


    void fillEmptyData(int16_t *audioData, int32_t numFrames);

};


#endif //ZOPADRAMMACHINE_AUDIOENGINE_H
