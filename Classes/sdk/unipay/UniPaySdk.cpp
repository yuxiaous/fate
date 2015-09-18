#include "UniPaySdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/unicom/UniPaySdkJni"


extern "C" {

    void Java_com_hdngame_fate_unicom_UniPaySdkJni_onUniPayChargeCallback(JNIEnv *env, jobject thiz, jint result, jstring jorder)
    {
        cocos2d::log("Java_com_hdn_fate_unicom_UniPaySdkJni_onUniPayChargeCallback");

        std::string order = JniHelper::jstring2string(jorder);
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
            SdkChargeProtocol::onChargeCallback(result, order.c_str());
        });
    }

    void UniPaySdk_init()
    {
        cocos2d::log("UniPaySdk_init");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }

    void UniPaySdk_charge(const std::string &order, const std::string &identifier)
    {
        cocos2d::log("UniPaySdk_charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

        if(order.empty() || identifier.empty()) {
            SdkChargeProtocol::onChargeCallback(1, order);
            return;
        }

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "pay", "(Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring jorder = minfo.env->NewStringUTF(order.c_str());
            jstring jidentifier = minfo.env->NewStringUTF(identifier.c_str());
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jorder, jidentifier);
        }
    }

    void UniPaySdk_onPause()
    {
        cocos2d::log("UniPaySdk_onPause");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onPause", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }

    void UniPaySdk_onResume()
    {
        cocos2d::log("UniPaySdk_onResume");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onResume", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }

    void UniPaySdk_moreGame()
    {
        cocos2d::log("UniPaySdk_moreGame");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "moreGame", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
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

void UniPaySdk::activityOnCreate()
{

}

void UniPaySdk::init()
{

}

void UniPaySdk::charge(const std::string &order, const std::string &identifier)
{
    UniPaySdk_charge(order, identifier);
}

void UniPaySdk::activityOnPause()
{
    UniPaySdk_onPause();
}

void UniPaySdk::activityOnResume()
{
    UniPaySdk_onResume();
}

void UniPaySdk::moreGame()
{
    UniPaySdk_moreGame();
}

