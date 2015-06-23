package com.fate.dev;

import android.app.Activity;

public class SdkJni {
	
	static Activity _activity = null;
	public void setActivity(Activity act) {
		_activity = act;
	}
	
    public void init() {
    	
    }
}
