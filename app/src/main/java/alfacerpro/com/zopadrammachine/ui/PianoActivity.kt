package alfacerpro.com.zopadrammachine.ui

import alfacerpro.com.zopadrammachine.R
import alfacerpro.com.zopadrammachine.Utils
import alfacerpro.com.zopadrammachine.ui.view.PianoKeyboardView
import alfacerpro.com.zopadrammachine.viewmodel.PianoAudioEngineViewModel
import android.arch.lifecycle.Observer
import android.arch.lifecycle.ViewModelProviders
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import kotlinx.android.synthetic.main.activity_piano.*

class PianoActivity : AppCompatActivity() {
    private val viewModel: PianoAudioEngineViewModel by lazy {
        ViewModelProviders.of(this).get(PianoAudioEngineViewModel::class.java)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_piano)
        Utils.loadLibrary()

        viewModel.state.observe(this, Observer { state ->
            Log.d("PianoActivity", "State changed to $state")
        })

        viewModel.onCreate(this)

        pianoKeyboard.onTouchEvents = object : PianoKeyboardView.OnTouchEvents {
            override fun onNoteTouchUp() {
                viewModel.setIsPlaying(false)
            }

            override fun onNoteTouchDown(note: Int) {
                viewModel.setIsPlaying(true)
                viewModel.setNote(note)
            }
        }
    }

    override fun onStop() {
        super.onStop()
        viewModel.onStop()
    }
}
