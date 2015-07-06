package com.fate.cmcc.mm;

import com.fate.SdkManagerJni;

//import mm.purchasesdk.OnPurchaseListener;
import mm.purchasesdk.Purchase;

/**
 * Created by yuxiao on 15/6/30.
 */
public class MMSdkJni {

	private static Purchase purchase = null;

    public static void init(String appid, String appkey) {
        System.out.println("MMSdkJni.init, appid: "+appid + ", appkey :"+appkey);

    	purchase = Purchase.getInstance();
    	purchase.setAppInfo(appid, appkey);
    	purchase.init(SdkManagerJni.activity, null);
    }
    
//    final static OnPurchaseListener purchaseListener = new OnPurchaseListener() {
//		@Override
//		public void onInitFinish(int var1) {
//
//        }
//	};
}
