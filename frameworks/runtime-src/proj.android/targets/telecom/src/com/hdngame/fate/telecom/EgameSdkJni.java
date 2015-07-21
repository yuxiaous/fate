package com.hdngame.fate.telecom;



import android.app.Activity;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import cn.egame.terminal.paysdk.EgamePay;
import com.hdngame.fate.SdkManagerJni;

/**
 * Created by yuxiao on 15/6/30.
 */
public class EgameSdkJni {

    protected static int GameId = 0;
    protected static int ChannelId = 0;

    public static void init() {
        System.out.println("EgameSdkJni.init");

        GameId = 5018840;
        try {
            Activity a = SdkManagerJni.activity;
            ApplicationInfo info = a.getPackageManager().getApplicationInfo(
                    a.getPackageName(),
                    PackageManager.GET_META_DATA);
            ChannelId = info.metaData.getInt("EGAME_CHANNEL");
        }
        catch(PackageManager.NameNotFoundException ex) {
            ChannelId = 10000000;
        }

        EgamePay.init(SdkManagerJni.activity);
//        CheckTool.init(this, ""+GameId, ""+ChannelId);
    }

    public static void pay(String number) {
        System.out.println("EgameSdkJni.pay, number: " + number);
    }

//    public static native void onEgameChargeCallback(int result);
}

