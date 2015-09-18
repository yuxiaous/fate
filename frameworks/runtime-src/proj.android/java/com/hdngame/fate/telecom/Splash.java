package com.hdngame.fate.telecom;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import com.fate.dev.R;
import android.os.Handler;
import org.cocos2dx.javascript.AppActivity;

import java.lang.Runnable;

/**
 * Created by yuxiao on 15/7/30.
 */
public class Splash extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.splash);
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                Intent intent = new Intent(Splash.this, AppActivity.class);
                Splash.this.startActivity(intent);
                Splash.this.finish();
            }
        }, 2000);
    }
}
