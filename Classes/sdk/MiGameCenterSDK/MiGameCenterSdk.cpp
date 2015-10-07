#include "MiGameCenterSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define CLASS_NAME "com/hdngame/fate/mi/MiGameCenterSdkJni"

extern "C" {

    void Java_com_hdngame_fate_mi_MiGameCenterSdkJni_onMiGameChargeCallback(JNIEnv *env, jobject thiz, jint result, jstring jorder)
    {
        cocos2d::log("Java_com_hdngame_fate_mi_MiGameCenterSdkJni_onMiGameChargeCallback");

        std::string order = JniHelper::jstring2string(jorder);
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
            SdkChargeProtocol::onChargeCallback(result, order.c_str());
        });
    }
}

void MiGameCenterSdk::activityOnCreate()
{
    cocos2d::log("MiGameCenterSdk::activityOnCreate");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void MiGameCenterSdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("MiGameCenterSdk::charge: %s, identifier: %s", order.c_str(), identifier.c_str()");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "pay", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jorder = minfo.env->NewStringUTF(order.c_str());
        jstring jidentifier = minfo.env->NewStringUTF(identifier.c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jorder, jidentifier);
    }
}

