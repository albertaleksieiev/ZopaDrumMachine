package alfacerpro.com.zopadrammachine.ui.view

import alfacerpro.com.zopadrammachine.utils.dp2Px
import android.app.Activity
import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.util.AttributeSet
import android.view.View
import java.util.*

class FrequencyView : View {
    private val paint: Paint
    val space = dp2Px(2f)

    private val maxFreqQueueSize = 45 // store the last n freqs for smooth animation
    private var frequencyQueue = ArrayDeque<ArrayList<Float>>()
    var frequencies = ArrayList<Float>()
        @Synchronized set(value) {
            if (!frequencyQueue.isEmpty() && frequencyQueue.last.size != value.size) {
                frequencyQueue.clear() // new number of bins
            }

            frequencyQueue.add(value)

            if (frequencyQueue.size > maxFreqQueueSize) {
                frequencyQueue.pop()
            }

            val newFrequencies = ArrayList(FloatArray(value.size) { 0f }.asList())

            for (arr in frequencyQueue) {
                for (i in 0 until newFrequencies.size) {
                    newFrequencies[i] += arr[i]
                }
            }

            for (i in 0 until newFrequencies.size) {
                newFrequencies[i] = newFrequencies[i] / frequencyQueue.size
            }

            field = newFrequencies

            (context as? Activity)?.runOnUiThread {
                invalidateChart()
                invalidate()
            }
        }

    private var frequenciesToDraw = ArrayList<Int>()

    init {
        paint = Paint()
        paint.isAntiAlias = true
        paint.strokeWidth = dp2Px(8).toFloat()
        paint.color = Color.BLACK
        paint.style = Paint.Style.FILL
        paint.strokeCap = Paint.Cap.ROUND
    }

    constructor(context: Context) : this(context, null)
    constructor(context: Context, attrs: AttributeSet?) : this(context, attrs, 0)

    constructor(context: Context, attrs: AttributeSet?, defStyleAttr: Int) : super(context, attrs, defStyleAttr) {}

    override fun onMeasure(widthMeasureSpec: Int, heightMeasureSpec: Int) {
        super.onMeasure(widthMeasureSpec, widthMeasureSpec)
    }

    override fun onSizeChanged(width: Int, height: Int, oldw: Int, oldh: Int) {
        super.onSizeChanged(width, height, oldw, oldh)
        invalidateChart(width, height)
    }

    fun invalidateChart(width: Int = getWidth(), height: Int = getHeight()) {
        val currentFrequenciesToDraw = ArrayList<Int>()
        val step = (paint.strokeWidth + space).toInt()

        if (width == 0) {
            return
        }


        val w = width.toFloat()

        for (i in 0..width step step) {
            if (i == 0) {
                continue // skip first bin
            }

            val lowerBoundFactor = i / w
            val upperBoundFactor = (i + step) / w

            val lowerIndex = (frequencies.size * lowerBoundFactor).toInt()
            val upperIndex = (frequencies.size * upperBoundFactor).toInt()

            var sum = 0f
            var count = 0
            for (index in lowerIndex..upperIndex) {
                if (index >= frequencies.size) {
                    break
                }


                sum += frequencies[index]
                count++
            }

            if (count > 0) {
                currentFrequenciesToDraw.add(((sum / count) * height).toInt())
            } else {
                currentFrequenciesToDraw.add(0)
            }
        }

        frequenciesToDraw = currentFrequenciesToDraw
    }

    override fun onDraw(canvas: Canvas?) {
        super.onDraw(canvas)

        val step = (paint.strokeWidth + space).toInt()
        var counter = 0
        for (x in step..width step step) {
            frequenciesToDraw.getOrNull(counter++)?.let { yEnd ->
                canvas?.drawLine(x.toFloat(), 0f, x.toFloat(), yEnd.toFloat(), paint)
            }
        }
    }
}
