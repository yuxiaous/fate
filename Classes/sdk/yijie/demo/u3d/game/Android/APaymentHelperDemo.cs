using UnityEngine;
using System.Collections;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;
using System;

public class APaymentHelperDemo : MonoBehaviour {
	Rect windowRect = new Rect(20, 20, 400, 600);
	string str = "show result";
	
	[DllImport ("libsfunityoffline")]
    private static extern void onInit(IntPtr context); 
	[DllImport ("libsfunityoffline")]
    private static extern void onExit(IntPtr context); 
	[DllImport ("libsfunityoffline")]
    private static extern void onExitWithUI(IntPtr context);
	[DllImport ("libsfunityoffline")]
	private static extern void pay (IntPtr context, string id, string gameObject, string runtimeScriptMethod);
	[DllImport ("libsfunityoffline")]
	private static extern int isPaid (IntPtr context, string id);
	[DllImport ("libsfunityoffline")]
	private static extern void viewMoreGames(IntPtr context); 
	[DllImport ("libsfunityoffline")]
	private static extern int isMusicEnabled(IntPtr context);
	[DllImport ("libsfunityoffline")]
	private static extern void onPause(IntPtr context);
	[DllImport ("libsfunityoffline")]
	private static extern void onResume(IntPtr context);
	[DllImport ("libsfunityoffline")]
	private static extern void setPaid(IntPtr context, string id);
	
    GUI.WindowFunction windowFunction;
    void OnGUI (){
        windowRect = GUI.Window(0, windowRect, DoMyWindow, str);
    }
	
	//bool startcheck;
	void DoMyWindow(int windowID) {
        if (GUI.Button(new Rect(10,20,300,60), "pay 0 test")){
          using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
				using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
            		pay(curActivity.GetRawObject(), "0", "Main Camera", "PayResult");
				}
			}
        }
		
		if (GUI.Button(new Rect(10,100,300,60), "pay 1 block")) {
			using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
				using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
					Debug.Log("PayResult=1");
            		pay(curActivity.GetRawObject(), "1", "Main Camera", "PayResult");
					Debug.Log("PayResult=2");
				}
			}
        }
				
		if (GUI.Button(new Rect(10,180,300,60), "viewMoreGames test")) {
			using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
				using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
            		viewMoreGames(curActivity.GetRawObject());
				}
			}
			}
			
		
			if (GUI.Button(new Rect(10,260,300,60), "onExitWithUI test")) {
				using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
					using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
	            		onExitWithUI(curActivity.GetRawObject());
					}
				}
			}
		
			
		if (GUI.Button(new Rect(10,340,300,60), "isPaid test")) {
				using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
					using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
	            		int ret = isPaid(curActivity.GetRawObject(), "0");
						if (ret == 1) {
							str = "isPaid =  TRUE";
						} else {
							str = "isPaid =  FALSE";
						}
					}
				}
			}
		
		if (GUI.Button(new Rect(10,420,300,60), "is isMusicEnabled")) {
				using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
					using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
	            		int ret = isMusicEnabled(curActivity.GetRawObject());
						if (ret == 1) {
							str = "isMusicEnabled =  TRUE";
						} else {
							str = "isMusicEnabled =  FALSE";
						}
					}
				}
			}
		
		
            //long userId = APaymentHelper.Instance.getUserId();
			//str = userId.ToString("D");
        
    } 
	// Use this for initialization
	void Start () {
		windowFunction = DoMyWindow;
	}
	
	// Update is called once per frame
	void Update () {

	}
	
	void PayResult(string result)
	{
		Debug.Log("------------PayResult="+result);
		
		str = "pay result = "+ result;

	}
	
	void Awake ()
	{
		if (Application.platform == RuntimePlatform.Android){
				using (AndroidJavaClass unityPlayer = new AndroidJavaClass ("com.unity3d.player.UnityPlayer")) {
				using (AndroidJavaObject curActivity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity")) {
					onInit (curActivity.GetRawObject());
				}
			}
		}
	}
}
