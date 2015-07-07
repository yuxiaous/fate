#include "AndGameSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

using namespace cocos2d;

#define  CLASS_NAME "com/fate/cmcc/and/AndGameSdkJni"

extern "C" {

    void Java_com_fate_cmcc_and_AndGameSdkJni_onAndChargeCallback(JNIEnv *env, jobject thiz, jint result, jstring jorder)
    {
        cocos2d::log("Java_com_fate_cmcc_and_AndGameSdkJni_onAndChargeCallback");
        std::string order = JniHelper::jstring2string(jorder);
        AndGameSdk::getInstance()->onChargeCallback(result, order.c_str());
    }

}



static AndGameSdk *instance = nullptr;
AndGameSdk *AndGameSdk::getInstance()
{
    if(instance == nullptr) {
        instance = new AndGameSdk();
    }
    return instance;
}

void AndGameSdk::init()
{
    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);

//        if(jobj) {
//            if (JniHelper::getMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
//                minfo.env->CallVoidMethod(jobj, minfo.methodID);
//            }
//        }
    }
}

void AndGameSdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("AndGameSdk::charge");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "charge", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jorder = minfo.env->NewStringUTF(order.c_str());
        jstring jidentifier = minfo.env->NewStringUTF(identifier.c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jorder, jidentifier);

//        if(jobj) {
//            if (JniHelper::getMethodInfo(minfo, CLASS_NAME, "charge", "(Ljava/lang/String;Ljava/lang/String;)V")) {
//                jstring jorder = minfo.env->NewStringUTF(order.c_str());
//                jstring jidentifier = minfo.env->NewStringUTF(identifier.c_str());
//
//                minfo.env->CallVoidMethod(jobj, minfo.methodID, jorder, jidentifier);
//            }
//        }
    }
}

bool AndGameSdk::isMusicEnabled()
{
    return true;
}
