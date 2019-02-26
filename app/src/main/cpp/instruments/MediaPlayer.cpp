//
// Created by Albert on 1/27/19.
//

#include "MediaPlayer.h"


MediaPlayer::MediaPlayer(AAssetManager *mAssetManager) {
    audioTrack = SoundRecording::loadFromAssets(mAssetManager, "Media - Track_1.wav");
    audioTrack->enableFadeout = false;
    audioTrack->setPlaying(true);
    audioTrack->setLooping(true);
}

std::vector<float> MediaPlayer::getWaveform() {
    auto res = std::vector<float>();
    int binsCounts = 256;
    for (int i = 0; i < binsCounts; i++) {
        auto v = ((float) i / binsCounts) * this->audioTrack->mTotalFrames;

        auto freqs = getAnalyzedFrequencies(v, 8, 256);
        double sum = 0;
        for (auto f: freqs) {
            sum += f;
        }
        res.push_back(sum / freqs.size());
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

std::vector<float> MediaPlayer::getAnalyzedFrequencies() {
    return getAnalyzedFrequencies(this->audioTrack->mReadFrameIndex, 4, 128);
}

std::vector<float> MediaPlayer::getAnalyzedFrequencies(int readIndex, int maxFrames, int binsCount) {
    int i = readIndex;

    auto res = std::vector<float>(NUM_FREQ, 0);

    int steps = std::min(kSampleRateHz / NUM_FFT, maxFrames);
    if (i < 0) i = 0;

    for (int k = 0; k < steps; k++) {
        int16_t sampv[NUM_FFT];
        kiss_fft_cpx freqv[NUM_FREQ];

        int end = i + NUM_FFT;
        for (int j = 0; i < end && i < audioTrack->mTotalFrames && j < NUM_FFT; i++, j++) {
            sampv[j] = audioTrack->mData[i];
        }

        kiss_fftr(fft, sampv, freqv);

        for (int j = 0; j < res.size(); j++) {
            kiss_fft_cpx cpx = freqv[j];
            auto s = sqrt(cpx.r * cpx.r + cpx.i * cpx.i);
            res[j] += s;
        }
    }

    for (float &re : res) {
        re /= steps * 40;
        re = std::min(re, 1.f);
    }

    auto final_res = std::vector<float>(binsCount, 0);
    auto step = res.size() / final_res.size();
    for (int i = 0; i < final_res.size(); i++) {
        int cnt = 0;
        for (auto j = i * step; j < (i + 1) * step && j < res.size(); j++) {
            final_res[i] += res[j];
            cnt++;
        }

        if (cnt > 0) {
            final_res[i] /= cnt;
        }
    }

    return final_res;
}
