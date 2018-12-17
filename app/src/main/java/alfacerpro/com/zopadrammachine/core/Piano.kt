package alfacerpro.com.zopadrammachine.core

import android.content.res.AssetManager

class Piano {
    val nativePointer: Long // DO not rename this field

    private external fun init() : Long

    public external fun setNotes(notes: IntArray)


    init {
        nativePointer = init()
    }
}