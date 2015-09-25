package com.hdngame.fate.m4399;

import android.content.pm.ActivityInfo;
import android.util.Log;
import cn.m4399.operate.OperateCenterConfig;
import cn.m4399.operate.SingleOperateCenter;
import cn.m4399.recharge.RechargeOrder;
import com.hdngame.fate.SdkManagerJni;

import java.lang.String;
import java.lang.System;

/**
 * Created by yuxiao on 15/9/24.
 */
public class M4399RechargeSdkJni {

    public static void init(String gameKey, String gameName) {
        System.out.println("M4399RechargeSdkJni.init");
        System.out.println(gameKey + ":" + gameName);

        new OperateCenterConfig.Builder(SdkManagerJni.activity)
                .setDebugEnabled(true)  //发布游戏时，要设为false
                .setOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE) //设置SDK界面方向，应与游戏设置一直
                .setSupportExcess(true) //设置是否支持超出金额充值
                .setGameKey(gameKey) 	//换成实际游戏的game key
                .setGameName(gameName)	//换成实际游戏的名字，原则上与游戏名字匹配
                .build();

        SingleOperateCenter.getInstance().init(SdkManagerJni.activity, new SingleOperateCenter.SingleRechargeListener() {

            /*
             * 充值过程结束时SDK回调此方法
             *
             * 充值过程结束并不代表订单生命周期全部完成，SDK还需要查询订单状态，游戏
             * 要根据订单状态决定是否发放物品等
             *
             * @param msg 表示充值结果的友好的文本说明
             *
             */
            @Override
            public void onRechargeFinished(boolean success, String msg) {
                System.out.println("Pay: [" + success + ", " + msg + "]");
            }

			/*
			 * 充值过程成功完成后，SDK会查询订单状态，根据订单状态状态正常则通知游戏发放物品
			 *
			 * @param shouldDeliver
			 *  是否要发放物品
			 * @param o
			 *  封装了最后提交的订单信息的对象，主要包含以下成员，各成员都有getter方法
			 *  payChannel：   充值渠道
			 *  orderId：      	充值订单号
			 *  je：			充值金额
			 *  goods：        	购买的物品
			 *
			 * @return
			 *  物品发放过程是否成功
			 */

            @Override
            synchronized public boolean notifyDeliverGoods(boolean shouldDeliver, RechargeOrder o) {
                if (shouldDeliver) {
                    System.out.println("单机充值发放物品, [" + o + "]");
//                    mSKUList.add("您花费 " + o.getJe() + "元， 购买了 " + o.getGoods());

                    return true;
                } else {
                    System.out.println("单机充值查询到的订单状态不正常，建议不要发放物品");
                    return false;
                }
            }
        });
    }

    public static void charge(String order, String name, int cost) {
        System.out.println("M4399RechargeSdkJni.charge");
        System.out.println(order + ":" + name + ":" + cost);

        //je充值金额：是整数字符串，4399充值中心仅支持整数金额充值，最小充值金额1元，最大不超过50000元。
        //productName商品名称：最长不超过8个字符。 如果传入商品名，充值中心将直接显示改商品名称，
        //如果充值金额大于下单时传入的je时，将显示商品名+XXX游戏币，相关游戏币的兑换比例在接入时提供给运营人员配置。
        //如果未传入商品名，则直接显示XXX游戏币。
        SingleOperateCenter.getInstance().recharge(SdkManagerJni.activity, String.valueOf(cost), name);
    }

    public static void destroy() {
        System.out.println("M4399RechargeSdkJni.destroy");

        SingleOperateCenter.getInstance().destroy();
    }
}
