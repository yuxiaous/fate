package com.fate;

import com.tendcloud.tenddata.TalkingDataGA;

/**
 * Created by yuxiao on 15/6/29.
 */
public class TalkingDataGASdkJni {
	public static TalkingDataGASdkJni instance = null;

	public static Object getInstance() {
		if (instance == null) {
			instance = new TalkingDataGASdkJni();
		}
		return instance;
	}

	public void init() {
		System.out.println("TalkingDataGASdkJni.init");

		if (SdkManagerJni.activity != null) {
			TalkingDataGA.init(SdkManagerJni.application, "59EC3DE05BB0234EA444193F4B9E0E4B", "AndroidDevelop");
		}
	}
}
