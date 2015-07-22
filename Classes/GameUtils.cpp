//
//  GameUtils.cpp
//  fate
//
//  Created by yuxiao on 15/7/1.
//
//

#include "GameUtils.h"
#include "ScriptingCore.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#endif

USING_NS_CC;

int GameUtils::getChannelId()
{
#if defined(CHANNEL_APPSTORE)
    return 1;
#elif defined(CHANNEL_CMCC_AND)
    return 2;
#elif defined(CHANNEL_CMCC_MM)
    return 3;
#elif defined(CHANNEL_TELECOM) //电信
    return 4;
#elif defined(CHANNEL_UNICOM) //联通
    return 5;
#endif
    
    return 0;
}

std::string GameUtils::getUdid()
{
    cocos2d::log("GameUtils::getUdid");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return getUdidWithIos();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return getUdidWithAndroid();
#endif

    return "hdngame";
}

std::string GameUtils::call(const std::string &clazz, const std::string &method, const std::string &param)
{
//    JS::HandleValueArray args;
//    JS::MutableHandleValue retVal;
//    
//    ScriptingCore *sc = ScriptingCore::getInstance();
//    sc->executeFunctionWithOwner(null, "", args, retVal);
    
    
    return std::string();
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
std::string GameUtils::getUdidWithAndroid()
{
    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
                                       "org/cocos2dx/javascript/AppActivity",
                                       "getAndroidId",
                                       "()Ljava/lang/String;")) {
        jstring jAndroidId = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
        std::string androidId = JniHelper::jstring2string(jAndroidId);
        return androidId;
    }
    
    return std::string();
}
#endif
