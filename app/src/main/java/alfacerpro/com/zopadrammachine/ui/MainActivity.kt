package alfacerpro.com.zopadrammachine.ui

import alfacerpro.com.zopadrammachine.DrumMachine
import alfacerpro.com.zopadrammachine.R
import android.content.res.Resources
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.widget.CheckBox
import android.widget.LinearLayout
import android.widget.RadioButton
import kotlinx.android.synthetic.main.activity_main.*
import kotlin.concurrent.thread

val Int.dp: Int
    get() = (this / Resources.getSystem().displayMetrics.density).toInt()
val Int.px: Int
    get() = (this * Resources.getSystem().displayMetrics.density).toInt()

class MainActivity : AppCompatActivity() {
    var machine: DrumMachine? = null
    var counter = 0

    val tickers = 16

    val kickPatern = Array(16) { false }
    val snarePatern = Array(16) { false }
    val clapPatern = Array(16) { false }


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        System.loadLibrary("native-lib")

        initTickersView()


        initPatternView(DrumMachine.Sound.KICK)
        initPatternView(DrumMachine.Sound.SNARE)
        initPatternView(DrumMachine.Sound.CLAP)

        machine = DrumMachine(assets)


        start()
    }

    private fun initPatternView(sound: DrumMachine.Sound) {
        val ll = LinearLayout(this)

        ll.layoutParams = LinearLayout.LayoutParams(
            LinearLayout.LayoutParams.MATCH_PARENT,
            LinearLayout.LayoutParams.WRAP_CONTENT
        )
        ll.orientation = LinearLayout.HORIZONTAL


        for (i in 1..tickers) {
            val button = CheckBox(this)
            button.setPadding(4.px, 4.px, 4.px, 4.px)
            button.isChecked = false

            ll.addView(button)
            button.setOnCheckedChangeListener { buttonView, isChecked ->
                when (sound) {
                    DrumMachine.Sound.KICK -> kickPatern[i] = isChecked
                    DrumMachine.Sound.SNARE -> snarePatern[i] = isChecked
                    DrumMachine.Sound.CLAP -> clapPatern[i] = isChecked
                }
            }
        }
        patternsViews.addView(ll)
    }

    fun initTickersView() {
        tickersView.removeAllViews()

        for (i in 1..tickers) {
            val button = RadioButton(this)
            button.setPadding(4.px, 4.px, 4.px, 4.px)
            button.isChecked = false
            tickersView.addView(button)
        }
    }


    fun start() {
        val sleepTime = 1000 / 6
        var childs = tickersView.childCount
        thread {
            while (true) {
                counter = counter % tickers

                if (kickPatern[counter]) {
                    machine?.playSound(DrumMachine.Sound.KICK)
                }

                if (snarePatern[counter]) {
                    machine?.playSound(DrumMachine.Sound.SNARE)
                }

                if (clapPatern[counter]) {
                    machine?.playSound(DrumMachine.Sound.CLAP)
                }


                (tickersView.getChildAt((counter - 1) % childs) as? RadioButton)?.isChecked = false
                (tickersView.getChildAt(counter++) as? RadioButton)?.isChecked = true


                Thread.sleep(sleepTime.toLong())
            }
        }

    }

    fun clearTickers() {
        for (i in 0 until tickersView.childCount) {
            (tickersView.getChildAt(i) as? RadioButton)?.isChecked = false
        }
    }


    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {

        }
    }
}
