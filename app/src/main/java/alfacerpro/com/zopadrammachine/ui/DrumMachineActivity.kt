package alfacerpro.com.zopadrammachine.ui

import alfacerpro.com.zopadrammachine.core.DrumMachine
import alfacerpro.com.zopadrammachine.R
import alfacerpro.com.zopadrammachine.Utils
import alfacerpro.com.zopadrammachine.viewmodel.DrumMachineAudioEngineViewModel
import android.arch.lifecycle.Observer
import android.arch.lifecycle.ViewModelProviders
import android.content.res.Resources
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.view.ViewGroup
import android.widget.CheckBox
import android.widget.LinearLayout
import android.widget.RadioButton
import kotlinx.android.synthetic.main.activity_main.*

val Int.px: Int
    get() = (this * Resources.getSystem().displayMetrics.density).toInt()

class DrumMachineActivity : AppCompatActivity() {
    private val viewModel: DrumMachineAudioEngineViewModel by lazy {
        ViewModelProviders.of(this).get(DrumMachineAudioEngineViewModel::class.java)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        Utils.loadLibrary()

        initTickersView()

        initPatternView(DrumMachine.Sound.KICK)
        initPatternView(DrumMachine.Sound.SNARE)
        initPatternView(DrumMachine.Sound.CLAP)

        viewModel.onCreate(this)
        viewModel.currentStep.observe(this, Observer { step ->
            step?.let {
                val childs = tickersView.childCount
                (tickersView.getChildAt((step - 1) % childs) as? RadioButton)?.isChecked = false
                (tickersView.getChildAt(step) as? RadioButton)?.isChecked = true
            }
        })
        viewModel.patternState.observe(this, Observer { stepState ->
            stepState?.forEach { setPattern(it.sound, it.pattern) }
        })
    }

    override fun onStop() {
        super.onStop()
        viewModel.onStop()
    }

    private fun setPattern(sound: DrumMachine.Sound, pattern: IntArray ) {
        patternsViews.findViewWithTag<ViewGroup>(sound)?.let {
            for (patternIndex in pattern) {
                (it.getChildAt(patternIndex) as CheckBox).isChecked = true
            }
        }
    }

    private fun initPatternView(sound: DrumMachine.Sound) {
        val ll = LinearLayout(this)
        ll.tag = sound

        ll.layoutParams = LinearLayout.LayoutParams(
            LinearLayout.LayoutParams.MATCH_PARENT,
            LinearLayout.LayoutParams.WRAP_CONTENT
        )
        ll.orientation = LinearLayout.HORIZONTAL

        for (i in 0 until viewModel.stepCount) {
            val button = CheckBox(this)
            button.setPadding(4.px, 4.px, 4.px, 4.px)
            button.isChecked = false

            ll.addView(button)
            button.setOnCheckedChangeListener { _, isChecked ->
                if (isChecked) {
                    viewModel.machine?.addPattern(sound.id, i)
                } else {
                    viewModel.machine?.removePattern(sound.id, i)
                }
            }
        }
        patternsViews.addView(ll)
    }

    fun initTickersView() {
        tickersView.removeAllViews()

        for (i in 1..viewModel.stepCount) {
            val button = RadioButton(this)
            button.setPadding(4.px, 4.px, 4.px, 4.px)
            button.isChecked = false
            tickersView.addView(button)
        }
    }
}
