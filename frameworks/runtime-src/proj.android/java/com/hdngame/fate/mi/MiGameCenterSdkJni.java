package com.hdngame.fate.mi;

import android.os.Handler;
import android.os.Message;
import android.widget.Toast;
import com.hdngame.fate.SdkManagerJni;
import com.xiaomi.gamecenter.sdk.MiCommplatform;
import com.xiaomi.gamecenter.sdk.MiErrorCode;
import com.xiaomi.gamecenter.sdk.OnLoginProcessListener;
import com.xiaomi.gamecenter.sdk.OnPayProcessListener;
import com.xiaomi.gamecenter.sdk.entry.MiAccountInfo;
import com.xiaomi.gamecenter.sdk.entry.MiAppInfo;
import com.xiaomi.gamecenter.sdk.entry.MiBuyInfo;
import com.xiaomi.gamecenter.sdk.entry.MiBuyInfoOffline;

import java.lang.Override;
import java.lang.String;
import java.lang.System;
import java.util.UUID;

/**
 * Created by yuxiao on 15/10/3.
 */
public class MiGameCenterSdkJni {

    public static void init() {
        System.out.println("MiGameCenterSdkJni.init");

        MiAppInfo appInfo = new MiAppInfo();
        appInfo.setAppId( "2882303761517390705" );
        appInfo.setAppKey( "5311739039705" );
        MiCommplatform.Init(SdkManagerJni.activity, appInfo);
    }

    private static MiAccountInfo miAccountInfo = null;
    private static String order = "";
    private static String info = "";

    public static void pay(String order, String info) {
        System.out.println("MiGameCenterSdkJni.pay");

        MiGameCenterSdkJni.order = order;
        MiGameCenterSdkJni.info = info;

        if(miAccountInfo == null) {
            MiCommplatform.getInstance().miLogin(SdkManagerJni.activity, new OnLoginProcessListener() {
                @Override
                public void finishLoginProcess(int code, MiAccountInfo accountInfo) {
                    System.out.println("MiGameCenterSdkJni.miLogin "+code);

                    if(code == MiErrorCode.MI_XIAOMI_GAMECENTER_SUCCESS) {
                        miAccountInfo = accountInfo;
                    }
                    loginHandler.sendEmptyMessage(code);
                }
            });
        }
        else {
            loginHandler.sendEmptyMessage(MiErrorCode.MI_XIAOMI_GAMECENTER_SUCCESS);
        }
    }

    private static Handler loginHandler = new Handler() {
        @Override
        public void handleMessage( Message msg ) {
            switch( msg.what ) {
                case MiErrorCode.MI_XIAOMI_GAMECENTER_SUCCESS:
                    Toast.makeText(SdkManagerJni.activity, "登录成功", Toast.LENGTH_SHORT).show();
                    doPay();
                    break;
                case MiErrorCode.MI_XIAOMI_GAMECENTER_ERROR_ACTION_EXECUTED:
                    Toast.makeText( SdkManagerJni.activity, "正在执行，不要重复操作", Toast.LENGTH_SHORT ).show();
                    break;
                default:
                    Toast.makeText( SdkManagerJni.activity, "登录失败", Toast.LENGTH_SHORT ).show();
                    break;
            }
        }
    };

    private static void doPay() {
        MiBuyInfo miBuyInfo = new MiBuyInfo();
        miBuyInfo.setCpOrderId( UUID.randomUUID().toString() );
        miBuyInfo.setCpUserInfo("xxxx透传参数");
        miBuyInfo.setAmount(1);
        MiCommplatform.getInstance().miUniPay(SdkManagerJni.activity, miBuyInfo,

//        MiBuyInfoOffline offline = new MiBuyInfoOffline();
//        offline.setCpOrderId(UUID.randomUUID().toString() );//订单号唯一(不为空)
//        offline.setProductCode("com.demo_1");//商品代码,开发者 申请获得(不为空)
//        offline.setCount(1);//购买数量 (商品数量最大 9999,最小 1)(不为空)
//        MiCommplatform.getInstance ().miUniPayOffline(SdkManagerJni.activity, offline,
                new OnPayProcessListener() {
                    @Override
                    public void finishPayProcess(int code) {
                        System.out.println("MiGameCenterSdkJni.miUniPayOffline " + code);
                        payHandler.sendEmptyMessage(code);
                    }
                });
    }

    private static Handler payHandler = new Handler() {
        @Override
        public void handleMessage( Message msg ) {
            switch( msg.what ) {
                case MiErrorCode.MI_XIAOMI_GAMECENTER_SUCCESS:
                    //购买成功 ,请处理发货
                    onMiGameChargeCallback(0, order);
                    break;
                case MiErrorCode.MI_XIAOMI_GAMECENTER_ERROR_PAY_CANCEL:
                    //取消购买
                    Toast.makeText( SdkManagerJni.activity, "取消购买", Toast.LENGTH_SHORT ).show();
                    break;
                case MiErrorCode.MI_XIAOMI_GAMECENTER_ERROR_ACTION_EXECUTED:
                    //操作正在执行
                    Toast.makeText( SdkManagerJni.activity, "操作正在执行，不要重复操作", Toast.LENGTH_SHORT ).show();
                    break;
                default:
                    //购买失败
                    Toast.makeText( SdkManagerJni.activity, "购买失败", Toast.LENGTH_SHORT ).show();
                    break;
            }
        }
    };

    public static native void onMiGameChargeCallback(int result, String order);
}
