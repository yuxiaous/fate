package com.hdngame.fate;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.telephony.TelephonyManager;

/**
 * Created by yuxiao on 15/8/11.
 */
public class GameUtils {

    public static int getSignatureCode(Context context) {
        String packageName = context.getPackageName();
//        System.out.println("checkSignature packageName: " + packageName);

        PackageInfo pi = null;
        try {
            pi = context.getPackageManager().getPackageInfo(packageName, PackageManager.GET_SIGNATURES);
        }
        catch (PackageManager.NameNotFoundException e) {
            return 0;
        }

        Signature sign = pi.signatures[0];
//        System.out.println("getSignatureCode: " + sign.hashCode());
        return sign.hashCode();
    }

    public static int getSimOperator(Context context) {
        TelephonyManager tm = (TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE);
        String operator = tm.getSimOperator();

        if(operator != null){
            if(operator.equals("46000") || operator.equals("46002")|| operator.equals("46007")) {
                //中国移动
                return 1;
            }
            else if(operator.equals("46001")) {
                //中国联通
                return 2;
            }
            else if(operator.equals("46003")) {
                //中国电信
                return 3;
            }
        }
        return 0;
    }
}
