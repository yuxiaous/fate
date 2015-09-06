
package com.qihoo.gamecenter.sdk.demosp.activity;

import com.qihoo.gamecenter.sdk.demosp.R;
import com.qihoo.gamecenter.sdk.protocols.ProtocolKeys;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.Button;

import java.io.File;
import java.io.IOException;
/**
 * 第一个activity，提供横屏和竖屏游戏的入口
 */
public class SdkMainActivity extends Activity implements View.OnClickListener {

    private Button portraitBtn;
    private Button landscapeBtn;
    private Button portraitTestBtn;
    private Button landscapeTestBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.sdk_main_activity);
        portraitBtn = (Button) findViewById(R.id.btn_portrait_game);
        landscapeBtn = (Button) findViewById(R.id.btn_landscape_game);
        portraitTestBtn = (Button) findViewById(R.id.btn_portrait_flow_test);
        landscapeTestBtn = (Button) findViewById(R.id.btn_landscape_flow_test);
        portraitBtn.setOnClickListener(this);
        landscapeBtn.setOnClickListener(this);
        portraitTestBtn.setOnClickListener(this);
        landscapeTestBtn.setOnClickListener(this);
    }

    private void startPortraitSdkUserActivity() {
        Intent intent = new Intent(SdkMainActivity.this, PortraitSdkUserActivity.class);
        startActivity(intent);
    }

    private void startLandscapeSdkUserActivity() {
        Intent intent = new Intent(SdkMainActivity.this, LandscapeSdkUserActivity.class);
        startActivity(intent);
    }
    private void startSdkShowFlowTestActivity(boolean isLandScape) {
        Intent intent = new Intent(this, FlowTestLoginActivity.class);
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandScape);
        startActivity(intent);
        finish();
    }
    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.btn_portrait_game) {
            startPortraitSdkUserActivity();
        } else if (v.getId() == R.id.btn_landscape_game) {
            startLandscapeSdkUserActivity();
        }else if (v.getId() == R.id.btn_portrait_flow_test) {
            startSdkShowFlowTestActivity(false);
        }else if (v.getId() == R.id.btn_landscape_flow_test) {
            startSdkShowFlowTestActivity(true);
        }
        this.finish();
    }
}

