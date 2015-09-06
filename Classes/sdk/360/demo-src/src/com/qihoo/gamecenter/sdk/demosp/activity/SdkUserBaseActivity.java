
package com.qihoo.gamecenter.sdk.demosp.activity;

import com.qihoo.gamecenter.sdk.activity.ContainerActivity;
import com.qihoo.gamecenter.sdk.common.IDispatcherCallback;
import com.qihoo.gamecenter.sdk.demosp.activity.SdkUserBaseActivity;
import com.qihoo.gamecenter.sdk.demosp.R;
import com.qihoo.gamecenter.sdk.demosp.payment.Constants;
import com.qihoo.gamecenter.sdk.demosp.payment.QihooPayInfo;
import com.qihoo.gamecenter.sdk.demosp.utils.ProgressUtil;
import com.qihoo.gamecenter.sdk.demosp.utils.QihooUserInfo;
import com.qihoo.gamecenter.sdk.demosp.utils.QihooUserInfoListener;
import com.qihoo.gamecenter.sdk.demosp.utils.QihooUserInfoTask;
import com.qihoo.gamecenter.sdk.demosp.utils.Utils;
import com.qihoo.gamecenter.sdk.matrix.Matrix;
import com.qihoo.gamecenter.sdk.protocols.ProtocolConfigs;
import com.qihoo.gamecenter.sdk.protocols.ProtocolKeys;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Toast;

/**
 * SdkUserBaseActivity这个基类，处理请求360SDK
 */
public abstract class SdkUserBaseActivity extends Activity{

    private static final String TAG = "SdkUserBaseActivity";

    protected QihooUserInfo mQihooUserInfo;

    protected boolean mIsLandscape;

    protected String mAccessToken = null;

    private boolean mIsInOffline = false;

    /**
     * AccessToken是否有效
     */
    protected static boolean isAccessTokenValid = true;
    /**
     * QT是否有效
     */
    protected static boolean isQTValid = true;

    public void onGotUserInfo(QihooUserInfo userInfo) {

    }

    private void getUserInfo() {

        isAccessTokenValid = true;
        isQTValid = true;
        final QihooUserInfoTask mUserInfoTask = QihooUserInfoTask.newInstance();

        // 提示用户进度
        final ProgressDialog progress = ProgressUtil.show(this,
                R.string.get_user_title,
                R.string.get_user_message,
                new OnCancelListener() {

                    @Override
                    public void onCancel(DialogInterface dialog) {
                        if (mUserInfoTask != null) {
                            mUserInfoTask.doCancel();
                        }
                    }
                });

        // 请求应用服务器，用AccessToken换取UserInfo
        mUserInfoTask.doRequest(this, mAccessToken, Matrix.getAppKey(this), new QihooUserInfoListener() {

            @Override
            public void onGotUserInfo(QihooUserInfo userInfo) {
                progress.dismiss();
                if (null == userInfo || !userInfo.isValid()) {
                    Toast.makeText(SdkUserBaseActivity.this, "从应用服务器获取用户信息失败", Toast.LENGTH_LONG).show();
                } else {
                    SdkUserBaseActivity.this.onGotUserInfo(userInfo);
                }
            }
        });
    }

    // 获取用来在demo上显示登录结果的字符串
    protected String getLoginResultText() {
        String result = "";

        try {
            if (mQihooUserInfo != null && mQihooUserInfo.isValid()) {
                JSONObject joUserInfo = new JSONObject();
                JSONObject joUserInfoData = new JSONObject();
                joUserInfo.put("data", joUserInfoData);
                joUserInfoData.put("name", mQihooUserInfo.getName());
                joUserInfoData.put("id", mQihooUserInfo.getId());
                joUserInfoData.put("avatar", mQihooUserInfo.getAvatar());
                joUserInfo.put("error_code", 0);
                result = "TokenInfo=" + mAccessToken +"\n\n" + "QihooUserInfo=" + joUserInfo.toString();
            }
        } catch (Throwable tr) {
            tr.printStackTrace();
        }

        return result;
    }

    // ---------------------------------调用360SDK接口------------------------------------

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // 调用其他SDK接口之前必须先调用init
        Matrix.init(this);
    }

    @Override
    protected void onDestroy() {
        // 游戏退出前，不再调用SDK其他接口时，需要调用Matrix.destroy接口
        onDemoActivityDestroy(true);
    }

    protected void onDemoActivityDestroy(boolean releaseSdk) {
        if (releaseSdk) {
            Matrix.destroy(this);
        }
        super.onDestroy();
    }

    /*
     * 当用户要退出游戏时，需要调用SDK的退出接口。
     */
