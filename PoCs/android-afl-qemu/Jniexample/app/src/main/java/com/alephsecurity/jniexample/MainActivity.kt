package com.alephsecurity.jniexample

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val btn = findViewById<Button>(R.id.jnibutton)
        val txt = findViewById<TextView>(R.id.jnitext)
        btn.setOnClickListener {
            val inp = findViewById<EditText>(R.id.jniinput)
            val echo = EchoUtils()
            val text = echo.sendString(inp.text.toString())
            txt.setText(text)
        }
    }
}