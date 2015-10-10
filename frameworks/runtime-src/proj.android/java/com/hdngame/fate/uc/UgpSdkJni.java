package com.hdngame.fate.uc;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Toast;
import cn.uc.gamesdk.sa.UCGameSdk;
import cn.uc.gamesdk.sa.iface.open.ActivityLifeCycle;
import cn.uc.gamesdk.sa.iface.open.SDKConst;
import cn.uc.gamesdk.sa.iface.open.UCCallbackListener;
import cn.uc.gamesdk.sa.iface.open.UCGameSDKStatusCode;
import cn.uc.paysdk.SDKCore;
import cn.uc.paysdk.face.commons.*;
import cn.uc.paysdk.face.commons.PayResponse;
import cn.uc.paysdk.face.commons.Response;
import cn.uc.paysdk.face.commons.SDKCallbackListener;
import cn.uc.paysdk.face.commons.SDKError;
import cn.uc.paysdk.face.commons.SDKProtocolKeys;
import cn.uc.paysdk.face.commons.SDKStatus;
import com.hdngame.fate.GameUtils;
import com.hdngame.fate.SdkManagerJni;
import org.json.JSONException;
import org.json.JSONObject;

import java.lang.Override;
import java.lang.String;
import java.lang.SuppressWarnings;

/**
 * Created by yuxiao on 15/9/30.
 */
public class UgpSdkJni {

    public static void init() {
        System.out.println("UgpSdkJni.init");

        UCGameSdk.defaultSdk().setCallback(SDKConst.PAY_INIT_LISTENER, payInitListener);
        UCGameSdk.defaultSdk().setCallback(SDKConst.SDK_INIT_LISTENER, sdkInitListener);

        try {
            Bundle payInitData = new Bundle();
            UCGameSdk.defaultSdk().init(SdkManagerJni.activity, payInitData);
        }
        catch (Exception e) {

        }
    }

