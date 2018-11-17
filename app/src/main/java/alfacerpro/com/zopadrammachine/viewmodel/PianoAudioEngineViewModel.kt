package alfacerpro.com.zopadrammachine.viewmodel

import alfacerpro.com.zopadrammachine.core.AudioEngine
import alfacerpro.com.zopadrammachine.core.Piano
import android.content.Context

class PianoAudioEngineViewModel: AudioEngineViewModelBase() {
    var piano: Piano? = null

    override fun onCreate(context: Context) {
        piano = Piano()

        audioEngine.clearInstruments()
        audioEngine.addInstrument(piano!!.nativePointer)

        audioEngine.setIsPlaying(false)
        audioEngine.start()
    }

    override fun onStop() {
        super.onStop()
    }

    fun setNote(note: Int) {
        piano?.setNote(note)
    }
}