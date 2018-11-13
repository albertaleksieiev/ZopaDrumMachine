package alfacerpro.com.zopadrammachine.core

import android.content.res.AssetManager

class SimpleOscillator {
    val nativePointer: Long // DO not rename this field
    private external fun init(): Long

    init {
        this.nativePointer = init()
    }
}