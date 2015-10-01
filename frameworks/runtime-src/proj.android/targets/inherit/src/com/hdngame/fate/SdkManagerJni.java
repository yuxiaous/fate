package com.hdngame.fate;

import android.app.Activity;
import android.app.Application;
import android.content.Intent;

public class SdkManagerJni {
	public static Activity activity = null;
	public static Application application = null;

	public static native void setAppActivity(Activity a);
	public static native void activityOnCreate();
	public static native void activityOnPause();
	public static native void activityOnResume();
	public static native void activityOnDestroy();
	public static native void activityOnStart();
	public static native void activityOnRestart();
	public static native void activityOnStop();
	public static native void activityOnNewIntent(Intent intent);
}
