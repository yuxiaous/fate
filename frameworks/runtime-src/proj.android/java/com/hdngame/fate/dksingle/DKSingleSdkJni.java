package com.hdngame.fate.dksingle;


import com.duoku.platform.single.DKPlatform;
import com.duoku.platform.single.DKPlatformSettings;
import com.duoku.platform.single.DkErrorCode;
import com.duoku.platform.single.DkProtocolKeys;
import com.duoku.platform.single.callback.IDKSDKCallBack;
import com.hdngame.fate.SdkManagerJni;
import org.json.JSONObject;

/**
 * Created by yuxiao on 15/9/21.
 */
public class DKSingleSdkJni {

    public static void init() {
        System.out.println("DKSingleSdkJni.init");

        //初始化函数
        DKPlatform.getInstance().init(SdkManagerJni.activity, true,
                DKPlatformSettings.SdkMode.SDK_BASIC,
                null, null,
                new IDKSDKCallBack() {
                    @Override
                    public void onResponse(String paramString) {
                        System.out.println("DKSingleSdkJni.init.IDKSDKCallBack.onResponse");
                        System.out.println(paramString);

                        try {
                            JSONObject jsonObject = new JSONObject(paramString);
                            // 返回的操作状态码
                            int mFunctionCode = jsonObject.getInt(DkProtocolKeys.FUNCTION_CODE);

                            //初始化完成
                            if (mFunctionCode == DkErrorCode.BDG_CROSSRECOMMEND_INIT_FINSIH) {
                                initAds();
                            }

                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
                });
    }

    private static void initAds() {
        System.out.println("DKSingleSdkJni.initAds");

        DKPlatform.getInstance().bdgameInit(SdkManagerJni.activity,
                new IDKSDKCallBack() {
                    @Override
                    public void onResponse(String paramString) {
                        System.out.println("DKSingleSdkJni.initAds.IDKSDKCallBack.onResponse");
                        System.out.println(paramString);
                    }
                });
    }

    public static void pause() {
        System.out.println("DKSingleSdkJni.pause");

        DKPlatform.getInstance().bdgamePause(SdkManagerJni.activity,
                new IDKSDKCallBack() {
                    @Override
                    public void onResponse(String paramString) {
                        System.out.println("DKSingleSdkJni.pause.IDKSDKCallBack.onResponse");
                        System.out.println(paramString);
                    }
                });
    }

    public static void exit() {
        System.out.println("DKSingleSdkJni.exit");

        SdkManagerJni.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                DKPlatform.getInstance().bdgameExit(SdkManagerJni.activity,
                        new IDKSDKCallBack() {
                            @Override
                            public void onResponse(String paramString) {
                                System.out.println("DKSingleSdkJni.exit.IDKSDKCallBack.onResponse");
//                                System.out.println(paramString);

                                onDKSingleSdkExit();
                            }
                        });
            }
        });
    }

    public static native void onDKSingleSdkExit();

    public static void onPause() {
        System.out.println("DKSingleSdkJni.onPause");
        DKPlatform.getInstance().pauseBaiduMobileStatistic(SdkManagerJni.activity);
    }

    public static void onResume() {
        System.out.println("DKSingleSdkJni.onResume");
        DKPlatform.getInstance().resumeBaiduMobileStatistic(SdkManagerJni.activity);
    }
}
