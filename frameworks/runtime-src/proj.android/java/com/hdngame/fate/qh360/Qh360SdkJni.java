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
    private static final String TAG = "Qh360SdkJni";

    public static void init() {
        System.out.println("Qh360SdkJni.init");

        Matrix.init(SdkManagerJni.activity);
    }

    public static void doSdkLogin() {
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

    // 登录、注册的回调
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


    private static SdkHttpTask sSdkHttpTask = null;
    private static String sUserId = null;
    private static String sUserName = null;
    private static void getUserInfo(String token) {
        System.out.println("Qh360SdkJni.getUserInfo token:" + token);

        String server = "https://openapi.360.cn/user/me.json";
        String url = String.format("%s?access_token=%s&fields=%s", server, token, "id,name");
        System.out.println("Qh360SdkJni.getUserInfo url:" + url);

        // 如果存在，取消上一次请求
        if (sSdkHttpTask != null) {
            sSdkHttpTask.cancel(true);
        }

        sSdkHttpTask = new SdkHttpTask(SdkManagerJni.activity);
        sSdkHttpTask.doGet(new SdkHttpListener() {
            @Override
            public void onResponse(String response) {
                System.out.println("sSdkHttpTask.onResponse:" + response);
                sSdkHttpTask = null;

                try {
                    JSONObject joResp = new JSONObject(response);
                    sUserId = joResp.optString("id");
                    sUserName = joResp.optString("name");

                    doSdkPay(_order, _identifier);

                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
            @Override
            public void onCancelled() {
                System.out.println("sSdkHttpTask.onCancelled");
                sSdkHttpTask = null;
            }
        }, url);
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

    public static void doSdkPay(String order, String identifier) {
        System.out.println("Qh360SdkJni.doSdkPay");
        System.out.println(order + ":" + identifier);


        Bundle bundle = new Bundle();
        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, true);
        bundle.putString(ProtocolKeys.QIHOO_USER_ID, sUserId); //???
        bundle.putString(ProtocolKeys.AMOUNT, "100");
        bundle.putString(ProtocolKeys.PRODUCT_NAME, "商品名称");
        bundle.putString(ProtocolKeys.PRODUCT_ID, "商品id");

        // 必需参数，应用方提供的支付结果通知uri，最大255字符。360服务器将把支付接口回调给该uri，具体协议请查看文档中，支付结果通知接口–应用服务器提供接口。
        bundle.putString(ProtocolKeys.NOTIFY_URI, "https://openapi.360.cn/status.html");

        // 必需参数，游戏或应用名称，最大16中文字。
        bundle.putString(ProtocolKeys.APP_NAME, "命运长夜");

        // 必需参数，应用内的用户名，如游戏角色名。 若应用内绑定360账号和应用账号，则可用360用户名，最大16中文字。（充值不分区服，
        // 充到统一的用户账户，各区服角色均可使用）。
        bundle.putString(ProtocolKeys.APP_USER_NAME, sUserName);

        // 必需参数，应用内的用户id。
        // 若应用内绑定360账号和应用账号，充值不分区服，充到统一的用户账户，各区服角色均可使用，则可用360用户ID最大32字符。
        bundle.putString(ProtocolKeys.APP_USER_ID, sUserId);

        // 可选参数，应用扩展信息1，原样返回，最大255字符。
//        bundle.putString(ProtocolKeys.APP_EXT_1, pay.getAppExt1());

        // 可选参数，应用扩展信息2，原样返回，最大255字符。
//        bundle.putString(ProtocolKeys.APP_EXT_2, pay.getAppExt2());

        // 可选参数，应用订单号，应用内必须唯一，最大32字符。
        bundle.putString(ProtocolKeys.APP_ORDER_ID, order);

        // 必需参数，使用360SDK的支付模块。
        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_PAY);

        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_PAY);
        intent.putExtras(bundle);




        // 启动接口
        Matrix.invokeActivity(SdkManagerJni.activity, intent, mPayCallback);
    }


    // 支付的回调
    protected static IDispatcherCallback mPayCallback = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
            Log.d(TAG, "Qh360SdkJni.mPayCallback, data is " + data);
            if(TextUtils.isEmpty(data)) {
                return;
            }

//            boolean isCallbackParseOk = false;
//            JSONObject jsonRes;
//            try {
//                jsonRes = new JSONObject(data);
//                // error_code 状态码： 0 支付成功， -1 支付取消， 1 支付失败， -2 支付进行中, 4010201和4009911 登录状态已失效，引导用户重新登录
//                // error_msg 状态描述
//                int errorCode = jsonRes.optInt("error_code");
//                isCallbackParseOk = true;
//                switch (errorCode) {
//                    case 0:
//                    case 1:
//                    case -1:
//                    case -2: {
//                        isAccessTokenValid = true;
//                        isQTValid = true;
//                        String errorMsg = jsonRes.optString("error_msg");
//                        String text = SdkManagerJni.activity.getString(R.string.pay_callback_toast, errorCode, errorMsg);
//                        Toast.makeText(SdkManagerJni.activity, text, Toast.LENGTH_SHORT).show();
//
//                    }
//                    break;
//                    case 4010201:
//                        //acess_token失效
//                        isAccessTokenValid = false;
//                        Toast.makeText(SdkManagerJni.activity, R.string.access_token_invalid, Toast.LENGTH_SHORT).show();
//                        break;
//                    case 4009911:
//                        //QT失效
//                        isQTValid = false;
//                        Toast.makeText(SdkManagerJni.activity, R.string.qt_invalid, Toast.LENGTH_SHORT).show();
//                        break;
//                    default:
//                        break;
//                }
//            } catch (Exception e) {
//                e.printStackTrace();
//            }
//
//            // 用于测试数据格式是否异常。
//            if (!isCallbackParseOk) {
//                Toast.makeText(SdkManagerJni.activity, SdkManagerJni.activity.getString(R.string.data_format_error), Toast.LENGTH_LONG).show();
//            }
        }
    };


