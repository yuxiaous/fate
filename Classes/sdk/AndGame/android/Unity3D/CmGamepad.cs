using UnityEngine;
using System;
using System.Collections.Generic;
/**
 * Gamepad script class for encapsulating java api in runtime\CMBilling.jar.
 */ 
public class CmGamepad
{
	//#if UNITY_ANDROID
	
	// The reflected class of java api of CMBilling.jar
	private AndroidJavaClass klass = new AndroidJavaClass("cn.cmgame.gamepad.api.Gamepad");
	
	// The instance of billing script.
    private static CmGamepad _instance;
    public static CmGamepad Instance
    {
        get
        {
			if(_instance==null){
				_instance = new CmGamepad();
			}
            return _instance;
        }
    }

	/**
	 * Initialize billing SDK's instance.It should be invoked at the beginning of the app.
	 * @param main The activity environment for SDK's UI displaying.
	 */
	public void InitGamepad()
	{
		AndroidJavaClass unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity");
		curActivity.Call("runOnUiThread", new AndroidJavaRunnable(() =>
        		{
            		klass.CallStatic("initGamepad", curActivity);
        		}));
	}

	//#endif
}