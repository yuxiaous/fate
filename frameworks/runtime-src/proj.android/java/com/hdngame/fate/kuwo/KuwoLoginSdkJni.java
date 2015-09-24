package com.hdngame.fate.kuwo;

import cn.kuwo.login.KuwoLoginSdk;
import com.hdngame.fate.SdkManagerJni;

import java.lang.String;
import java.lang.System;

/**
 * Created by yuxiao on 15/9/24.
 */
public class KuwoLoginSdkJni {

    public static void enterGame(String gameShortGame) {
        System.out.println("KuwoLoginSdkJni.init");
        KuwoLoginSdk.enterGame(SdkManagerJni.activity, gameShortGame);
    }
}
