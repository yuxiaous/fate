package org.cocos2dx.javascript;

import android.app.Application;
import com.fate.SdkManagerJni;

/**
 * Created by yuxiao on 15/7/10.
 */
public class AppApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        SdkManagerJni.application = this;
    }
}
