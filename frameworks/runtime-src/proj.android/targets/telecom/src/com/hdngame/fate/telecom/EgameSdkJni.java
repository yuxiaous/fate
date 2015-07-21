package com.hdngame.fate.telecom;

import android.app.Activity;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.widget.Toast;
import android.os.Handler;
import cn.egame.terminal.paysdk.EgameExitListener;
import cn.egame.terminal.paysdk.EgamePay;
import cn.egame.terminal.paysdk.EgamePayListener;
import com.hdngame.fate.SdkManagerJni;

import java.lang.Override;
import java.lang.Runnable;
import java.lang.String;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by yuxiao on 15/6/30.
 */
public class EgameSdkJni {

    public static void init() {
        System.out.println("EgameSdkJni.init");

        int GameId = 5018840;
        int ChannelId = 10000000;
        try {
            Activity a = SdkManagerJni.activity;
            ApplicationInfo info = a.getPackageManager().getApplicationInfo(
                    a.getPackageName(),
                    PackageManager.GET_META_DATA);
            ChannelId = info.metaData.getInt("EGAME_CHANNEL");
        }
        catch(PackageManager.NameNotFoundException ex) {
            ChannelId = 10000000;
        }

        EgamePay.init(SdkManagerJni.activity);
//        CheckTool.init(this, ""+GameId, ""+ChannelId);
    }

    private static String  _alias = "";
    private static Handler _handler = new Handler();

    public static void pay(String alias) {
        System.out.println("EgameSdkJni.pay 1, alias: " + alias);
        _alias = alias;

        _handler.post(new Runnable() {
            @Override
            public void run() {
                System.out.println("EgameSdkJni.pay 2, alias: " + _alias);

                HashMap payParam = new HashMap();
                payParam.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, _alias);
                //payParams.put(EgamePay.PAY_PARAMS_KEY_PRIORITY, "sms");
                //payParams.put(EgamePay.PAY_PARAMS_KEY_USE_SMSPAY, "false");

                EgamePay.pay(SdkManagerJni.activity, payParam, listener);
            }
        });
    }

    final static EgamePayListener listener = new EgamePayListener() {
        @Override
        public void paySuccess(Map map) {
            Toast.makeText(SdkManagerJni.activity, "支付成功", Toast.LENGTH_SHORT).show();
        }

        @Override
        public void payFailed(Map params, int errorInt) {
            Toast.makeText(SdkManagerJni.activity, "支付失败：错误代码："+errorInt, Toast.LENGTH_SHORT).show();
        }

        @Override
        public void payCancel(Map map) {
            Toast.makeText(SdkManagerJni.activity, "取消支付", Toast.LENGTH_SHORT).show();
        }
    };

    public static void moreGame() {
        EgamePay.moreGame(SdkManagerJni.activity);
    }

    public static void exit() {
        //用户退出游戏的时候调用，弹出退出确认对话框
        EgamePay.exit(SdkManagerJni.activity, new EgameExitListener() {
            @Override
            public void exit() {
                //用户点击退出游戏，游戏需要处理退出逻辑
                //finish();
            }

            @Override
            public void cancel() {
                //用户取消退出游戏，这里不用处理
            }
        });
    }

//    public static native void onEgameChargeCallback(int result);
}

