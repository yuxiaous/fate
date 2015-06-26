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
};



class AccountProtocol
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
    virtual void setAccountType(AccountProtocol::AccountType accountType) {}
    virtual void setLevel(int level) {}
    virtual void setGender(AccountProtocol::Gender gender) {}
    virtual void setAge(int age) {}
    virtual void setGameServer(const char* gameServer) {}
};



class BuyProtocol
{
public:
    virtual void buy(const std::string &param) {}
    
    virtual void setBuyCallback(const std::function<void(char *param)> &callback) {
        _buyCallback = callback;
    }
    void onBuyCallback(const char *param) {
        // result: [int] 0:success 1:fail
        // order: [string]
        _buyCallback((char*)param);
    }
    
protected:
    BuyProtocol() : _buyCallback(nullptr) {};
    virtual ~BuyProtocol() {}
    
    std::function<void(char*)> _buyCallback;
};

#endif /* defined(__crows__Sdk__) */

