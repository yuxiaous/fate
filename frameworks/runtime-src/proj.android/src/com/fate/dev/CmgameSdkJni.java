package com.fate.dev;

import android.widget.Toast;

import com.fate.SdkJni;
import com.fate.SdkManagerJni;

import cn.cmgame.billing.api.BillingResult;
import cn.cmgame.billing.api.GameInterface;
import cn.cmgame.billing.api.GameInterface.IPayCallback;

public class CmgameSdkJni extends SdkJni {
	@Override
	public void init() {
		if(SdkManagerJni.activity != null) {
			GameInterface.initializeApp(SdkManagerJni.activity);
		}
	}
	
	@Override
	public void buy(String param) {
        GameInterface.doBilling(SdkManagerJni.activity, true, true, "001", null, payCallback);  
    }
	
    final IPayCallback payCallback = new IPayCallback() {  
    	@Override
        public void onResult(int resultCode, String billingIndex, Object obj) {  
          String result = "";  
          switch (resultCode) {  
            case BillingResult.SUCCESS:  
                result = "������ߣ�[" + billingIndex + "] �ɹ���";  
                break;  
              case BillingResult.FAILED:  
                result = "������ߣ�[" + billingIndex + "] ʧ�ܣ�";  
                break;  
              default:  
                result = "������ߣ�[" + billingIndex + "] ȡ����"; 
//              getPoint(10000);  
              break;  
          }  
          Toast.makeText(SdkManagerJni.activity, result, Toast.LENGTH_SHORT).show();  
        }  
  }; 
	
	public boolean isMusicOn() {
		return GameInterface.isMusicEnabled();
	}
	
	public void showMoreGames() {
		GameInterface.viewMoreGames(SdkManagerJni.activity);
	}
	
       
}
