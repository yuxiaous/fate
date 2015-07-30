#include "EgameSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/telecom/EgameSdkJni"


static std::string g_order;
static int g_result;
static bool g_confirm = false;

extern "C" {

    void Java_com_hdngame_fate_telecom_EgameSdkJni_onEgameChargeCallback(JNIEnv *env, jobject thiz, jint result)
    {
        cocos2d::log("Java_com_hdngame_fate_telecom_EgameSdkJni_onEgameChargeCallback");
        g_result = result;
        g_confirm = true;
    }

    void Java_com_hdngame_fate_telecom_EgameSdkJni_onEgameExit(JNIEnv *env, jobject thiz)
    {
        cocos2d::log("Java_com_hdngame_fate_telecom_EgameSdkJni_onEgameExit");
        Director::getInstance()->end();
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

void EgameSdk::update(float dt)
{
    if(g_confirm) {
        onChargeCallback(g_result, g_order.c_str());
        g_result = 0;
        g_order.clear();
        g_confirm = false;
    }
}

void EgameSdk::activityOnCreate()
{
    cocos2d::log("EgameSdk::activityOnCreate");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void EgameSdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("EgameSdk::charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

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

