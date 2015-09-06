
package com.qihoo.gamecenter.sdk.demosp.activity;

import com.qihoo.gamecenter.sdk.demosp.payment.QihooPayInfo;
import com.qihoo.gamecenter.sdk.matrix.Matrix;
import com.qihoo.gamecenter.sdk.protocols.ProtocolConfigs;
import com.qihoo.gamecenter.sdk.protocols.ProtocolKeys;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;

import java.util.ArrayList;
import java.util.List;

public abstract class FlowTestPayBaseActivity extends SdkUserBaseActivity {

    private static final String[] PAY_TYPE_VAL = new String[] {
            ProtocolKeys.PayType.MOBILE_BANKCARD,
            ProtocolKeys.PayType.ALIPAY,
            ProtocolKeys.PayType.MOBILE_CARD,
            ProtocolKeys.PayType.JCARD,
            ProtocolKeys.PayType.QIHOO_BI,
    };
    private static final String[] PAY_TYPE_DES = new String[] {
            "银行卡",
            "支付宝",
            "充值卡",
            "骏网卡",
            "360币"
    };

    private List<String> mPayTypeList = new ArrayList<String>();

    private String mDefaultPayType;

    // -----------------------------------------------------------------------------------------

    /**
     * 仅用于测试，不要应用于实际生产。
     *
     * @param isLandScape 是否横屏显示支付界面
     * @param isFixed 是否定额支付
     */
    protected void doFlowTestSdkPay(final boolean isLandScape, final boolean isFixed) {
        mPayTypeList.clear();
        new AlertDialog.Builder(FlowTestPayBaseActivity.this)
                .
                setTitle("请定制支付方式")
                .
                setIcon(android.R.drawable.ic_dialog_info)
                .
                setMultiChoiceItems(PAY_TYPE_DES, null,
                        new DialogInterface.OnMultiChoiceClickListener() {

                            @Override
                            public void onClick(DialogInterface dialog, int which, boolean isChecked) {
                                String payType = PAY_TYPE_VAL[which];
                                if (isChecked && !mPayTypeList.contains(payType)) {
                                    mPayTypeList.add(payType);
                                }
                                else if (!isChecked && mPayTypeList.contains(payType)) {
                                    mPayTypeList.remove(payType);
                                }
                            }
                        }).
                setPositiveButton("确定", new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        showDefaultPayTypeDialog(isLandScape, isFixed);
                    }
                }).setNegativeButton("取消", null).show();
    }

    /**
     * 仅用于测试，不要应用于实际生产。
     *
     * @param isLandScape 是否横屏显示支付界面
     * @param isFixed 是否定额支付
     */
    private void doCustomSdkPay(boolean isLandScape, boolean isFixed) {

        // 基础支付参数

        QihooPayInfo payInfo = getQihooPayInfo(isFixed);
        Intent intent = getPayIntent(isLandScape, payInfo);

        Bundle bundle = new Bundle();
        // 可选参数，定制支付类型
        int iLen = mPayTypeList.size();
        if (iLen > 0) {
            String[] payType = (String[]) mPayTypeList.toArray(new String[iLen]);
            bundle.putStringArray(ProtocolKeys.PAY_TYPE, payType);
        }

        // 可选参数，默认支付类型
        bundle.putString(ProtocolKeys.DEFAULT_PAY_TYPE, mDefaultPayType == null ? ""
                : mDefaultPayType);
        intent.putExtras(bundle);

        // 必需参数，使用360SDK的支付模块。
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_PAY);

        Matrix.invokeActivity(this, intent, mPayCallback);
    }

    /**
     * 仅用于测试，不要应用于实际生产。
     */
    private void showDefaultPayTypeDialog(final boolean isLandScape, final boolean isFixed) {
        mDefaultPayType = null;
        String[] tempValues = PAY_TYPE_VAL;
        if (!mPayTypeList.isEmpty()) {
            tempValues = (String[]) mPayTypeList.toArray(new String[mPayTypeList.size()]);
        }
        final String[] values = tempValues;
        new AlertDialog.Builder(FlowTestPayBaseActivity.this)
                .
                setTitle("请选择默认定位到哪个支付类型上")
                .
                setIcon(android.R.drawable.ic_dialog_info)
                .
                setSingleChoiceItems(values, -1,
                        new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                if (values != null && values.length != 0) {
                                    mDefaultPayType = values[which];
                                }

                            }
                        }).
                setPositiveButton("确定", new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        FlowTestPayBaseActivity.this.doCustomSdkPay(isLandScape, isFixed);
                    }
                }).setNegativeButton("取消", null).show();
    }

}
