package com.hdngame.fate;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import org.cocos2dx.javascript.AppActivity;

import java.lang.Runnable;

/**
 * Created by yuxiao on 15/7/30.
 */
public class SplashActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        String packageName = this.getPackageName();
        int layoutID = this.getResources().getIdentifier("splash", "layout", packageName);
        setContentView(layoutID);

        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                Intent intent = new Intent(SplashActivity.this, AppActivity.class);
                SplashActivity.this.startActivity(intent);
                SplashActivity.this.finish();
            }
        }, 2000);
    }
}
