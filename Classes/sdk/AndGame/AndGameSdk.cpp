#include "AndGameSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/cmcc/and/AndGameSdkJni"


static std::string g_order;
static int g_result = 0;

extern "C" {

    void Java_com_hdngame_fate_cmcc_and_AndGameSdkJni_onAndChargeCallback(JNIEnv *env, jobject thiz, jint result, jstring jorder)
    {
        cocos2d::log("Java_com_hdngame_fate_cmcc_and_AndGameSdkJni_onAndChargeCallback");
        g_order = JniHelper::jstring2string(jorder);
        g_result = result;
//        std::string order = JniHelper::jstring2string(jorder);
//        AndGameSdk::getInstance()->onChargeCallback(result, order.c_str());
    }

}



static AndGameSdk *instance = nullptr;

AndGameSdk::AndGameSdk()
{
    instance = this;
}

AndGameSdk *AndGameSdk::getInstance()
{
    return instance;
}

void AndGameSdk::init()
{
    cocos2d::log("AndGameSdk::init");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void AndGameSdk::update(float dt)
{
    if(!g_order.empty()) {
        onChargeCallback(g_result, g_order.c_str());
        g_result = 0;
        g_order.clear();
    }
}

void AndGameSdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("AndGameSdk::charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

    if(order.empty() || identifier.empty()) {
        return;
    }

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "charge", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jorder = minfo.env->NewStringUTF(order.c_str());
        jstring jidentifier = minfo.env->NewStringUTF(identifier.c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jorder, jidentifier);
    }
}

void AndGameSdk::sdkCommand(const std::string &clazz, const std::string &method, const std::string &param)
{
    if(clazz != "AndGame"){
        return;
    }
    if(method == "exit") {
        exit();
    }
    else if(method == "showMoreGames") {
        showMoreGames();
    }
    else if(method == "doScreenShotShare") {
        doScreenShotShare();
    }
}

bool AndGameSdk::isMusicEnabled()
{
    cocos2d::log("AndGameSdk::isMusicEnabled");
    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "isMusicEnabled", "()Z")) {
        bool ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID);
        cocos2d::log("isMusicEnabled: %d", ret);
        return ret;
    }
    return true;
}

void AndGameSdk::exit()
{
    cocos2d::log("AndGameSdk::exit");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "exit", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void AndGameSdk::showMoreGames()
{
    cocos2d::log("AndGameSdk::showMoreGames");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "showMoreGames", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void AndGameSdk::doScreenShotShare()
{
    cocos2d::log("AndGameSdk::doScreenShotShare");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "doScreenShotShare", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

