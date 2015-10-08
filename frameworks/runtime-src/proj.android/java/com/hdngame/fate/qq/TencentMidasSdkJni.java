package com.hdngame.fate.qq;

import android.util.Log;
import android.widget.Toast;
import com.hdngame.fate.SdkManagerJni;
import com.tencent.midas.api.APMidasPayAPI;
import com.tencent.midas.api.APMidasResponse;
import com.tencent.midas.api.IAPMidasPayCallBack;
import com.tencent.midas.api.request.APMidasBaseRequest;
import com.tencent.midas.api.request.APMidasGameRequest;
import com.tencent.midas.api.request.APMidasGoodsRequest;
import com.tencent.midas.comm.APLog;
import org.json.JSONObject;

import java.lang.Override;
import java.lang.String;
import java.security.MessageDigest;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by yuxiao on 15/9/7.
 */
public class TencentMidasSdkJni {

    public static native boolean isDebugMode();

    public static String offerId = "";
    public static String appKey = "";

    public static String openId = "uin_fate_id";
    public static String openKey = "uin_fate_key";

    public static String sessionType = "st_dummy";
    public static String sessionId = "hy_gameid";

    public static String zoneId = "1";

    public static String pf = "huyu_m-2001-android";
    public static String pfKey ="pfKey";


    private static String getMidasPluginVersion() {
        return APMidasPayAPI.getMidasPluginVersion();
    }

    private static String getMidasCoreVersion() {
        return APMidasPayAPI.getMidasCoreVersion(SdkManagerJni.activity);
    }

    public static void init(String offerId, String appKey) {
        System.out.println("TencentMidasSdkJni.init");

        TencentMidasSdkJni.offerId = offerId;
        TencentMidasSdkJni.appKey = appKey;

        APMidasBaseRequest request = new APMidasGameRequest();
        request.offerId = TencentMidasSdkJni.offerId;
        request.openId = openId;
        request.openKey = openKey;
        request.sessionType = sessionType;
        request.sessionId = sessionId;
        request.pf = pf;
        request.pfKey = pfKey;

        APMidasPayAPI.init(SdkManagerJni.activity, request);

        if(isDebugMode()) {
            System.out.println("debug");
            APMidasPayAPI.setEnv(APMidasPayAPI.ENV_TEST);
            APMidasPayAPI.setLogEnable(true);
        }
        else {
            System.out.println("release");
            APMidasPayAPI.setEnv(APMidasPayAPI.ENV_RELEASE);
            APMidasPayAPI.setLogEnable(false);
        }
    }

    private static String _order = "";

    private static String _name = "";
    private static int _price = 0;
    public static void launchPayClient(String order, String name, int price) {
        System.out.println("TencentMidasSdkJni.launchPayClient");
        System.out.println(order + ":" + name + ":" + price);

        _order = order;
        _name = name;
        _price = price;

        SdkManagerJni.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                APMidasGoodsRequest request = new APMidasGoodsRequest();

                request.offerId = TencentMidasSdkJni.offerId;

                request.openId = openId;
                request.openKey = openKey;
                request.sessionType = sessionType;
                request.sessionId = sessionId;
                request.pf = pf;
                request.pfKey = pfKey;
                request.zoneId = zoneId;

                request.acctType = APMidasPayAPI.ACCOUNT_TYPE_COMMON;
                request.saveValue = "1";
                request.isCanChange = false; //false数量不可改，true 数量用户可以修改

                request.tokenType = APMidasGoodsRequest.GETTOKENTYPE_CLIENT;
                request.prodcutId = getClientProdcutId(launchPayClient_name, launchPayClient_price);

                APMidasPayAPI.launchPay(SdkManagerJni.activity, request, payCallBack);
            }
        });
    }

    private static String _prodcutId = "";
    public static void launchPaySdk(String order, String prodcutId) {
        System.out.println("TencentMidasSdkJni.launchPaySdk");
        System.out.println(order + ":" + prodcutId);

        _order = order;
        _prodcutId = prodcutId;

        SdkManagerJni.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                APMidasGoodsRequest request = new APMidasGoodsRequest();

                request.offerId = TencentMidasSdkJni.offerId;

                request.openId = openId;
                request.openKey = openKey;
                request.sessionType = sessionType;
                request.sessionId = sessionId;
                request.pf = pf;
                request.pfKey = pfKey;
                request.zoneId = zoneId;

                request.acctType = APMidasPayAPI.ACCOUNT_TYPE_COMMON;
                request.saveValue = "1";
                request.isCanChange = false; //false数量不可改，true 数量用户可以修改;

                request.tokenType = APMidasGoodsRequest.GETTOKENTYPE_SDK;
                request.prodcutId = _prodcutId;

                APMidasPayAPI.launchPay(SdkManagerJni.activity, request, payCallBack);
            }
        });
    }

    final static IAPMidasPayCallBack payCallBack = new IAPMidasPayCallBack() {
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

    //游戏客户端下单，获取物品信息
    private static String getClientProdcutId(String name, int price)
    {
        int unitPrice = price;//以Q点为单位，1Q币=10Q点
        String goodsName = name;
        String goodsDes = "描述";
        String appTransferData = "12346jjjjjjj";
        String appKey = TencentMidasSdkJni.appKey; //后台单独配置的key
        String saveNum = "1";
        String productId = "12345678";

        HashMap<String, String> urlEncodeParams = new HashMap<String, String>();
        String payItem = productId + "*" + unitPrice + "*" + saveNum;
        String appMode = "1";
        String goodsMeta = goodsName + "*" + goodsDes;
        String[] strArr = new String[5];
        strArr[0] = payItem;
        strArr[1] = appMode;
        strArr[2] = goodsMeta;
        strArr[3] = appTransferData;
        strArr[4] = appKey;
//        APLog.i("APGoodsTokenReq", "排序前,payitem:" + strArr[0] + ";appmode:" + strArr[1] + ";goodsmeta:" + strArr[2] + ";appTransferData:" + strArr[3] + ";SecretKey:" + strArr[4]);
        Arrays.sort(strArr);
//        APLog.i("APGoodsTokenReq", "排序后,strArr[0]:"+strArr[0]+";strArr[1]:"+strArr[1]+";strArr[2]:"+strArr[2]+";strArr[3]:"+strArr[3]+";strArr[4]:"+strArr[4]);
        String str = strArr[0]+strArr[1]+strArr[2]+strArr[3]+strArr[4];

        urlEncodeParams.put("payitem", payItem);
        urlEncodeParams.put("appmode", appMode);
        urlEncodeParams.put("goodsmeta",goodsMeta);
        urlEncodeParams.put("app_metadata", appTransferData);
        urlEncodeParams.put("sig", encodeBySHA(str));

        return  mapToString(urlEncodeParams);
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
