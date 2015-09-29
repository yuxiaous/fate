//
//  GameUtils.cpp
//  fate
//
//  Created by yuxiao on 15/7/1.
//
//

#include "GameUtils.h"
#include "ScriptingCore.h"
#include "sdk/SdkManager.h"

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
#elif defined(CHANNEL_MZW)
    return 6;
#elif defined(CHANNEL_4399)
    return 7;
#elif defined(CHANNEL_360)
    return 8;
#elif defined(CHANNEL_TENCENT_QQ) //应用宝
    return 9;
#elif defined(CHANNEL_MIX)
    return 10;
#elif defined(CHANNEL_PPS)
    return 11;
#elif defined(CHANNEL_SOHUWAN)
    return 12;
#elif defined(CHANNEL_YOUKU)
    return 13;
#elif defined(CHANNEL_BAIDU_91)
    return 14;
#elif defined(CHANNEL_BAIDU_TIEBA)
    return 15;
#elif defined(CHANNEL_BAIDU_SHOUJIZHUSHOU)
    return 16;
#elif defined(CHANNEL_BAIDU_DUOKU)
    return 17;
#elif defined(CHANNEL_KUWO)
    return 18;
#elif defined(CHANNEL_TTYX)
    return 19;
#elif defined(CHANNEL_7K7K)
    return 20;
#elif defined(CHANNEL_LETVS)
    return 21;
#elif defined(CHANNEL_YOULETANG)
    return 22;
#elif defined(CHANNEL_FEILIU)
    return 23;
#elif defined(CHANNEL_HTC)
    return 24;
#elif defined(CHANNEL_YOUYOUCUN)
    return 25;
#elif defined(CHANNEL_ANZHI)
    return 26;
#elif defined(CHANNEL_MEITU)
    return 27;
#elif defined(CHANNEL_YINGYONGHUI)
    return 28;
#elif defined(CHANNEL_DANGLE)
    return 29;
#elif defined(CHANNEL_SANXING)
    return 30;
#elif defined(CHANNEL_XY_ANZHUO)
    return 31;
#elif defined(CHANNEL_WANDOUJIA)
    return 32;
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

int GameUtils::getSignatureCode()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
                                       "com/hdngame/fate/GameUtils",
                                       "getSignatureCode",
                                       "(Landroid/content/Context;)I")) {
        int jSignatureCode = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, SdkManager::appActivity);
        return jSignatureCode;
    }
#endif

    return 0;
}

int GameUtils::getSimOperator()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
                                       "com/hdngame/fate/GameUtils",
                                       "getSimOperator",
                                       "(Landroid/content/Context;)I")) {
        int jSimOperatorId = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, SdkManager::appActivity);
        return jSimOperatorId;
    }
#endif

    return 0;
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

void GameUtils::split(const std::string &s, const std::string &delim, std::vector<std::string> &ret)
{
    size_t last = 0;
    size_t index = s.find_first_of(delim, last);
    while (index != std::string::npos) {
        ret.push_back(s.substr(last, index - last));
        last = index + 1;
        index = s.find_first_of(delim, last);
    }
    if (index - last > 0) {
        ret.push_back(s.substr(last, index - last));
    }
}

GameUtils::ConfigGetter GameUtils::_configGetter = nullptr;

void GameUtils::setConfigGetter(const ConfigGetter &getter)
{
    _configGetter = getter;
}

const GameUtils::ConfigGetter &GameUtils::getConfigGetter()
{
    return _configGetter;
}
