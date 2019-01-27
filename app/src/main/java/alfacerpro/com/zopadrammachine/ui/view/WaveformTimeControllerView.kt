package alfacerpro.com.zopadrammachine.ui.view

import alfacerpro.com.zopadrammachine.utils.dp2Px
import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.util.AttributeSet
import android.view.MotionEvent
import android.view.View
import java.util.*

class WaveformTimeControllerView : View {
    interface OnProgressChangeListener {
        fun progressChanged(progress: Float)
    }

    private val paint: Paint
    private val paintDone: Paint

    val stepPx = dp2Px(3)
    val spaceBeetweenStepsPx = dp2Px(1.5f)
    var progress = 0.7f // 0...1
        set(value) {
            field = value
            invalidate()
        }

    var horizontalLinesCount: Int = 0
    var pointStep: Int = 0
    var progressChangeListener: OnProgressChangeListener? = null
    var points = ArrayList<Float>()

    constructor(context: Context) : this(context, null)
    constructor(context: Context, attrs: AttributeSet?) : this(context, attrs, 0)

    constructor(context: Context, attrs: AttributeSet?, defStyleAttr: Int) : super(context, attrs, defStyleAttr) {}

    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        super.onSizeChanged(w, h, oldw, oldh)

        horizontalLinesCount = (w.toFloat() / (stepPx + spaceBeetweenStepsPx)).toInt()
        pointStep = Math.max(points.count() / horizontalLinesCount, 1)

        if (pointStep > points.size) {
            pointStep = 0
        }
    }

    init {
        paint = Paint()
        paint.isAntiAlias = true
        paint.strokeWidth = stepPx.toFloat()
        paint.color = Color.GRAY
        paint.style = Paint.Style.FILL
        paint.strokeCap = Paint.Cap.ROUND

        paintDone = Paint()
        paintDone.isAntiAlias = true
        paintDone.strokeWidth = stepPx.toFloat()
        paintDone.color = Color.BLACK
        paintDone.style = Paint.Style.FILL
        paintDone.strokeCap = Paint.Cap.ROUND
    }

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        if (event == null) {
            return super.onTouchEvent(event)
        }

        progressChangeListener?.progressChanged(event.x / width)

        return true
    }

    override fun onDraw(canvas: Canvas?) {
        super.onDraw(canvas)

        val canvas = canvas ?: return

        val midX = height / 2

        var pointIndex = 0
        for (x in 0..width step stepPx + spaceBeetweenStepsPx) {
            var factor = 0f
            val curPaint = if (x.toFloat() / width <= progress) paintDone else paint
            if (pointIndex < points.size) {
                factor = points[pointIndex]
            }
            pointIndex += pointStep

            val lineHalfHeight = height.toFloat() * factor / 2

            canvas.drawLine(
                x.toFloat(),
                midX - lineHalfHeight,
                x.toFloat(),
                midX + lineHalfHeight,
                curPaint
            )
        }
    }
}
