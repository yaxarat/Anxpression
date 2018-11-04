package com.sensationmeter.yaxar.mobileapp

import android.content.Context
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*
import android.os.Vibrator;


class MainActivity : AppCompatActivity() {
    val handler = Handler()
    var delay = 5000 //milliseconds
    var hr = 90
    var rr = 30

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        user_btn.setOnClickListener {
            val intent = Intent(applicationContext, LoginActivity::class.java)
            startActivity(intent)
        }

        handler.postDelayed(object : Runnable {
            override fun run() {
                handler.postDelayed(this, delay.toLong())
                hr = (90..150).random()
                rr = (25..40).random()
                setText(hr, rr)
                check(hr, rr)
            }
        }, delay.toLong())
    }

    fun IntRange.random() = Random().nextInt((endInclusive + 1) - start) +  start

    fun check(hr: Int, rr: Int) {
        if (hr > 120 && rr > 30) {
            report_et.text = "Are you in distress?\nLet's concentrate on calming down."
            viberate()
        } else if (rr > 30) {
            report_et.text = "Respiration rate little high.\nLet's take a break."
            viberate()
        } else if (hr > 120) {
            report_et.text = "Heart rate little high.\nLet's sit down and relax."
            viberate()
        } else {

        }
    }

    fun setText(hr: Int, rr: Int) {
        heartR_tv.text = hr.toString() + "bpm"
        lungR_tv.text = rr.toString() + "bpm"
    }

    fun viberate() {
        val vibratorService = getSystemService(Context.VIBRATOR_SERVICE) as Vibrator
        vibratorService.vibrate(500)
    }


}
