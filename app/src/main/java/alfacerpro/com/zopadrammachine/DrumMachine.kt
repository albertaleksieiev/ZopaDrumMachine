package alfacerpro.com.zopadrammachine

import android.content.res.AssetManager

class DrumMachine(assetManager: AssetManager) {
    enum class Sound(val id: Int) {
        CLAP(0),
        SNARE(1),
        KICK(2)
    }

    fun playSound(sound: Sound) {
        this.playSound(sound.id)
    }

    public external fun getPatternForSound(id: Int): IntArray?
    public external fun playSound(id: Int)
    public external fun addPattern(id: Int, patternIndex: Int)
    public external fun removePattern(id: Int, patternIndex: Int)
    public external fun setPatternForSound(id: Int, pattern: IntArray)
    public external fun currentStep(): Int
    public external fun stop()

    private external fun onCreate(assetManager: AssetManager)

    init {
        onCreate(assetManager)
    }
}