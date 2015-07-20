#include "UniPaySdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/unicom/UniPaySdkJni"


static std::string g_order;
static int g_result;
static bool g_confirm = false;

extern "C" {

    void Java_com_hdngame_fate_unicom_UniPaySdkJni_onUniPayChargeCallback(JNIEnv *env, jobject thiz, jint result)
    {
        cocos2d::log("Java_com_hdn_fate_unicom_UniPaySdkJni_onUniPayChargeCallback");
        g_result = result;
        g_confirm = true;
//        UniPaySdk::getInstance()->onChargeCallback(result, g_order);
    }
}



static UniPaySdk *instance = nullptr;

UniPaySdk::UniPaySdk()
{
    instance = this;
}

UniPaySdk *UniPaySdk::getInstance()
{
    return instance;
}

void UniPaySdk::init()
{

}

void UniPaySdk::update(float dt)
{
    if(g_confirm) {
        onChargeCallback(g_result, g_order.c_str());
        g_result = 0;
        g_order.clear();
        g_confirm = false;
    }
}

void UniPaySdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("UniPaySdk::charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

    if(order.empty() || identifier.empty()) {
        onChargeCallback(1, order);
        return;
    }

    g_order = order;

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "pay", "(Ljava/lang/String;)V")) {
        jstring jidentifier = minfo.env->NewStringUTF(identifier.c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jidentifier);
        minfo.env->DeleteLocalRef(jidentifier);
    }
}

void UniPaySdk::activityOnPause()
{
    cocos2d::log("UniPaySdk::activityOnPause");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onPause", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void UniPaySdk::activityOnResume()
{
    cocos2d::log("UniPaySdk::activityOnResume");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onResume", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void UniPaySdk::moreGame()
{
    cocos2d::log("UniPaySdk::moreGame");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "moreGame", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

