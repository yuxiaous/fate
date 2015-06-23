package com.fate;

import java.util.HashSet;
import java.util.Set;

import android.app.Activity;
import android.app.Application;

import com.fate.SdkJni;
import com.fate.dev.CmgameSdkJni;

public class SdkManagerJni {
	public static Activity activity = null;
	public static Application application = null;
	
	private static Set<SdkJni> _sdks = new HashSet<SdkJni>();
	
	public static void addSdk(SdkJni sdk) {
		_sdks.add(sdk);
	}

	public static void removeSdk(SdkJni sdk) {
		_sdks.remove(sdk);
	}
	
	public static void init() {
		System.out.println("SdkManagerJni.init");

		addSdk(new CmgameSdkJni());
		
		for (SdkJni sdk: _sdks) {  
		      sdk.init(); 
		}  
	}

	public static void buy(String param) {
		System.out.println("SdkManagerJni.buy, param: " + param);

		for (SdkJni sdk: _sdks) {  
		      sdk.buy(param); 
		} 
	}
}
