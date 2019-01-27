//
// Created by Albert on 1/27/19.
//

#ifndef ZOPADRAMMACHINE_MEDIAPLAYER_H
#define ZOPADRAMMACHINE_MEDIAPLAYER_H

#include <oboe/Oboe.h>
#include <vector>
#include "../google/SoundRecording.h"
#include "../google/Mixer.h"
#include "../effects/SimpleDelay.h"
#include "../const.h"
#include "../utils/kiss_fft.h"
#include "../../../../../../../android/oboe/src/common/OboeDebug.h"

const int fftN = 4096 * 4;

class MediaPlayer : public RenderableAudio {
public:
    MediaPlayer(AAssetManager *mAssetManager);

    std::vector<float> getWaveform();

    void renderAudio(int16_t *targetData, int32_t numFrames) override;
    void setProgress(float progress);
    float getProgress();


private:
    SoundRecording *audioTrack = nullptr;

    kiss_fft_cpx in[fftN], out[fftN];
    kiss_fft_cfg cfg = kiss_fft_alloc(fftN, 0/*is_inverse_fft*/, nullptr, nullptr);
};


#endif //ZOPADRAMMACHINE_MEDIAPLAYER_H
