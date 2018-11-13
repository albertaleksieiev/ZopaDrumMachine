package alfacerpro.com.zopadrammachine.core

class AudioEngine {
    external fun start()
    external fun stop()
    external fun addInstrument(nativePointer: Long)
    external fun clearInstruments()
}