//
//  SdkManager.cpp
//  crows
//
//  Created by yuxiao on 15/4/7.
//
//

#include <set>
#include "SdkManager.h"
#include "Sdk.h"

#ifdef YMTXRECORDSDK
#include "YMTXSdk.h"
#endif

#ifdef ANDGAMESDK
#include "AndGameSdk.h"
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
#ifdef YMTXRECORDSDK
    addSdk(new YMTXSdk());
#endif

#ifdef ANDGAMESDK
    addSdk(new AndGameSdk());
#endif
    
    for(Sdk *sdk : _sdks) {
        sdk->init();
    }
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void SdkManager::setAppController(void *ac)
{
    Sdk::_appController = ac;
}

void SdkManager::setViewController(void *vc)
{
    Sdk::_viewController = vc;
}

void SdkManager::setWindow(void *win)
{
    Sdk::_window = win;
}

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


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C" {
void Java_org_cocos2dx_javascript_AppActivity_setActivity(JNIEnv *env, jobject thiz, jobject act)
{
    cocos2d::log("Java_org_cocos2dx_javascript_AppActivity_setActivity");
    SdkManager::setActivity(act);
}
}

void SdkManager::setActivity(jobject act)
{
    Sdk::_activity = act;
}
#endif