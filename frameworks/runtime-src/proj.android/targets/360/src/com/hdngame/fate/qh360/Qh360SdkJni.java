package com.hdngame.fate.qh360;


import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.text.TextUtils;
import android.util.Log;
import android.widget.Toast;
import android.os.Bundle;
import com.hdngame.fate.SdkManagerJni;
import com.hdngame.fate.qh360.payment.Constants;
import com.hdngame.fate.qh360.utils.ProgressUtil;
import com.hdngame.fate.qh360.utils.QihooUserInfo;
import com.hdngame.fate.qh360.utils.QihooUserInfoListener;
import com.hdngame.fate.qh360.utils.QihooUserInfoTask;
import com.hdngame.fate.qh360.payment.QihooPayInfo;
import com.qihoo.gamecenter.sdk.matrix.Matrix;
import com.qihoo.gamecenter.sdk.activity.ContainerActivity;
import com.qihoo.gamecenter.sdk.protocols.ProtocolConfigs;
import com.qihoo.gamecenter.sdk.protocols.ProtocolKeys;
import com.qihoo.gamecenter.sdk.common.IDispatcherCallback;
import org.json.JSONObject;

/**
 * Created by yuxiao on 15/9/6.
 */
public class Qh360SdkJni {
    private static final String TAG = "Qh360SdkJni";
    protected static boolean _isSupportOffline = false;
    protected static boolean _isLandScape = true;
    protected static boolean _isShowClose = true;
    protected static boolean _isShowSwitchButton = true;
    protected static boolean _isHideWellcome = false;
    protected static boolean _isShowDlgOnFailedAutoLogin = true;
    protected static boolean _isAutoLoginHideUI = false;
    protected static boolean _isDebugSocialShare = true;
    protected static boolean _isPayFixed = true;

    protected static String  mAccessToken = null;
    protected static boolean mIsInOffline = false;
    protected static boolean isAccessTokenValid = true;
    protected static boolean isQTValid = true;
    protected static QihooUserInfo mQihooUserInfo;

    public static void init() {
        System.out.println("Qh360SdkJni.init");

        Matrix.init(SdkManagerJni.activity);
    }

