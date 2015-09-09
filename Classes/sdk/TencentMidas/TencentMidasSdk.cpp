#include "TencentMidasSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

using namespace cocos2d;


#define  CLASS_NAME "com/hdngame/fate/qq/TencentMidasSdkJni"

extern "C" {
    int Java_com_hdngame_fate_qq_TencentMidasSdkJni_getLaunchType(JNIEnv *env, jobject thiz) {
        return 1;
    }
    jstring Java_com_hdngame_fate_qq_TencentMidasSdkJni_getAppSecretKey(JNIEnv *env, jobject thiz) {
        return env->NewStringUTF("111222333444555");
    }
    jstring Java_com_hdngame_fate_qq_TencentMidasSdkJni_getOfferId(JNIEnv *env, jobject thiz) {
        return env->NewStringUTF("1450000766");
    }
    jstring Java_com_hdngame_fate_qq_TencentMidasSdkJni_getUserId(JNIEnv *env, jobject thiz) {
        return env->NewStringUTF("uin_20150909");
    }
    jstring Java_com_hdngame_fate_qq_TencentMidasSdkJni_getUserKey(JNIEnv *env, jobject thiz) {
        return env->NewStringUTF("skey");
    }
    jstring Java_com_hdngame_fate_qq_TencentMidasSdkJni_getSessionId(JNIEnv *env, jobject thiz) {
        return env->NewStringUTF("hy_gameid");
    }
    jstring Java_com_hdngame_fate_qq_TencentMidasSdkJni_getSessionType(JNIEnv *env, jobject thiz) {
        return env->NewStringUTF("st_dummy");
    }
    jstring Java_com_hdngame_fate_qq_TencentMidasSdkJni_getPf(JNIEnv *env, jobject thiz) {
        return env->NewStringUTF("huyu_m-2001-android");
    }
    jstring Java_com_hdngame_fate_qq_TencentMidasSdkJni_getPfKey(JNIEnv *env, jobject thiz) {
        return env->NewStringUTF("pfKey");
    }
}


static TencentMidasSdk *instance = nullptr;

TencentMidasSdk::TencentMidasSdk()
{
    instance = this;
}

TencentMidasSdk *TencentMidasSdk::getInstance()
{
    return instance;
}

void TencentMidasSdk::init()
{
    cocos2d::log("TencentMidasSdk::init");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

