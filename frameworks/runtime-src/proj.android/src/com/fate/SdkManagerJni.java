package com.fate;

import android.app.Activity;
import android.app.Application;

public class SdkManagerJni {
	public static Activity activity = null;
	public static Application application = null;

	public static native void configureSdk();
	public static native void activityOnCreate();
	public static native void activityOnPause();
	public static native void activityOnResume();
}