//    @Override
//    public boolean onKeyDown(int keyCode, KeyEvent event) {
//        switch (keyCode) {
//            case KeyEvent.KEYCODE_BACK:
//                doSdkQuit(mIsLandscape);
//                return true;
//            default:
//                return super.onKeyDown(keyCode, event);
//        }
//    }

    /**
     * 使用360SDK的登录接口
     *
     * @param isLandScape 是否横屏显示登录界面
     */
    protected void doSdkLogin(boolean isLandScape) {
        mIsInOffline = false;
        Intent intent = getLoginIntent(isLandScape);
        IDispatcherCallback callback = mLoginCallback;
        if (getCheckBoxBoolean(R.id.isSupportOffline)) {
            callback = mLoginCallbackSupportOffline;
        }
        Matrix.execute(this, intent, callback);
    }

    /**
     * 使用360SDK的切换账号接口
     *
     * @param isLandScape 是否横屏显示登录界面
     */
    protected void doSdkSwitchAccount(boolean isLandScape) {
        Intent intent = getSwitchAccountIntent(isLandScape);
        IDispatcherCallback callback = mAccountSwitchCallback;
        if (getCheckBoxBoolean(R.id.isSupportOffline)) {
            callback = mAccountSwitchSupportOfflineCB;
        }
        Matrix.invokeActivity(this, intent, callback);
    }

    // -----------------------------------登录选项-------------------------------------

    private boolean getCheckBoxBoolean(int id) {
        CheckBox cb = (CheckBox)findViewById(id);
        if (cb != null) {
            return cb.isChecked();
        }
        return false;
    }

    private String getUiBackgroundPicPath() {
        EditText et = (EditText)findViewById(R.id.bgPictruePath);
        if (et != null) {
            return et.getText().toString();
        }
        return null;
    }

    private String getUiBackgroundPathInAssets() {
        EditText et = (EditText)findViewById(R.id.bgAssetsPicturePath);
        if (et != null) {
            return et.getText().toString();
        }
        return null;
    }
    /**
     * 生成调用360SDK登录接口的Intent
     * @param isLandScape 是否横屏
     * @return intent
     */
    private Intent getLoginIntent(boolean isLandScape) {

        Intent intent = new Intent(this, ContainerActivity.class);

        // 界面相关参数，360SDK界面是否以横屏显示。
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandScape);

        // 必需参数，使用360SDK的登录模块。
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_LOGIN);

        //是否显示关闭按钮
        intent.putExtra(ProtocolKeys.IS_LOGIN_SHOW_CLOSE_ICON, getCheckBoxBoolean(R.id.isShowClose));

        // 可选参数，是否支持离线模式，默认值为false
        intent.putExtra(ProtocolKeys.IS_SUPPORT_OFFLINE, getCheckBoxBoolean(R.id.isSupportOffline));

        // 可选参数，是否在自动登录的过程中显示切换账号按钮
        intent.putExtra(ProtocolKeys.IS_SHOW_AUTOLOGIN_SWITCH, getCheckBoxBoolean(R.id.isShowSwitchButton));

        // 可选参数，是否隐藏欢迎界面
        intent.putExtra(ProtocolKeys.IS_HIDE_WELLCOME, getCheckBoxBoolean(R.id.isHideWellcome));

        // 可选参数，登录界面的背景图片路径，必须是本地图片路径
        intent.putExtra(ProtocolKeys.UI_BACKGROUND_PICTRUE, getUiBackgroundPicPath());
        // 可选参数，指定assets中的图片路径，作为背景图
        intent.putExtra(ProtocolKeys.UI_BACKGROUND_PICTURE_IN_ASSERTS, getUiBackgroundPathInAssets());

        //-- 以下参数仅仅针对自动登录过程的控制
        // 可选参数，自动登录过程中是否不展示任何UI，默认展示。
        intent.putExtra(ProtocolKeys.IS_AUTOLOGIN_NOUI, getCheckBoxBoolean(R.id.isAutoLoginHideUI));

        // 可选参数，静默自动登录失败后是否显示登录窗口，默认不显示
        intent.putExtra(ProtocolKeys.IS_SHOW_LOGINDLG_ONFAILED_AUTOLOGIN, getCheckBoxBoolean(R.id.isShowDlgOnFailedAutoLogin));
        // 测试参数，发布时要去掉
        intent.putExtra(ProtocolKeys.IS_SOCIAL_SHARE_DEBUG, getCheckBoxBoolean(R.id.isDebugSocialShare));

        return intent;
    }

    /***
     * 生成调用360SDK切换账号接口的Intent
     *
     * @param isLandScape 是否横屏
     * @return Intent
     */
    private Intent getSwitchAccountIntent(boolean isLandScape) {

        Intent intent = new Intent(this, ContainerActivity.class);

        // 必须参数，360SDK界面是否以横屏显示。
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandScape);

        // 必需参数，使用360SDK的切换账号模块。
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_SWITCH_ACCOUNT);

        //是否显示关闭按钮
        intent.putExtra(ProtocolKeys.IS_LOGIN_SHOW_CLOSE_ICON, getCheckBoxBoolean(R.id.isShowClose));

        // 可选参数，是否支持离线模式，默认值为false
        intent.putExtra(ProtocolKeys.IS_SUPPORT_OFFLINE, getCheckBoxBoolean(R.id.isSupportOffline));

        // 可选参数，是否隐藏欢迎界面
        intent.putExtra(ProtocolKeys.IS_HIDE_WELLCOME, getCheckBoxBoolean(R.id.isHideWellcome));

        /*
         * 指定界面背景（可选参数）：
         *  1.ProtocolKeys.UI_BACKGROUND_PICTRUE 使用的系统路径，如/sdcard/1.png
         *  2.ProtocolKeys.UI_BACKGROUND_PICTURE_IN_ASSERTS 使用的assest中的图片资源，
         *    如传入bg.png字符串，就会在assets目录下加载这个指定的文件
         *  3.图片大小不要超过5M，尺寸不要超过1280x720
         */
        // 可选参数，登录界面的背景图片路径，必须是本地图片路径
        // 可选参数，登录界面的背景图片路径，必须是本地图片路径
        intent.putExtra(ProtocolKeys.UI_BACKGROUND_PICTRUE, getUiBackgroundPicPath());
        // 可选参数，指定assets中的图片路径，作为背景图
        intent.putExtra(ProtocolKeys.UI_BACKGROUND_PICTURE_IN_ASSERTS, getUiBackgroundPathInAssets());

        // 测试参数，发布时要去掉
        intent.putExtra(ProtocolKeys.IS_SOCIAL_SHARE_DEBUG, getCheckBoxBoolean(R.id.isDebugSocialShare));

        return intent;
    }

    // ---------------------------------360SDK接口的回调-----------------------------------

    // 登录、注册的回调
    private IDispatcherCallback mLoginCallback = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
            // press back
            if (isCancelLogin(data)) {
                return;
            }
            // 显示一下登录结果
            Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_LONG).show();
            mIsInOffline = false;
            mQihooUserInfo = null;
