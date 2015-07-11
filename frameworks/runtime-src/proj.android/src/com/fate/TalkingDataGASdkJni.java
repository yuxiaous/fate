package com.fate;

import com.tendcloud.tenddata.TalkingDataGA;

/**
 * Created by yuxiao on 15/6/29.
 */
public class TalkingDataGASdkJni {

	public static void init(String appid, String channel) {
		System.out.println("TalkingDataGASdkJni.init appid: "+appid + ", channel: "+channel);

		if (SdkManagerJni.activity != null) {
			TalkingDataGA.init(SdkManagerJni.activity, appid, channel);
			
		}
	}
}
