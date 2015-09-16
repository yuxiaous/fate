#include "AndGameSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#include "JsonStorage.h"

using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/andgame/AndGameSdkJni"


extern "C" {

    void Java_com_hdngame_fate_andgame_AndGameSdkJni_onAndChargeCallback(JNIEnv *env, jobject thiz, jint result, jstring jorder)
    {
        cocos2d::log("Java_com_hdngame_fate_andgame_AndGameSdkJni_onAndChargeCallback");

        std::string order = JniHelper::jstring2string(jorder);
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
            AndGameSdk::onChargeCallback(result, order.c_str());
        });
    }

    void AndGameSdk_init()
    {
        cocos2d::log("AndGameSdk_init");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }

    void AndGameSdk_charge(const std::string &order, const std::string &identifier)
    {
        cocos2d::log("AndGameSdk_charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

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
    AndGameSdk_init();

    bool enable = isMusicEnabled();
    JsonStorage *storage = JsonStorage::GetInstance("setting.json");
    storage->setBoolForKey("background_music_is_open_key", enable);
    storage->setBoolForKey("effect_music_is_open_key", enable);
}

void AndGameSdk::charge(const std::string &order, const std::string &identifier)
{
    AndGameSdk_charge(order, identifier);
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

