package org.cocos2dx.javascript;

import android.app.Application;
import com.fate.SdkManagerJni;
//import com.ktplay.open.KTPlay;

/**
 * Created by yuxiao on 15/7/9.
 */
public class AppApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        SdkManagerJni.application = this;
    }
}
