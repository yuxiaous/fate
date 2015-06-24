//
//  SdkManager.cpp
//  crows
//
//  Created by yuxiao on 15/4/7.
//
//

#include <set>
#include "cocos2d.h"
#include "SdkManager.h"
#include "Sdk.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
//#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#endif

#ifdef YMTXRECORDSDK
#include "YMTXSdk.h"
#endif

#ifdef ANDGAMESDK
#include "AndGameSdk.h"
#endif

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C" {
void Java_com_fate_SdkManagerJni_init()
{
    JniMethodInfo minfo;
    if(JniHelper::getStaticMethodInfo(minfo, "com/fate/SdkManagerJni", "init", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void Java_com_fate_SdkManagerJni_buy(const std::string &param)
{
    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, "com/fate/SdkManagerJni", "buy", "(Ljava/lang/String;)V")) {
        jstring jparam = minfo.env->NewStringUTF(param.c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jparam);
    }
}

}
#endif


static std::set<Sdk*> _sdks;

void SdkManager::addSdk(Sdk *sdk)
{
    _sdks.insert(sdk);
}

void SdkManager::removeSdk(Sdk *sdk)
{
    _sdks.erase(sdk);
}

void SdkManager::init()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Java_com_fate_SdkManagerJni_init();
#else
#ifdef YMTXRECORDSDK
    addSdk(new YMTXSdk());
#endif

#ifdef ANDGAMESDK
    addSdk(new AndGameSdk());
#endif

    for(Sdk *sdk : _sdks) {
        sdk->init();
    }
#endif
}

void SdkManager::buy(const std::string &param)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Java_com_fate_SdkManagerJni_buy(param);
#else
    for(Sdk *sdk : _sdks) {
        sdk->buy(param);
    }
#endif
}

void SdkManager::setBuyCallback(const std::function<void(char *param)> &callback)
{
    
}

void SdkManager::event(const std::string &param)
{
    
}



#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void *SdkManager::appController = nullptr;
void *SdkManager::viewController = nullptr;
void *SdkManager::window = nullptr;

void SdkManager::applicationDidFinishLaunching()
{
    for(Sdk *sdk : _sdks) {
        sdk->applicationDidFinishLaunching();
    }
}

void SdkManager::applicationWillResignActive(void *iosUIApplication)
{
    for(Sdk *sdk : _sdks) {
        sdk->applicationWillResignActive(iosUIApplication);
    }
}

void SdkManager::applicationDidBecomeActive(void *iosUIApplication)
{
    for(Sdk *sdk : _sdks) {
        sdk->applicationDidBecomeActive(iosUIApplication);
    }
}

void SdkManager::applicationDidEnterBackground(void *iosUIApplication)
{
    for(Sdk *sdk : _sdks) {
        sdk->applicationDidEnterBackground(iosUIApplication);
    }
}

void SdkManager::applicationWillEnterForeground(void *iosUIApplication)
{
    for(Sdk *sdk : _sdks) {
        sdk->applicationWillEnterForeground(iosUIApplication);
    }
}

void SdkManager::applicationWillTerminate(void *iosUIApplication)
{
    for(Sdk *sdk : _sdks) {
        sdk->applicationWillTerminate(iosUIApplication);
    }
}

void SdkManager::applicationDidRegisterForRemoteNotificationsWithDeviceToken(void *iosNSData)
{
    for(Sdk *sdk : _sdks) {
        sdk->applicationDidRegisterForRemoteNotificationsWithDeviceToken(iosNSData);
    }
}

void SdkManager::applicationDidReceiveRemoteNotification(void *iosNSDictionary)
{
    for(Sdk *sdk : _sdks) {
        sdk->applicationDidReceiveRemoteNotification(iosNSDictionary);
    }
}

bool SdkManager::applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString)
{
    bool ret = false;
    
    for(Sdk *sdk : _sdks) {
        ret = ret || sdk->applicationOpenURL(iosUIApplication, iosNSURL, iosNSString);
    }
    
    return ret;
}
#endif

