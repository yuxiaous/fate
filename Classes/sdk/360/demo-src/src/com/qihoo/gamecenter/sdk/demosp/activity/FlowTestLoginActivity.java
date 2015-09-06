
package com.qihoo.gamecenter.sdk.demosp.activity;

import com.qihoo.gamecenter.sdk.demosp.R;
import com.qihoo.gamecenter.sdk.demosp.payment.QihooPayInfo;
import com.qihoo.gamecenter.sdk.demosp.utils.ProgressUtil;
import com.qihoo.gamecenter.sdk.demosp.utils.QihooUserInfo;
import com.qihoo.gamecenter.sdk.demosp.utils.QihooUserInfoListener;
import com.qihoo.gamecenter.sdk.demosp.utils.QihooUserInfoTask;
import com.qihoo.gamecenter.sdk.matrix.Matrix;
import com.qihoo.gamecenter.sdk.protocols.ProtocolKeys;

import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.EditText;
import android.widget.Toast;

/**
 * 流程测试第一步，登录或注册登录。（注：流程测试第一步为，登录或注册登录；流程测试第二步为，定额支付或不定额支付。）
 * 此类调用360SDK完成登录过程，并把获取的AccessToken和UserId通过Intent传给流程测试第二步activity
 * ：FlowTestPayActivity
 */
public class FlowTestLoginActivity extends SdkUserBaseActivity
    implements OnClickListener, QihooUserInfoListener {

    private static final String TAG = "FlowTestLoginActivity";

    // 进度等待框
    private ProgressDialog mProgress;

    private boolean mIsLandscape;

    // 登录返回的TokenInfo
//    private TokenInfo mTokenInfo;

    private QihooUserInfoTask mUserInfoTask;

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_login:
                // 使用360SDK登录接口（横屏）
                doSdkLogin(mIsLandscape);
                break;
            default:
                break;
        }
    }


    /**
     * 通过此方法返回UserInfo
     */
//    @Override
//    public void onGotTokenInfo(TokenInfo tokenInfo) {
//        if (tokenInfo != null && tokenInfo.isValid()) {
//            mTokenInfo = tokenInfo;
//
//            isAccessTokenValid = true;
//
//            mUserInfoTask = QihooUserInfoTask.newInstance();
//
//            // 提示用户进度
//            mProgress = ProgressUtil.show(this,
//                    R.string.get_user_info_title,
//                    R.string.get_user_info_message,
//                    new OnCancelListener() {
//
//                        @Override
//                        public void onCancel(DialogInterface dialog) {
//                            if (mUserInfoTask != null) {
//                                mUserInfoTask.doCancel();
//                            }
//                        }
//                    });
//
//            // 请求应用服务器，用AccessToken换取UserInfo
//            mUserInfoTask.doRequest(this, tokenInfo.getAccessToken(), Matrix.getAppKey(this), this);
//        } else {
//            ProgressUtil.dismiss(mProgress);
//            Toast.makeText(this, R.string.get_token_fail, Toast.LENGTH_LONG).show();
//        }
//    }


    /**
     * 应用服务器，通过此方法返回UserInfo
     */
    @Override
    public void onGotUserInfo(QihooUserInfo userInfo) {
        ProgressUtil.dismiss(mProgress);
        if (userInfo != null && userInfo.isValid()) {
            // 保存QihooUserInfo
            mQihooUserInfo = userInfo;
        } else {
            Toast.makeText(this, R.string.get_user_fail, Toast.LENGTH_SHORT).show();
            clearLoginResult();
        }
        if (mQihooUserInfo == null) {
            Toast.makeText(this, R.string.get_user_fail, Toast.LENGTH_LONG).show();
        } else {
            if (!userInfo.isValid()) {
                Toast.makeText(this, R.string.get_user_fail, Toast.LENGTH_LONG).show();
            } else {
                startFlowTestPayActivity(mQihooUserInfo);
            }
        }
    }
    private void clearLoginResult() {
        mQihooUserInfo = null;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Intent intent = getIntent();
        if (intent != null) {
            mIsLandscape = intent.getBooleanExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, true);
        }

        setRequestedOrientation(mIsLandscape ? ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
                : ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        setContentView(R.layout.flow_test_login_activity);
        initViews();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    private void initViews() {
        EditText appKey = (EditText) findViewById(R.id.value_app_key);
        appKey.setHint(Matrix.getAppKey(this));
        appKey.setOnClickListener(null);

        EditText appChannel = (EditText) findViewById(R.id.value_app_channel);
        appChannel.setHint(Matrix.getChannel(this));
        appChannel.setOnClickListener(null);

        // 登录按钮，点击后调用360SDK登录（竖屏显示界面）
        findViewById(R.id.btn_login).setOnClickListener(this);
    }

    /**
     * 启动流程第二步，自定义支付界面。 把UserId 和 AccessToken，通过Intent传递给FlowTestPayActivity
     */
    private void startFlowTestPayActivity(QihooUserInfo userInfo) {
        Intent intent = new Intent(this, FlowTestPayActivity.class);
        intent.putExtra(FlowTestPayActivity.ACCESS_TOKEN, mAccessToken);
        intent.putExtra(FlowTestPayActivity.QIHOO_USER_ID, userInfo.getId());
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, mIsLandscape);
        startActivity(intent);
    }

    @Override
    protected QihooPayInfo getQihooPayInfo(boolean isFixed) {
        return null;
    }

}