    public static void doSdkLogin() {
        System.out.println("Qh360SdkJni.doSdkLogin");

        SdkManagerJni.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mIsInOffline = false;

                Intent intent = getLoginIntent();
                IDispatcherCallback callback = mLoginCallback;
                if (_isSupportOffline) {
                    callback = mLoginCallbackSupportOffline;
                }
                Matrix.execute(SdkManagerJni.activity, intent, callback);
            }
        });
    }

    public static void doSdkSwitchAccount() {
        System.out.println("Qh360SdkJni.doSdkSwitchAccount");

        SdkManagerJni.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Intent intent = getSwitchAccountIntent();
                IDispatcherCallback callback = mAccountSwitchCallback;
                if (_isSupportOffline) {
                    callback = mAccountSwitchSupportOfflineCB;
                }
                Matrix.invokeActivity(SdkManagerJni.activity, intent, callback);
            }
        });
    }

    protected void doSdkPay(QihooUserInfo usrinfo) {
        System.out.println("Qh360SdkJni.doSdkPay");

        if (!checkLoginInfo(usrinfo)) {
            return;
        }

        if(!isAccessTokenValid) {
            Toast.makeText(SdkManagerJni.activity, R.string.access_token_invalid, Toast.LENGTH_SHORT).show();
            return;
        }
        if(!isQTValid) {
            Toast.makeText(SdkManagerJni.activity, R.string.qt_invalid, Toast.LENGTH_SHORT).show();
            return;
        }

        // 支付基础参数
        QihooPayInfo payInfo = getQihooPayInfo(_isPayFixed);
        Intent intent = getPayIntent(payInfo);

        // 必需参数，使用360SDK的支付模块。
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_PAY);

        // 启动接口
        Matrix.invokeActivity(SdkManagerJni.activity, intent, mPayCallback);
    }


    // 登录、注册的回调
    private static IDispatcherCallback mLoginCallback = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
            System.out.println("Qh360SdkJni.mLoginCallback " + data);

            // press back
            if (isCancelLogin(data)) {
                return;
            }
            // 显示一下登录结果
            Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_LONG).show();
            mIsInOffline = false;
            mQihooUserInfo = null;

            // 解析access_token
            mAccessToken = parseAccessTokenFromLoginResult(data);

            if (!TextUtils.isEmpty(mAccessToken)) {
                // 需要去应用的服务器获取用access_token获取一下带qid的用户信息
                getUserInfo();
            } else {
                Toast.makeText(SdkManagerJni.activity, "get access_token failed!", Toast.LENGTH_LONG).show();
            }
        }
    };


    private static IDispatcherCallback mLoginCallbackSupportOffline = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
            System.out.println("Qh360SdkJni.mLoginCallbackSupportOffline " + data);

            if (isCancelLogin(data)) {
                return;
            }

            try {
                JSONObject joRes = new JSONObject(data);
                JSONObject joData = joRes.getJSONObject("data");
                String mode = joData.optString("mode", "");
                if (!TextUtils.isEmpty(mode) && mode.equals("offline")) {
                    Toast.makeText(SdkManagerJni.activity, "login success in offline mode", Toast.LENGTH_SHORT).show();
                    mIsInOffline = true;

                    // 显示一下登录结果
                    Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_LONG).show();
                } else {
                    mLoginCallback.onFinished(data);
                }
            } catch (Exception e) {
                Log.e(TAG, "mLoginCallbackSupportOffline exception", e);
            }

        }
    };

    // 切换账号的回调
    private static IDispatcherCallback mAccountSwitchCallback = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
            // press back
            if (isCancelLogin(data)) {
                return;
            }

            // 显示一下登录结果
            Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_LONG).show();

//            Log.d(TAG, "mAccountSwitchCallback, data is " + data);
            // 解析access_token
            mAccessToken = parseAccessTokenFromLoginResult(data);

            if (!TextUtils.isEmpty(mAccessToken)) {
                // 需要去应用的服务器获取用access_token获取一下带qid的用户信息
                getUserInfo();
            } else {
                Toast.makeText(SdkManagerJni.activity, "get access_token failed!", Toast.LENGTH_LONG).show();
            }
        }
    };

    // 支持离线模式的切换账号的回调
    private static IDispatcherCallback mAccountSwitchSupportOfflineCB = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
            // press back
            if (isCancelLogin(data)) {
                return;
            }
            // 显示一下登录结果
            Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_LONG).show();
//            Log.d(TAG, "mAccountSwitchSupportOfflineCB, data is " + data);
            // 解析access_token
            mAccessToken = parseAccessTokenFromLoginResult(data);

            if (!TextUtils.isEmpty(mAccessToken)) {
                // 登录结果直接返回的userinfo中没有qid，需要去应用的服务器获取用access_token获取一下带qid的用户信息
                getUserInfo();
            } else {
                Toast.makeText(SdkManagerJni.activity, "get access_token failed!", Toast.LENGTH_LONG).show();
            }
        }
    };

    // 支付的回调
    protected static IDispatcherCallback mPayCallback = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
