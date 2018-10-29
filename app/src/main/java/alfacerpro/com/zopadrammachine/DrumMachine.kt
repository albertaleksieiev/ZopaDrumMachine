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


    public external fun playSound(id: Int)
    private external fun onCreate(assetManager: AssetManager)

    init {
        onCreate(assetManager)
    }
}