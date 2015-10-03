package com.hdngame.fate.mi;

import com.hdngame.fate.SdkManagerJni;
import com.xiaomi.gamecenter.sdk.MiCommplatform;
import com.xiaomi.gamecenter.sdk.entry.MiAppInfo;

import java.lang.System;

/**
 * Created by yuxiao on 15/10/3.
 */
public class MiGameCenterSdkJni {

    public static void init() {
        System.out.println("MiGameCenterSdkJni.init");

        MiAppInfo appInfo = new MiAppInfo();
        appInfo.setAppId( "2882303761517390705" );
        appInfo.setAppKey( "5311739039705" );
        MiCommplatform.Init(SdkManagerJni.activity, appInfo);
    }

    public static void pay() {
        System.out.println("MiGameCenterSdkJni.pay");

//        MiCommplatform.getInstance().miLogin();
    }
}
