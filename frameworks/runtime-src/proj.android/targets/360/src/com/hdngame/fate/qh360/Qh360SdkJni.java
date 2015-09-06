package com.hdngame.fate.qh360;


import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.text.TextUtils;
import android.util.Log;
import android.widget.Toast;
import com.hdngame.fate.SdkManagerJni;
import com.hdngame.fate.qh360.utils.ProgressUtil;
import com.hdngame.fate.qh360.utils.QihooUserInfo;
import com.hdngame.fate.qh360.utils.QihooUserInfoListener;
import com.hdngame.fate.qh360.utils.QihooUserInfoTask;
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
    protected static String _accessToken = null;

    public static void init() {
        System.out.println("Qh360SdkJni.init");

        Matrix.init(SdkManagerJni.activity);
    }

    public static void login() {
        System.out.println("Qh360SdkJni.login");

        SdkManagerJni.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Intent intent = getLoginIntent();
                IDispatcherCallback callback = mLoginCallback;
                if (_isSupportOffline) {
                    callback = mLoginCallbackSupportOffline;
                }
                Matrix.execute(SdkManagerJni.activity, intent, callback);
            }
        });
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
//            mIsInOffline = false;
//            mQihooUserInfo = null;
//            Log.d(TAG, "mLoginCallback, data is " + data);

            // 解析access_token
            _accessToken = parseAccessTokenFromLoginResult(data);

            if (!TextUtils.isEmpty(_accessToken)) {
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

    private static Intent getLoginIntent() {

        Intent intent = new Intent(SdkManagerJni.activity, ContainerActivity.class);

        // 必需参数，使用360SDK的登录模块。
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_LOGIN);

        // 界面相关参数，360SDK界面是否以横屏显示。
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, true);

        //是否显示关闭按钮
        intent.putExtra(ProtocolKeys.IS_LOGIN_SHOW_CLOSE_ICON, true);

        // 可选参数，是否支持离线模式，默认值为false
        intent.putExtra(ProtocolKeys.IS_SUPPORT_OFFLINE, false);

        // 可选参数，是否在自动登录的过程中显示切换账号按钮
        intent.putExtra(ProtocolKeys.IS_SHOW_AUTOLOGIN_SWITCH, true);

        // 可选参数，是否隐藏欢迎界面
        intent.putExtra(ProtocolKeys.IS_HIDE_WELLCOME, false);

        // 可选参数，登录界面的背景图片路径，必须是本地图片路径
//        intent.putExtra(ProtocolKeys.UI_BACKGROUND_PICTRUE, getUiBackgroundPicPath());

        // 可选参数，指定assets中的图片路径，作为背景图
//        intent.putExtra(ProtocolKeys.UI_BACKGROUND_PICTURE_IN_ASSERTS, getUiBackgroundPathInAssets());

        //-- 以下参数仅仅针对自动登录过程的控制
        // 可选参数，自动登录过程中是否不展示任何UI，默认展示。
        intent.putExtra(ProtocolKeys.IS_AUTOLOGIN_NOUI, true);

        // 可选参数，静默自动登录失败后是否显示登录窗口，默认不显示
        intent.putExtra(ProtocolKeys.IS_SHOW_LOGINDLG_ONFAILED_AUTOLOGIN, false);

        // 测试参数，发布时要去掉
        intent.putExtra(ProtocolKeys.IS_SOCIAL_SHARE_DEBUG, true);

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
                _accessToken,
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
}
