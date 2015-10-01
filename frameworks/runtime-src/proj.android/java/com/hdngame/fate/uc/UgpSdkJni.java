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
import cn.uc.paysdk.face.commons.Response;
import cn.uc.paysdk.face.commons.SDKCallbackListener;
import cn.uc.paysdk.face.commons.SDKError;
import cn.uc.paysdk.face.commons.SDKProtocolKeys;
import com.hdngame.fate.SdkManagerJni;

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
//            payInitData.putString(SDKProtocolKeys.APP_ID, "300008973569");
//            payInitData.putString(SDKProtocolKeys.APP_KEY, "044B0F69808C6151552A90ACF757A323");
            UCGameSdk.defaultSdk().init(SdkManagerJni.activity, payInitData);
        }
        catch (Exception e) {

        }
    }


    final static SDKCallbackListener payInitListener = new SDKCallbackListener() {
        @SuppressWarnings("unused")
        @Override
        public void onSuccessful(int statusCode, Response response) {
            System.out.println("payInitListener.onSuccessful");

            int responseType = response.getType();

            if (responseType == Response.LISTENER_TYPE_INIT) {
                // 用于处理初始化消息
                Toast.makeText(SdkManagerJni.activity, "支付初始化成功啦!", Toast.LENGTH_LONG).show();
            }
            else if (responseType == Response.LISTENER_TYPE_PAY) {
                // 用于处理历史订单的响应确认消息
                /**
                 * 当为支付回调时，必须响应消息设置setMessage 必须及时响应，不要进行耗时操作，否则会导致线程阻塞
                 * 相关异步操作可以在handler中进行，另起工作者线程 设置为
                 * Response.OPERATE_SUCCESS_MSG 代表CP成功进行相关动作时，响应SDK
                 * Response.OPERATE_FAIL_MSG 代表CP进行相关动作失败时，响应SDK
                 */
                // #########################[重要，确认收到]############################
                response.setMessage(Response.OPERATE_SUCCESS_MSG);
                // #########################!!!!!!!!!!!!!!!!!!!!!!!!!############################

//                try {
//                    JSONObject data = new JSONObject(response.getData());
//                    String orderId = data.getString(PayResponse.CP_ORDER_ID); // CP订单号
//                    String tradeId = data.getString(PayResponse.TRADE_ID); // 交易号
//                    String payMoney = data.getString(PayResponse.PAY_MONEY); // 支付金额
//                    String payType = data.getString(PayResponse.PAY_TYPE); // 支付类型
//                    // [207:支付宝快捷支付]
//                    String orderStatus = data.getString(PayResponse.ORDER_STATUS); // 订单状态
//                    // [00:成功][01:失败]
//                    String orderFinishTime = data.getString(PayResponse.ORDER_FINISH_TIME); // 订单完成时间
//                    String productName = data.getString(PayResponse.PRO_NAME);// 道具名称
//                    String extendInfo = data.optString(PayResponse.EXT_INFO); // 商品扩展信息
//                    String attachInfo = data.optString(PayResponse.ATTACH_INFO); // 附加透传信息
//                }
//                catch (JSONException ex) {
//                    ex.printStackTrace();
//                }
            }
        }

        @Override
        public void onErrorResponse(SDKError error) {
            System.out.println("payInitListener.onErrorResponse");
            // 失败,该回调是在子线程中调用，UI操作需转到UI线程执行

            String msg = error.getMessage();
            System.out.println(msg);

//            if (TextUtils.isEmpty(msg)) {
//                msg = "SDK occur error!";
//            }
//            Message message = new Message();
//            message.what = HANDLER_SHOW_ERRORDIALOG;
//            message.obj = msg;
//            handler.sendMessage(message);
        }
    };

    final static UCCallbackListener<String> sdkInitListener = new UCCallbackListener<String>() {
        @Override
        public void callback(int statuscode, String msg) {
            System.out.println("sdkInitListener.callback");
            System.out.println(msg);

            switch (statuscode) {
                case UCGameSDKStatusCode.SUCCESS: {
//                    firstTime = false;
//                    Message message = new Message();
//                    message.what = FlashMsg.HANDLER_END_LOGO_MSG1;
//                    handler.sendMessageDelayed(message, 3000);
                }
                break;

                default: {
//                    if (TextUtils.isEmpty(msg)) {
//                        msg = "SDK occur error!";
//                    }
//                    Message message = new Message();
//                    message.what = HANDLER_SHOW_ERRORDIALOG;
//                    message.obj = msg;
//                    handler.sendMessage(message);
//                    if (firstTime) {
//                        firstTime = false;
//                        message = new Message();
//                        message.what = FlashMsg.HANDLER_END_LOGO_MSG1;
//                        handler.sendMessageDelayed(message, 3000);
//                    }
                }
                break;
            }
        }
    };

    public static void pay(String order, String paycode) {
        System.out.println("UgpSdkJni.pay");
        System.out.println(order + ":" + paycode);

        // 调起SDK支付界面
        Intent payIntent = new Intent();
        payIntent.putExtra(SDKProtocolKeys.APP_NAME, "命运长夜测试");
        payIntent.putExtra(SDKProtocolKeys.CP_ORDER_ID, order);
        payIntent.putExtra(SDKProtocolKeys.PRODUCT_NAME, "product_name1");
        payIntent.putExtra(SDKProtocolKeys.AMOUNT, "2"); // 计费点价格
        // 如果需要设置服务端通知，可以在此设置订单的通知地址
        // payIntent.putExtra(SDKProtocolKeys.NOTIFY_URL,"http://10.1.84.183/receiveNotify.jsp");
        payIntent.putExtra(SDKProtocolKeys.DEBUG_MODE, true);
        //payIntent.putExtra(SDKProtocolKeys.ATTACH_INFO, "ATTACHINFOtest");
        //如果支持运营商sdk短代支付，那么需要先判断用户手机号，然后传入相对应的paycode
        payIntent.putExtra(SDKProtocolKeys.PAY_CODE, paycode); // demo现在是写死的paycode，实际需要cp传计费点

        try {
            SDKCore.pay(SdkManagerJni.activity, payIntent, payCallback);
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    final static SDKCallbackListener payCallback = new SDKCallbackListener() {
        @Override
        public void onSuccessful(int status, Response response) {
            System.out.println("payCallback.onSuccessful");
            int responseType = response.getType();

            if (responseType == Response.LISTENER_TYPE_INIT) {
//                firstTime = false;
//                Message msg = new Message();
//                msg.what = FlashMsg.HANDLER_END_LOGO_MSG1;
//                handler.sendMessageDelayed(msg, 3000);
            }
            else if(responseType == Response.LISTENER_TYPE_PAY) {
				/*重要：CP必须设置确认结果，告诉CP是否成功收到，不然SDK会不断回调通知CP*/
                response.setMessage(Response.OPERATE_SUCCESS_MSG);
                /*重要：CP必须设置确认结果，告诉CP是否成功收到，不然SDK会不断回调通知CP*/

//                Message msg = new Message();
//                msg.what = HANDLER_SDK_CALLBACK;
//                String s = response.getData();
//                if (s != null) {
//                    msg.obj = response.getData();
//                }
//                msg.arg1 = response.getStatus();
//                handler.sendMessage(msg);
            }
        }

        @Override
        public void onErrorResponse(SDKError error) {
            System.out.println("payCallback.onErrorResponse");

            String errorMsg = error.getMessage();
            System.out.println(errorMsg);


//            if (TextUtils.isEmpty(errorMsg))
//                errorMsg = "SDK occur error!";
//            Message msg = new Message();
//            msg.what = HANDLER_SHOW_ERRORDIALOG;
//            msg.obj = errorMsg;
//            handler.sendMessage(msg);
//            if (firstTime) {
//                firstTime = false;
//                msg = new Message();
//                msg.what = FlashMsg.HANDLER_END_LOGO_MSG1;
//                handler.sendMessageDelayed(msg, 3000);
//            }
        }
    };

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
