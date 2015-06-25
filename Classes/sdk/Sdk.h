//
//  Sdk.h
//  crows
//
//  Created by yuxiao on 15/4/7.
//
//

#ifndef __crows__Sdk__
#define __crows__Sdk__

#include <stdio.h>
#include "cocos2d.h"
#include "SdkManager.h"

class Sdk
{
public:
    Sdk();
    virtual ~Sdk();
    
    virtual void init() {}
    virtual void buy(const std::string &param);
    virtual void setBuyCallback(const std::function<void(char *param)> &callback);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
public:
    virtual void applicationDidFinishLaunching() {}
    virtual void applicationWillResignActive(void *iosUIApplication) {}
    virtual void applicationDidBecomeActive(void *iosUIApplication) {}
    virtual void applicationDidEnterBackground(void *iosUIApplication) {}
    virtual void applicationWillEnterForeground(void *iosUIApplication) {}
    virtual void applicationWillTerminate(void *iosUIApplication) {}
    virtual void applicationDidRegisterForRemoteNotificationsWithDeviceToken(void *iosNSData) {}
    virtual void applicationDidReceiveRemoteNotification(void *iosNSDictionary) {}
    virtual bool applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString) { return false; }
#endif

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//protected:
//    static jobject _activity;
//#endif
    
};

#endif /* defined(__crows__Sdk__) */