//            Log.d(TAG, "mPayCallback, data is " + data);
            if(TextUtils.isEmpty(data)) {
                return;
            }

            boolean isCallbackParseOk = false;
            JSONObject jsonRes;
            try {
                jsonRes = new JSONObject(data);
                // error_code 状态码： 0 支付成功， -1 支付取消， 1 支付失败， -2 支付进行中, 4010201和4009911 登录状态已失效，引导用户重新登录
                // error_msg 状态描述
                int errorCode = jsonRes.optInt("error_code");
                isCallbackParseOk = true;
                switch (errorCode) {
                    case 0:
                    case 1:
                    case -1:
                    case -2: {
                        isAccessTokenValid = true;
                        isQTValid = true;
                        String errorMsg = jsonRes.optString("error_msg");
                        String text = SdkManagerJni.activity.getString(R.string.pay_callback_toast, errorCode, errorMsg);
                        Toast.makeText(SdkManagerJni.activity, text, Toast.LENGTH_SHORT).show();

                    }
                    break;
                    case 4010201:
                        //acess_token失效
                        isAccessTokenValid = false;
                        Toast.makeText(SdkManagerJni.activity, R.string.access_token_invalid, Toast.LENGTH_SHORT).show();
                        break;
                    case 4009911:
                        //QT失效
                        isQTValid = false;
                        Toast.makeText(SdkManagerJni.activity, R.string.qt_invalid, Toast.LENGTH_SHORT).show();
                        break;
                    default:
                        break;
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

            // 用于测试数据格式是否异常。
            if (!isCallbackParseOk) {
                Toast.makeText(SdkManagerJni.activity, SdkManagerJni.activity.getString(R.string.data_format_error), Toast.LENGTH_LONG).show();
            }
        }
    };

    private static Intent getLoginIntent() {

        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);

        // 必需参数，使用360SDK的登录模块。
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_LOGIN);

        // 界面相关参数，360SDK界面是否以横屏显示。
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, _isLandScape);

        //是否显示关闭按钮
        intent.putExtra(ProtocolKeys.IS_LOGIN_SHOW_CLOSE_ICON, _isShowClose);

        // 可选参数，是否支持离线模式，默认值为false
        intent.putExtra(ProtocolKeys.IS_SUPPORT_OFFLINE, _isSupportOffline);

        // 可选参数，是否在自动登录的过程中显示切换账号按钮
        intent.putExtra(ProtocolKeys.IS_SHOW_AUTOLOGIN_SWITCH, _isShowSwitchButton);

        // 可选参数，是否隐藏欢迎界面
        intent.putExtra(ProtocolKeys.IS_HIDE_WELLCOME, _isHideWellcome);

        // 可选参数，登录界面的背景图片路径，必须是本地图片路径
//        intent.putExtra(ProtocolKeys.UI_BACKGROUND_PICTRUE, getUiBackgroundPicPath());

        // 可选参数，指定assets中的图片路径，作为背景图
//        intent.putExtra(ProtocolKeys.UI_BACKGROUND_PICTURE_IN_ASSERTS, getUiBackgroundPathInAssets());

        //-- 以下参数仅仅针对自动登录过程的控制
        // 可选参数，自动登录过程中是否不展示任何UI，默认展示。
        intent.putExtra(ProtocolKeys.IS_AUTOLOGIN_NOUI, _isAutoLoginHideUI);

        // 可选参数，静默自动登录失败后是否显示登录窗口，默认不显示
        intent.putExtra(ProtocolKeys.IS_SHOW_LOGINDLG_ONFAILED_AUTOLOGIN, _isShowDlgOnFailedAutoLogin);

        // 测试参数，发布时要去掉
        intent.putExtra(ProtocolKeys.IS_SOCIAL_SHARE_DEBUG, _isDebugSocialShare);

        return intent;
    }

    private static Intent getSwitchAccountIntent() {

        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);

        // 必需参数，使用360SDK的切换账号模块。
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_SWITCH_ACCOUNT);

        // 必须参数，360SDK界面是否以横屏显示。
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, _isLandScape);

        //是否显示关闭按钮
        intent.putExtra(ProtocolKeys.IS_LOGIN_SHOW_CLOSE_ICON, _isShowClose);

        // 可选参数，是否支持离线模式，默认值为false
        intent.putExtra(ProtocolKeys.IS_SUPPORT_OFFLINE, _isSupportOffline);

        // 可选参数，是否隐藏欢迎界面
        intent.putExtra(ProtocolKeys.IS_HIDE_WELLCOME, _isHideWellcome);

        /*
         * 指定界面背景（可选参数）：
         *  1.ProtocolKeys.UI_BACKGROUND_PICTRUE 使用的系统路径，如/sdcard/1.png
         *  2.ProtocolKeys.UI_BACKGROUND_PICTURE_IN_ASSERTS 使用的assest中的图片资源，
         *    如传入bg.png字符串，就会在assets目录下加载这个指定的文件
         *  3.图片大小不要超过5M，尺寸不要超过1280x720
         */
        // 可选参数，登录界面的背景图片路径，必须是本地图片路径
        // 可选参数，登录界面的背景图片路径，必须是本地图片路径
