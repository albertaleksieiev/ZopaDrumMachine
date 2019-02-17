package alfacerpro.com.zopadrammachine.ui

import alfacerpro.com.zopadrammachine.R
import alfacerpro.com.zopadrammachine.Utils
import alfacerpro.com.zopadrammachine.core.AudioEngine
import alfacerpro.com.zopadrammachine.core.MediaPlayer
import alfacerpro.com.zopadrammachine.ui.view.WaveformPlaybackView
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_media_player.*
import kotlin.concurrent.thread


class WaveformActivity : AppCompatActivity() {


    var mediaPlayer: MediaPlayer? = null
    var audioEngine: AudioEngine? = null
    private var backgroundThread: Thread? = null


    private fun startBackgroundThread() {
        backgroundThread = thread {
            while (!Thread.interrupted()) {
                try {
                    Thread.sleep(350)
                } catch (e: InterruptedException) {
                }

                mediaPlayer?.getProgress()?.let {
                    runOnUiThread { waveformController.progress = it }
                }
            }
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_waveform)

        Utils.loadLibrary()

        audioEngine = AudioEngine()
        mediaPlayer = MediaPlayer(assets)
        audioEngine?.setIsAttackReleaseEnabled(false)

        mediaPlayer?.let {
            audioEngine?.addInstrument(it.nativePointer)
        }


        waveformController.progressChangeListener = object : WaveformPlaybackView.OnProgressChangeListener {
            override fun progressChanged(progress: Float) {
                mediaPlayer?.setProgress(progress)
                audioEngine?.setIsPlaying(true)
            }
        }
        Toast.makeText(this, "Touch to play an audio", Toast.LENGTH_LONG)
            .show()
    }

    override fun onStart() {
        super.onStart()
        audioEngine?.setIsPlaying(false) // disable auto play
        audioEngine?.start()
        startBackgroundThread()

        mediaPlayer?.getWaveform()?.let { waveform ->
            waveformController.points = ArrayList(waveform.toList())
        }
    }

    override fun onStop() {
        super.onStop()

        backgroundThread?.interrupt()
        audioEngine?.stop()
    }
}
