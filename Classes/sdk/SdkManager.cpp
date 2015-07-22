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
AndGameSdk andgamesdk;
#endif

#ifdef SDK_MM_BILLING
#include "mmbilling/MMSdk.h"
MMSdk mmsdk;
#endif

#ifdef SDK_KTPLAY
#include "ktplay/KtplaySdk.h"
KtplaySdk ktplaysdk;
#endif

#ifdef SDK_UNIPAY
#include "unipay/UniPaySdk.h"
UniPaySdk unipaysdk;
#endif

#ifdef SDK_EGAME
#include "egame/EgameSdk.h"
EgameSdk egamesdk;
#endif

USING_NS_CC;


class SdkManagerUpdate : public cocos2d::Ref
{
public:
    SdkManagerUpdate() {
        cocos2d::Scheduler *scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->schedule(CC_SCHEDULE_SELECTOR(SdkManagerUpdate::update), this, 0, false);
    }
    void update(float dt) {
        SdkManager::update(dt);
    }
};
static SdkManagerUpdate *s_sdk_manager_update = nullptr;



void SdkManager::addSdk(Sdk *sdk)
{
    _sdks.insert(sdk);
}

void SdkManager::removeSdk(Sdk *sdk)
{
    _sdks.erase(sdk);
}

void SdkManager::update(float dt)
{
    for(Sdk *sdk : _sdks) {
        sdk->update(dt);
    }
}

void SdkManager::init()
{
    if(s_sdk_manager_update == nullptr) {
        s_sdk_manager_update = new SdkManagerUpdate();
    }
    
    for(Sdk *sdk : _sdks) {
        sdk->init();
    }
}

void SdkManager::sendSdkCommand(const std::string &name, const std::string &cmd)
{
    for(Sdk *sdk : _sdks) {
        sdk->sdkCommand(name, cmd);
    }
}

std::function<void(char*, char*)> SdkManager::_sdkCmdCallback = nullptr;

void SdkManager::recvSdkCommand(const std::string &name, const std::string &cmd)
{
    if(_sdkCmdCallback) {
        _sdkCmdCallback((char*)name.c_str(), (char*)cmd.c_str());
    }
}


// AccountProtocol
void SdkManager::login()
{
    for(Sdk *sdk : _sdks) {
        SdkAccountProtocol *account = dynamic_cast<SdkAccountProtocol *>(sdk);
        if(account) {
            account->login();
        }
    }
}

// ChargeProtocol
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
void *SdkManager::appActivity = nullptr;

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

extern "C" {
    void Java_com_hdngame_fate_SdkManagerJni_setAppActivity(JNIEnv *env, jobject thiz, jobject activity)
    {
        cocos2d::log("Java_com_hdngame_fate_SdkManagerJni_setAppActivity");
        SdkManager::appActivity = (void*)env->NewGlobalRef(activity);
    }

    void Java_com_hdngame_fate_SdkManagerJni_activityOnCreate(JNIEnv *env, jobject thiz)
    {
        cocos2d::log("Java_com_hdngame_fate_SdkManagerJni_activityOnCreate");
        SdkManager::activityOnCreate();
    }

    void Java_com_hdngame_fate_SdkManagerJni_activityOnPause(JNIEnv *env, jobject thiz)
    {
        cocos2d::log("Java_com_hdngame_fate_SdkManagerJni_activityOnPause");
        SdkManager::activityOnPause();
    }

    void Java_com_hdngame_fate_SdkManagerJni_activityOnResume(JNIEnv *env, jobject thiz)
    {
        cocos2d::log("Java_com_hdngame_fate_SdkManagerJni_activityOnResume");
        SdkManager::activityOnResume();
    }
}
#endif
