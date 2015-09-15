package com.hdngame.fate.andgame;

import android.app.Application;

import com.hdngame.fate.SdkManagerJni;
import org.cocos2dx.javascript.AppApplication;

/**
 * Created by yuxiao on 15/6/20.
 */
public class CmgameApplication extends AppApplication {
    public void onCreate() {
        super.onCreate();
        System.loadLibrary("megjb");
    }
}

