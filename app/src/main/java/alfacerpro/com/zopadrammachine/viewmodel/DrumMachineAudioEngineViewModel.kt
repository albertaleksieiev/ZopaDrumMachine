package alfacerpro.com.zopadrammachine.viewmodel

import alfacerpro.com.zopadrammachine.core.AudioEngine
import alfacerpro.com.zopadrammachine.core.DrumMachine
import alfacerpro.com.zopadrammachine.utils.DrumMachinePref
import alfacerpro.com.zopadrammachine.utils.DrumMachineSoundPattern
import android.arch.lifecycle.MutableLiveData
import android.content.Context
import kotlin.concurrent.thread

class DrumMachineAudioEngineViewModel : AudioEngineViewModelBase() {

    val currentStep = MutableLiveData<Int>()
    val patternState = MutableLiveData<List<DrumMachineSoundPattern>>()
    var machine: DrumMachine? = null
    var stepCount = 16

    private var backgroundThread: Thread? = null

    override  fun onCreate(context: Context) {
        machine = DrumMachine(context.assets)

        audioEngine.clearInstruments()
        audioEngine.addInstrument(machine!!.nativePointer)
        audioEngine.start()
        loadState()
        startBackgroundThread()
    }

    override fun onStop() {
        super.onStop()

        saveState()
        backgroundThread?.interrupt()
        audioEngine.stop()
    }

    private fun startBackgroundThread() {
        backgroundThread = thread {
            while (!Thread.interrupted()) {
                machine?.currentStep().let {
                    currentStep.postValue(it)
                }
                try {
                    Thread.sleep(100)
                } catch (e: InterruptedException) { }
            }
        }
    }

    private fun getCurrentMachineState(): ArrayList<DrumMachineSoundPattern> {
        val newPattern = ArrayList<DrumMachineSoundPattern>()
        machine?.let {
            for (sound in DrumMachine.Sound.values()) {
                newPattern.add(DrumMachineSoundPattern(sound, it.getPatternForSound(sound.id) ?: IntArray(0)))
            }
        }
        return newPattern
    }

    private fun saveState() {
        DrumMachinePref.patterns = getCurrentMachineState()
    }

    private fun loadState() {
        val patterns = DrumMachinePref.patterns

        for (pattern in patterns) {
            machine?.setPatternForSound(pattern.sound.id, pattern.pattern)
        }

        patternState.postValue(getCurrentMachineState())
    }
}