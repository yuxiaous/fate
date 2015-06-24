using UnityEngine;
using System;
using System.Collections.Generic;
/**
 * Billing script class for encapsulating java api in libs\CMBilling.jar.
 */ 
public class CmGameLeaderboard
{
	//#if UNITY_ANDROID
	
	// The reflected class of java api of CMBilling.jar
	private AndroidJavaClass klass = new AndroidJavaClass("cn.cmgame.leaderboard.api.GameLeaderboard");
	
	// The instance of billing script.
    private static CmGameLeaderboard _instance;
    public static CmGameLeaderboard Instance
    {
        get
        {
			if(_instance==null){
				_instance = new CmGameLeaderboard();
			}
            return _instance;
        }
    }

	/**
	 * Initialize billing SDK's instance.It should be invoked at the beginning of the app.
	 * @param main The activity environment for SDK's UI displaying.
	 */
	public void InitLeaderboard(String key, String secret, String appId)
	{
		using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
			using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
				klass.CallStatic("initializeLeaderboard", curActivity, key, secret, appId);
			}
		}
	}
	
	public void ShowLeaderboard()
	{
		using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
			using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
				klass.CallStatic("showLeaderboard", curActivity);
			}
		}
	}
	
	//#endif
}