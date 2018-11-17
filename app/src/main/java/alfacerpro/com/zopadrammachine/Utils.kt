package alfacerpro.com.zopadrammachine

public class Utils {
    companion object System {
        fun loadLibrary() {
            java.lang.System.loadLibrary("native-lib")
        }
    }
}