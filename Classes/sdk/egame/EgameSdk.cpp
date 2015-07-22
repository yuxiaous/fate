#include "EgameSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/telecom/EgameSdkJni"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void EgameSdk::activityOnCreate()
{
    cocos2d::log("EgameSdk::activityOnCreate");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}
#endif

void EgameSdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("EgameSdk::charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

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

void EgameSdk::moreGame()
{
    cocos2d::log("EgameSdk::moreGame");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "moreGame", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

