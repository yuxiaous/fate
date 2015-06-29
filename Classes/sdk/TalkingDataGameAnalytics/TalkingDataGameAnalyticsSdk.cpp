//
//  TalkingDataGameAnalyticsSdk.cpp
//  fate
//
//  Created by yuxiao on 15/6/26.
//
//

#include "TalkingDataGameAnalyticsSdk.h"

#if  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#include "TalkingDataGameAnalytics/android/TDGAJniHelper.h"
#endif

USING_NS_CC;


#if  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C" {

#define  CLASS_NAME "com/fate/TalkingDataGASdkJni"

static void TalkingDataGASdkJni_init()
{
    JniMethodInfo minfo;

    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "getInstance", "()Ljava/lang/Object;")) {
        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

        if(jobj) {
            if (JniHelper::getMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
                minfo.env->CallVoidMethod(jobj, minfo.methodID);
            }
        }
    }
}

}
#endif


TalkingDataGameAnalyticsSdk::TalkingDataGameAnalyticsSdk()
: _account(nullptr)
{
    
}

static TalkingDataGameAnalyticsSdk *instance = nullptr;
TalkingDataGameAnalyticsSdk *TalkingDataGameAnalyticsSdk::getInstance()
{
    if(instance == nullptr) {
        instance = new TalkingDataGameAnalyticsSdk();
    }
    return instance;
}

void TalkingDataGameAnalyticsSdk::init()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    TDCCTalkingDataGA::onStart("59EC3DE05BB0234EA444193F4B9E0E4B", "IosDevelop");
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    TDGAJniHelper::setJavaVM(JniHelper::getJavaVM());
    TalkingDataGASdkJni_init();
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

