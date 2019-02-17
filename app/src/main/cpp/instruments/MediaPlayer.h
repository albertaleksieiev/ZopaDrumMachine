//
// Created by Albert on 1/27/19.
//

#ifndef ZOPADRAMMACHINE_MEDIAPLAYER_H
#define ZOPADRAMMACHINE_MEDIAPLAYER_H

#include <oboe/Oboe.h>
#include <vector>
#include <cmath>
#include "../google/SoundRecording.h"
#include "../google/Mixer.h"
#include "../effects/SimpleDelay.h"
#include "../const.h"
#include "../utils/kiss_fftr.h"
#include "../../../../../../../android/oboe/src/common/OboeDebug.h"

#define NUM_FFT 2048
#define NUM_FREQ (((NUM_FFT)/2)+1)

class MediaPlayer : public RenderableAudio {
public:
    MediaPlayer(AAssetManager *mAssetManager);

    std::vector<float> getWaveform();

    void renderAudio(int16_t *targetData, int32_t numFrames) override;
    void setProgress(float progress);
    float getProgress();


    std::vector<float> getAnalyzedFrequencies();
    SoundRecording *audioTrack = nullptr;
private:

    std::vector<float> getAnalyzedFrequencies(int readIndex, int maxFrames, int binsCount);
    kiss_fftr_cfg fft = kiss_fftr_alloc(NUM_FFT, 0, 0, 0);
};


#endif //ZOPADRAMMACHINE_MEDIAPLAYER_H
