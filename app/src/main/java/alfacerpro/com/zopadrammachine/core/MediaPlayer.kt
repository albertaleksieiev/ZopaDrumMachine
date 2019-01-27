package alfacerpro.com.zopadrammachine.core

import android.content.res.AssetManager

class MediaPlayer(assetManager: AssetManager) {
    val nativePointer: Long

    external fun getWaveform(): FloatArray?
    private external fun init(assetManager: AssetManager): Long
    external fun setProgress(progress: Float)
    external fun getProgress(): Float

    init {
        nativePointer = init(assetManager)
    }
}