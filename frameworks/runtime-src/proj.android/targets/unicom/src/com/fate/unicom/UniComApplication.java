package com.fate.unicom;

import org.cocos2dx.javascript.AppApplication;

/**
 * Created by yuxiao on 15/7/15.
 */
public class UniComApplication extends AppApplication {
    @Override
    public void onCreate() {
        System.out.println("UniComApplication.onCreate");
        super.onCreate();

        System.loadLibrary("megjb"); //如果支持移动支付，请在初始化前加载这个SO。
        UniPaySdkJni.init();
    }
}

