package com.hdngame.fate.cmcc.mm;

import com.hdngame.fate.SdkManagerJni;

import mm.purchasesdk.Purchase;
import mm.purchasesdk.PurchaseCode;
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

    private static String _order = "";
    public static void charge(String order, String identifier) {
        System.out.println("MMSdkJni.charge");

        if(_order.length() == 0) {
            System.out.println(order+":"+identifier);

            _order = order;
            purchase.order(SdkManagerJni.activity, identifier, listener);
        }
    }

    public static void handleResult(int code) {
        if(_order.length() > 0) {
            System.out.println("MMSdkJni.handleResult, code: " + code);
            int result = (code == PurchaseCode.ORDER_OK || code == PurchaseCode.AUTH_OK || code == PurchaseCode.WEAK_ORDER_OK) ? 0 : 1;

            onMmChargeCallback(result, _order);
            _order = "";
        }
    }

    private static native void onMmChargeCallback(int result, String order);
}