//    protected Intent getPayIntent(QihooPayInfo pay) {
//        Bundle bundle = new Bundle();
//
//        // 界面相关参数，360SDK界面是否以横屏显示。
//        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, _isLandScape);
//
//        // *** 以下非界面相关参数 ***
//
//        // 设置QihooPay中的参数。
//
//        // 必需参数，360账号id，整数。
//        bundle.putString(ProtocolKeys.QIHOO_USER_ID, pay.getQihooUserId());
//
//        // 必需参数，所购买商品金额, 以分为单位。金额大于等于100分，360SDK运行定额支付流程； 金额数为0，360SDK运行不定额支付流程。
//        bundle.putString(ProtocolKeys.AMOUNT, pay.getMoneyAmount());
//
//        // 必需参数，所购买商品名称，应用指定，建议中文，最大10个中文字。
//        bundle.putString(ProtocolKeys.PRODUCT_NAME, pay.getProductName());
//
//        // 必需参数，购买商品的商品id，应用指定，最大16字符。
//        bundle.putString(ProtocolKeys.PRODUCT_ID, pay.getProductId());
//
//        // 必需参数，应用方提供的支付结果通知uri，最大255字符。360服务器将把支付接口回调给该uri，具体协议请查看文档中，支付结果通知接口–应用服务器提供接口。
//        bundle.putString(ProtocolKeys.NOTIFY_URI, pay.getNotifyUri());
//
//        // 必需参数，游戏或应用名称，最大16中文字。
//        bundle.putString(ProtocolKeys.APP_NAME, pay.getAppName());
//
//        // 必需参数，应用内的用户名，如游戏角色名。 若应用内绑定360账号和应用账号，则可用360用户名，最大16中文字。（充值不分区服，
//        // 充到统一的用户账户，各区服角色均可使用）。
//        bundle.putString(ProtocolKeys.APP_USER_NAME, pay.getAppUserName());
//
//        // 必需参数，应用内的用户id。
//        // 若应用内绑定360账号和应用账号，充值不分区服，充到统一的用户账户，各区服角色均可使用，则可用360用户ID最大32字符。
//        bundle.putString(ProtocolKeys.APP_USER_ID, pay.getAppUserId());
//
//        // 可选参数，应用扩展信息1，原样返回，最大255字符。
//        bundle.putString(ProtocolKeys.APP_EXT_1, pay.getAppExt1());
//
//        // 可选参数，应用扩展信息2，原样返回，最大255字符。
//        bundle.putString(ProtocolKeys.APP_EXT_2, pay.getAppExt2());
//
//        // 可选参数，应用订单号，应用内必须唯一，最大32字符。
//        bundle.putString(ProtocolKeys.APP_ORDER_ID, pay.getAppOrderId());
//
//        // 必需参数，使用360SDK的支付模块。
//        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_PAY);
//
//        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);
//        intent.putExtras(bundle);
//
//        return intent;
//    }


