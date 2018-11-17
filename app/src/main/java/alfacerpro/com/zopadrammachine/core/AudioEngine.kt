package alfacerpro.com.zopadrammachine.core

class AudioEngine {
    /*
   AAUDIO_STREAM_STATE_UNINITIALIZED = 0,
   AAUDIO_STREAM_STATE_UNKNOWN,
   AAUDIO_STREAM_STATE_OPEN,
   AAUDIO_STREAM_STATE_STARTING,
   AAUDIO_STREAM_STATE_STARTED,
   AAUDIO_STREAM_STATE_PAUSING,
   AAUDIO_STREAM_STATE_PAUSED,
   AAUDIO_STREAM_STATE_FLUSHING,
   AAUDIO_STREAM_STATE_FLUSHED,
   AAUDIO_STREAM_STATE_STOPPING,
   AAUDIO_STREAM_STATE_STOPPED,
   AAUDIO_STREAM_STATE_CLOSING,
   AAUDIO_STREAM_STATE_CLOSED,
   AAUDIO_STREAM_STATE_DISCONNECTED
    */
    enum class AAudioSteamState(val state: Int) {
        AAUDIO_STREAM_STATE_UNINITIALIZED(0),
        AAUDIO_STREAM_STATE_UNKNOWN(1),
        AAUDIO_STREAM_STATE_OPEN(2),
        AAUDIO_STREAM_STATE_STARTING(3),
        AAUDIO_STREAM_STATE_STARTED(4),
        AAUDIO_STREAM_STATE_PAUSING(5),
        AAUDIO_STREAM_STATE_PAUSED(6),
        AAUDIO_STREAM_STATE_FLUSHING(7),
        AAUDIO_STREAM_STATE_FLUSHED(8),
        AAUDIO_STREAM_STATE_STOPPING(9),
        AAUDIO_STREAM_STATE_STOPPED(10),
        AAUDIO_STREAM_STATE_CLOSING(11),
        AAUDIO_STREAM_STATE_CLOSED(12),
        AAUDIO_STREAM_STATE_DISCONNECTED(13);

        companion object {
            private val map = AAudioSteamState.values().associateBy(AAudioSteamState::state)
            fun valueOf(type: Int) = map[type]
        }
    }

    external fun start()
    external fun stop()
    external fun pause()
    external fun resume()
    private external fun getOboeAudioStreamState(): Int
    fun getState(): AAudioSteamState? {
        return AAudioSteamState.valueOf(getOboeAudioStreamState())
    }

    external fun addInstrument(nativePointer: Long)
    external fun clearInstruments()
    external fun setIsPlaying(playing: Boolean)
}