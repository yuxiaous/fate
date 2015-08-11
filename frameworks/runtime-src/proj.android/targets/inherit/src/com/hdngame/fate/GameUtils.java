package com.hdngame.fate;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;

/**
 * Created by yuxiao on 15/8/11.
 */
public class GameUtils {

    private static int SignCode = -903721661;
    private static boolean

    public static void checkSignature(Context context) {
        String packageName = context.getPackageName();
//        System.out.println("checkSignature packageName: " + packageName);

        PackageInfo pi = null;
        try {
            pi = context.getPackageManager().getPackageInfo(packageName, PackageManager.GET_SIGNATURES);
        }
        catch (PackageManager.NameNotFoundException e) {
            return;
        }

        Signature sign = pi.signatures[0];

        int code = sign.hashCode();
        System.out.println("checkSignature code: " + code);

        return code == SignCode;
    }

}
