package com.hdngame.fate.coolpad;

import android.content.pm.ActivityInfo;
import com.android.qikupaysdk.QiKuPay;
import com.hdngame.fate.SdkManagerJni;

import java.lang.System;

/**
 * Created by yuxiao on 15/10/2.
 */
public class QiKuPaySdkJni {

    public static void init(String appid) {
        System.out.println("QiKuPaySdkJni.init");

        QiKuPay.payInit(SdkManagerJni.activity, ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE, appid);
    }
}
