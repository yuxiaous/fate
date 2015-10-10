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

    public static native String getAppId();
    public static native String getAppKey();

    public static void init() {
        System.out.println("QiKuPaySdkJni.init");

        String appid = getAppId();
        QiKuPay.payInit(SdkManagerJni.activity, ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE, appid);
    }

    public static void pay(String order, String info) {
        System.out.println("QiKuPaySdkJni.pay");
        System.out.println(order + ":" + info);

        PayParams parms = new PayParams();
        parms.setAppId(getAppId());
        parms.setAppKey(getAppKey());
        parms.setWaresid(String.valueOf(1));
        parms.setCpOrder(order);
        parms.setCpPrivate("cp private info!!");
        parms.setPrice(123);

        QiKuPay.startPay(SdkManagerJni.activity, parms, null, iPayResultCallback);
    }

    final static CallBackToCPInterface iPayResultCallback = new CallBackToCPInterface() {
        @Override
        public void paySuccess(String result, String resultCode) {
            System.out.println("iPayResultCallback.paySuccess");
            System.out.println(result + ":" + resultCode);
            /*Toast.makeText(TestActivity.this,
              "CP reciver  result: " + result,
              1).show();*/
//            sendMessage(PAY_SUCCESS,null);
//            Log.e("coolpay", " cp  paySuccess !! ");
        }

        @Override
        public void payFail(String result, String resultCode) {
            System.out.println("iPayResultCallback.payFail");
            System.out.println(result + ":" + resultCode);
           /* Toast.makeText(TestActivity.this,
              "CP reciver  result: " + result,
              1).show();*/
//            sendMessage(PAY_FAIL,null);
//            Log.e("coolpay", " cp  payFaile !! ");
        }
    };
}
