package com.hdngame.fate.cmcc.mm;

import com.hdngame.fate.SdkManagerJni;

import mm.purchasesdk.Purchase;
import android.os.Handler;

/**
 * Created by yuxiao on 15/6/30.
 */
public class MMSdkJni {

	private static Purchase purchase = null;
	private static IAPListener listener = null;

    public static void init(String appid, String appkey) {
        System.out.println("MMSdkJni.init, appid: "+appid + ", appkey :"+appkey);

        listener = new IAPListener();
        purchase = Purchase.getInstance();

        try {
            purchase.setAppInfo(appid, appkey);

        } catch (Exception e1) {
            e1.printStackTrace();
        }

        try {
            purchase.init(SdkManagerJni.activity, listener);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String _paycode = "";
    private static Handler _handler = new Handler();

    public static void order(String paycode) {
        System.out.println("MMSdkJni.order 1, paycode: " + paycode);
        _paycode = paycode;

        _handler.post(new Runnable() {
            @Override
            public void run() {
                System.out.println("MMSdkJni.order 2, paycode: " + _paycode);

                try {
                    purchase.order(SdkManagerJni.activity, _paycode, listener);
                } catch (Exception e1) {
                    //
                    e1.printStackTrace();
                    return;
                }
            }
        });
    }

    public static native void onMmChargeCallback(int result);
}
