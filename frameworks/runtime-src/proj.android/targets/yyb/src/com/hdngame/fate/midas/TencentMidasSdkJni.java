package com.hdngame.fate.midas;

import com.hdngame.fate.SdkManagerJni;
import com.tencent.midas.api.APMidasPayAPI;

/**
 * Created by yuxiao on 15/9/7.
 */
public class TencentMidasSdkJni {

    public static void init() {
        System.out.println("TencentMidasSdkJni.init");

        APMidasPayAPI.init(SdkManagerJni.activity);
        APMidasPayAPI.setEnv("test");
        APMidasPayAPI.setLogEnable(true);
    }

    private static String getMidasPluginVersion() {
        return APMidasPayAPI.getMidasPluginVersion();
    }

    private static String getMidasCoreVersion() {
        return APMidasPayAPI.getMidasCoreVersion(SdkManagerJni.activity);
    }

    public static void launchPay() {
        APMidasGoodsRequest request = new APMidasGoodsRequest();
        request.offerId = "1450000766";


        request.openId = userId;
        request.openKey = userKey;
        request.sessionId = sessionId;
        request.sessionType = sessionType;
        request.zoneId = zoneId;
        request.pf = pf;
        request.pfKey = pfKey;
        request.saveValue = "1";
        request.acctType ="common";
        //request.resId = appBuyResId;
        request.tokenType = APMidasGoodsRequest.GETTOKENTYPE_CLIENT;
        APLog.i("登录", "tokenType:"+request.tokenType );
        //定额不可改
        request.prodcutId=getGoodsInfo(false);
        APMidasPayAPI.launchPay(MidasLoginActivity.this, request, MidasLoginActivity.this);
    }
}
