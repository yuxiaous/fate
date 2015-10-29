#include "UmengOnlineConfigSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#include "GameUtils.h"
using namespace cocos2d;


bool UmengOnlineConfigSdk::_free = false;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void UmengOnlineConfigSdk::activityOnCreate()
{
//    cocos2d::log("UmengOnlineConfigSdk::activityOnCreate");
    _jinstance = nullptr;

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
                                    "com/umeng/onlineconfig/OnlineConfigAgent",
                                    "getInstance",
                                    "()Lcom/umeng/onlineconfig/OnlineConfigAgent;")) {
        _jinstance = (void*)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    if (_jinstance && JniHelper::getMethodInfo(minfo,
                                    "com/umeng/onlineconfig/OnlineConfigAgent",
                                    "updateOnlineConfig",
                                    "(Landroid/content/Context;)V")) {
        minfo.env->CallVoidMethod((jobject)_jinstance, minfo.methodID, SdkManager::appActivity);
    }
    if (_jinstance && JniHelper::getMethodInfo(minfo,
                                    "com/umeng/onlineconfig/OnlineConfigAgent",
                                    "setDebugMode",
                                    "(Z)V")) {
        minfo.env->CallVoidMethod((jobject)_jinstance, minfo.methodID, GameUtils::isDebugMode());
    }
}
#endif

void UmengOnlineConfigSdk::init()
{
    Director::getInstance()->getScheduler()->schedule([this](float dt) {
        if(getConfigParams("crash") == "true") {
            assert(0);
        }
        if(getConfigParams("free") == "true") {
            _free = true;
        }
    }, this, 15, 0, 0, false, "UmengOnlineConfigSdk");
}

std::string UmengOnlineConfigSdk::getConfigParams(const std::string &key)
{
//    cocos2d::log("UmengOnlineConfigSdk::getConfigParams %s", key.c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (_jinstance && JniHelper::getMethodInfo(minfo,
                                "com/umeng/onlineconfig/OnlineConfigAgent",
                                "getConfigParams",
                                "(Landroid/content/Context;Ljava/lang/String;)Ljava/lang/String;")) {
        jstring jkey = minfo.env->NewStringUTF(key.c_str());
        jstring jvalue = (jstring)minfo.env->CallObjectMethod((jobject)_jinstance, minfo.methodID, SdkManager::appActivity, jkey);
        std::string value = JniHelper::jstring2string(jvalue);
        return value;
    }
#endif

    return "";
}

