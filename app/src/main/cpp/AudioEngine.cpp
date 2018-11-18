//
// Created by Albert on 11/13/18.
//

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

        if (releaseDataPointerNext != -1 && releaseDataPointerUntil != -1) {
            if (releaseDataPointerNext == releaseDataPointerUntil) {
                releaseDataPointerNext = -1;
                releaseDataPointerUntil = -1;
                releaseDataPointer = 0;
            } else {
                for (int i = 0; i < numFrames && releaseDataPointerNext != releaseDataPointerUntil; i++) {
                    float factor
                    = (float)(releaseDataPointerNext > releaseDataPointerUntil ? releaseDataSize - releaseDataPointerNext + releaseDataPointerUntil : releaseDataPointerUntil - releaseDataPointerNext)
                            / (releaseDataSize);
                    begin[i] = releaseDataList[releaseDataPointerNext] * factor;

                    releaseDataPointerNext = (releaseDataPointerNext + 1) % releaseDataSize;
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
        for (int i = 0; i < numFrames; i++) {
            this->releaseDataList[releaseDataPointer] = begin[i];
            releaseDataPointer = (releaseDataPointer + 1) % releaseDataSize;
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
    skipAllFrames = !playing;

    releaseDataPointerUntil = (releaseDataPointer) % releaseDataSize;
    releaseDataPointerNext = (releaseDataPointerUntil + 1) % releaseDataSize;
}
