package alfacerpro.com.zopadrammachine.utils

import alfacerpro.com.zopadrammachine.DrumMachine
import com.chibatching.kotpref.KotprefModel
import com.chibatching.kotpref.gsonpref.gsonPref

object DrumMachinePref : KotprefModel() {
    var patterns: List<DrumMachineSoundPattern> by gsonPref(emptyList())
}

data class DrumMachineSoundPattern(var sound: DrumMachine.Sound, var pattern: IntArray) {}