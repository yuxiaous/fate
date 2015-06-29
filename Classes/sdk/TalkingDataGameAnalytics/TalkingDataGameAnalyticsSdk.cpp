//
//  TalkingDataGameAnalyticsSdk.cpp
//  fate
//
//  Created by yuxiao on 15/6/26.
//
//

#include "TalkingDataGameAnalyticsSdk.h"

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
    TDCCTalkingDataGA::onStart("59EC3DE05BB0234EA444193F4B9E0E4B", "Develop");
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
