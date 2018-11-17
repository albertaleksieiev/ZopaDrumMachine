package alfacerpro.com.zopadrammachine.viewmodel

import alfacerpro.com.zopadrammachine.core.AudioEngine
import android.arch.lifecycle.MutableLiveData
import android.arch.lifecycle.ViewModel
import android.content.Context
import kotlin.concurrent.thread

abstract class AudioEngineViewModelBase : ViewModel() {
    private var backgroundStateThread: Thread? = null
    val state = MutableLiveData<AudioEngine.AAudioSteamState>()

    protected var audioEngine = AudioEngine()
    abstract fun onCreate(context: Context)

    open fun onStop() {
        backgroundStateThread?.interrupt()
    }

    private fun startBackgroundThread() {
        backgroundStateThread = thread {
            while (!Thread.interrupted()) {
                audioEngine.getState()?.let {
                    if (state.value == null || state.value != it) {
                        state.postValue(it)
                    }
                }
                try {
                    Thread.sleep(30)
                } catch (e: InterruptedException) {
                }
            }
        }
        backgroundStateThread?.priority = Thread.MIN_PRIORITY
    }

    fun pause() {
        audioEngine.pause()
    }

    fun resume() {
        audioEngine.resume()
    }

    fun setIsPlaying(playing: Boolean) {
        audioEngine.setIsPlaying(playing)
    }

    init {
        //startBackgroundThread()
    }
}