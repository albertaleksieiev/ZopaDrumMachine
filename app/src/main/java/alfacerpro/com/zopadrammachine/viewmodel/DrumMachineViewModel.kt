package alfacerpro.com.zopadrammachine.viewmodel

import alfacerpro.com.zopadrammachine.DrumMachine
import alfacerpro.com.zopadrammachine.utils.DrumMachinePref
import alfacerpro.com.zopadrammachine.utils.DrumMachineSoundPattern
import android.arch.lifecycle.MutableLiveData
import android.arch.lifecycle.ViewModel
import android.content.Context
import kotlin.concurrent.thread

class DrumMachineViewModel : ViewModel() {
    val currentStep = MutableLiveData<Int>()
    val patternState = MutableLiveData<List<DrumMachineSoundPattern>>()
    var machine: DrumMachine? = null
    var stepCount = 16

    private var backgroundThread: Thread? = null

    fun onStart(context: Context) {
        machine = DrumMachine(context.assets)
        loadState()
        startBackgroundThread()
    }

    fun onStop() {
        saveState()
        backgroundThread?.interrupt()
        machine?.stop()
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
       // backgroundThread?.start()
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