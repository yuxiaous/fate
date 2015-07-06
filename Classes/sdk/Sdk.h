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
#endif
};



class SdkAccountProtocol
{
public:
    enum class AccountType {
        Anonymous = 0,
        Registered,
        SianWeibo,
        QQ,
        TencentWeibo,
        ND91,
    };
    
    enum class Gender {
        Unknown = 0,
        Male = 1,
        Female = 2
    };
    
public:
    virtual void login() {}
    
    virtual void setAccount(const char* accountId) {}
    virtual void setAccountName(const char* accountName) {}
    virtual void setAccountType(SdkAccountProtocol::AccountType accountType) {}
    virtual void setLevel(int level) {}
    virtual void setGender(SdkAccountProtocol::Gender gender) {}
    virtual void setAge(int age) {}
    virtual void setGameServer(const char* gameServer) {}
};



class SdkChargeProtocol
{
public:
    virtual void charge(const std::string &order, const std::string &identifier) {}
    virtual void onChargeResult(int result, const std::string &order) {}
    virtual void onPurchase(const char* item, int number, double price) {}
    virtual void onUse(const char* item, int number) {}
    
    void setChargeCallback(const std::function<void(char *param)> &cb) {_chargeCallback = cb;}
    void onChargeCallback(int result, const std::string &order);
    
protected:
    SdkChargeProtocol() : _chargeCallback(nullptr) {};
    virtual ~SdkChargeProtocol() {}
    
    std::function<void(char*)> _chargeCallback;
};

#endif /* defined(__crows__Sdk__) */

