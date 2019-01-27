//
// Created by Albert on 1/27/19.
//

#include "MediaPlayer.h"


MediaPlayer::MediaPlayer(AAssetManager *mAssetManager) {
    audioTrack = SoundRecording::loadFromAssets(mAssetManager, "Media - Track.wav");
    audioTrack->setPlaying(true);
}

std::vector<float> MediaPlayer::getWaveform() {
    int totalFrames = audioTrack->mTotalFrames;
    int stepCount = totalFrames / fftN;

    auto res = std::vector<float>();


    for (int step = 0; step < stepCount; step++) {

        int j = 0;
        for (int curFrame = step * fftN; curFrame < fftN * (step + 1)
                                         && curFrame < audioTrack->mTotalFrames
                                         && j < fftN; curFrame++) {
            auto v = audioTrack->mData[curFrame];
            in[j].r = v / 32768.0f;
            in[j].i = 0;
        }

        kiss_fft(cfg, in, out);

        float sum = 0;
        for (int i = 0; i < fftN; i++) {
            sum += sqrt(pow(out[i].r, 2) + pow(out[i].i, 2));
        }

        res.push_back(sum / fftN);
    }
    return res;
}

void MediaPlayer::renderAudio(int16_t *targetData, int32_t numFrames) {
    audioTrack->renderAudio(targetData, numFrames);
}

void MediaPlayer::setProgress(float progress) {
    audioTrack->mReadFrameIndex = static_cast<int32_t>(audioTrack->mTotalFrames * progress);
}

float MediaPlayer::getProgress() {
    if (audioTrack->mTotalFrames == 0) {
        return 0;
    }

    return (float) audioTrack->mReadFrameIndex / audioTrack->mTotalFrames;
}
