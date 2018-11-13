//
// Created by Albert on 10/28/18.
//

#include "DrumMachine.h"

DrumMachine::DrumMachine(AAssetManager *mAssetManager) : mAssetManager(mAssetManager) {
    mClap = SoundRecording::loadFromAssets(mAssetManager, "Clap.wav");
    mKick = SoundRecording::loadFromAssets(mAssetManager, "Kick.wav");
    mSnaire = SoundRecording::loadFromAssets(mAssetManager, "Snare.wav");

    mMixer.addTrack(mClap);
    mMixer.addTrack(mKick);
    mMixer.addTrack(mSnaire);
}

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

void DrumMachine::renderAudio(int16_t *targetData, int32_t numFrames) {
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
            mMixer.renderAudio(targetData + (kChannelCount * i), t);
            mCurrentFrame = (mCurrentFrame + t) % kMaxWindowHZ;
            break;
        } else {
            mMixer.renderAudio(targetData + (kChannelCount * i), 1);
            mCurrentFrame = (mCurrentFrame + 1) % kMaxWindowHZ;
        }
    }
}
