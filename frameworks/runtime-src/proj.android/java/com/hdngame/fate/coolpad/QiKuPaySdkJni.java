package com.hdngame.fate.coolpad;

import android.content.pm.ActivityInfo;
import com.android.qikupaysdk.CallBackToCPInterface;
import com.android.qikupaysdk.PayParams;
import com.android.qikupaysdk.QiKuPay;
import com.hdngame.fate.SdkManagerJni;

import java.lang.String;
import java.lang.System;

/**
 * Created by yuxiao on 15/10/2.
 */
public class QiKuPaySdkJni {

    public static String _appId = "";
    public static String _appKey = "";

    public static void init(String appId, String appKey) {
        System.out.println("QiKuPaySdkJni.init");

        _appId = appId;
        _appKey = appKey;

        QiKuPay.payInit(SdkManagerJni.activity, ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE, _appId);
    }

    private static String _order = "";
    private static String _waresid = "";
    private static int _price = 0;

    public static void pay(String order, String waresid, int price) {
        System.out.println("QiKuPaySdkJni.pay");
        System.out.println(order + ":" + waresid + ":" + price);

        _order = order;
        _waresid = waresid;
        _price = price;

        SdkManagerJni.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                PayParams parms = new PayParams();
                parms.setAppId(_appId);
                parms.setAppKey(_appKey);
                parms.setWaresid(_waresid);
                parms.setCpOrder(_order);
                parms.setPrice(_price);

                QiKuPay.startPay(SdkManagerJni.activity, parms, null, iPayResultCallback);
            }
        });
    }

    final static CallBackToCPInterface iPayResultCallback = new CallBackToCPInterface() {
        @Override
        public void paySuccess(String resultInfo, String resultCode) {
            System.out.println("iPayResultCallback.paySuccess");
            System.out.println(resultInfo + ":" + resultCode);

            onQiKuPayChargeCallback(0, _order);
        }

        @Override
        public void payFail(String resultInfo, String resultCode) {
            System.out.println("iPayResultCallback.payFail");
            System.out.println(resultInfo + ":" + resultCode);

            onQiKuPayChargeCallback(1, _order);
        }
    };

    public static native void onQiKuPayChargeCallback(int result, String order);
}