//    private static String parseAccessTokenFromLoginResult(String loginRes) {
//        try {
//            JSONObject joRes = new JSONObject(loginRes);
//            JSONObject joData = joRes.getJSONObject("data");
//            return joData.getString("access_token");
//        } catch (Exception e) {
//            e.printStackTrace();
//        }
//        return null;
//    }


//    private static boolean checkLoginInfo(QihooUserInfo info){
//        if (mIsInOffline) {
//            return true;
//        }
//        if(null == info || !info.isValid()){
//            Toast.makeText(SdkManagerJni.activity, "需要登录才能执行此操作", Toast.LENGTH_SHORT).show();
//            return false;
//        }
//        return true;
//    }

//    protected static QihooPayInfo getQihooPayInfo(boolean isFixed) {
//        QihooPayInfo payInfo = null;
//        if(isFixed) {
//            payInfo = getQihooPay(Constants.DEMO_FIXED_PAY_MONEY_AMOUNT);
//        }
//        else {
//            payInfo = getQihooPay(Constants.DEMO_NOT_FIXED_PAY_MONEY_AMOUNT);
//        }
//        return payInfo;
//    }
//
//    // payment begin
//    /***
//     * @param moneyAmount 金额数，使用者可以自由设定数额。金额数为100的整数倍，360SDK运行定额支付流程；
//     *            金额数为0，360SDK运行不定额支付流程。
//     * @return QihooPay
//     */
//    private static QihooPayInfo getQihooPay(String moneyAmount) {
//
//        String qihooUserId = (mQihooUserInfo != null) ? mQihooUserInfo.getId() : null;
//
//        // 创建QihooPay
//        QihooPayInfo qihooPay = new QihooPayInfo();
//        qihooPay.setQihooUserId(qihooUserId);
//        qihooPay.setMoneyAmount(moneyAmount);
//        qihooPay.setExchangeRate(Constants.DEMO_PAY_EXCHANGE_RATE);
//
//        qihooPay.setProductName(SdkManagerJni.activity.getString(R.string.demo_pay_product_name));
//        qihooPay.setProductId(Constants.DEMO_PAY_PRODUCT_ID);
//
//        qihooPay.setNotifyUri(Constants.DEMO_APP_SERVER_NOTIFY_URI);
//
//        qihooPay.setAppName(SdkManagerJni.activity.getString(R.string.demo_pay_app_name));
//        qihooPay.setAppUserName(SdkManagerJni.activity.getString(R.string.demo_pay_app_user_name));
//        qihooPay.setAppUserId(Constants.DEMO_PAY_APP_USER_ID);
//
//        // 可选参数
//        qihooPay.setAppExt1(SdkManagerJni.activity.getString(R.string.demo_pay_app_ext1));
//        qihooPay.setAppExt2(SdkManagerJni.activity.getString(R.string.demo_pay_app_ext2));
//        qihooPay.setAppOrderId(System.currentTimeMillis()+"");
//
//        return qihooPay;
//    }
//
//    // ------------------------获取社交服务器初始化信息接口--------------
//    public static void doSDKGetSocialInitInfo(QihooUserInfo usrInfo) {
//        if (!checkLoginInfo(usrInfo)) {
//            return;
//        }
//
//        Intent intent = getSocialInitInfoIntent();
//        Matrix.execute(SdkManagerJni.activity, intent, new IDispatcherCallback() {
//
//            @Override
//            public void onFinished(String data) {
//                Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_SHORT).show();
//            }
//        });
//    }
//
//    private static Intent getSocialInitInfoIntent() {
//        Intent intent = new Intent();
//        // function_code : 必须参数，表示调用SDK接口执行的功能为获取社交模块初始化信息
//        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_GET_SOCIAL_INIT_INFO);
//        return intent;
//    }
//
//    // ----------------------结合本地通信录获取可邀请好友列表-----------------
//    public static void doSdkGetContactContent(QihooUserInfo usrInfo){
//
//        if(!checkLoginInfo(usrInfo)) {
//            return;
//        }
//
//        Intent intent = getGetContactContentIntent();
//        Matrix.execute(SdkManagerJni.activity, intent, new IDispatcherCallback() {
//
//            @Override
//            public void onFinished(String data) {
//                Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_SHORT).show();
////                System.out.println(data);
//            }
//        });
//    }
//
//    private static Intent getGetContactContentIntent(){
//        Intent intent = new Intent();
//        /*
//         * 必须参数：
//         *  function_code : 必须参数，表示调用SDK接口执行的功能
//         *  screen_orientation : 必须参数，屏幕方向
//         *  start : 非必须参数，表示此次获取可邀请好友列表的开始位置，从0开始。
//         *          无此参数时会获取所有的可邀请好友列表，不进行翻页。
//         *  count : 非必须参数，表示此次获取可邀请好友的个数。
//         *          无此参数时会获取所有的可邀请好友列表，不进行翻页。
//        */
//        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, _isLandScape);
//        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_GET_CONTACT_CONTENT);
////        intent.putExtra(ProtocolKeys.START, mEditGetcontactStart.getText().toString());
////        intent.putExtra(ProtocolKeys.COUNT, mEditGetcontactCount.getText().toString());
//
//        return intent;
//    }
//
//    // -----------------------邀请好友---------------------
//    // usrInfo : 必须参数，用户信息
//    // bLandScape : 屏幕方向，true为横屏，flase为竖屏
//    public static void doSdkInviteFriend(QihooUserInfo usrInfo){
//        // 检查用户是否登录
//        if(!checkLoginInfo(usrInfo)) {
//            return;
//        }
//
//        Intent intent = getInviteFriendIntent();
//        Matrix.execute(SdkManagerJni.activity, intent, new IDispatcherCallback() {
//            @Override
//            public void onFinished(String data) {
//                Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_SHORT).show();
////                System.out.println(data);
//            }
//        });
//    }
//
//    // bLandScape : 屏幕方向，true为横屏，flase为竖屏
//    private static Intent getInviteFriendIntent(){
//
//        Intent intent = new Intent();
//
//        // 从界面读取输入数据
//        String strNick = "";
//        String strPhone = "";
//        String strQid = "";
//        String strSMS = "";
//
//        /*
//         * 必须参数：
//         *  function_code : 必须参数，表示调用SDK接口执行的功能为批量邀请好友
//         *  nick_name: 必须参数，对方的昵称
//         *  phone : 有值就要传入，加密后的好友电话。使用“获取可邀请好友列表”接口返回的phone字段中的值。
//         *  sms : 必须参数，邀请信息内容。
//         *  qid : 有值就要传入，被邀请用户的qid，如果没有可以不传
//         *  screen_orientation : 屏幕方向，bool值 true为横屏，flase为竖屏
//        */
//        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_INVITE_FRIEND_BATCH);
//        intent.putExtra(ProtocolKeys.NICK_NAME, strNick);
//        intent.putExtra(ProtocolKeys.PHONE, strPhone);
//        intent.putExtra(ProtocolKeys.QID, strQid);
//        intent.putExtra(ProtocolKeys.SMS, strSMS);
//        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, _isLandScape);
//        return intent;
//    }
//
//    public static void doSdkInviteFriendBySdk(QihooUserInfo usrinfo, boolean bLandScape) {
//        if (!checkLoginInfo(usrinfo)) {
//            return;
//        }
//        Intent intent = getInviteFriendBySdkIntent(bLandScape);
//        Matrix.invokeActivity(SdkManagerJni.activity, intent, new IDispatcherCallback() {
//
//            @Override
//            public void onFinished(String data) {
////                System.out.println("result: " + data);
//                Toast.makeText(SdkManagerJni.activity, "result: " + data, Toast.LENGTH_SHORT).show();
//            }
//        });
//    }
//
//    private static Intent getInviteFriendBySdkIntent(boolean bLandScape) {
//        /*
//         * function_code : 必须参数，表示调用SDK接口执行的功能
//         * screen_orientation : 360SDK界面是否以横屏显示。
//         * sms: 可选参数，邀请信息，不需要主语，sdk会添加。
//         */
//        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);
//        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_INVITE_FRIEND_BY_SDK);
//        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, bLandScape);
////        intent.putExtra(ProtocolKeys.SMS, inviteMsg);
//        return intent;
//
//    }
//
//    // ------------------------上传积分接口--------------------
//    // usrInfo : 必须参数，用户信息
//    protected static void doSdkUploadScore(QihooUserInfo usrInfo){
//        // 检查用户是否登录
//        if(!checkLoginInfo(usrInfo))
//            return;
//        Intent intent = getUploadScoreIntent();
//        Matrix.execute(SdkManagerJni.activity, intent, new IDispatcherCallback() {
//
//            @Override
//            public void onFinished(String data) {
//                Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_SHORT).show();
////                System.out.println(data);
//            }
//        });
//    }
//
//    private static Intent getUploadScoreIntent(){
//        Intent intent = new Intent();
//
//        // 从界面获取用户输入的数据
//        String strScore = "100";
//        String topnid;
////        EditText et = (EditText)findViewById(R.id.edit_upload_score);
////        EditText etTopnid = (EditText) findViewById(R.id.edit_score_topnid);
////        strScore = et.getText().toString();
////        topnid = etTopnid.getText().toString();
//
//        /*
//         * 必须参数：
//         *  function_code : 必须参数，表示调用SDK接口执行的功能为上传积分
//         *  score : 必须参数，用户积分。
//         *  topnid : 可选参数，排行榜标识，使用该参数需要确认对应ID的排行榜已经开通。
//        */
//        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_UPLOAD_SCORE);
//        intent.putExtra(ProtocolKeys.SCORE, strScore/*"100"*/);
////        intent.putExtra(ProtocolKeys.TOPNID, topnid);
//        return intent;
//    }
//
//    // -----------------------------获取好友排行榜接口---------------
//    // usrInfo : 必须参数，用户信息
//    protected void doSdkGetRankFriend(QihooUserInfo usrInfo){
//        // 检查用户是否登录
//        if(!checkLoginInfo(usrInfo)) {
//            return;
//        }
//        Intent intent = getGetGameTopFriendIntent();
//        Matrix.execute(SdkManagerJni.activity, intent, new IDispatcherCallback() {
//
//            @Override
//            public void onFinished(String data) {
//                Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_SHORT).show();
////                System.out.println(data);
//            }
//        });
//    }
//
//    private Intent getGetGameTopFriendIntent(){
//        Intent intent = new Intent();
//
//        String strStart = "0";
//        String strCount = "20";
//        String strTopNID;
//        String StrOrderby;
////        EditText et = (EditText)findViewById(R.id.edit_getgamefrient_top_start);
////        strStart = et.getText().toString();
////        et = (EditText)findViewById(R.id.edit_getgamefrient_top_count);
////        strCount = et.getText().toString();
////        et = (EditText)findViewById(R.id.edit_getgamefrient_topnid);
////        strTopNID = et.getText().toString();
////        et = (EditText)findViewById(R.id.edit_getgamefrient_orderby);
////        StrOrderby = et.getText().toString();
//        /*
//         * 必须参数：
//         *  function_code : 必须参数，表示调用SDK接口执行的功能为游戏的排行榜。
//        */
//        /*
//         * 可选参数：
//         *  start : 可选参数，排名榜的第几位开始获取(索引从0开始)
//         *  count : 可选参数，排名榜上从start开始，获取多少位,最小值为20。
//         *          start和count参数如果不传的话，会返回最多前20个排行榜内容。
//         *  topnid:可选参数，排行榜类型（不填写，则为默认的排行榜）
//         *  orderby:可选参数，排序类型（填写为0则按正序排序，其它情况按倒序排序）
//        */
//        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_GET_RANK_FRIENDS);
//        intent.putExtra(ProtocolKeys.START, strStart/*"0"*/);
//        intent.putExtra(ProtocolKeys.COUNT, strCount/*"20"*/);
////        intent.putExtra(ProtocolKeys.TOPNID, strTopNID);
////        intent.putExtra(ProtocolKeys.ORDERBY, StrOrderby);
//
//        return intent;
//    }
//
//    // -----------------------------获取全球排行榜接口---------------
//    // usrInfo : 必须参数，用户信息
//    protected void doSdkGetGlobalRankList(QihooUserInfo usrInfo){
//        // 检查用户是否登录
//        if(!checkLoginInfo(usrInfo)) {
//            return;
//        }
//        Intent intent = getGetGameGlobleRankListIntent();
//        Matrix.execute(SdkManagerJni.activity, intent, new IDispatcherCallback() {
//
//            @Override
//            public void onFinished(String data) {
//                Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_SHORT).show();
////                System.out.println(data);
//            }
//        });
//    }
//
//    private Intent getGetGameGlobleRankListIntent(){
//        Intent intent = new Intent();
//        String strTopNID;
//        String StrOrderby;
////        EditText et = (EditText)findViewById(R.id.edit_getgame_topnid);
////        strTopNID = et.getText().toString();
////        et = (EditText)findViewById(R.id.edit_getgame_orderby);
////        StrOrderby = et.getText().toString();
//        /*
//         * 必须参数：
//         *  function_code : 必须参数，表示调用SDK接口执行的功能为游戏的排行榜。
//        */
//        /*
//         * 可选参数：
//         *  topnid:可选参数，排行榜类型（不填写，则为默认的排行榜）
//         *  orderby:可选参数，排序类型（填写为0则按正序排序，其它情况按倒序排序）
//        */
//        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_GET_RANK);
////        intent.putExtra(ProtocolKeys.TOPNID, strTopNID);
////        intent.putExtra(ProtocolKeys.ORDERBY, StrOrderby);
//        return intent;
//    }
//
//    protected void doSdkDisplayGameFriendRank(QihooUserInfo usrInfo, boolean bLandScape) {
//        if (!checkLoginInfo(usrInfo)) {
//            return;
//        }
//        Intent intent = getDisplayGameFriendRankIntent(bLandScape);
//        Matrix.invokeActivity(SdkManagerJni.activity, intent, new IDispatcherCallback() {
//
//            @Override
//            public void onFinished(String data) {
////                System.out.println("result: " + data);
//                Toast.makeText(SdkManagerJni.activity, "result: " + data, Toast.LENGTH_SHORT).show();
//            }
//        });
//    }
//
//    private Intent getDisplayGameFriendRankIntent(boolean bLandScape) {
//
//        /*
//         * function_code : 必须参数，表示调用SDK接口执行的功能
//         * screen_orientation : 360SDK界面是否以横屏显示。
//         * topnid : 可选参数，排行榜ID
//         */
//        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);
//        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_DISPLAY_GAME_FRIEND_RANK);
//
////        String topnId = ((EditText)findViewById(R.id.et_rank_id)).getText().toString();
////        if (!TextUtils.isEmpty(topnId)) {
////            // 可选参数，排行榜ID，与上传积分时对应的排行榜ID对应，使用该参数，需要确定后台存在对应ID的排行榜，否则会显示错误
////            intent.putExtra(ProtocolKeys.TOPNID, topnId);
////        }
//
//        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, bLandScape);
//
//        return intent;
//    }
//
//    protected void doSdkGetUserInfo(QihooUserInfo usrinfo) {
//        if (!checkLoginInfo(usrinfo)) {
//            return;
//        }
//
//        Intent intent = getUserInfoIntent();
//        Matrix.execute(SdkManagerJni.activity, intent, new IDispatcherCallback() {
//
//            @Override
//            public void onFinished(String data) {
////                System.out.println(data);
//                Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_LONG).show();
//            }
//        });
//    }
//    private Intent getUserInfoIntent() {
////        EditText et = (EditText) findViewById(R.id.et_get_user_info);
////        String qid = et.getText().toString();
//
//        Intent intent = new Intent();
//        // function code
//        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_GET_USER_INFO);
//        // 用户QID
////        intent.putExtra(ProtocolKeys.QID, qid);
//
//        return intent;
//    }
//
//    //--------------分享--------------
//    protected void doSdkShare(QihooUserInfo usrInfo, final boolean bLandScape){
//        if(!checkLoginInfo(usrInfo)) {
//            return;
//        }
//
////        AlertDialog.Builder ab = new AlertDialog.Builder(SdkUserBaseActivity.this);
////
////        LinearLayout llt = (LinearLayout)SdkUserBaseActivity.this.getLayoutInflater().inflate(R.layout.share_weibo_layout, null);
////        final EditText etTitle = (EditText)llt.findViewById(R.id.edit_share_title);
////        final EditText etDesc = (EditText)llt.findViewById(R.id.edit_share_desc);
////        final EditText etPic = (EditText)llt.findViewById(R.id.edit_share_pic);
////        final EditText etUiBg = (EditText)llt.findViewById(R.id.edit_share_ui_bg);
////        final EditText etIcon = (EditText)llt.findViewById(R.id.edit_share_icon);
////        ab.setView(llt);
////
////        ab.setTitle("输入分享内容");
////        ab.setView(llt);
////        ab.setPositiveButton("确定", new DialogInterface.OnClickListener(){
////
////            @Override
////            public void onClick(DialogInterface dialog, int which) {
////                Intent intent = getShareIntent(etTitle.getText().toString(),
////                        etDesc.getText().toString(), etPic.getText().toString(),
////                        etIcon.getText().toString(), etUiBg.getText().toString(), bLandScape);
////                Matrix.invokeActivity(SdkUserBaseActivity.this, intent, new IDispatcherCallback() {
////
////                    @Override
////                    public void onFinished(String data) {
////                        if (null == data) {
////                            return;
////                        }
////                        Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_SHORT).show();
////                    }
////                });
////            }
////        });
////        ab.show();
//    }
//
//    public static void destroy() {
//        Matrix.destroy(SdkManagerJni.activity);
//    }
//
//    protected static void doSdkQuit(boolean isLandScape) {
//
//        Bundle bundle = new Bundle();
//
//        // 界面相关参数，360SDK界面是否以横屏显示。
//        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandScape);
//
//        // 必需参数，使用360SDK的退出模块。
//        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_QUIT);
//
//        // 可选参数，登录界面的背景图片路径，必须是本地图片路径
//        bundle.putString(ProtocolKeys.UI_BACKGROUND_PICTRUE, "");
//
//        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);
//        intent.putExtras(bundle);
//
//        Matrix.invokeActivity(SdkManagerJni.activity, intent, mQuitCallback);
//    }
//
//    // 退出的回调
//    private static IDispatcherCallback mQuitCallback = new IDispatcherCallback() {
//
//        @Override
//        public void onFinished(String data) {
////            Log.d(TAG, "mQuitCallback, data is " + data);
//            JSONObject json;
//            try {
//                json = new JSONObject(data);
//                int which = json.optInt("which", -1);
//                String label = json.optString("label");
//
//                Toast.makeText(SdkManagerJni.activity,
//                        "按钮标识：" + which + "，按钮描述:" + label, Toast.LENGTH_LONG)
//                        .show();
//
//                switch (which) {
//                    case 0: // 用户关闭退出界面
//                        return;
//                    default:// 退出游戏
////                        finish();
//                        return;
//                }
//            } catch (Exception e) {
//                e.printStackTrace();
//            }
//        }
//
//    };
//
//    protected static void doSdkBBS(QihooUserInfo usrinfo) {
//        if (!checkLoginInfo(usrinfo)) {
//            return;
//        }
//
//        if (!Utils.isNetAvailable(SdkManagerJni.activity)) {
//            Toast.makeText(SdkManagerJni.activity, "网络不可用", Toast.LENGTH_SHORT).show();
//            return;
//        }
//
//        Intent intent = getBBSIntent();
//
//        Matrix.invokeActivity(SdkManagerJni.activity, intent, null);
//    }
//
//    private static Intent getBBSIntent() {
//
//        Bundle bundle = new Bundle();
//
//        // 界面相关参数，360SDK界面是否以横屏显示。
//        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, _isLandScape);
//
//        // 必需参数，使用360SDK的论坛模块。
//        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_BBS);
//
//        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);
//        intent.putExtras(bundle);
//
//        return intent;
//    }
}
