//
// Created by Albert on 10/28/18.
//

#include "DrumMachine.h"
#include "../../../../../android/oboe/src/common/OboeDebug.h"


void DrumMachine::start() {

    oboe::AudioStreamBuilder builder;
    builder.setFormat(AudioFormat::I16);
    builder.setChannelCount(2);
    builder.setSampleRate(kSampleRateHz); //48k
    builder.setCallback(this);
    builder.setPerformanceMode(PerformanceMode::LowLatency);
    builder.setSharingMode(SharingMode::Exclusive);


    mClap = SoundRecording::loadFromAssets(mAssetManager, "Clap.wav");
    mKick = SoundRecording::loadFromAssets(mAssetManager, "Kick.wav");
    mSnaire = SoundRecording::loadFromAssets(mAssetManager, "Snare.wav");

    mMixer.addTrack(mClap);
    mMixer.addTrack(mKick);
    mMixer.addTrack(mSnaire);

    Result result = builder.openStream(&mAudioStream);
    if (result != Result::OK) {
        LOGE("Failed to open stream. Error: %s", convertToText(result));
    }

    LOGD("kickSize => %ld", kickEvents.size());

    // Reduce stream latency by setting the buffer size to a multiple of the burst size
    auto setBufferSizeResult = mAudioStream->setBufferSizeInFrames(
            mAudioStream->getFramesPerBurst() * kBufferSizeInBursts);
    if (setBufferSizeResult != Result::OK) {
        LOGW("Failed to set buffer size. Error: %s", convertToText(setBufferSizeResult.error()));
    }

    result = mAudioStream->requestStart();
    if (result != Result::OK) {
        LOGE("Failed to start stream. Error: %s", convertToText(result));
    }
}

DataCallbackResult DrumMachine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {
    auto begin = static_cast<int16_t *>(audioData);
    for (int i = 0; i < numFrames; ++i) {

        if (mCurrentFrame % kBeatMultiplier == 0) {
            auto step = mCurrentFrame / kBeatMultiplier;
            if (clapEvents[step]) {
                mClap->setPlaying(true);
            }
            if (snareEvents[step]) {
                mSnaire->setPlaying(true);
            }

            if (kickEvents[step]) {
                mKick->setPlaying(true);
            }
            auto t = numFrames - i;
            mMixer.renderAudio(begin + (kChannelCount * i), t);
            mCurrentFrame = (mCurrentFrame + t) % kMaxWindowHZ;
            break;
        } else {

            mMixer.renderAudio(begin + (kChannelCount * i), 1);
            mCurrentFrame = (mCurrentFrame + 1) % kMaxWindowHZ;
        }
    }

    return DataCallbackResult::Continue;
}

DrumMachine::DrumMachine(AAssetManager *mAssetManager) : mAssetManager(mAssetManager) {}

void DrumMachine::addPattern(int idSound, int patternIndex) {
    std::vector<bool> *patternBank = getPatternBank(idSound);

    if (patternBank != nullptr) {
        (*patternBank)[patternIndex] = true;
    }
}

void DrumMachine::removePattern(int idSound, int patternIndex) {
    std::vector<bool> *patternBank = getPatternBank(idSound);

    if (patternBank != nullptr) {
        (*patternBank)[patternIndex] = false;
    }
    std::vector<int> t(16, 1);
}


int DrumMachine::currentStep() {
    return mCurrentFrame / kBeatMultiplier;
}

std::vector<bool> *DrumMachine::getPatternBank(int idSound) {
    if (idSound == 0) {
        return &clapEvents;
    } else if (idSound == 1) {
        return &snareEvents;
    } else if (idSound == 2) {
        return &kickEvents;
    }
    return nullptr;
}

std::vector<int> DrumMachine::getPatternForSound(int idSound) {
    auto bank = getPatternBank(idSound);
    std::vector<int> pattern;

    for (int i = 0; i < bank->size(); ++i) {
        if ((*bank)[i]) {
            pattern.push_back(i);
        }
    }

    LOGD("Get pattern for idSound = %d, pattern = %s", idSound, toString(pattern).c_str());

    return pattern;
}

void DrumMachine::setPatternForSound(int idSound, std::vector<int> pattern) {
    LOGD("Set pattern for idSound = %d, pattern = %s", idSound, toString(pattern).c_str());
    auto bank = getPatternBank(idSound);

    // clear
    std::fill(bank->begin(), bank->end(), false);

    for (auto patternIndex: pattern) {
        (*bank)[patternIndex] = true;
    }
}

void DrumMachine::stop() {
    mAudioStream->requestStop();
}
