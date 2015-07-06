package com.fate.cmcc.mm;

import com.fate.SdkManagerJni;

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
        purchase.setAppInfo(appid, appkey);
        purchase.init(SdkManagerJni.activity, listener);
    }


}
