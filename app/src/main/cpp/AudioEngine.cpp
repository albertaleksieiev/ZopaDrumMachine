//
// Created by Albert on 10/28/18.
//

#include "AudioEngine.h"
#include "../../../../../android/oboe/src/common/OboeDebug.h"



void AudioEngine::start() {

    oboe::AudioStreamBuilder builder;
    builder.setFormat(AudioFormat::I16);
    builder.setChannelCount(2);
    builder.setSampleRate(kSampleRateHz);
    builder.setCallback(this);
    builder.setPerformanceMode(PerformanceMode::LowLatency);
    builder.setSharingMode(SharingMode::Exclusive);

    this->mClap = SoundRecording::loadFromAssets(mAssetManager, "Clap.wav");
    this->mKick = SoundRecording::loadFromAssets(mAssetManager, "Kick.wav");
    this->mSnaire = SoundRecording::loadFromAssets(mAssetManager, "Snare.wav");




    Result result = builder.openStream(&mAudioStream);
    if (result != Result::OK){
        LOGE("Failed to open stream. Error: %s", convertToText(result));
    }

    // Reduce stream latency by setting the buffer size to a multiple of the burst size
    auto setBufferSizeResult = mAudioStream->setBufferSizeInFrames(
            mAudioStream->getFramesPerBurst() * kBufferSizeInBursts);
    if (setBufferSizeResult != Result::OK){
        LOGW("Failed to set buffer size. Error: %s", convertToText(setBufferSizeResult.error()));
    }

    result = mAudioStream->requestStart();
    if (result != Result::OK){
        LOGE("Failed to start stream. Error: %s", convertToText(result));
    }
}

DataCallbackResult AudioEngine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {
    if (mCurrentlyPlaying != nullptr) {
        mCurrentlyPlaying->renderAudio(static_cast<int16_t *>(audioData), numFrames);
    } else {
        mClap->renderAudio(static_cast<int16_t *>(audioData), numFrames); //
    }
    return DataCallbackResult::Continue;
}

void AudioEngine::playSound(int id) {
    if(id == 0) {
        mCurrentlyPlaying = mClap;
    } else if(id == 1) {
        mCurrentlyPlaying = mSnaire;
    } else if(id == 2) {
        mCurrentlyPlaying = mKick;
    }

    if (mCurrentlyPlaying != nullptr) {
        mCurrentlyPlaying->setPlaying(true);
    }


}

AudioEngine::AudioEngine(AAssetManager *mAssetManager) : mAssetManager(mAssetManager) {}
