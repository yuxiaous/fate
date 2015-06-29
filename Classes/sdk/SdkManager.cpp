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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "TalkingDataGameAnalyticsSdk.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "DeveloperSdk.h"
#endif

#ifdef YMTXRECORDSDK
#include "YMTXSdk.h"
#endif

#ifdef ANDGAMESDK
#include "AndGameSdk.h"
#endif

USING_NS_CC;


static std::set<Sdk*> _sdks;

void SdkManager::addSdk(Sdk *sdk)
{
    _sdks.insert(sdk);
}

void SdkManager::removeSdk(Sdk *sdk)
{
    _sdks.erase(sdk);
}

void SdkManager::configureSdk()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    addSdk(TalkingDataGameAnalyticsSdk::getInstance());
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    addSdk(DeveloperSdk::getInstance());
#endif
    
#ifdef YMTXRECORDSDK
    addSdk(new YMTXSdk());
#endif
    
#ifdef ANDGAMESDK
    addSdk(AndGameSdk::getInstance());
#endif
}

void SdkManager::init()
{
    for(Sdk *sdk : _sdks) {
        sdk->init();
    }
}

void SdkManager::buy(const std::string &param)
{
    for(Sdk *sdk : _sdks) {
        BuyProtocol *buy = dynamic_cast<BuyProtocol *>(sdk);
        if(buy) {
            buy->buy(param);
        }
    }
}

void SdkManager::setBuyCallback(const std::function<void(char *param)> &callback)
{
    for(Sdk *sdk : _sdks) {
        BuyProtocol *buy = dynamic_cast<BuyProtocol *>(sdk);
        if(buy) {
            buy->setBuyCallback(callback);
        }
    }
}


void SdkManager::login()
{
    
}

void SdkManager::setAccount(const char* accountId)
{
    for(Sdk *sdk : _sdks) {
        AccountProtocol *account = dynamic_cast<AccountProtocol *>(sdk);
        if(account) {
            account->setAccount(accountId);
        }
    }
}

void SdkManager::setAccountName(const char* accountName)
{
    for(Sdk *sdk : _sdks) {
        AccountProtocol *account = dynamic_cast<AccountProtocol *>(sdk);
        if(account) {
            account->setAccountName(accountName);
        }
    }
}

void SdkManager::setAccountType(int accountType)
{
    for(Sdk *sdk : _sdks) {
        AccountProtocol *account = dynamic_cast<AccountProtocol *>(sdk);
        if(account) {
            account->setAccountType((AccountProtocol::AccountType)accountType);
        }
    }
}

void SdkManager::setLevel(int level)
{
    for(Sdk *sdk : _sdks) {
        AccountProtocol *account = dynamic_cast<AccountProtocol *>(sdk);
        if(account) {
            account->setLevel(level);
        }
    }
}

void SdkManager::setGender(int gender)
{
    for(Sdk *sdk : _sdks) {
        AccountProtocol *account = dynamic_cast<AccountProtocol *>(sdk);
        if(account) {
            account->setGender((AccountProtocol::Gender)gender);
        }
    }
}

void SdkManager::setAge(int age)
{
    for(Sdk *sdk : _sdks) {
        AccountProtocol *account = dynamic_cast<AccountProtocol *>(sdk);
        if(account) {
            account->setAge(age);
        }
    }
}

void SdkManager::setGameServer(const char* gameServer)
{
    for(Sdk *sdk : _sdks) {
        AccountProtocol *account = dynamic_cast<AccountProtocol *>(sdk);
        if(account) {
            account->setGameServer(gameServer);
        }
    }
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

