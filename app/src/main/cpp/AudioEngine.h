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
#include "google/Mixer.h"
#include "effects/SimpleDelay.h"
#include "const.h"
#include "../../../../../android/oboe/src/common/OboeDebug.h"
using namespace oboe;

class AudioEngine : public AudioStreamCallback {
public:
    void start();
    void pause();
    void stop();
    aaudio_stream_state_t getState();
    std::vector<RenderableAudio*> renderableAudios;

    DataCallbackResult onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

    void resume();

    void setIsPlaying(bool i);

private:

    AudioStream *audioStream = nullptr;

    void fillEmptyData(int16_t *audioData, int32_t numFrames);

    bool skipAllFrames = false;//if false we will skip all frames
};


#endif //ZOPADRAMMACHINE_AUDIOENGINE_H
