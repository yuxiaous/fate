#include "UgpSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#include "GameUtils.h"
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/uc/UgpSdkJni"

extern "C" {
    void Java_com_hdngame_fate_uc_UgpSdkJni_onUgpSdkChargeCallback(JNIEnv *env, jobject thiz, jint result, jstring jorder)
    {
        cocos2d::log("Java_com_hdngame_fate_uc_UgpSdkJni_onUgpSdkChargeCallback");

        std::string order = JniHelper::jstring2string(jorder);
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
            SdkChargeProtocol::onChargeCallback(result, order.c_str());
        });
    }
}

void UgpSdk::activityOnCreate()
{
    cocos2d::log("UgpSdk::activityOnCreate");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onCreate", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void UgpSdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("UgpSdk::charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

    std::vector<std::string> ret;
    GameUtils::split(order, "-", ret);
    std::string config = getShopConfig(ret[0]);

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "pay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jorder = minfo.env->NewStringUTF(order.c_str());
        jstring jidentifier = minfo.env->NewStringUTF(identifier.c_str());
        jstring jconfig = minfo.env->NewStringUTF(config.c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jorder, jidentifier, jconfig);
    }
}

void UgpSdk::exit()
{
    cocos2d::log("UgpSdk::exit");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "exit", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void UgpSdk::activityOnPause()
{
    cocos2d::log("UgpSdk::activityOnPause");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onPause", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void UgpSdk::activityOnResume()
{
    cocos2d::log("UgpSdk::activityOnResume");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onResume", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void UgpSdk::activityOnDestroy()
{
    cocos2d::log("UgpSdk::activityOnDestroy");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onDestory", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void UgpSdk::activityOnStart()
{
    cocos2d::log("UgpSdk::activityOnStart");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onStart", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void UgpSdk::activityOnRestart()
{
    cocos2d::log("UgpSdk::activityOnRestart");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onRestart", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void UgpSdk::activityOnStop()
{
    cocos2d::log("UgpSdk::activityOnStop");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onStop", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void UgpSdk::activityOnNewIntent(void *intent)
{
    cocos2d::log("UgpSdk::activityOnNewIntent");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onNewIntent", "(Landroid/content/Intent;)V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, intent);
    }
}

