#include "UniPaySdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/unicom/UniPaySdkJni"


static std::string g_order;
static int g_result = 0;

extern "C" {

    void Java_com_hdn_fate_unicom_UniPaySdkJni_onUniPayChargeCallback(JNIEnv *env, jobject thiz, jint result, jstring jorder)
    {
        cocos2d::log("Java_com_hdngame_fate_unicom_UniPaySdkJni_onUniPayChargeCallback");
        g_order = JniHelper::jstring2string(jorder);
        g_result = result;
//        MMSdk::getInstance()->onChargeCallback(result, order.c_str());
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

void UniPaySdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("UniPaySdk::charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

    if(order.empty() || identifier.empty()) {
        onChargeCallback(1, order);
        return;
    }

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