//            Log.d(TAG, "mLoginCallback, data is " + data);
            // 解析access_token
            mAccessToken = parseAccessTokenFromLoginResult(data);

            if (!TextUtils.isEmpty(mAccessToken)) {
                // 需要去应用的服务器获取用access_token获取一下带qid的用户信息
                getUserInfo();
            } else {
                Toast.makeText(SdkUserBaseActivity.this, "get access_token failed!", Toast.LENGTH_LONG).show();
            }
        }
    };


    private IDispatcherCallback mLoginCallbackSupportOffline = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
            if (isCancelLogin(data)) {
                return;
            }

//            Log.d(TAG, "mLoginCallbackSupportOffline, data is " + data);
            try {
                JSONObject joRes = new JSONObject(data);
                JSONObject joData = joRes.getJSONObject("data");
                String mode = joData.optString("mode", "");
                if (!TextUtils.isEmpty(mode) && mode.equals("offline")) {
                    Toast.makeText(SdkUserBaseActivity.this, "login success in offline mode", Toast.LENGTH_SHORT).show();
                    mIsInOffline = true;
                    // 显示一下登录结果
                    Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_LONG).show();
                } else {
                    mLoginCallback.onFinished(data);
                }
            } catch (Exception e) {
                Log.e(TAG, "mLoginCallbackSupportOffline exception", e);
            }

        }
    };

    // 切换账号的回调
    private IDispatcherCallback mAccountSwitchCallback = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
            // press back
            if (isCancelLogin(data)) {
                return;
            }

            // 显示一下登录结果
            Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_LONG).show();

//            Log.d(TAG, "mAccountSwitchCallback, data is " + data);
            // 解析access_token
            mAccessToken = parseAccessTokenFromLoginResult(data);

            if (!TextUtils.isEmpty(mAccessToken)) {
                // 需要去应用的服务器获取用access_token获取一下带qid的用户信息
                getUserInfo();
            } else {
                Toast.makeText(SdkUserBaseActivity.this, "get access_token failed!", Toast.LENGTH_LONG).show();
            }
        }
    };

    // 支持离线模式的切换账号的回调
    private IDispatcherCallback mAccountSwitchSupportOfflineCB = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
            // press back
            if (isCancelLogin(data)) {
                return;
            }
            // 显示一下登录结果
            Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_LONG).show();
