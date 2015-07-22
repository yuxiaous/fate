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
    virtual void update(float dt) {}
    virtual void sdkCommand(const std::string &name, const std::string &cmd) {}
    
    
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() {}
    virtual void activityOnPause() {}
    virtual void activityOnResume() {}
#endif
};



class SdkAccountProtocol
{
public:
    virtual void login() {}
};



class SdkChargeProtocol
{
public:
    virtual void charge(const std::string &order, const std::string &identifier) {}
    
    void setChargeCallback(const std::function<void(char *param)> &cb) {_chargeCallback = cb;}
    void onChargeCallback(int result, const std::string &order);
    
protected:
    SdkChargeProtocol() : _chargeCallback(nullptr) {};
    virtual ~SdkChargeProtocol() {}
    
    std::function<void(char*)> _chargeCallback;
};

#endif /* defined(__crows__Sdk__) */

