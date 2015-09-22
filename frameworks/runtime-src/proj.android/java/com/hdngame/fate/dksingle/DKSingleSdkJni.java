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


        IDKSDKCallBack initcompletelistener = new IDKSDKCallBack() {
            @Override
            public void onResponse(String paramString) {
                System.out.println("IDKSDKCallBack.onResponse 1");
                System.out.println(paramString);

                try {
                    JSONObject jsonObject = new JSONObject(paramString);
                    // 返回的操作状态码
                    int mFunctionCode = jsonObject.getInt(DkProtocolKeys.FUNCTION_CODE);

                    //初始化完成
                    if (mFunctionCode == DkErrorCode.BDG_CROSSRECOMMEND_INIT_FINSIH) {
//                                initAds();
                        DKPlatform.getInstance().bdgameInit(SdkManagerJni.activity,
                                new IDKSDKCallBack() {
                                    @Override
                                    public void onResponse(String paramString) {
                                        System.out.println("IDKSDKCallBack.onResponse 2");
                                        System.out.println(paramString);
                                    }
                                });
                    }

                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };

                //初始化函数
        DKPlatform.getInstance().init(SdkManagerJni.activity, true,
                DKPlatformSettings.SdkMode.SDK_BASIC,
                null, null,
                initcompletelistener);
    }
}
