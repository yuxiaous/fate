#include "DKSingleSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/dksingle/DKSingleSdkJni"

extern "C" {
    void DKSingleSdk_init()
    {
        cocos2d::log("DKSingleSdk_init");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }

    void DKSingleSdk_pause()
    {
        cocos2d::log("DKSingleSdk_pause");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "pause", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }

    void DKSingleSdk_exit()
    {
        cocos2d::log("DKSingleSdk_exit");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "exit", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }

    void Java_com_hdngame_fate_dksingle_DKSingleSdkJni_onDKSingleSdkExit(JNIEnv *env, jobject thiz)
    {
        cocos2d::log("Java_com_hdngame_fate_dksingle_DKSingleSdkJni_onDKSingleSdkExit");

        Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
            Director::getInstance()->end();
        });
    }

}

void DKSingleSdk::activityOnCreate()
{
    DKSingleSdk_init();
}

void DKSingleSdk::activityOnPause()
{
    cocos2d::log("DKSingleSdk::activityOnPause");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onPause", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void DKSingleSdk::activityOnResume()
{
    cocos2d::log("DKSingleSdk::activityOnResume");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "onResume", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void DKSingleSdk::sdkCommand(const std::string &clazz, const std::string &method, const std::string &param)
{
//    cocos2d::log("DKSingleSdk::sdkCommand %s %s %s", clazz.c_str(), method.c_str(), param.c_str());

    if(clazz != "DKSingle"){
        return;
    }
    if(method == "pause") {
        DKSingleSdk_pause();
    }
    else if(method == "exit") {
        DKSingleSdk_exit();
    }
}

