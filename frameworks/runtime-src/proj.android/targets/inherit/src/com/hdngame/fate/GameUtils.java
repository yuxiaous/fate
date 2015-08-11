package com.hdngame.fate;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;

/**
 * Created by yuxiao on 15/8/11.
 */
public class GameUtils {

    
    public static boolean checkSignature(Context context, String packageName) {
        PackageInfo pi = null;

        try {
            pi = context.getPackageManager().getPackageInfo(packageName, PackageManager.GET_SIGNATURES);
        }
        catch (PackageManager.NameNotFoundException e) {
            System.out.println("checkSignature name not found");
            return false;
        }

        Signature sign = pi.signatures[0];
        System.out.println("checkSignature sign: " + sign.toCharsString());

        int code = sign.hashCode();
        System.out.println("checkSignature code: " + code);

        if (code == 123) {
            return true;
        }

        return false;
    }
}
