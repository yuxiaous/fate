
package com.qihoo.gamecenter.sdk.demosp.activity;

import com.qihoo.gamecenter.sdk.demosp.R;
import com.qihoo.gamecenter.sdk.demosp.payment.Constants;
import com.qihoo.gamecenter.sdk.demosp.payment.QihooPayInfo;
import com.qihoo.gamecenter.sdk.matrix.Matrix;
import com.qihoo.gamecenter.sdk.protocols.ProtocolKeys;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.EditText;

/**
 * 流程测试第二步，定额支付或不定额支付。
 * 此类调用360SDK完成支付过程，其中AccessToken和QihooUserId来自FlowTestLoginActivity发送的Intent。
 */
public class FlowTestPayActivity extends FlowTestPayBaseActivity implements OnClickListener {

    // Intent Extra Name，用于传：奇虎UserId
    public static final String QIHOO_USER_ID = "qid";

    // Intent Extra Name，用于传：AccessToken
    public static final String ACCESS_TOKEN = "token";

    private EditText mAccessToken;

    private EditText mQihooUserId;

    private EditText mAppKey;

    private EditText mPrivateKey;

    private EditText mMoneyAmount;

    private EditText mExchangeRate;

    private EditText mProductName;

    private EditText mProductId;

    private EditText mNotifyUri;

    private EditText mAppName;

    private EditText mAppUserName;

    private EditText mAppUserId;

    private EditText mAppExt1;

    private EditText mAppExt2;

    private EditText mAppOrderId;

    private boolean mIsLandscape;

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_pay: {
                doFlowTestSdkPay(mIsLandscape, false);
            }
                break;
            default:
                break;
        }

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Intent intent = getIntent();
        if (intent != null) {
            mIsLandscape = intent.getBooleanExtra(
                    ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, true);

        }
        setRequestedOrientation(mIsLandscape ? ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
                : ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        setContentView(R.layout.flow_test_pay_activity);
        initViews();
    }

    @Override
    protected void onDestroy() {
        onDemoActivityDestroy(false);
    }

    private void initViews() {

        Intent intent = getIntent();

        // 支付流程的必需参数，从流程第一步界面的Intent中得到 Access Token和User Id
        mAccessToken = (EditText) findViewById(R.id.value_access_token);
        mAccessToken.setHint(intent.getStringExtra(ACCESS_TOKEN));

        mQihooUserId = (EditText) findViewById(R.id.value_qihoo_user_id);
        mQihooUserId.setHint(intent.getStringExtra(QIHOO_USER_ID));
        mQihooUserId.setOnClickListener(null);

        // 从360SDK接口获取AppKey PrivateKey
        mAppKey = (EditText) findViewById(R.id.value_app_key);
        mAppKey.setHint(Matrix.getAppKey(this));
        mAppKey.setOnClickListener(null);
        mPrivateKey = (EditText) findViewById(R.id.value_private_key);
        mPrivateKey.setHint(Matrix.getPrivateKey(this));
        mPrivateKey.setOnClickListener(null);

        // 用户自定义的支付参数——金额。金额为"0"时，将调用360SDK不定额支付流程。金额>=100时，将调用360SDK定额支付流程。
        mMoneyAmount = (EditText) findViewById(R.id.value_amount);
        mMoneyAmount.setHint(Constants.DEMO_FIXED_PAY_MONEY_AMOUNT);

        // 支付比例
        mExchangeRate = (EditText) findViewById(R.id.value_exchange_rate);
        mExchangeRate.setHint(Constants.DEMO_PAY_EXCHANGE_RATE);

        // 产品名称和Id
        mProductName = (EditText) findViewById(R.id.value_product_name);
        mProductId = (EditText) findViewById(R.id.value_product_id);
        mProductId.setHint(Constants.DEMO_PAY_PRODUCT_ID);

        // 接收支付结果通知的接口URI
        mNotifyUri = (EditText) findViewById(R.id.value_notify_uri);
        mNotifyUri.setHint(Constants.DEMO_APP_SERVER_NOTIFY_URI);

        // 用户自定义的支付参数
        mAppName = (EditText) findViewById(R.id.value_app_name);
        mAppUserName = (EditText) findViewById(R.id.value_app_user_name);
        mAppUserId = (EditText) findViewById(R.id.value_app_user_id);
        mAppUserId.setHint(Constants.DEMO_PAY_APP_USER_ID);

        // 可选参数
        mAppExt1 = (EditText) findViewById(R.id.value_app_ext_1);
        mAppExt2 = (EditText) findViewById(R.id.value_app_ext_2);
        // 可选参数，订单Id，无论成功失败，只能用一次
        mAppOrderId = (EditText) findViewById(R.id.value_app_order_id);

        // 发起支付的按钮，点击后调用360SDK支付
        findViewById(R.id.btn_pay).setOnClickListener(this);
    }

    // -----------------------------------------------------

    private String getAccessToken() {
        return getEditText(mAccessToken);
    }

    private String getQihooUserId() {
        return getEditText(mQihooUserId);
    }

    /**
     * 获取金额，如果数字格式不合法，则返回为"0"
     */
    private String getMoneyAmount() {
        String amountString = getEditText(mMoneyAmount);

        // 检查是否是合法数字格式，如果数字格式不合法，则返回为"0"
        Integer amount = -1;
        try {
            amount = Integer.valueOf(amountString);
        } catch (NumberFormatException e) {
            e.printStackTrace();
        }

        if (amount == null || amount < 0) {
            amountString = "0";
        }

        return amountString;
    }

    private String getExchangeRate() {
        return getEditText(mExchangeRate);
    }

    private String getProductName() {
        return getEditText(mProductName);
    }

    private String getProductId() {
        return getEditText(mProductId);
    }

    private String getNotifyUri() {
        return getEditText(mNotifyUri);
    }

    private String getAppName() {
        return getEditText(mAppName);
    }

    private String getAppUserId() {
        return getEditText(mAppUserId);
    }

    private String getAppUserName() {
        return getEditText(mAppUserName);
    }

    private String getAppExt2() {
        return getEditText(mAppExt2);
    }

    private String getAppExt1() {
        return getEditText(mAppExt1);
    }

    private String getAppOrderId() {
        return getEditText(mAppOrderId);
    }

    // ----------------------------------------

    /**
     * 从EditText读取text，如果为空，则使用hint；hint空，则返回""
     */
    private String getEditText(EditText editText) {
        String text = editText.getText().toString();
        if (TextUtils.isEmpty(text)) {
            CharSequence hint = editText.getHint();
            text = (hint != null) ? hint.toString() : "";
        }

        // 输入null识别为空
        if ("null".equalsIgnoreCase(text)) {
            return null;
        }

        return text;
    }

    @Override
    protected QihooPayInfo getQihooPayInfo(boolean isFixed) {
        // 创建QihooPay
        QihooPayInfo qihooPay = new QihooPayInfo();

        qihooPay.setAccessToken(getAccessToken());
        qihooPay.setQihooUserId(getQihooUserId());

        qihooPay.setMoneyAmount(getMoneyAmount());
        qihooPay.setExchangeRate(getExchangeRate());

        qihooPay.setProductName(getProductName());
        qihooPay.setProductId(getProductId());

        qihooPay.setNotifyUri(getNotifyUri());

        qihooPay.setAppName(getAppName());
        qihooPay.setAppUserName(getAppUserName());
        qihooPay.setAppUserId(getAppUserId());

        qihooPay.setAppExt1(getAppExt1());
        qihooPay.setAppExt2(getAppExt2());
        qihooPay.setAppOrderId(getAppOrderId());

        return qihooPay;
    }

}
