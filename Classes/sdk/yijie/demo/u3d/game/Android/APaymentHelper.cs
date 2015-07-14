using UnityEngine;
using System.Collections;
using System;
public class APaymentHelper{

#if UNITY_ANDROID
	private AndroidJavaClass klass = new AndroidJavaClass("com.snowfish.android.ahelper.APaymentUnity");
	// The instance of billing script.
    private static APaymentHelper _instance;
    public static APaymentHelper Instance
    {
        get
        {
			if (_instance==null) {
				_instance = new APaymentHelper();
			}
            return _instance;
        }
    }
	
	public void Init()
	{	
		using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
			using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
				klass.CallStatic("onInit", curActivity);
			}
		}
	}
	
	
	public void Pay(String payId, String gameObject, String runtimeScriptMethod, String usedPrice, String remained)
	{
		using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
			using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
				klass.CallStatic("pay", curActivity, payId, gameObject, runtimeScriptMethod, usedPrice, remained);
			}
		}
	}
	
	
	public void Exit()
    {
		using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
			using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
				klass.CallStatic("onExit", curActivity);
			}
		}
	}
	
	public bool isPaid (String id) 
	{
		using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
			using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
				return klass.CallStatic<Boolean>("isPaid", curActivity, id);
			}
		}
	}
	
	public void setPaid (String id, Boolean paid) 
	{
		using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
			using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
				klass.CallStatic("setPaid", curActivity, id, paid);
			}
		}
	}
	
	public String getPayingResult (String id) 
	{
		using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
			using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
				return klass.CallStatic<String>("getPayingResult",curActivity, id);
			}
		}
	}
	
	public long getUserId () 
	{
		using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
			using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
				return klass.CallStatic<long>("getUserId", curActivity);
			}
		}
	}
	
	#endif
	
	/**
	 * Result of paying.
	 */
	public class PayResult
	{
		/** pay success */
		public const String SUCCESS = "0";

		/** pay failure */
		public const String FAILURE = "1";

		/** pay canceled, such as use cancel to purchase it in billing ui */
		public const String CANCELED = "2";
	}
}
