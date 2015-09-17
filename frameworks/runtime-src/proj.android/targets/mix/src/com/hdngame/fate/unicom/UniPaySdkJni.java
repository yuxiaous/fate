package com.hdngame.fate.unicom;


import com.hdngame.fate.SdkManagerJni;
import com.unicom.dcLoader.Utils;

import java.lang.String;
import android.os.Handler;
import android.widget.Toast;

/**
 * Created by yuxiao on 15/6/30.
 */
public class UniPaySdkJni {

    public static void init() {
        System.out.println("UniPaySdkJni.init");
        Utils.getInstances().initSDK(SdkManagerJni.application, new Utils.UnipayPayResultListener() {
            @Override
            public void PayResult(String paycode, int flag, int flag2, String error) {}
        });
    }

    private static String _number = "";
    private static String _order = "";
    private static Handler _handler = new Handler();

    public static void pay(String order, String number) {
        System.out.println("UniPaySdkJni.pay 1");
        System.out.println(order + ":" + number);

        _order = order;
        _number = number;

        _handler.post(new Runnable() {
            @Override
            public void run() {
                System.out.println("UniPaySdkJni.pay 2");
                Utils.getInstances().pay(SdkManagerJni.activity, _number, callback);
            }
        });
    }

    final static Utils.UnipayPayResultListener callback = new Utils.UnipayPayResultListener() {
        @Override
        public void PayResult(String paycode, int flag, int flag2, String error) {
            // flag为支付回调结果，flag2为回调类型，error为当前结果描述，paycode是完整的支付编码
            System.out.println("UnipayPayResultListener.PayResult paycode: "+paycode
                    + ", flag: "+flag + ", flag2: "+flag2 + ", error:"+error);

            // flag2参数，请参考如下定义：
            // SMS_SEND = 5;
            // VAC_SEND = 8;
            // MONTH_SEND = 11;
            // UNMONTH_SEND = 12;
            // DX_SMS_SEND = 13;

            // SUBCOMMIT_VAC = 20; // VAC支付提交
            // SUCCESS_SMS = 21; // 短代支付成功
            // SUBCOMMIT_WEBALIPAY = 22; // WEB支付宝提交
            // SUCCESS_KALIPAY = 23; // 支付宝快捷支付成功
            // SUBCOMMIT_SZF = 24; // 神州付提交
            // SUCCESS_EXCHANGECODE = 25; // 兑换成功
            // CANCEL_FIRSTPAGE = 26; // 第一次确认支付取消
            // CANCEL_VACPAYPAGE = 27; // VAC支付页面取消
            // CANCEL_OTHERPAYPAGE = 28; // 其他支付页面取消
            // CANCEL_CHANGECODE = 29; // 兑换码页面取消
            // CANCEL_VACYZM = 30; // 话费验证码页面取消
            // CANCEL_CHINAMOBILE = 31;

            // INIT_FIALD = 101010;
            // INIT_ING = 101011;

            switch (flag) {
                case 1://success
                    //此处放置支付请求已提交的相关处理代码
                    onUniPayChargeCallback(0, _order);
                    _number = "";
                    _order = "";
                    break;

                case 2://fail
                    //此处放置支付请求失败的相关处理代码
                    Toast.makeText(SdkManagerJni.activity, error, Toast.LENGTH_SHORT).show();
                    break;

                case 3://cancel
                    //此处放置支付请求被取消的相关处理代码
                    Toast.makeText(SdkManagerJni.activity, error, Toast.LENGTH_SHORT).show();
                    break;

                default:
                    break;
            }
        }
    };

    public static void onPause() {
        System.out.println("UniPaySdkJni.onPause");
        Utils.getInstances().onPause(SdkManagerJni.activity);
    }

    public static void onResume() {
        System.out.println("UniPaySdkJni.onResume");
        Utils.getInstances().onResume(SdkManagerJni.activity);
    }

    public static void moreGame() {
        System.out.println("UniPaySdkJni.moreGame");
        Utils.getInstances().MoreGame(SdkManagerJni.activity);
    }

//    public static Utils.SimType getSimType() {
//        return Utils.getInstances().getSimType(SdkManagerJni.activity);
//    }

    public static boolean isInit() {
        System.out.println("UniPaySdkJni.isInit");
        return Utils.getInstances().isInit();
    }

    public static native void onUniPayChargeCallback(int result, String order);
}

