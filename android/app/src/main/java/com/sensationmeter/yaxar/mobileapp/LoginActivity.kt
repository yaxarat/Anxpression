package com.sensationmeter.yaxar.mobileapp

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_login.*

class LoginActivity : AppCompatActivity() {
    private var user = "kate"
    private var pass = "pass"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)

        return_btn.setOnClickListener {
            auth()
        }
    }

    private fun auth() {
        if (username_et.text.toString().equals(user) && password_et.text.toString().equals(pass)) {
            val intent = Intent(applicationContext, ProfileActivity::class.java)
            startActivity(intent)
        } else {
            Toast.makeText(this, "Username or password is incorrect.", Toast.LENGTH_LONG).show()
        }
    }
}
