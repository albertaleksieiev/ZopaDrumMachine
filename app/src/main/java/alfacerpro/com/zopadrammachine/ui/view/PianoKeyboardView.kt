package alfacerpro.com.zopadrammachine.ui.view

import alfacerpro.com.zopadrammachine.ui.px
import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.graphics.Rect
import android.util.AttributeSet
import android.view.MotionEvent
import android.view.View


class PianoKeyboardView : View {
    interface OnTouchEvents {
        fun onNoteTouchDown(notes: ArrayList<Int>)
        fun onNoteTouchUp()
    }

    private val whiteKeyPaint: Paint
    private val blackKeyPaint: Paint
    private var whiteKeyWidth: Float
    private var blackKeyWidth: Float
    public var onTouchEvents: OnTouchEvents? = null

    val whiteIds = intArrayOf(0, 2, 4, 5, 7, 9, 11)
    val blackIds = intArrayOf(1, 3, 6, 8, 10)
    val noteCount = 12
    val noteToRect = HashMap<Int, Rect>()

    val touchIntexToNote = HashMap<Int, Int>()
    private var notes: ArrayList<Int> = ArrayList()
        get() = ArrayList(touchIntexToNote.values.toList())


    constructor(context: Context) : this(context, null)
    constructor(context: Context, attrs: AttributeSet?) : this(context, attrs, 0)

    constructor(context: Context, attrs: AttributeSet?, defStyleAttr: Int) : super(context, attrs, defStyleAttr) {}


    init {
        whiteKeyPaint = Paint()
        whiteKeyPaint.isAntiAlias = true
        whiteKeyPaint.strokeWidth = 2.px.toFloat()
        whiteKeyPaint.color = Color.BLACK
        whiteKeyPaint.style = Paint.Style.STROKE

        blackKeyPaint = Paint()
        blackKeyPaint.isAntiAlias = true
        blackKeyPaint.strokeWidth = 2.px.toFloat()
        blackKeyPaint.color = Color.BLACK
        blackKeyPaint.style = Paint.Style.FILL

        whiteKeyWidth = 50.px.toFloat()
        blackKeyWidth = 40.px.toFloat()
    }


    override fun onDraw(canvas: Canvas?) {
        super.onDraw(canvas)

        val canvas = canvas ?: return

        var x = 0
        for (octave in 4..5) {
            x = drawOctave(canvas, x, height, octave)
        }
    }

    private fun getNoteFromTouchPointer(x: Int, y: Int): Int? {
        // Get the pointer's current position
        val ids = ArrayList<Int>()
        for ((note, rect) in noteToRect) {
            if (rect.contains(x, y)) {
                ids.add(note)
            }
        }

        // to prevent ambiguous between black and white buttons
        val blackButton = ids.filter { blackIds.contains(it % noteCount) }
        val whiteButton = ids.filter { whiteIds.contains(it % noteCount) }

        if (!blackButton.isEmpty()) { // black button have rank of 1
            return blackButton.first()
        } else if (!whiteButton.isEmpty()) {
            return whiteButton.first()
        }

        return null
    }

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        if (event == null) {
            return super.onTouchEvent(event)
        }

        if (event.actionMasked == MotionEvent.ACTION_POINTER_DOWN ||
            event.actionMasked == MotionEvent.ACTION_DOWN) {
            val index = event.actionIndex

            val note = getNoteFromTouchPointer(event.getX(index).toInt(), event.getY(index).toInt())
            if (note != null) {
                touchIntexToNote[index] = note
            }
            onTouchEvents?.onNoteTouchDown(notes)

        } else if (event.actionMasked == MotionEvent.ACTION_MOVE) {
            // Bad perfomance
//            val index = event.actionIndex
//            getNoteFromTouchPointer(event.getX(index).toInt(), event.getY(index).toInt())
//                ?.let {
//                    val prevNote = touchIntexToNote.get(it)
//                    if (prevNote != null && prevNote != it) {
//                        touchIntexToNote[index] = prevNote
//                    }
//                    onTouchEvents?.onNoteTouchDown(notes)
//                }
        } else if (event.actionMasked == MotionEvent.ACTION_POINTER_UP) {
            touchIntexToNote.remove(event.actionIndex)
            onTouchEvents?.onNoteTouchDown(notes)
        } else if (event.actionMasked == MotionEvent.ACTION_UP) {
            touchIntexToNote.clear()
            onTouchEvents?.onNoteTouchUp()
        }

        return true
    }

    /**
     * Returns right X
     */
    fun drawOctave(canvas: Canvas, x: Int, height: Int, octave: Int): Int {
        var xMax = 0
        for (i in 0..6) {
            xMax = drawWhiteKey(
                canvas,
                (x + whiteKeyWidth * i).toInt(),
                height,
                whiteIds[i] + octave * noteCount
            )
        }

        for (i in 0..5) {
            if (i == 2) {
                continue
            }

            drawBlackKey(
                canvas,
                (x + whiteKeyWidth * (i + 1) - blackKeyWidth / 2).toInt(),
                height,
                blackIds[if (i < 2) i else i - 1] + octave * noteCount
            )
        }
        return xMax
    }

    /**
     * Return right boarding X
     */
    fun drawWhiteKey(canvas: Canvas, x: Int, height: Int, noteId: Int): Int {
        val rect = Rect(x, 0, (x + whiteKeyWidth).toInt(), height)
        // TODO move it away from DRAW
        noteToRect[noteId] = rect

        canvas.drawRect(rect, whiteKeyPaint)
        return rect.right
    }

    fun drawBlackKey(canvas: Canvas, x: Int, height: Int, noteId: Int) {
        val rect = Rect(x, 0, (x + blackKeyWidth).toInt(), (height.toFloat() * 0.6f).toInt())
        // TODO move it away from DRAW
        noteToRect[noteId] = rect

        canvas.drawRect(rect, blackKeyPaint)
    }
}