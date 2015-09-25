#include "EgameSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/telecom/EgameSdkJni"


extern "C" {
    void Java_com_hdngame_fate_telecom_EgameSdkJni_onEgameChargeCallback(JNIEnv *env, jobject thiz, jint result, jstring jorder)
    {
        cocos2d::log("Java_com_hdngame_fate_telecom_EgameSdkJni_onEgameChargeCallback");

        std::string order = JniHelper::jstring2string(jorder);
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
            SdkChargeProtocol::onChargeCallback(result, order.c_str());
        });
    }

    void Java_com_hdngame_fate_telecom_EgameSdkJni_onEgameExit(JNIEnv *env, jobject thiz)
    {
        cocos2d::log("Java_com_hdngame_fate_telecom_EgameSdkJni_onEgameExit");
        Director::getInstance()->end();
    }

    void EgameSdk_init()
    {
        cocos2d::log("EgameSdk_init");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }

    void EgameSdk_charge(const std::string &order, const std::string &identifier)
    {
        cocos2d::log("EgameSdk_charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

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
}

static EgameSdk *instance = nullptr;

EgameSdk::EgameSdk()
{
    instance = this;
}

EgameSdk *EgameSdk::getInstance()
{
    return instance;
}

void EgameSdk::activityOnCreate()
{
    EgameSdk_init();
}

void EgameSdk::charge(const std::string &order, const std::string &key)
{
    std::string identifier = getChargeIdentifier(key);
    EgameSdk_charge(order, identifier);
}

void EgameSdk::moreGame()
{
    cocos2d::log("EgameSdk::moreGame");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "moreGame", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void EgameSdk::exit()
{
    cocos2d::log("EgameSdk::exit");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "exit", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void EgameSdk::sdkCommand(const std::string &clazz, const std::string &method, const std::string &param)
{
    if(clazz != "Egame"){
        return;
    }
    if(method == "moreGame") {
        moreGame();
    }
    else if(method == "exit") {
        exit();
    }
}

