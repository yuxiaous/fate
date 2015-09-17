package com.hdngame.fate.mix;

import com.hdngame.fate.unicom.UniPaySdkJni;
import org.cocos2dx.javascript.AppApplication;

/**
 * Created by yuxiao on 15/6/20.
 */
public class MixApplication extends AppApplication {
    public void onCreate() {
        System.out.println("MixApplication.onCreate");

        super.onCreate();
        System.loadLibrary("megjb");
        UniPaySdkJni.init();
    }
}

