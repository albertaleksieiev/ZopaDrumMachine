/*
 * Copyright 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "SoundRecording.h"
#include "../../../../../../android/oboe/src/common/OboeDebug.h"

void SoundRecording::renderAudio(int16_t *targetData, int32_t numFrames) {
    if (mIsPlaying) {
        // LOGD("Current frame = %d, total max number of frames %d", mReadFrameIndex, mTotalFrames);
        // Check whether we're about to reach the end of the recording
        if (!mIsLooping && mReadFrameIndex + numFrames >= mTotalFrames) {
            numFrames = mTotalFrames - mReadFrameIndex;
            mIsPlaying = false;
        }

        auto pivotFactor = enableFadeout ? calculatePivotFactor() : 1.0f;

//        if(mReadFrameIndex % 4 == 0) {
//            LOGD("factor = %d, item = %ld of %ld", factor, mReadFrameIndex, mTotalFrames);
//        }

        for (int i = 0; i < numFrames; ++i) {
            for (int j = 0; j < kChannelCount; ++j) {
                targetData[(i * kChannelCount) + j] = mData[(mReadFrameIndex * kChannelCount) + j];
            }

            // Increment and handle wraparound
            if (++mReadFrameIndex >= mTotalFrames) mReadFrameIndex = 0;

            for (int j = 0; j < kChannelCount; ++j) {
                targetData[(i * kChannelCount) + j] *= pivotFactor;
            }
        }
    } else {
        // fill with zeros to output silence
        for (int i = 0; i < numFrames * kChannelCount; ++i) {
            targetData[i] = 0;
        }
    }

    //simpleDelay.renderAudio(targetData, numFrames);
}

SoundRecording *SoundRecording::loadFromAssets(AAssetManager *assetManager, const char *filename) {

    // Load the backing track
    AAsset *asset = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);

    if (asset == nullptr) {
        LOGE("Failed to open track, filename %s", filename);
        return nullptr;
    }

    // Get the length of the track (we assume it is stereo 48kHz)
    off_t trackLength = AAsset_getLength(asset);

    // Load it into memory
    auto *audioBuffer = static_cast<const int16_t *>(AAsset_getBuffer(asset));

    if (audioBuffer == nullptr) {
        LOGE("Could not get buffer for track");
        return nullptr;
    }

    // There are 4 bytes per frame because
    // each sample is 2 bytes and
    // it's a stereo recording which has 2 samples per frame.
    auto numFrames = static_cast<int32_t>(trackLength / 4);
    LOGD("Opened backing track, bytes: %ld frames: %d", trackLength, numFrames);
    return new SoundRecording(audioBuffer, numFrames);
}

float SoundRecording::calculatePivotFactor() {
    auto factor = (float) mReadFrameIndex / mTotalFrames; //0...1
    if (factor < pivotPerc) {
        factor = factor / pivotPerc;
    } else {
        factor = (1 - factor) / (1 - pivotPerc);
    }
    return std::min(factor, 0.95f);
}
