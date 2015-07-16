package com.hdngame.fate.cmcc.and;

import android.widget.Toast;

import com.hdngame.fate.SdkManagerJni;

import cn.cmgame.billing.api.BillingResult;
import cn.cmgame.billing.api.GameInterface;
import cn.cmgame.billing.api.GameInterface.IPayCallback;

public class AndGameSdkJni {

	public static void init() {
		System.out.println("AndGameSdkJni.init");

		GameInterface.initializeApp(SdkManagerJni.activity);
	}

	private static String _order = "";

	public static void charge(String order, String identifier) {
		System.out.println("AndGameSdkJni.charge");
		
		if(_order.length() == 0) {
	        System.out.println(order+":"+identifier);

	        _order = order;
	        GameInterface.doBilling(SdkManagerJni.activity, true, true, identifier, null, payCallback);
		}
    }

	final static IPayCallback payCallback = new IPayCallback() {
		@Override
		public void onResult(int resultCode, String billingIndex, Object obj) {
			String result = "";
			switch (resultCode) {
				case BillingResult.SUCCESS:
					result = "购买商品【" + billingIndex + "】成功！";
					break;
				case BillingResult.FAILED:
					result = "购买商品【" + billingIndex + "】失败！";
					break;
				default:
					result = "购买商品【" + billingIndex + "】取消！";
					break;
			}
			Toast.makeText(SdkManagerJni.activity, result, Toast.LENGTH_SHORT).show();

			handleResult(resultCode, billingIndex);
		}
	};
	
	private static void handleResult(int resultCode, String billingIndex) {
		if(_order.length() > 0) {
			System.out.println("AndGameSdkJni.handleResult");

			int result = (resultCode == BillingResult.SUCCESS) ? 0 : 1;
			onAndChargeCallback(result, _order);
			_order = "";
		}
	}

	private static native void onAndChargeCallback(int result, String order);
	
	public static boolean isMusicOn() {
		return GameInterface.isMusicEnabled();
	}
	
	public static void showMoreGames() {
		GameInterface.viewMoreGames(SdkManagerJni.activity);
	}
	
       
}
