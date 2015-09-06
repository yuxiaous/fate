
package com.qihoo.gamecenter.sdk.demosp.activity;

import com.qihoo.gamecenter.sdk.demosp.R;
import com.qihoo.gamecenter.sdk.demosp.utils.ProgressUtil;
import com.qihoo.gamecenter.sdk.demosp.utils.QihooUserInfo;
import com.qihoo.gamecenter.sdk.matrix.Matrix;

import android.app.ProgressDialog;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.TextView;
import android.widget.Toast;


public class PortraitSdkUserActivity extends SdkUserBaseActivity implements
        OnClickListener {
    private static final String TAG = "PortraitSdkUserActivity";

    private TextView mLoginResultView;

    private ProgressDialog mProgress;

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_login_choose:
                clearLoginResult();
                doSdkLogin(false);
                break;
            case R.id.btn_switch_account:
                doSdkSwitchAccount(false);
                break;
            case R.id.btn_social_module_init:
                doSDKGetSocialInitInfo(mQihooUserInfo);
                break;
            case R.id.btn_upload_score:
                doSdkUploadScore(mQihooUserInfo);
                break;
            case R.id.btn_get_contact_content:
                doSdkGetContactContent(mQihooUserInfo, false);
                break;
            case R.id.btn_invite_friend_batch:
                doSdkInviteFriend(mQihooUserInfo, false);
                break;
            case R.id.btn_share:
                doSdkShare(mQihooUserInfo, false);
                break;
            case R.id.btn_logout:
                doSdkLogout(mQihooUserInfo);
                clearLoginResult();
                break;
            case R.id.btn_get_game_top_friend:
                doSdkGetRankFriend(mQihooUserInfo);
                break;
            case R.id.btn_get_game_top:
                doSdkGetGlobalRankList(mQihooUserInfo);
                break;
            case R.id.btn_invite_friend_by_sdk:
                doSdkInviteFriendBySdk(mQihooUserInfo, false);
                break;
            case R.id.btn_display_rank:
                doSdkDisplayGameFriendRank(mQihooUserInfo, false);
                break;
            case R.id.btn_get_user_info:
                doSdkGetUserInfo(mQihooUserInfo);
                break;
            case R.id.btn_bbs:
                doSdkBBS(mQihooUserInfo, false);
                break;
            case R.id.btn_quit:
                doSdkQuit(false);
                break;
            case R.id.btn_pay:
                doSdkPay(mQihooUserInfo, false);
                break;
            case R.id.btn_realnamereg:
                doSdkRealNameRegister(mQihooUserInfo, false);
                break;
            case R.id.btn_antAddiction:
                doSdkAntiAddictionQuery(mAccessToken, mQihooUserInfo);
                break;
            default:
                break;
        }

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.sdk_user_activity);
        resetViews();
        mIsLandscape = true;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    private void resetViews() {
        TextView sdkVerView = (TextView) findViewById(R.id.sdk_ver);
        sdkVerView.setText(getString(R.string.sdk_ver) + Matrix.getVersionName(this) + "(" + Matrix.getVersionCode(this) + ")");

        TextView channelView = (TextView) findViewById(R.id.channel);
        channelView.setText(getString(R.string.channel).concat("default"));

        mLoginResultView = (TextView) findViewById(R.id.login_result);

        View btnLoginChoose = findViewById(R.id.btn_login_choose);
        btnLoginChoose.setOnClickListener(this);

        View btnLoginSwitchAccount = findViewById(R.id.btn_switch_account);
        btnLoginSwitchAccount.setOnClickListener(this);

        View btnSocialInit = findViewById(R.id.btn_social_module_init);
        btnSocialInit.setOnClickListener(this);

        View btnUploadScore = findViewById(R.id.btn_upload_score);
        btnUploadScore.setOnClickListener(this);


        View btnGetContact = findViewById(R.id.btn_get_contact_content);
        btnGetContact.setOnClickListener(this);

        View btnInviteFriendBatch = findViewById(R.id.btn_invite_friend_batch);
        btnInviteFriendBatch.setOnClickListener(this);

        View btnWeiboShare = findViewById(R.id.btn_share);
        btnWeiboShare.setOnClickListener(this);

        View btnLogout = findViewById(R.id.btn_logout);
        btnLogout.setOnClickListener(this);

        View btnFriendTop = findViewById(R.id.btn_get_game_top_friend);
        btnFriendTop.setOnClickListener(this);
        View btnTop = findViewById(R.id.btn_get_game_top);
        btnTop.setOnClickListener(this);

        View btnInviteBySdk = findViewById(R.id.btn_invite_friend_by_sdk);
        btnInviteBySdk.setOnClickListener(this);

        View btnDisplayRank = findViewById(R.id.btn_display_rank);
        btnDisplayRank.setOnClickListener(this);

        View btnShowUserInfo = findViewById(R.id.btn_get_user_info);
        btnShowUserInfo.setOnClickListener(this);

        View bbsBtn = findViewById(R.id.btn_bbs);
        bbsBtn.setOnClickListener(this);

        View bbsPostImage = findViewById(R.id.btn_quit);
        bbsPostImage.setOnClickListener(this);

        View pay = findViewById(R.id.btn_pay);
        pay.setOnClickListener(this);

        View realNameReg = findViewById(R.id.btn_realnamereg);
        realNameReg.setOnClickListener(this);

        View antAddiction = findViewById(R.id.btn_antAddiction);
        antAddiction.setOnClickListener(this);
    }

    private void clearLoginResult() {
        mLoginResultView.setText(null);
        mQihooUserInfo = null;
    }

    @Override
    public void onGotUserInfo(QihooUserInfo userInfo) {
        ProgressUtil.dismiss(mProgress);

        if (userInfo != null && userInfo.isValid()) {
            // 保存QihooUserInfo
            mQihooUserInfo = userInfo;

            // 界面显示QihooUser的Id和Name
            mLoginResultView.setText(getLoginResultText());

        } else {
            Toast.makeText(this, R.string.get_user_fail, Toast.LENGTH_SHORT).show();
            clearLoginResult();
        }
    }

    /*
     * 当用户要退出游戏时，需要调用SDK的退出接口。
     */
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        switch (keyCode) {
            case KeyEvent.KEYCODE_BACK:
                doSdkQuit(mIsLandscape);
                return true;
            default:
                return super.onKeyDown(keyCode, event);
        }
    }
}
