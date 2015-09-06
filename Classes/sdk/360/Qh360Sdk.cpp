#include "Qh360Sdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

using namespace cocos2d;


#define  CLASS_NAME "com/hdngame/fate/qh360/Qh360SdkJni"


static Qh360Sdk *instance = nullptr;

Qh360Sdk::Qh360Sdk()
{
    instance = this;
}

Qh360Sdk *Qh360Sdk::getInstance()
{
    return instance;
}

void Qh360Sdk::activityOnCreate()
{
    cocos2d::log("Qh360Sdk::activityOnCreate");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void Qh360Sdk::init()
{
//    cocos2d::log("Qh360Sdk::init");
//
//    JniMethodInfo minfo;
//    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
//        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
//    }
}

void Qh360Sdk::update(float dt)
{

}

void Qh360Sdk::sdkCommand(const std::string &clazz, const std::string &method, const std::string &param)
{

}

void Qh360Sdk::login()
{
    cocos2d::log("Qh360Sdk::login");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "login", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void Qh360Sdk::charge(const std::string &order, const std::string &identifier)
{

}