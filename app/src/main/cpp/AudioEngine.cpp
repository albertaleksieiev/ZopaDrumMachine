//
// Created by Albert on 11/13/18.
//

#include <instruments/MediaPlayer.h>
#include "AudioEngine.h"

void AudioEngine::start() {
    oboe::AudioStreamBuilder builder;
    builder.setFormat(AudioFormat::I16);
    builder.setChannelCount(2);
    builder.setSampleRate(kSampleRateHz); //48k
    builder.setCallback(this);
    builder.setPerformanceMode(PerformanceMode::LowLatency);
    builder.setSharingMode(SharingMode::Exclusive);

    Result result = builder.openStream(&audioStream);
    if (result != Result::OK) {
        LOGE("Failed to open stream. Error: %s", convertToText(result));
    }

    // Reduce stream latency by setting the buffer size to a multiple of the burst size
    auto setBufferSizeResult = audioStream->setBufferSizeInFrames(
            audioStream->getFramesPerBurst() * kBufferSizeInBursts);
    if (setBufferSizeResult != Result::OK) {
        LOGW("Failed to set buffer size. Error: %s", convertToText(setBufferSizeResult.error()));
    }

    result = audioStream->requestStart();
    if (result != Result::OK) {
        LOGE("Failed to start stream. Error: %s", convertToText(result));
    }
}

void AudioEngine::stop() {
    audioStream->requestStop();
}

DataCallbackResult AudioEngine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {
    auto begin = static_cast<int16_t *>(audioData);
    if (skipAllFrames) {
        fillEmptyData(begin, numFrames);

        if (releaseFramesCounter >= releaseFrames) {
            releaseFramesCounter = -1;
        } else if (releaseFramesCounter >= 0 && attackAndReleaseEnabled) {
            for (auto renderableAudio: renderableAudios) {
                renderableAudio->renderAudio(begin, numFrames);
            }

            float factor = ((float) releaseFrames - releaseFramesCounter) / releaseFrames;
            for (int i = 0; i < numFrames && releaseFramesCounter <= releaseFrames; ++i, ++releaseFramesCounter) {
                for (int j = 0; j < kChannelCount; j++) {
                    begin[i * kChannelCount + j] *= factor;
                }
            }
        }


        return DataCallbackResult::Continue;
    }


    if (this->renderableAudios.empty()) {
        fillEmptyData(begin, numFrames);
    } else {
        for (auto renderableAudio: renderableAudios) {
            renderableAudio->renderAudio(begin, numFrames);
        }


        if (attackFramesCounter != -1 && attackAndReleaseEnabled) {
            if (attackFramesCounter >= attackFrames) {
                attackFramesCounter = -1;
            } else {
                float factor = ((float) attackFramesCounter) / attackFrames;
                for (int i = 0; i < numFrames && attackFramesCounter <= attackFrames; ++i, ++attackFramesCounter) {
                    for (int j = 0; j < kChannelCount; j++) {
                        begin[i * kChannelCount + j] *= factor;
                    }
                }
            }
        }
    }

    return DataCallbackResult::Continue;
}

void AudioEngine::fillEmptyData(int16_t *audioData, int32_t numFrames) {
    for (int i = 0; i < numFrames * kChannelCount; i++) {
        audioData[i] = 0;
    }
}

void AudioEngine::pause() {
    audioStream->requestPause();
}

int AudioEngine::getState() {
    return static_cast<aaudio_stream_state_t>(audioStream->getState());
}

void AudioEngine::resume() {
    // TODO add checks
    audioStream->requestStart();
}

void AudioEngine::setIsPlaying(bool playing) {
    if (this->skipAllFrames && playing) {
        attackFramesCounter = 0;
    }

    if (!this->skipAllFrames && !playing) {
        releaseFramesCounter = 0;
    }

    skipAllFrames = !playing;

}

void AudioEngine::setIsAttackReleaseEnabled(jboolean enabled) {
    this->attackAndReleaseEnabled = enabled;
}
