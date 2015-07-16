package org.cocos2dx.javascript;

import android.app.Application;
import com.hdngame.fate.SdkManagerJni;

/**
 * Created by yuxiao on 15/7/9.
 */
public class AppApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        SdkManagerJni.application = this;

        System.loadLibrary("KTPlay");
        System.loadLibrary("KTAccountmanager");
        System.loadLibrary("KTFriendship");
        System.loadLibrary("KTLeaderboard");
    }
}
