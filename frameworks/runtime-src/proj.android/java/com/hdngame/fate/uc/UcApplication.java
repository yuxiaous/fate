package com.hdngame.fate.uc;

import cn.uc.paysdk.SDKCore;
import org.cocos2dx.javascript.AppApplication;

/**
 * Created by yuxiao on 15/10/1.
 */
public class UcApplication extends AppApplication {
    public void onCreate() {
        System.out.println("UcApplication.onCreate");

        super.onCreate();
        SDKCore.registerEnvironment(this);
    }
}
