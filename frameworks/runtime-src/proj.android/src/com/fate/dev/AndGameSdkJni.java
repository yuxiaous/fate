package com.fate.dev;

import org.json.JSONException;
import org.json.JSONObject;

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
	public void buy(String param) throws JSONException {
		System.out.println("AndGameSdkJni.buy");
		
		if(_order.length() == 0) {
	        JSONObject jsonobj = new JSONObject(param);  
	        String order = jsonobj.getString("order");  
	        String good_id = jsonobj.getString("platform_good_id");  
	        System.out.println(order+":"+good_id);  

	        _order = order;
	        GameInterface.doBilling(SdkManagerJni.activity, true, true, good_id, null, payCallback);
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
					result = "购买商品【" + billingIndex + "】取消";
					break;
			}
			Toast.makeText(SdkManagerJni.activity, result, Toast.LENGTH_SHORT).show();

			try {
				handleResult(resultCode, billingIndex);
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	};
	
	private void handleResult(int resultCode, String billingIndex) throws JSONException {
		if(_order.length() > 0) {
			System.out.println("AndGameSdkJni.handleResult");
			JSONObject jsonobj = new JSONObject();
			jsonobj.put("result", (resultCode == BillingResult.SUCCESS) ? 0 : 1);
			jsonobj.put("order", _order);

			onBuyCallback(jsonobj.toString());
			_order = "";
		}
	}

	private static native void onBuyCallback(String param);
	
	public boolean isMusicOn() {
		return GameInterface.isMusicEnabled();
	}
	
	public void showMoreGames() {
		GameInterface.viewMoreGames(SdkManagerJni.activity);
	}
	
       
}
