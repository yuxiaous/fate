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

static std::set<Sdk*> _sdks;

#ifdef SDK_TALKING_DATA_GA
#include "TalkingDataGameAnalytics/TalkingDataGameAnalyticsSdk.h"
TalkingDataGameAnalyticsSdk talkingdatagameanalyticssdk;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || defined(CHANNEL_DEVELOP)
#include "DeveloperSdk.h"
DeveloperSdk developersdk;
#endif

#ifdef SDK_YMTX_RECORD
#include "YMTXSdk.h"
YMTXSdk ymtxsdk;
#endif

#ifdef SDK_ANDGAME
#include "AndGame/AndGameSdk.h"
#endif

#ifdef SDK_MM_BILLING
#include "mmbilling/MMSdk.h"
#endif

#ifdef SDK_KTPLAY
#include "ktplay/KtplaySdk.h"
KtplaySdk ktplaysdk;
#endif

USING_NS_CC;



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
#if SDK_TALKING_DATA_GA
//    addSdk(TalkingDataGameAnalyticsSdk::getInstance());
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || defined(CHANNEL_DEVELOP)
//    addSdk(DeveloperSdk::getInstance());
#endif
    
#ifdef SDK_YMTX_RECORD
//    addSdk(new YMTXSdk());
#endif
    
#ifdef SDK_ANDGAME
    addSdk(AndGameSdk::getInstance());
#endif

#ifdef SDK_MM_BILLING
    addSdk(MMSdk::getInstance());
#endif
    
#ifdef SDK_KTPLAY
//    addSdk(KtplaySdk::getInstance());
#endif
}

void SdkManager::init()
{
    for(Sdk *sdk : _sdks) {
        sdk->init();
    }
}

void SdkManager::sdkCommond(const std::string &cmd)
{
    for(Sdk *sdk : _sdks) {
        sdk->sdkCommond(cmd);
    }
}

void SdkManager::charge(const std::string &order, const std::string &identifier)
{
    for(Sdk *sdk : _sdks) {
        SdkChargeProtocol *charge = dynamic_cast<SdkChargeProtocol *>(sdk);
        if(charge) {
            charge->charge(order, identifier);
        }
    }
}

void SdkManager::setChargeCallback(const std::function<void(char *param)> &callback)
{
    for(Sdk *sdk : _sdks) {
        SdkChargeProtocol *charge = dynamic_cast<SdkChargeProtocol *>(sdk);
        if(charge) {
            charge->setChargeCallback(callback);
        }
    }
}

void SdkManager::onChargeResult(int result, const std::string &order)
{
    for(Sdk *sdk : _sdks) {
        SdkChargeProtocol *charge = dynamic_cast<SdkChargeProtocol *>(sdk);
        if(charge) {
            charge->onChargeResult(result, order);
        }
    }
}

void SdkManager::onPurchase(const char* item, int number, double price)
{
    for(Sdk *sdk : _sdks) {
        SdkChargeProtocol *charge = dynamic_cast<SdkChargeProtocol *>(sdk);
        if(charge) {
            charge->onPurchase(item, number, price);
        }
    }
}

void SdkManager::onUse(const char* item, int number)
{
    for(Sdk *sdk : _sdks) {
        SdkChargeProtocol *charge = dynamic_cast<SdkChargeProtocol *>(sdk);
        if(charge) {
            charge->onUse(item, number);
        }
    }
}

void SdkManager::login()
{
    for(Sdk *sdk : _sdks) {
        SdkAccountProtocol *account = dynamic_cast<SdkAccountProtocol *>(sdk);
        if(account) {
            account->login();
        }
    }
}

void SdkManager::setAccount(const char* accountId)
{
    cocos2d::log("SdkManager::setAccount: %s", accountId);
    for(Sdk *sdk : _sdks) {
        SdkAccountProtocol *account = dynamic_cast<SdkAccountProtocol *>(sdk);
        if(account) {
            account->setAccount(accountId);
        }
    }
}

void SdkManager::setAccountName(const char* accountName)
{
    cocos2d::log("SdkManager::setAccountName: %s", accountName);
    for(Sdk *sdk : _sdks) {
        SdkAccountProtocol *account = dynamic_cast<SdkAccountProtocol *>(sdk);
        if(account) {
            account->setAccountName(accountName);
        }
    }
}

void SdkManager::setAccountType(int accountType)
{
    for(Sdk *sdk : _sdks) {
        SdkAccountProtocol *account = dynamic_cast<SdkAccountProtocol *>(sdk);
        if(account) {
            account->setAccountType((SdkAccountProtocol::AccountType)accountType);
        }
    }
}

void SdkManager::setLevel(int level)
{
    for(Sdk *sdk : _sdks) {
        SdkAccountProtocol *account = dynamic_cast<SdkAccountProtocol *>(sdk);
        if(account) {
            account->setLevel(level);
        }
    }
}

void SdkManager::setGender(int gender)
{
    for(Sdk *sdk : _sdks) {
        SdkAccountProtocol *account = dynamic_cast<SdkAccountProtocol *>(sdk);
        if(account) {
            account->setGender((SdkAccountProtocol::Gender)gender);
        }
    }
}

void SdkManager::setAge(int age)
{
    for(Sdk *sdk : _sdks) {
        SdkAccountProtocol *account = dynamic_cast<SdkAccountProtocol *>(sdk);
        if(account) {
            account->setAge(age);
        }
    }
}

void SdkManager::setGameServer(const char* gameServer)
{
    for(Sdk *sdk : _sdks) {
        SdkAccountProtocol *account = dynamic_cast<SdkAccountProtocol *>(sdk);
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


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C" {
    void Java_com_fate_SdkManagerJni_configureSdk()
    {
        cocos2d::log("Java_com_fate_SdkManagerJni_configureSdk");
        SdkManager::configureSdk();
    }

    void Java_com_fate_SdkManagerJni_activityOnCreate(JNIEnv *env, jobject thiz)
    {
        cocos2d::log("Java_com_fate_SdkManagerJni_activityOnCreate");
        SdkManager::activityOnCreate();
    }

    void Java_com_fate_SdkManagerJni_activityOnPause(JNIEnv *env, jobject thiz)
    {
        cocos2d::log("Java_com_fate_SdkManagerJni_activityOnPause");
        SdkManager::activityOnCreate();
    }

    void Java_com_fate_SdkManagerJni_activityOnResume(JNIEnv *env, jobject thiz)
    {
        cocos2d::log("Java_com_fate_SdkManagerJni_activityOnResume");
        SdkManager::activityOnCreate();
    }
}

void SdkManager::activityOnCreate()
{
    for(Sdk *sdk : _sdks) {
        sdk->activityOnCreate();
    }
}

void SdkManager::activityOnPause()
{
    for(Sdk *sdk : _sdks) {
        sdk->activityOnPause();
    }
}

void SdkManager::activityOnResume()
{
    for(Sdk *sdk : _sdks) {
        sdk->activityOnResume();
    }
}
#endif
