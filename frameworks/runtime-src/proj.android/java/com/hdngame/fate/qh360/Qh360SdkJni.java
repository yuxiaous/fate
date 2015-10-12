package com.hdngame.fate.qh360;


import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.text.TextUtils;
import android.util.Log;
import android.widget.Toast;
import android.os.Bundle;
import com.hdngame.fate.GameUtils;
import com.hdngame.fate.SdkManagerJni;
//import com.hdngame.fate.qh360.payment.Constants;
import com.hdngame.fate.qh360.utils.*;
//import com.hdngame.fate.qh360.payment.QihooPayInfo;
import com.hdngame.fate.qh360.utils.SdkHttpTask;
import com.qihoo.gamecenter.sdk.matrix.Matrix;
import com.qihoo.gamecenter.sdk.activity.ContainerActivity;
import com.qihoo.gamecenter.sdk.protocols.ProtocolConfigs;
import com.qihoo.gamecenter.sdk.protocols.ProtocolKeys;
import com.qihoo.gamecenter.sdk.common.IDispatcherCallback;
import org.json.JSONException;
import org.json.JSONObject;

import java.lang.String;

/**
 * Created by yuxiao on 15/9/6.
 */
public class Qh360SdkJni {

    public static void init() {
        System.out.println("Qh360SdkJni.init");
        Matrix.init(SdkManagerJni.activity);
    }


    private static String _order = null;
    private static String _identifier = null;

    public static void pay(String order, String identifier) {
        System.out.println("Qh360SdkJni.pay");
        System.out.println(order + ":" + identifier);

        _order = order;
        _identifier = identifier;

        doSdkLogin();
    }

