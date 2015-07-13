//
//  TalkingDataGameAnalyticsSdk.cpp
//  fate
//
//  Created by yuxiao on 15/6/26.
//
//

#include "TalkingDataGameAnalyticsSdk.h"

#if  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "TalkingDataGameAnalytics/android/TDGAJniHelper.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#endif

USING_NS_CC;


static TalkingDataGameAnalyticsSdk *instance = nullptr;

TalkingDataGameAnalyticsSdk::TalkingDataGameAnalyticsSdk()
: _account(nullptr)
{
    instance = this;
}

TalkingDataGameAnalyticsSdk *TalkingDataGameAnalyticsSdk::getInstance()
{
    return instance;
}

void TalkingDataGameAnalyticsSdk::init()
{
    cocos2d::log("TalkingDataGameAnalyticsSdk::init");

    const char *appid = "59EC3DE05BB0234EA444193F4B9E0E4B";

#if defined(CHANNEL_CMCC_MM)
    const char *channel = "CmccMm";
#elif defined(CHANNEL_CMCC_AND)
    const char *channel = "CmccAnd";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    const char *channel = "IosDevelop";
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    const char *channel = "AndroidDevelop";
#else
    const char *channel = "Develop";
#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    TDCCTalkingDataGA::onStart(appid, channel);
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    TDGAJniHelper::setJavaVM(JniHelper::getJavaVM());

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
        "com.tendcloud.tenddata.TalkingDataGA",
        "init",
        "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V")) {

        jobject jactivity = (jobject)SdkManager::appActivity;
        jstring jappid = minfo.env->NewStringUTF(appid);
        jstring jchannel = minfo.env->NewStringUTF(channel);

        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jactivity, jappid, jchannel);

        minfo.env->DeleteLocalRef(jappid);
        minfo.env->DeleteLocalRef(jchannel);
    }
#endif
}

void TalkingDataGameAnalyticsSdk::setAccount(const char* accountId)
{
    if(_account == nullptr) {
        _account = TDCCAccount::setAccount(accountId);
    }
}

void TalkingDataGameAnalyticsSdk::setAccountName(const char* accountName)
{
    if(_account) {
        _account->setAccountName(accountName);
    }
}

void TalkingDataGameAnalyticsSdk::setAccountType(SdkAccountProtocol::AccountType accountType)
{
    if(_account) {
        TDCCAccount::TDCCAccountType type = TDCCAccount::kAccountAnonymous;
        switch (accountType) {
            case AccountType::Registered:
                type = TDCCAccount::kAccountRegistered;
                break;
            case AccountType::SianWeibo:
                type = TDCCAccount::kAccountSianWeibo;
                break;
            case AccountType::QQ:
                type = TDCCAccount::kAccountQQ;
                break;
            case AccountType::TencentWeibo:
                type = TDCCAccount::kAccountTencentWeibo;
                break;
            case AccountType::ND91:
                type = TDCCAccount::kAccountND91;
                break;
            default:
                type = TDCCAccount::kAccountAnonymous;
                break;
        }
        _account->setAccountType(type);
    }
}

void TalkingDataGameAnalyticsSdk::setLevel(int level)
{
    if(_account) {
        _account->setLevel(level);
    }
}

void TalkingDataGameAnalyticsSdk::setGender(SdkAccountProtocol::Gender gender)
{
    if(_account) {
        switch (gender) {
            case Gender::Male:
                _account->setGender(TDCCAccount::kGenderMale);
                break;
            case Gender::Female:
                _account->setGender(TDCCAccount::kGenderFemale);
                break;
            default:
                _account->setGender(TDCCAccount::kGenderUnknown);
                break;
        }
    }
}

void TalkingDataGameAnalyticsSdk::setAge(int age)
{
    if(_account) {
        _account->setAge(age);
    }
}

void TalkingDataGameAnalyticsSdk::setGameServer(const char* gameServer)
{
    if(_account) {
        SdkAccountProtocol::setGameServer(gameServer);
    }
}

void TalkingDataGameAnalyticsSdk::charge(const std::string &order, const std::string &identifier)
{
    TDCCVirtualCurrency::onChargeRequest(order.c_str(), "test", 100, "CNY", 100, "test pay");
}

void TalkingDataGameAnalyticsSdk::onChargeResult(int result, const std::string &order)
{
    if(result == 0) {
        TDCCVirtualCurrency::onChargeSuccess(order.c_str());
    }
}

void TalkingDataGameAnalyticsSdk::onPurchase(const char* item, int number, double price)
{
    TDCCItem::onPurchase(item, number, price);
}

void TalkingDataGameAnalyticsSdk::onUse(const char* item, int number)
{
    TDCCItem::onUse(item, number);
}

