package alfacerpro.com.zopadrammachine.ui

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import alfacerpro.com.zopadrammachine.R
import alfacerpro.com.zopadrammachine.core.DrumMachine
import android.content.Intent
import kotlinx.android.synthetic.main.activity_launch.*

class LaunchActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_launch)

        buttonDrumMachine.setOnClickListener {
            startActivity(Intent(this, DrumMachineActivity::class.java))
        }
        buttonMediaPlayer.setOnClickListener {
            startActivity(Intent(this, MediaPlayerActivity::class.java))
        }
        buttonPiano.setOnClickListener {
            startActivity(Intent(this, PianoActivity::class.java))
        }
        buttonWaveform.setOnClickListener {
            startActivity(Intent(this, WaveformActivity::class.java))
        }
    }
}