//            Log.d(TAG, "mAccountSwitchSupportOfflineCB, data is " + data);
            // 解析access_token
            mAccessToken = parseAccessTokenFromLoginResult(data);

            if (!TextUtils.isEmpty(mAccessToken)) {
                // 登录结果直接返回的userinfo中没有qid，需要去应用的服务器获取用access_token获取一下带qid的用户信息
                getUserInfo();
            } else {
                Toast.makeText(SdkUserBaseActivity.this, "get access_token failed!", Toast.LENGTH_LONG).show();
            }
        }
    };

    private boolean isCancelLogin(String data) {
        try {
            JSONObject joData = new JSONObject(data);
            int errno = joData.optInt("errno", -1);
            if (-1 == errno) {
                Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_LONG).show();
                return true;
            }
        } catch (Exception e) {}
        return false;
    }

    // ------------------------获取社交服务器初始化信息接口--------------
    protected void doSDKGetSocialInitInfo(QihooUserInfo usrInfo) {
        if (!checkLoginInfo(usrInfo)) {
            return;
        }

        Intent intent = getSocialInitInfoIntent();
        Matrix.execute(this, intent, new IDispatcherCallback() {

            @Override
            public void onFinished(String data) {
                Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_SHORT).show();
            }
        });
    }

    private Intent getSocialInitInfoIntent() {
        Intent intent = new Intent();
        // function_code : 必须参数，表示调用SDK接口执行的功能为获取社交模块初始化信息
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_GET_SOCIAL_INIT_INFO);
        return intent;
    }

    // ------------------------上传积分接口--------------------
    // usrInfo : 必须参数，用户信息
    protected void doSdkUploadScore(QihooUserInfo usrInfo){
        // 检查用户是否登录
        if(!checkLoginInfo(usrInfo))
            return;
        Intent intent = this.getUploadScoreIntent();
        Matrix.execute(this, intent, new IDispatcherCallback() {

            @Override
            public void onFinished(String data) {
                Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_SHORT).show();
//                System.out.println(data);
            }
        });
    }

    private Intent getUploadScoreIntent(){
        Intent intent = new Intent();

        // 从界面获取用户输入的数据
        String strScore;
        String topnid;
        EditText et = (EditText)findViewById(R.id.edit_upload_score);
        EditText etTopnid = (EditText) findViewById(R.id.edit_score_topnid);
        strScore = et.getText().toString();
        topnid = etTopnid.getText().toString();

        /*
         * 必须参数：
         *  function_code : 必须参数，表示调用SDK接口执行的功能为上传积分
         *  score : 必须参数，用户积分。
         *  topnid : 可选参数，排行榜标识，使用该参数需要确认对应ID的排行榜已经开通。
        */
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_UPLOAD_SCORE);
        intent.putExtra(ProtocolKeys.SCORE, strScore/*"100"*/);
        intent.putExtra(ProtocolKeys.TOPNID, topnid);
        return intent;
    }

    // -----------------------邀请好友---------------------
    // usrInfo : 必须参数，用户信息
    // bLandScape : 屏幕方向，true为横屏，flase为竖屏
    protected void doSdkInviteFriend(QihooUserInfo usrInfo, boolean bLandScape){
        // 检查用户是否登录
        if(!checkLoginInfo(usrInfo)) {
            return;
        }

        Intent intent = getInviteFriendIntent(bLandScape);
        Matrix.execute(this, intent, new IDispatcherCallback() {
            @Override
            public void onFinished(String data) {
                Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_SHORT).show();
//                System.out.println(data);
            }
        });
    }

    // bLandScape : 屏幕方向，true为横屏，flase为竖屏
    private Intent getInviteFriendIntent(boolean bLandScape){

        Intent intent = new Intent();

        // 从界面读取输入数据
        String strNick;
        String strPhone;
        String strQid;
        String strSMS;
        EditText et = (EditText)findViewById(R.id.edit_invite_phone);
        strPhone = et.getText().toString();
        et = (EditText)findViewById(R.id.edit_invite_qid);
        strQid = et.getText().toString();
        et = (EditText)findViewById(R.id.edit_invite_sms);
        strSMS = et.getText().toString();
        et = (EditText)findViewById(R.id.edit_invite_nick);
        strNick = et.getText().toString();

        /*
         * 必须参数：
         *  function_code : 必须参数，表示调用SDK接口执行的功能为批量邀请好友
         *  nick_name: 必须参数，对方的昵称
         *  phone : 有值就要传入，加密后的好友电话。使用“获取可邀请好友列表”接口返回的phone字段中的值。
         *  sms : 必须参数，邀请信息内容。
         *  qid : 有值就要传入，被邀请用户的qid，如果没有可以不传
         *  screen_orientation : 屏幕方向，bool值 true为横屏，flase为竖屏
        */
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_INVITE_FRIEND_BATCH);
        intent.putExtra(ProtocolKeys.NICK_NAME, strNick);
        intent.putExtra(ProtocolKeys.PHONE, strPhone);
        intent.putExtra(ProtocolKeys.QID, strQid);
        intent.putExtra(ProtocolKeys.SMS, strSMS);
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, bLandScape);
        return intent;
    }

 // ----------------------结合本地通信录获取可邀请好友列表-----------------
    private EditText mEditGetcontactStart;
    private EditText mEditGetcontactCount;
    protected void doSdkGetContactContent(QihooUserInfo usrInfo, boolean isLandScape ){

        if(!checkLoginInfo(usrInfo)) {
            return;
        }
        mEditGetcontactStart = (EditText)findViewById(R.id.edit_getcontact_start);
        mEditGetcontactCount = (EditText)findViewById(R.id.edit_getcontact_count);
        Intent intent = this.getGetContactContentIntent(isLandScape);
        Matrix.execute(this, intent, new IDispatcherCallback() {

            @Override
            public void onFinished(String data) {
                Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_SHORT).show();
//                System.out.println(data);
            }
        });
    }

    private Intent getGetContactContentIntent(boolean isLandScape){
        Intent intent = new Intent();
        /*
         * 必须参数：
         *  function_code : 必须参数，表示调用SDK接口执行的功能
         *  screen_orientation : 必须参数，屏幕方向
         *  start : 非必须参数，表示此次获取可邀请好友列表的开始位置，从0开始。
         *          无此参数时会获取所有的可邀请好友列表，不进行翻页。
         *  count : 非必须参数，表示此次获取可邀请好友的个数。
         *          无此参数时会获取所有的可邀请好友列表，不进行翻页。
        */
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandScape);
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_GET_CONTACT_CONTENT);
        intent.putExtra(ProtocolKeys.START, mEditGetcontactStart.getText().toString());
        intent.putExtra(ProtocolKeys.COUNT, mEditGetcontactCount.getText().toString());

        return intent;
    }

    //--------------分享--------------
    protected void doSdkShare(QihooUserInfo usrInfo, final boolean bLandScape){
        if(!checkLoginInfo(usrInfo)) {
            return;
        }

        AlertDialog.Builder ab = new AlertDialog.Builder(SdkUserBaseActivity.this);

        LinearLayout llt = (LinearLayout)SdkUserBaseActivity.this.getLayoutInflater().inflate(R.layout.share_weibo_layout, null);
        final EditText etTitle = (EditText)llt.findViewById(R.id.edit_share_title);
        final EditText etDesc = (EditText)llt.findViewById(R.id.edit_share_desc);
        final EditText etPic = (EditText)llt.findViewById(R.id.edit_share_pic);
        final EditText etUiBg = (EditText)llt.findViewById(R.id.edit_share_ui_bg);
        final EditText etIcon = (EditText)llt.findViewById(R.id.edit_share_icon);
        ab.setView(llt);

        ab.setTitle("输入分享内容");
        ab.setView(llt);
        ab.setPositiveButton("确定", new DialogInterface.OnClickListener(){

            @Override
            public void onClick(DialogInterface dialog, int which) {
                Intent intent = getShareIntent(etTitle.getText().toString(),
                        etDesc.getText().toString(), etPic.getText().toString(),
                        etIcon.getText().toString(), etUiBg.getText().toString(), bLandScape);
                Matrix.invokeActivity(SdkUserBaseActivity.this, intent, new IDispatcherCallback() {

                    @Override
                    public void onFinished(String data) {
                        if (null == data) {
                            return;
                        }
                        Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });
        ab.show();
    }


    private Intent getShareIntent(String title, String desc, String picture, String icon, String uibg, boolean isLandScape){

        Intent intent = new Intent();

        /*
         * 必须参数：
         *  function_code : 必须参数，标识通知SDK要执行的功能
         *  screen_orientation: 可选参数，指定横竖屏，默认为横屏
         *  ui_background_picture: 可选参数，分享界面的背景图，不传就是透明
         *  share_title: 必须参数，分享的标题
         *  share_desc: 必须参数，分享的描述
         *  share_pic: 可选参数，分享的图片路径（必须是本地路径如：/sdcard/1.png，后缀可以是png、jpg、jpeg，大小不能超过5M，尺寸不能超过1280x720）
         *  share_icon: 可选参数，分享的icon路径（必须是本地路径，最好是png文件，32k以内）
        */
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_SHARE);
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandScape);
        if (!TextUtils.isEmpty(uibg)) {
            intent.putExtra(ProtocolKeys.UI_BACKGROUND_PICTRUE, uibg);
        }
        intent.putExtra(ProtocolKeys.SHARE_TITLE, title);
        intent.putExtra(ProtocolKeys.SHARE_DESC, desc);
        intent.putExtra(ProtocolKeys.SHARE_PIC, picture);
        intent.putExtra(ProtocolKeys.SHARE_ICON, icon);
        return intent;
    }

 // ------------------注销登录----------------
    protected void doSdkLogout(QihooUserInfo usrInfo){
        if(!checkLoginInfo(usrInfo)) {
            return;
        }
        Intent intent = getLogoutIntent();
        Matrix.execute(this, intent, new IDispatcherCallback() {
            @Override
            public void onFinished(String data) {
                Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_SHORT).show();
//                System.out.println(data);
            }
        });
    }

    private Intent getLogoutIntent(){

        /*
         * 必须参数：
         *  function_code : 必须参数，表示调用SDK接口执行的功能
        */
        Intent intent = new Intent();
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_LOGOUT);
        return intent;
    }

    private boolean checkLoginInfo(QihooUserInfo info){
        if (mIsInOffline) {
            return true;
        }
        if(null == info || !info.isValid()){
            Toast.makeText(this, "需要登录才能执行此操作", Toast.LENGTH_SHORT).show();
            return false;
        }
        return true;
    }

    // -----------------------------获取好友排行榜接口---------------
    // usrInfo : 必须参数，用户信息
    protected void doSdkGetRankFriend(QihooUserInfo usrInfo){
        // 检查用户是否登录
        if(!checkLoginInfo(usrInfo)) {
            return;
        }
        Intent intent = this.getGetGameTopFriendIntent();
        Matrix.execute(this, intent, new IDispatcherCallback() {

            @Override
            public void onFinished(String data) {
                Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_SHORT).show();
//                System.out.println(data);
            }
        });
    }

    // -----------------------------获取全球排行榜接口---------------
    // usrInfo : 必须参数，用户信息
    protected void doSdkGetGlobalRankList(QihooUserInfo usrInfo){
        // 检查用户是否登录
        if(!checkLoginInfo(usrInfo)) {
            return;
        }
        Intent intent = this.getGetGameGlobleRankListIntent();
        Matrix.execute(this, intent, new IDispatcherCallback() {

            @Override
            public void onFinished(String data) {
                Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_SHORT).show();
//                System.out.println(data);
            }
        });
    }

    private Intent getGetGameGlobleRankListIntent(){
        Intent intent = new Intent();
        String strTopNID;
        String StrOrderby;
        EditText et = (EditText)findViewById(R.id.edit_getgame_topnid);
        strTopNID = et.getText().toString();
        et = (EditText)findViewById(R.id.edit_getgame_orderby);
        StrOrderby = et.getText().toString();
        /*
         * 必须参数：
         *  function_code : 必须参数，表示调用SDK接口执行的功能为游戏的排行榜。
        */
        /*
         * 可选参数：
         *  topnid:可选参数，排行榜类型（不填写，则为默认的排行榜）
         *  orderby:可选参数，排序类型（填写为0则按正序排序，其它情况按倒序排序）
        */
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_GET_RANK);
        intent.putExtra(ProtocolKeys.TOPNID, strTopNID);
        intent.putExtra(ProtocolKeys.ORDERBY, StrOrderby);
        return intent;
    }

    private Intent getGetGameTopFriendIntent(){
        Intent intent = new Intent();

        String strStart;
        String strCount;
        String strTopNID;
        String StrOrderby;
        EditText et = (EditText)findViewById(R.id.edit_getgamefrient_top_start);
        strStart = et.getText().toString();
        et = (EditText)findViewById(R.id.edit_getgamefrient_top_count);
        strCount = et.getText().toString();
        et = (EditText)findViewById(R.id.edit_getgamefrient_topnid);
        strTopNID = et.getText().toString();
        et = (EditText)findViewById(R.id.edit_getgamefrient_orderby);
        StrOrderby = et.getText().toString();
        /*
         * 必须参数：
         *  function_code : 必须参数，表示调用SDK接口执行的功能为游戏的排行榜。
        */
        /*
         * 可选参数：
         *  start : 可选参数，排名榜的第几位开始获取(索引从0开始)
         *  count : 可选参数，排名榜上从start开始，获取多少位,最小值为20。
         *          start和count参数如果不传的话，会返回最多前20个排行榜内容。
         *  topnid:可选参数，排行榜类型（不填写，则为默认的排行榜）
         *  orderby:可选参数，排序类型（填写为0则按正序排序，其它情况按倒序排序）
        */
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_GET_RANK_FRIENDS);
        intent.putExtra(ProtocolKeys.START, strStart/*"0"*/);
        intent.putExtra(ProtocolKeys.COUNT, strCount/*"20"*/);
        intent.putExtra(ProtocolKeys.TOPNID, strTopNID);
        intent.putExtra(ProtocolKeys.ORDERBY, StrOrderby);

        return intent;
    }

    protected void doSdkInviteFriendBySdk(QihooUserInfo usrinfo, boolean bLandScape) {
        if (!checkLoginInfo(usrinfo)) {
            return;
        }
        Intent intent = getInviteFriendBySdkIntent(bLandScape);
        Matrix.invokeActivity(this, intent, new IDispatcherCallback() {

            @Override
            public void onFinished(String data) {
//                System.out.println("result: " + data);
                Toast.makeText(SdkUserBaseActivity.this, "result: " + data, Toast.LENGTH_SHORT).show();
            }
        });
    }

    private Intent getInviteFriendBySdkIntent(boolean bLandScape) {

        EditText et = (EditText)findViewById(R.id.et_invite_msg);
        String inviteMsg = et.getText().toString();
        /*
         * function_code : 必须参数，表示调用SDK接口执行的功能
         * screen_orientation : 360SDK界面是否以横屏显示。
         * sms: 可选参数，邀请信息，不需要主语，sdk会添加。
         */
        Intent intent = new Intent(this, ContainerActivity.class);
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_INVITE_FRIEND_BY_SDK);
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, bLandScape);
        intent.putExtra(ProtocolKeys.SMS, inviteMsg);
        return intent;

    }

    protected void doSdkDisplayGameFriendRank(QihooUserInfo usrInfo, boolean bLandScape) {
        if (!checkLoginInfo(usrInfo)) {
            return;
        }
        Intent intent = getDisplayGameFriendRankIntent(bLandScape);
        Matrix.invokeActivity(this, intent, new IDispatcherCallback() {

            @Override
            public void onFinished(String data) {
//                System.out.println("result: " + data);
                Toast.makeText(SdkUserBaseActivity.this, "result: " + data, Toast.LENGTH_SHORT).show();
            }
        });
    }

    private Intent getDisplayGameFriendRankIntent(boolean bLandScape) {

        /*
         * function_code : 必须参数，表示调用SDK接口执行的功能
         * screen_orientation : 360SDK界面是否以横屏显示。
         * topnid : 可选参数，排行榜ID
         */
        Intent intent = new Intent(this, ContainerActivity.class);
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_DISPLAY_GAME_FRIEND_RANK);
        String topnId = ((EditText)findViewById(R.id.et_rank_id)).getText().toString();
        if (!TextUtils.isEmpty(topnId)) {
            // 可选参数，排行榜ID，与上传积分时对应的排行榜ID对应，使用该参数，需要确定后台存在对应ID的排行榜，否则会显示错误
            intent.putExtra(ProtocolKeys.TOPNID, topnId);
        }
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, bLandScape);

        return intent;
    }

    private String parseAccessTokenFromLoginResult(String loginRes) {
        try {

            JSONObject joRes = new JSONObject(loginRes);
            JSONObject joData = joRes.getJSONObject("data");
            return joData.getString("access_token");
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    protected void doSdkGetUserInfo(QihooUserInfo usrinfo) {
        if (!checkLoginInfo(usrinfo)) {
            return;
        }

        Intent intent = getUserInfoIntent();
        Matrix.execute(this, intent, new IDispatcherCallback() {

            @Override
            public void onFinished(String data) {
//                System.out.println(data);
                Toast.makeText(SdkUserBaseActivity.this, data, Toast.LENGTH_LONG).show();
            }
        });
    }

    private Intent getUserInfoIntent() {
        EditText et = (EditText) findViewById(R.id.et_get_user_info);
        String qid = et.getText().toString();

        Intent intent = new Intent();
        // function code
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_GET_USER_INFO);
        // 用户QID
        intent.putExtra(ProtocolKeys.QID, qid);

        return intent;
    }

    /**
     * 使用360SDK的论坛接口
     *
     * @param isLandScape 是否横屏显示支付界面
     */
    protected void doSdkBBS(QihooUserInfo usrinfo, boolean isLandScape) {
        if (!checkLoginInfo(usrinfo)) {
            return;
        }

        if (!Utils.isNetAvailable(this)) {
            Toast.makeText(this, "网络不可用", Toast.LENGTH_SHORT).show();
            return;
        }

        Intent intent = getBBSIntent(isLandScape);

        Matrix.invokeActivity(this, intent, null);
    }

    /***
     * 生成调用360SDK论坛接口的Intent
     *
     * @param isLandScape
     * @return Intent
     */
    private Intent getBBSIntent(boolean isLandScape) {

        Bundle bundle = new Bundle();

        // 界面相关参数，360SDK界面是否以横屏显示。
        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandScape);

        // 必需参数，使用360SDK的论坛模块。
        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_BBS);

        Intent intent = new Intent(this, ContainerActivity.class);
        intent.putExtras(bundle);

        return intent;
    }

    /**
     * 使用360SDK的退出接口
     *
     * @param isLandScape 是否横屏显示支付界面
     */
    protected void doSdkQuit(boolean isLandScape) {

        Bundle bundle = new Bundle();

        // 界面相关参数，360SDK界面是否以横屏显示。
        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandScape);

        // 必需参数，使用360SDK的退出模块。
        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_QUIT);

        // 可选参数，登录界面的背景图片路径，必须是本地图片路径
        bundle.putString(ProtocolKeys.UI_BACKGROUND_PICTRUE, "");

        Intent intent = new Intent(this, ContainerActivity.class);
        intent.putExtras(bundle);

        Matrix.invokeActivity(this, intent, mQuitCallback);
    }

    // 退出的回调
    private IDispatcherCallback mQuitCallback = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