//        intent.putExtra(ProtocolKeys.UI_BACKGROUND_PICTRUE, getUiBackgroundPicPath());
        // 可选参数，指定assets中的图片路径，作为背景图
//        intent.putExtra(ProtocolKeys.UI_BACKGROUND_PICTURE_IN_ASSERTS, getUiBackgroundPathInAssets());

        // 测试参数，发布时要去掉
        intent.putExtra(ProtocolKeys.IS_SOCIAL_SHARE_DEBUG, _isDebugSocialShare);

        return intent;
    }

    protected Intent getPayIntent(QihooPayInfo pay) {
        Bundle bundle = new Bundle();

        // 界面相关参数，360SDK界面是否以横屏显示。
        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, _isLandScape);

        // *** 以下非界面相关参数 ***

        // 设置QihooPay中的参数。

        // 必需参数，360账号id，整数。
        bundle.putString(ProtocolKeys.QIHOO_USER_ID, pay.getQihooUserId());

        // 必需参数，所购买商品金额, 以分为单位。金额大于等于100分，360SDK运行定额支付流程； 金额数为0，360SDK运行不定额支付流程。
        bundle.putString(ProtocolKeys.AMOUNT, pay.getMoneyAmount());

        // 必需参数，所购买商品名称，应用指定，建议中文，最大10个中文字。
        bundle.putString(ProtocolKeys.PRODUCT_NAME, pay.getProductName());

        // 必需参数，购买商品的商品id，应用指定，最大16字符。
        bundle.putString(ProtocolKeys.PRODUCT_ID, pay.getProductId());

        // 必需参数，应用方提供的支付结果通知uri，最大255字符。360服务器将把支付接口回调给该uri，具体协议请查看文档中，支付结果通知接口–应用服务器提供接口。
        bundle.putString(ProtocolKeys.NOTIFY_URI, pay.getNotifyUri());

        // 必需参数，游戏或应用名称，最大16中文字。
        bundle.putString(ProtocolKeys.APP_NAME, pay.getAppName());

        // 必需参数，应用内的用户名，如游戏角色名。 若应用内绑定360账号和应用账号，则可用360用户名，最大16中文字。（充值不分区服，
        // 充到统一的用户账户，各区服角色均可使用）。
        bundle.putString(ProtocolKeys.APP_USER_NAME, pay.getAppUserName());

        // 必需参数，应用内的用户id。
        // 若应用内绑定360账号和应用账号，充值不分区服，充到统一的用户账户，各区服角色均可使用，则可用360用户ID最大32字符。
        bundle.putString(ProtocolKeys.APP_USER_ID, pay.getAppUserId());

        // 可选参数，应用扩展信息1，原样返回，最大255字符。
        bundle.putString(ProtocolKeys.APP_EXT_1, pay.getAppExt1());

        // 可选参数，应用扩展信息2，原样返回，最大255字符。
        bundle.putString(ProtocolKeys.APP_EXT_2, pay.getAppExt2());

        // 可选参数，应用订单号，应用内必须唯一，最大32字符。
        bundle.putString(ProtocolKeys.APP_ORDER_ID, pay.getAppOrderId());

        // 必需参数，使用360SDK的支付模块。
        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_PAY);

        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);
        intent.putExtras(bundle);

        return intent;
    }

    private static boolean isCancelLogin(String data) {
        try {
            JSONObject joData = new JSONObject(data);
            int errno = joData.optInt("errno", -1);
            if (-1 == errno) {
                Toast.makeText(SdkManagerJni.activity, data, Toast.LENGTH_LONG).show();
                return true;
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    private static String parseAccessTokenFromLoginResult(String loginRes) {
        try {
            JSONObject joRes = new JSONObject(loginRes);
            JSONObject joData = joRes.getJSONObject("data");
            return joData.getString("access_token");
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    private static void getUserInfo() {
        final QihooUserInfoTask mUserInfoTask = QihooUserInfoTask.newInstance();

        // 提示用户进度
        final ProgressDialog progress = ProgressUtil.show(SdkManagerJni.activity,
                R.string.get_user_title,
                R.string.get_user_message,
                new DialogInterface.OnCancelListener() {
                    @Override
                    public void onCancel(DialogInterface dialog) {
                        if (mUserInfoTask != null) {
                            mUserInfoTask.doCancel();
                        }
                    }
                });

        // 请求应用服务器，用AccessToken换取UserInfo
        mUserInfoTask.doRequest(SdkManagerJni.activity,
                mAccessToken,
                Matrix.getAppKey(SdkManagerJni.activity),
                new QihooUserInfoListener() {

                    @Override
                    public void onGotUserInfo(QihooUserInfo userInfo) {
                        progress.dismiss();
                        if (null == userInfo || !userInfo.isValid()) {
                            Toast.makeText(SdkManagerJni.activity, "从应用服务器获取用户信息失败", Toast.LENGTH_LONG).show();
                        } else {
//                            SdkUserBaseActivity.this.onGotUserInfo(userInfo);
                        }
                    }
                });
    }

    private static boolean checkLoginInfo(QihooUserInfo info){
        if (mIsInOffline) {
            return true;
        }
        if(null == info || !info.isValid()){
            Toast.makeText(SdkManagerJni.activity, "需要登录才能执行此操作", Toast.LENGTH_SHORT).show();
            return false;
        }
        return true;
    }

    protected static QihooPayInfo getQihooPayInfo(boolean isFixed) {
        QihooPayInfo payInfo = null;
        if(isFixed) {
            payInfo = getQihooPay(Constants.DEMO_FIXED_PAY_MONEY_AMOUNT);
        }
        else {
            payInfo = getQihooPay(Constants.DEMO_NOT_FIXED_PAY_MONEY_AMOUNT);
        }
        return payInfo;
    }

    // payment begin
    /***
     * @param moneyAmount 金额数，使用者可以自由设定数额。金额数为100的整数倍，360SDK运行定额支付流程；
     *            金额数为0，360SDK运行不定额支付流程。
     * @return QihooPay
     */
    private static QihooPayInfo getQihooPay(String moneyAmount) {

        String qihooUserId = (mQihooUserInfo != null) ? mQihooUserInfo.getId() : null;

        // 创建QihooPay
        QihooPayInfo qihooPay = new QihooPayInfo();
        qihooPay.setQihooUserId(qihooUserId);
        qihooPay.setMoneyAmount(moneyAmount);
        qihooPay.setExchangeRate(Constants.DEMO_PAY_EXCHANGE_RATE);

        qihooPay.setProductName(SdkManagerJni.activity.getString(R.string.demo_pay_product_name));
        qihooPay.setProductId(Constants.DEMO_PAY_PRODUCT_ID);

        qihooPay.setNotifyUri(Constants.DEMO_APP_SERVER_NOTIFY_URI);

        qihooPay.setAppName(SdkManagerJni.activity.getString(R.string.demo_pay_app_name));
        qihooPay.setAppUserName(SdkManagerJni.activity.getString(R.string.demo_pay_app_user_name));
        qihooPay.setAppUserId(Constants.DEMO_PAY_APP_USER_ID);

        // 可选参数
        qihooPay.setAppExt1(SdkManagerJni.activity.getString(R.string.demo_pay_app_ext1));
        qihooPay.setAppExt2(SdkManagerJni.activity.getString(R.string.demo_pay_app_ext2));
        qihooPay.setAppOrderId(System.currentTimeMillis()+"");

        return qihooPay;
    }
}
