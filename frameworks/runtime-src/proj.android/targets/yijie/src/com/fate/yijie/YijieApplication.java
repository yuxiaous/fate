package com.fate.yijie;

import com.fate.SdkManagerJni;
import com.snowfish.cn.ganga.offline.helper.SFOfflineApplication;

/**
 * Created by yuxiao on 15/7/14.
 */
public class YijieApplication extends SFOfflineApplication {
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
