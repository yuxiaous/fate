package com.hdngame.fate.mm;

import android.content.Context;
import com.secneo.sdkp.DexHelper;
import org.cocos2dx.javascript.AppApplication;

import java.lang.Override;

/**
 * Created by yuxiao on 15/11/4.
 */
public class MmApplication extends AppApplication {
    @Override
    protected void attachBaseContext(Context ctx){
        System.out.println("MmApplication.attachBaseContext");
        super.attachBaseContext(ctx);

        DexHelper.install(this, "mmbilling.3.1.8.jar.protected.jar");
    }
}