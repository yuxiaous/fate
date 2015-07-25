package com.hdngame.fate.andgame;

import android.net.Uri;
import android.widget.Toast;

import com.hdngame.fate.SdkManagerJni;

import cn.cmgame.billing.api.BillingResult;
import cn.cmgame.billing.api.GameInterface;

import java.lang.Override;
import java.lang.String;

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

	final static GameInterface.IPayCallback payCallback = new GameInterface.IPayCallback() {
		@Override
		public void onResult(int resultCode, String billingIndex, Object obj) {
			System.out.println("AndGameSdkJni.charge IPayCallback" +
					", code: " + resultCode +
					", index: " + billingIndex +
					", obj: " + obj.toString());

			String result = "";
			switch (resultCode) {
				case BillingResult.SUCCESS:
					result = "购买成功！";
					break;
				case BillingResult.FAILED:
					result = "购买失败！";
					break;
				default:
					result = "取消购买！";
					break;
			}
			Toast.makeText(SdkManagerJni.activity, result, Toast.LENGTH_SHORT).show();

			handleResult(resultCode, billingIndex);
		}
	};
	
	private static void handleResult(int resultCode, String billingIndex) {
		if(_order.length() > 0) {
			int result = (resultCode == BillingResult.SUCCESS) ? 0 : 1;
			onAndChargeCallback(result, _order);
			_order = "";
		}
	}

	private static native void onAndChargeCallback(int result, String order);
	
	public static boolean isMusicEnabled() {
		System.out.println("AndGameSdkJni.isMusicEnabled");
		return GameInterface.isMusicEnabled();
	}
	
	public static void showMoreGames() {
		System.out.println("AndGameSdkJni.showMoreGames");
		GameInterface.viewMoreGames(SdkManagerJni.activity);
	}
	
	public static void exit() {
		System.out.println("AndGameSdkJni.exit");
		GameInterface.exit(SdkManagerJni.activity, new GameInterface.GameExitCallback() {
			@Override
			public void onConfirmExit() {
				System.out.println("AndGameSdkJni.exit onConfirmExit");
			}

			@Override
			public void onCancelExit() {
				System.out.println("AndGameSdkJni.exit onCancelExit");
			}
		});
	}

//	public static boolean getActivateFlag(String billingIndex) {
//		System.out.println("AndGameSdkJni.getActivateFlag");
//		return GameInterface.getActivateFlag(billingIndex);
//	}

//	public static int getGamePlayerAuthState() {
//		System.out.println("AndGameSdkJni.getGamePlayerAuthState");
//		return GameInterface.getGamePlayerAuthState();
//	}

	public static void doScreenShotShare() {
		System.out.println("AndGameSdkJni.doScreenShotShare");
		GameInterface.doScreenShotShare(SdkManagerJni.activity, null);
	}
}
