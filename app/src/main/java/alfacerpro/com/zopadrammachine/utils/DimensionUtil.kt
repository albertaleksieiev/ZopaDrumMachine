package alfacerpro.com.zopadrammachine.utils

import android.content.res.Resources
import android.util.TypedValue
import android.view.View

private fun View.applyDimension(unit: Int, value: Float) =
    TypedValue.applyDimension(unit, value, (resources ?: Resources.getSystem()).displayMetrics)

fun View.dp2Px(dp: Float) = applyDimension(TypedValue.COMPLEX_UNIT_DIP, dp).toInt()
fun View.dp2Px(dp: Int) = applyDimension(TypedValue.COMPLEX_UNIT_DIP, dp.toFloat()).toInt()