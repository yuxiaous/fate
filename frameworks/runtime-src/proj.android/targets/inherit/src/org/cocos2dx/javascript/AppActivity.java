/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.javascript;

import android.content.Intent;
import android.provider.Settings;
import com.hdngame.fate.GameUtils;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.pm.ActivityInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.view.WindowManager;

import com.hdngame.fate.SdkManagerJni;

import java.lang.Override;
import java.lang.String;


// The name of .so is specified in AndroidMenifest.xml. NativityActivity will load it automatically for you.
// You can use "System.loadLibrary()" to load other .so files.

public class AppActivity extends Cocos2dxActivity{

    static String hostIPAdress = "0.0.0.0";
    static String androidId = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        System.out.println("AppActivity.onCreate");

        // TODO Auto-generated method stub
        super.onCreate(savedInstanceState);
        
        if(nativeIsLandScape()) {
            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
        } else {
            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_PORTRAIT);
        }
        if(nativeIsDebug()){
            getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        }
        hostIPAdress = getHostIpAddress();
        androidId = Settings.Secure.getString(getContext().getContentResolver(), Settings.Secure.ANDROID_ID);

        // sdk manager
        SdkManagerJni.activity = this;
        SdkManagerJni.setAppActivity(this);
        SdkManagerJni.activityOnCreate();
    }
    
    @Override
    public Cocos2dxGLSurfaceView onCreateView() {
        Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
        // TestCpp should create stencil buffer
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

        return glSurfaceView;
    }

    public String getHostIpAddress() {
        WifiManager wifiMgr = (WifiManager) getSystemService(WIFI_SERVICE);
        WifiInfo wifiInfo = wifiMgr.getConnectionInfo();
        int ip = wifiInfo.getIpAddress();
        return ((ip & 0xFF) + "." + ((ip >>>= 8) & 0xFF) + "." + ((ip >>>= 8) & 0xFF) + "." + ((ip >>>= 8) & 0xFF));
    }
    
    public static String getLocalIpAddress() {
        return hostIPAdress;
    }

    public static String getAndroidId() {
        return androidId;
    }
    
    private static native boolean nativeIsLandScape();
    private static native boolean nativeIsDebug();

    @Override
    protected void onPause() {
        System.out.println("AppActivity.onPause");
        super.onPause();
        SdkManagerJni.activityOnPause();
    }

    @Override
    protected void onResume() {
        System.out.println("AppActivity.onResume");
        super.onResume();
        SdkManagerJni.activityOnResume();
    }

    @Override
    protected void onDestroy() {
        System.out.println("AppActivity.onDestroy");
        super.onDestroy();
        SdkManagerJni.activityOnDestroy();
    }

    @Override
    protected void onStart() {
        System.out.println("AppActivity.onStart");
        super.onStart();
        SdkManagerJni.activityOnStart();
    }

    @Override
    protected void onRestart() {
        System.out.println("AppActivity.onRestart");
        super.onRestart();
        SdkManagerJni.activityOnRestart();
    }

    @Override
    protected void onStop() {
        System.out.println("AppActivity.onStop");
        super.onStop();
        SdkManagerJni.activityOnStop();
    }

    @Override
    protected void onNewIntent(Intent intent) {
        System.out.println("AppActivity.onNewIntent");
        super.onNewIntent(intent);
        SdkManagerJni.activityOnNewIntent(intent);
    }
}