//            Log.d(TAG, "mQuitCallback, data is " + data);
            JSONObject json;
            try {
                json = new JSONObject(data);
                int which = json.optInt("which", -1);
                String label = json.optString("label");

                Toast.makeText(SdkUserBaseActivity.this,
                        "按钮标识：" + which + "，按钮描述:" + label, Toast.LENGTH_LONG)
                        .show();

                switch (which) {
                    case 0: // 用户关闭退出界面
                        return;
                    default:// 退出游戏
                        finish();
                        return;
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

    };

    // 实名注册
    protected void doSdkRealNameRegister(QihooUserInfo usrinfo, boolean isLandScape) {
        if (!checkLoginInfo(usrinfo)) {
            return;
        }
        Intent intent = getRealNameRegisterIntent(isLandScape, (usrinfo != null) ? usrinfo.getId() : null);

        Matrix.invokeActivity(this, intent, new IDispatcherCallback() {
            @Override
            public void onFinished(String data) {
//                Log.d(TAG, "RealNameRegisterCallback, data is " + data);
            }
        });
    }

    private Intent getRealNameRegisterIntent(boolean isLandScape, String qihooUserId) {

        Bundle bundle = new Bundle();
        // 界面相关参数，360SDK界面是否以横屏显示。
        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandScape);

        // 必需参数，360账号id，整数。
        bundle.putString(ProtocolKeys.QIHOO_USER_ID, qihooUserId);

        // 可选参数，登录界面的背景图片路径，必须是本地图片路径
        bundle.putString(ProtocolKeys.UI_BACKGROUND_PICTRUE, "");

        // 必需参数，使用360SDK的实名注册模块。
        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_REAL_NAME_REGISTER);

        Intent intent = new Intent(this, ContainerActivity.class);
        intent.putExtras(bundle);
        return intent;
    }

    /**
     * 本方法中的callback实现仅用于测试, 实际使用由游戏开发者自己处理
     *
     * @param accessToken
     * @param userInfo 奇虎360用户信息
     */
    protected void doSdkAntiAddictionQuery(String accessToken, QihooUserInfo userInfo) {

        if (!checkLoginInfo(userInfo)) {
            return;
        }

        Intent intent = getAntAddictionIntent(accessToken, (userInfo != null) ? userInfo.getId() : null);
        Matrix.execute(this, intent, new IDispatcherCallback() {

            @Override
            public void onFinished(String data) {
//                Log.d("demo,anti-addiction query result = ", data);
                if (!TextUtils.isEmpty(data)) {
                    try {
                        JSONObject resultJson = new JSONObject(data);
                        int errorCode = resultJson.optInt("error_code");
                        if (errorCode == 0) {
                            JSONObject contentData = resultJson.getJSONObject("content");
                            if(contentData != null) {
                                // 保存登录成功的用户名及密码
                                JSONArray retData = contentData.getJSONArray("ret");
//                                Log.d(TAG, "ret data = " + retData);
                                if(retData != null && retData.length() > 0) {
                                    int status = retData.getJSONObject(0).optInt("status");
//                                    Log.d(TAG, "status = " + status);
                                    switch (status) {

                                        case 0:  // 查询结果:无此用户数据
                                            Toast.makeText(SdkUserBaseActivity.this,
                                                    getString(R.string.anti_addiction_query_result_0),
                                                    Toast.LENGTH_LONG).show();
                                            break;

                                        case 1:  // 查询结果:未成年
                                            Toast.makeText(SdkUserBaseActivity.this,
                                                    getString(R.string.anti_addiction_query_result_1),
                                                    Toast.LENGTH_LONG).show();
                                            break;

                                        case 2:  // 查询结果:已成年
                                            Toast.makeText(SdkUserBaseActivity.this,
                                                    getString(R.string.anti_addiction_query_result_2),
                                                    Toast.LENGTH_LONG).show();
                                            break;

                                        default:
                                            break;
                                    }
                                    return;
                                }
                            }
                        } else {
                            Toast.makeText(SdkUserBaseActivity.this,
                                    resultJson.optString("error_msg"), Toast.LENGTH_SHORT).show();
                            return;
                        }

                    } catch (JSONException e) {
                        e.printStackTrace();
                    }

                    Toast.makeText(SdkUserBaseActivity.this,
                            getString(R.string.anti_addiction_query_exception),
                            Toast.LENGTH_LONG).show();
                }
            }
        });
    }

    private Intent getAntAddictionIntent(String token, String qid) {
        Bundle bundle = new Bundle();

        // 必需参数，用户access token，要使用注意过期和刷新问题，最大64字符。
        bundle.putString(ProtocolKeys.ACCESS_TOKEN, token);

        // 必需参数，360账号id，整数。
        bundle.putString(ProtocolKeys.QIHOO_USER_ID, qid);

        // 必需参数，使用360SDK的防沉迷查询模块。
        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_ANTI_ADDICTION_QUERY);

        Intent intent = new Intent(this, ContainerActivity.class);
        intent.putExtras(bundle);
        return intent;
    }

    // payment begin
    /***
     * @param moneyAmount 金额数，使用者可以自由设定数额。金额数为100的整数倍，360SDK运行定额支付流程；
     *            金额数为0，360SDK运行不定额支付流程。
     * @return QihooPay
     */
    private QihooPayInfo getQihooPay(String moneyAmount) {

        String qihooUserId = (mQihooUserInfo != null) ? mQihooUserInfo.getId() : null;

        // 创建QihooPay
        QihooPayInfo qihooPay = new QihooPayInfo();
        qihooPay.setQihooUserId(qihooUserId);
        qihooPay.setMoneyAmount(moneyAmount);
        qihooPay.setExchangeRate(Constants.DEMO_PAY_EXCHANGE_RATE);

        qihooPay.setProductName(getString(R.string.demo_pay_product_name));
        qihooPay.setProductId(Constants.DEMO_PAY_PRODUCT_ID);

        qihooPay.setNotifyUri(Constants.DEMO_APP_SERVER_NOTIFY_URI);

        qihooPay.setAppName(getString(R.string.demo_pay_app_name));
        qihooPay.setAppUserName(getString(R.string.demo_pay_app_user_name));
        qihooPay.setAppUserId(Constants.DEMO_PAY_APP_USER_ID);

        // 可选参数
        qihooPay.setAppExt1(getString(R.string.demo_pay_app_ext1));
        qihooPay.setAppExt2(getString(R.string.demo_pay_app_ext2));
        qihooPay.setAppOrderId(System.currentTimeMillis()+"");

        return qihooPay;
    }

    protected QihooPayInfo getQihooPayInfo(boolean isFixed) {
        QihooPayInfo payInfo = null;
        if(isFixed) {
            payInfo = getQihooPay(Constants.DEMO_FIXED_PAY_MONEY_AMOUNT);
        }
        else {
            payInfo = getQihooPay(Constants.DEMO_NOT_FIXED_PAY_MONEY_AMOUNT);
        }
        return payInfo;
    }

    /***
     * 生成调用360SDK支付接口的Intent
     *
     * @param isLandScape
     * @param pay
     * @return Intent
     */
    protected Intent getPayIntent(boolean isLandScape, QihooPayInfo pay) {
        Bundle bundle = new Bundle();

        // 界面相关参数，360SDK界面是否以横屏显示。
        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandScape);

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

        Intent intent = new Intent(this, ContainerActivity.class);
        intent.putExtras(bundle);

        return intent;
    }

    protected void doSdkPay(QihooUserInfo usrinfo, boolean isLandScape) {

        if (!checkLoginInfo(usrinfo)) {
            return;
        }

        if(!isAccessTokenValid) {
            Toast.makeText(SdkUserBaseActivity.this, R.string.access_token_invalid, Toast.LENGTH_SHORT).show();
            return;
        }
        if(!isQTValid) {
            Toast.makeText(SdkUserBaseActivity.this, R.string.qt_invalid, Toast.LENGTH_SHORT).show();
            return;
        }

        boolean isFixed = getCheckBoxBoolean(R.id.isPayFixed);
        // 支付基础参数
        QihooPayInfo payInfo = getQihooPayInfo(isFixed);
        Intent intent = getPayIntent(isLandScape, payInfo);

        // 必需参数，使用360SDK的支付模块。
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_PAY);

        // 启动接口
        Matrix.invokeActivity(SdkUserBaseActivity.this, intent, mPayCallback);
    }

    // 支付的回调
    protected IDispatcherCallback mPayCallback = new IDispatcherCallback() {

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
                        String text = getString(R.string.pay_callback_toast, errorCode, errorMsg);
                        Toast.makeText(SdkUserBaseActivity.this, text, Toast.LENGTH_SHORT).show();

                    }
                        break;
                    case 4010201:
                        //acess_token失效
                        isAccessTokenValid = false;
                        Toast.makeText(SdkUserBaseActivity.this, R.string.access_token_invalid, Toast.LENGTH_SHORT).show();
                        break;
                    case 4009911:
                        //QT失效
                        isQTValid = false;
                        Toast.makeText(SdkUserBaseActivity.this, R.string.qt_invalid, Toast.LENGTH_SHORT).show();
                        break;
                    default:
                        break;
                }
            } catch (JSONException e) {
                e.printStackTrace();
            }

            // 用于测试数据格式是否异常。
            if (!isCallbackParseOk) {
                Toast.makeText(SdkUserBaseActivity.this, getString(R.string.data_format_error),
                        Toast.LENGTH_LONG).show();
            }
        }
    };

    // payment end
}