    private static void doSdkLogin() {
        System.out.println("Qh360SdkJni.doSdkLogin");

        SdkManagerJni.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);
                intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_LOGIN);
                intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, true);
                intent.putExtra(ProtocolKeys.IS_LOGIN_SHOW_CLOSE_ICON, true);
                intent.putExtra(ProtocolKeys.IS_SUPPORT_OFFLINE, false);
                intent.putExtra(ProtocolKeys.IS_SHOW_AUTOLOGIN_SWITCH, false);
                intent.putExtra(ProtocolKeys.IS_HIDE_WELLCOME, true);
                intent.putExtra(ProtocolKeys.IS_AUTOLOGIN_NOUI, true);
                intent.putExtra(ProtocolKeys.IS_SHOW_LOGINDLG_ONFAILED_AUTOLOGIN, true);

                if (GameUtils.isDebugMode()) {
                    System.out.println("debug");
                    intent.putExtra(ProtocolKeys.IS_SOCIAL_SHARE_DEBUG, true);
                }

                Matrix.execute(SdkManagerJni.activity, intent, mLoginCallback);
            }
        });
    }
    final static IDispatcherCallback mLoginCallback = new IDispatcherCallback() {

        @Override
        public void onFinished(String resp) {
            System.out.println("Qh360SdkJni.mLoginCallback " + resp);

            try {
                JSONObject joResp = new JSONObject(resp);
                int errno = joResp.optInt("errno", -1);
                if(errno == -1) {
                    String errmsg = joResp.optString("errmsg");
                    Toast.makeText(SdkManagerJni.activity, errmsg, Toast.LENGTH_LONG).show();
                }
                else {
                    JSONObject joData = joResp.getJSONObject("data");
                    String accessToken = joData.getString("access_token");
                    if(!TextUtils.isEmpty(accessToken)) {
                        System.out.println("Qh360SdkJni.mLoginCallback success, token: " + accessToken);

                        getUserInfo(accessToken);
                    }
                }
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
    };


    private static SdkHttpTask _sdkHttpTask = null;
    private static String _userId = null;
    private static String _userName = null;
    private static void getUserInfo(String token) {
        System.out.println("Qh360SdkJni.getUserInfo token:" + token);

        String server = "https://openapi.360.cn/user/me.json";
        String url = String.format("%s?access_token=%s&fields=%s", server, token, "id,name");
        System.out.println("Qh360SdkJni.getUserInfo url:" + url);

        // 如果存在，取消上一次请求
        if (_sdkHttpTask != null) {
            _sdkHttpTask.cancel(true);
        }

        _sdkHttpTask = new SdkHttpTask(SdkManagerJni.activity);
        _sdkHttpTask.doGet(new SdkHttpListener() {
            @Override
            public void onResponse(String response) {
                System.out.println("_sdkHttpTask.onResponse:" + response);
                _sdkHttpTask = null;

                try {
                    JSONObject joResp = new JSONObject(response);
                    _userId = joResp.optString("id");
                    _userName = joResp.optString("name");

                    doSdkPay();
                }
                catch (JSONException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void onCancelled() {
                System.out.println("_sdkHttpTask.onCancelled");
                _sdkHttpTask = null;
            }
        }, url);
    }

    private static void doSdkPay() {
        System.out.println("Qh360SdkJni.doSdkPay");

        Bundle bundle = new Bundle();
        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, true);
        bundle.putString(ProtocolKeys.QIHOO_USER_ID, _userId);
        bundle.putString(ProtocolKeys.AMOUNT, "100");
        bundle.putString(ProtocolKeys.PRODUCT_NAME, "商品名称");
        bundle.putString(ProtocolKeys.PRODUCT_ID, "商品id");
        bundle.putString(ProtocolKeys.NOTIFY_URI, "https://openapi.360.cn/status.html");
        bundle.putString(ProtocolKeys.APP_NAME, "命运长夜(单机版)");
        bundle.putString(ProtocolKeys.APP_USER_NAME, _userName);
        bundle.putString(ProtocolKeys.APP_USER_ID, _userId);
        bundle.putString(ProtocolKeys.APP_ORDER_ID, _order);
        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_PAY);

        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_PAY);
        intent.putExtras(bundle);

        Matrix.invokeActivity(SdkManagerJni.activity, intent, mPayCallback);
    }
    final static IDispatcherCallback mPayCallback = new IDispatcherCallback() {
        @Override
        public void onFinished(String resp) {
            System.out.println("Qh360SdkJni.mPayCallback, data is " + resp);
            if(TextUtils.isEmpty(resp)) {
                return;
            }

            JSONObject jsonRes;
            try {
                jsonRes = new JSONObject(resp);
                int errorCode = jsonRes.optInt("error_code");
                String errorMsg = jsonRes.optString("error_msg");
                Toast.makeText(SdkManagerJni.activity, errorMsg, Toast.LENGTH_SHORT).show();

                switch (errorCode) {
                    case 0:
                        onQh360ChargeCallback(0, _order);
                        break;
                    default:
                        break;
                }
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
    };
    public static native void onQh360ChargeCallback(int result, String order);


    public static void destroy() {
        System.out.println("Qh360SdkJni.destroy");
        Matrix.destroy(SdkManagerJni.activity);
    }

    public static void doSdkQuit() {
        System.out.println("Qh360SdkJni.doSdkQuit");

        Bundle bundle = new Bundle();
        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, true);
        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_QUIT);

        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);
        intent.putExtras(bundle);

        Matrix.invokeActivity(SdkManagerJni.activity, intent, mQuitCallback);
    }
    final static IDispatcherCallback mQuitCallback = new IDispatcherCallback() {
        @Override
        public void onFinished(String data) {
            System.out.println("Qh360SdkJni.mQuitCallback:" + data);

            try {
                JSONObject json = new JSONObject(data);
                int which = json.optInt("which", -1);
                switch (which) {
                    case 0: // 用户关闭退出界面
                        return;
                    default:// 退出游戏
                        onQh360Exit();
                        return;
                }
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
    };
    public static native void onQh360Exit();

}
