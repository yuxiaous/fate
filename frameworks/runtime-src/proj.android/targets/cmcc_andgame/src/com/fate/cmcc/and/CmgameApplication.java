package com.fate.cmcc.and;

import android.app.Application;

import com.fate.SdkManagerJni;

/**
 * Created by yuxiao on 15/6/20.
 */
public class CmgameApplication extends Application {
    public void onCreate() {
        System.loadLibrary("megjb");
        SdkManagerJni.application = this;
    }
}

