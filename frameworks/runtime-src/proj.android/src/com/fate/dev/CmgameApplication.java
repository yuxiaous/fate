package com.fate.dev;

import android.app.Application;

/**
 * Created by yuxiao on 15/6/20.
 */
public class CmgameApplication extends Application {
    public void onCreate() {
        System.loadLibrary("megjb");
    }
}

