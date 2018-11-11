package alfacerpro.com.zopadrammachine.utils

import alfacerpro.com.zopadrammachine.DrumMachine
import com.chibatching.kotpref.KotprefModel
import com.chibatching.kotpref.gsonpref.gsonPref

object DrumMachinePref : KotprefModel() {
    /*
                     Default pattern
     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
    {0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1}); Clap
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0}); Snare
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}); Kick
    */
    var patterns: List<DrumMachineSoundPattern> by gsonPref(
        arrayListOf(
            DrumMachineSoundPattern(DrumMachine.Sound.KICK, intArrayOf(0, 2, 4, 6, 8, 10, 12, 14)),
            DrumMachineSoundPattern(DrumMachine.Sound.SNARE, intArrayOf(2, 6, 10, 11, 13, 14)),
            DrumMachineSoundPattern(DrumMachine.Sound.CLAP, intArrayOf(3, 4, 7, 8, 11, 12, 13, 15))
        )
    )
}

data class DrumMachineSoundPattern(var sound: DrumMachine.Sound, var pattern: IntArray)