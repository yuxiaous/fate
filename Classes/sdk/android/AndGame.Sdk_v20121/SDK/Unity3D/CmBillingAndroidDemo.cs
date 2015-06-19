using UnityEngine;
using System;
using System.Collections.Generic;

public class CmBillingAndroidDemo : MonoBehaviour
{
	#if UNITY_ANDROID

	void Awake ()
	{
		if (Application.platform == RuntimePlatform.Android)
		{
			CmBillingAndroid.Instance.InitializeApp();
			CmBillingAndroidDemo.CheckGameBackgroundMusic();
		}
	}

	void Start ()
	{
		//CmBillingAndroidDemo.Billing("001");
	}

    public static void CheckGameBackgroundMusic()
	{
		if (CmBillingAndroid.Instance.IsMusicEnabled())
		{
			Debug.Log("IsMusicEnabled=true");
		}
		else
		{
			Debug.Log("IsMusicEnabled=false");
		}
	}

	void OnBillingResult(String result)
	{ 
		Debug.Log("BillingResult="+result);
		String[] results = result.Split('|');
		if(CmBillingAndroid.BillingResult.CANCELLED==results[1])
		{
			CmBillingAndroid.Instance.ExitWithUI();
		} 
	}
	
	void OnLoginResult(String result)
	{ 
		Debug.Log("LoginResult="+result);
	}

	public static void Billing(String index)
    {
        if(!CmBillingAndroid.Instance.GetActivateFlag(index))
		{
			CmBillingAndroid.Instance.DoBilling(true, false, "001", "", "Main Camera", "OnBillingResult");
		}
    }
	#endif
}
