package com.fate.cmcc.and;

import android.widget.Toast;

import com.fate.SdkManagerJni;

import cn.cmgame.billing.api.BillingResult;
import cn.cmgame.billing.api.GameInterface;
import cn.cmgame.billing.api.GameInterface.IPayCallback;

public class AndGameSdkJni {
	public static AndGameSdkJni instance = null;
	public static Object getInstance() {
		if(instance == null) {
			instance = new AndGameSdkJni();
		}
		return instance;
	}

	public void init() {
		System.out.println("AndGameSdkJni.init");

		if(SdkManagerJni.activity != null) {
			GameInterface.initializeApp(SdkManagerJni.activity);
		}
	}

	private String _order = "";
	public void charge(String order, String identifier) {
		System.out.println("AndGameSdkJni.charge");
		
		if(_order.length() == 0) {
	        System.out.println(order+":"+identifier);

	        _order = order;
	        GameInterface.doBilling(SdkManagerJni.activity, true, true, identifier, null, payCallback);
		}
    }

	final IPayCallback payCallback = new IPayCallback() {
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
	
	private void handleResult(int resultCode, String billingIndex) {
		if(_order.length() > 0) {
			System.out.println("AndGameSdkJni.handleResult");

			int result = (resultCode == BillingResult.SUCCESS) ? 0 : 1;
			onChargeCallback(result, _order);
			_order = "";
		}
	}

	private static native void onChargeCallback(int result, String order);
	
	public boolean isMusicOn() {
		return GameInterface.isMusicEnabled();
	}
	
	public void showMoreGames() {
		GameInterface.viewMoreGames(SdkManagerJni.activity);
	}
	
       
}
