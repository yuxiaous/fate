package com.hdngame.fate;


import android.app.Activity;
import android.content.Context;
import android.telephony.TelephonyManager;
import com.hdngame.fate.SdkManagerJni;

import java.lang.String;
import java.util.UUID;

public class GameUtilsJni {

    private static String udid;

    public static String getUdid() {
        return udid;
    }

    public static void initUdid {
        if(SdkManagerJni.activity != null) {
            Context bc = SdkManagerJni.activity.getBaseContext();
            TelephonyManager tm = (TelephonyManager)bc.getSystemService(Context.TELEPHONY_SERVICE);

            udid = tm.getDeviceId();


        }
    }
}