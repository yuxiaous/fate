package com.hdngame.fate.midas;

import android.util.Log;
import android.widget.Toast;
import com.hdngame.fate.SdkManagerJni;
import com.tencent.midas.api.APMidasPayAPI;
import com.tencent.midas.api.APMidasResponse;
import com.tencent.midas.api.IAPMidasPayCallBack;
import com.tencent.midas.api.request.APMidasGoodsRequest;
import com.tencent.midas.comm.APLog;
import org.json.JSONObject;

import java.security.MessageDigest;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by yuxiao on 15/9/7.
 */
public class TencentMidasSdkJni {

    public static int launchType;
    public static String appSecretKey;
    public static String offerId;
    public static String userId;
    public static String userKey;
    public static String sessionId;
    public static String sessionType;
    public static String pf;
    public static String pfKey;

    public static native int getLaunchType();
    public static native String getAppSecretKey();
    public static native String getOfferId();
    public static native String getUserId();
    public static native String getUserKey();
    public static native String getSessionId();
    public static native String getSessionType();
    public static native String getPf();
    public static native String getPfKey();

//    public static void setLaunchType(int launchType) {
//        TencentMidasSdkJni.launchType = launchType;
//    }
//    public static void setAppSecretKey(String appSecretKey) {
//        TencentMidasSdkJni.appSecretKey = appSecretKey;
//    }
//    public static void setOfferId(String offerId) {
//        TencentMidasSdkJni.offerId = offerId;
//    }
//    public static void setUserId(String userId) {
//        TencentMidasSdkJni.userId = userId;
//    }
//    public static void setUserKey(String userKey) {
//        TencentMidasSdkJni.userKey = userKey;
//    }
//    public static void setSessionId(String sessionId) {
//        TencentMidasSdkJni.sessionId = sessionId;
//    }
//    public static void setSessionType(String sessionType) {
//        TencentMidasSdkJni.sessionType = sessionType;
//    }
//    public static void setPf(String pf) {
//        TencentMidasSdkJni.pf = pf;
//    }
//    public static void setPfKey(String pfKey) {
//        TencentMidasSdkJni.pfKey = pfKey;
//    }

    private static String getMidasPluginVersion() {
        return APMidasPayAPI.getMidasPluginVersion();
    }

    private static String getMidasCoreVersion() {
        return APMidasPayAPI.getMidasCoreVersion(SdkManagerJni.activity);
    }


    public static void init() {
        System.out.println("TencentMidasSdkJni.init");

        launchType = getLaunchType();
        appSecretKey = getAppSecretKey();
        offerId = getOfferId();
        userId = getUserId();
        userKey = getUserKey();
        sessionId = getSessionId();
        sessionType = getSessionType();
        pf = getPf();
        pfKey = getPfKey();

        APMidasPayAPI.init(SdkManagerJni.activity);
        APMidasPayAPI.setEnv(APMidasPayAPI.ENV_TEST);
        APMidasPayAPI.setLogEnable(true);
    }

    private static IAPMidasPayCallBack payCallBack = new IAPMidasPayCallBack() {
        @Override
        public void MidasPayNeedLogin() {
            APLog.i("MidasPayCallBack", "NeedLogin" );
        }

        @Override
        public void MidasPayCallBack(APMidasResponse responseInfo)
        {
            Toast.makeText(SdkManagerJni.activity, "支付回调", Toast.LENGTH_LONG).show();
            APLog.i("MidasPayCallBack", "resultCode:" + responseInfo.resultCode);
            APLog.i("MidasPayCallBack", "resultMsg:" + responseInfo.resultMsg);
            APLog.i("MidasPayCallBack", "realSaveNum:" + responseInfo.realSaveNum);
            APLog.i("MidasPayCallBack", "payChannel:" + responseInfo.payChannel);
            APLog.i("MidasPayCallBack", "payState:" + responseInfo.payState);
            APLog.i("MidasPayCallBack", "provideState:" + responseInfo.provideState);
        }
    };
    public static void launchPay(String prodcutId, String order) {
        APMidasGoodsRequest request = new APMidasGoodsRequest();

        request.offerId = offerId;
        request.openId = userId;
        request.sessionId = sessionId;
        request.sessionType = sessionType;
        request.saveValue = "1";
        request.isCanChange = false;//false数量不可改，true 数量用户可以修改
        request.pf = pf;
        request.pfKey = pfKey;
        request.zoneId = "1";
        request.acctType ="common";
        request.openKey = userKey;

        if(launchType == 1) {
            request.tokenType = APMidasGoodsRequest.GETTOKENTYPE_CLIENT;
            request.prodcutId = getProdcutId(prodcutId, order);
        }
        else if(launchType == 2) {
            request.tokenType = APMidasGoodsRequest.GETTOKENTYPE_SDK;
            request.prodcutId = prodcutId;
        }

        APMidasPayAPI.launchPay(SdkManagerJni.activity, request, payCallBack);
    }

    //游戏客户端下单，获取物品信息
    private static String getProdcutId(String productInfo, String appTransferData)
    {
        try {
            JSONObject json = new JSONObject(productInfo);

            int unitPrice = json.getInt("unitPrice");//以Q点为单位，1Q币=10Q点
            String productId = json.getString("productId");
            String goodsName = json.getString("goodsName");
            String goodsDes = json.getString("goodsDes");

            String payItem = productId+"*"+unitPrice+"*"+1;
            String appMode = "1";
            String goodsMeta = goodsName+"*"+goodsDes;

            HashMap<String, String> urlEncodeParams = new HashMap<String, String>();
            urlEncodeParams.put("payitem", payItem);
            urlEncodeParams.put("appmode", appMode);
            urlEncodeParams.put("goodsmeta",goodsMeta);
            urlEncodeParams.put("app_metadata", appTransferData);

            String[] strArr = new String[5];
            strArr[0] = payItem;
            strArr[1] = appMode;
            strArr[2] = goodsMeta;
            strArr[3] = appTransferData;
            strArr[4] = appSecretKey;
            Arrays.sort(strArr);
            String str = strArr[0]+strArr[1]+strArr[2]+strArr[3]+strArr[4];
            urlEncodeParams.put("sig", encodeBySHA(str));

            return  mapToString(urlEncodeParams);
        }
        catch (Exception e) {
            APLog.e("getProdcutId", e.toString());
            return "";
        }
    }
    private static String mapToString(HashMap<String, String> encodeMap) {
        StringBuffer strBuff = new StringBuffer();
        for (Map.Entry<String, String> entry : encodeMap.entrySet()) {
            strBuff.append(entry.getKey());
            strBuff.append("=");
            strBuff.append(entry.getValue());
            strBuff.append("&");
        }
        if (strBuff.length() > 0) {
            strBuff.deleteCharAt(strBuff.length() - 1);
        }
        return strBuff.toString();
    }
    private static String encodeBySHA(String str)
    {
        try
        {
            MessageDigest md = MessageDigest.getInstance("SHA-1");
            md.update(str.getBytes("UTF-8"));
            byte[] result = md.digest();
            StringBuffer sb = new StringBuffer();
            for (byte b : result)
            {
                int i = b & 0xff;
                if (i < 0xf)
                {
                    sb.append(0);
                }
                sb.append(Integer.toHexString(i));
            }
            String str2=sb.toString().toUpperCase();

            return str2;
        }catch(Exception e)
        {
            return "";
        }
    }

}
