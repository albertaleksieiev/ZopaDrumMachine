package alfacerpro.com.zopadrammachine

import android.app.Application
import com.chibatching.kotpref.Kotpref
import com.chibatching.kotpref.gsonpref.gson
import com.google.gson.Gson

class App: Application() {
    override fun onCreate() {
        super.onCreate()
        Kotpref.init(applicationContext)
        Kotpref.gson = Gson()

        Utils.loadLibrary()
    }
}