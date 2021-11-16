package com.alephsecurity.jniexample

class EchoUtils {

    companion object {
        init {
            System.loadLibrary("vulnlib")
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun sendString(str: String): String
}