    final static UCCallbackListener<String> sdkInitListener = new UCCallbackListener<String>() {

        int callbackCode;
        String callbackMessage;

        @Override
        public void callback(int statuscode, String msg) {
            callbackCode = statuscode;
            callbackMessage = msg;
            System.out.println("sdkInitListener.callback");
            System.out.println(callbackMessage + ":" + callbackCode);

            SdkManagerJni.activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    switch (callbackCode) {
                        case UCGameSDKStatusCode.SUCCESS: {
//                            Toast.makeText(SdkManagerJni.activity, callbackMessage, Toast.LENGTH_LONG).show();
                        }
                        break;

                        default: {
                            Toast.makeText(SdkManagerJni.activity, callbackMessage, Toast.LENGTH_LONG).show();
                        }
                        break;
                    }
                }
            });
        }
    };

    final static SDKCallbackListener payInitListener = new SDKCallbackListener() {
        @SuppressWarnings("unused")
        @Override
        public void onSuccessful(int statusCode, Response response) {
            System.out.println("payInitListener.onSuccessful");
            System.out.println(statusCode + ":" +response.getMessage());

            int responseType = response.getType();
            if (responseType == Response.LISTENER_TYPE_INIT) {
                System.out.println("LISTENER_TYPE_INIT");
                // 用于处理初始化消息
//                Toast.makeText(SdkManagerJni.activity, "支付初始化成功啦!", Toast.LENGTH_LONG).show();
            }
            else if (responseType == Response.LISTENER_TYPE_PAY) {
                System.out.println("LISTENER_TYPE_PAY");
                /**
                 * 当为支付回调时，必须响应消息设置setMessage 必须及时响应，不要进行耗时操作，否则会导致线程阻塞
                 * 相关异步操作可以在handler中进行，另起工作者线程 设置为
                 * Response.OPERATE_SUCCESS_MSG 代表CP成功进行相关动作时，响应SDK
                 * Response.OPERATE_FAIL_MSG 代表CP进行相关动作失败时，响应SDK
                 */
                // #########################[重要，确认收到]############################
                response.setMessage(Response.OPERATE_SUCCESS_MSG);
                // #########################!!!!!!!!!!!!!!!!!!!!!!!!!############################

                try {
                    JSONObject data = new JSONObject(response.getData());

                    String orderId = data.getString(PayResponse.CP_ORDER_ID); // CP订单号
                    System.out.println("orderId:" + orderId);

                    String tradeId = data.getString(PayResponse.TRADE_ID); // 交易号
                    System.out.println("tradeId:" + tradeId);

                    String payMoney = data.getString(PayResponse.PAY_MONEY); // 支付金额
                    System.out.println("payMoney:" + payMoney);

                    String payType = data.getString(PayResponse.PAY_TYPE); // 支付类型 [207:支付宝快捷支付]
                    System.out.println("payType:" + payType);

                    String orderStatus = data.getString(PayResponse.ORDER_STATUS); // 订单状态 [00:成功][01:失败]
                    System.out.println("orderStatus:" + orderStatus);

                    String orderFinishTime = data.getString(PayResponse.ORDER_FINISH_TIME); // 订单完成时间
                    System.out.println("orderFinishTime:" + orderFinishTime);

                    String productName = data.getString(PayResponse.PRO_NAME);// 道具名称
                    System.out.println("productName:" + productName);

                    String extendInfo = data.optString(PayResponse.EXT_INFO); // 商品扩展信息
                    System.out.println("extendInfo:" + extendInfo);

                    String attachInfo = data.optString(PayResponse.ATTACH_INFO); // 附加透传信息
                    System.out.println("attachInfo:" + attachInfo);

                    onUgpSdkChargeCallback(0, orderId);
                }
                catch (JSONException ex) {
                    ex.printStackTrace();
                }
            }
        }

        public int errorCode;
        public String errorMessage;

        @Override
        public void onErrorResponse(SDKError error) {
            // 失败,该回调是在子线程中调用，UI操作需转到UI线程执行
            errorCode = error.getCode();
            errorMessage = error.getMessage();
            System.out.println("payInitListener.onErrorResponse");
            System.out.println(errorMessage + ":" + errorCode);

            SdkManagerJni.activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    switch (errorCode) {
                        case SDKStatus.ERROR_CODE_PAY_FAIL:
                            Toast.makeText(SdkManagerJni.activity, "支付失败", Toast.LENGTH_LONG).show();
                            break;
                        default:
                            Toast.makeText(SdkManagerJni.activity, errorMessage, Toast.LENGTH_LONG).show();
                            break;
                    }
                }
            });
        }
    };

    public static void pay(String order, String paycode, String jconfig) {
        System.out.println("UgpSdkJni.pay");
        System.out.println(order + ":" + paycode);

        String appName = GameUtils.getApplicationName(SdkManagerJni.activity);
        String amount;
        String productName;
        try {
            JSONObject config = new JSONObject(jconfig);
            amount = String.valueOf(config.getInt("pay_cost"));
            productName = config.getString("name");
        }
        catch (JSONException ex) {
            ex.printStackTrace();
            return;
        }
        System.out.println(appName + ":" + amount + ":" + productName);

        // 调起SDK支付界面
        Intent payIntent = new Intent();
        payIntent.putExtra(SDKProtocolKeys.APP_NAME, appName);
        payIntent.putExtra(SDKProtocolKeys.AMOUNT, amount); // 计费点价格
        payIntent.putExtra(SDKProtocolKeys.PRODUCT_NAME, productName);
        payIntent.putExtra(SDKProtocolKeys.CP_ORDER_ID, order);
        payIntent.putExtra(SDKProtocolKeys.PAY_CODE, paycode);
        payIntent.putExtra(SDKProtocolKeys.DEBUG_MODE, true);

        try {
            SDKCore.pay(SdkManagerJni.activity, payIntent, payInitListener);
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public static native void onUgpSdkChargeCallback(int result, String order);

    public static void exit() {
        System.out.println("UgpSdkJni.exit");

        SDKCore.exitSDK(SdkManagerJni.activity);
        UCGameSdk.defaultSdk().exit(null);
    }



    public static void onCreate() {
        System.out.println("UgpSdkJni.onCreate");
        UCGameSdk.defaultSdk().lifeCycle(SdkManagerJni.activity, ActivityLifeCycle.LIFE_ON_CREATE);
    }
    public static void onStart() {
        System.out.println("UgpSdkJni.onStart");
        UCGameSdk.defaultSdk().lifeCycle(SdkManagerJni.activity, ActivityLifeCycle.LIFE_ON_START);
    }
    public static void onRestart() {
        System.out.println("UgpSdkJni.onRestart");
        UCGameSdk.defaultSdk().lifeCycle(SdkManagerJni.activity, ActivityLifeCycle.LIFE_ON_RESTART);
    }
    public static void onResume() {
        System.out.println("UgpSdkJni.onResume");
        UCGameSdk.defaultSdk().lifeCycle(SdkManagerJni.activity, ActivityLifeCycle.LIFE_ON_RESUME);
    }
    public static void onPause() {
        System.out.println("UgpSdkJni.onPause");
        UCGameSdk.defaultSdk().lifeCycle(SdkManagerJni.activity, ActivityLifeCycle.LIFE_ON_PAUSE);
    }
    public static void onStop() {
        System.out.println("UgpSdkJni.onStop");
        UCGameSdk.defaultSdk().lifeCycle(SdkManagerJni.activity, ActivityLifeCycle.LIFE_ON_STOP);
    }
    public static void onDestory() {
        System.out.println("UgpSdkJni.onDestory");
        UCGameSdk.defaultSdk().lifeCycle(SdkManagerJni.activity, ActivityLifeCycle.LIFE_ON_DESTROY);
    }
    public static void onNewIntent(Intent intent) {
        System.out.println("UgpSdkJni.onNewIntent");
        UCGameSdk.defaultSdk().lifeCycle(SdkManagerJni.activity, ActivityLifeCycle.LIFE_ON_NEW_INTENT);
    }
}
