//
//  TalkingDataGameAnalyticsSdk.h
//  fate
//
//  Created by yuxiao on 15/6/26.
//
//

#ifndef __fate__TalkingDataGameAnalyticsSdk__
#define __fate__TalkingDataGameAnalyticsSdk__

#include <stdio.h>
#include "Sdk.h"
#include "TalkingData.h"

class TalkingDataGameAnalyticsSdk : public Sdk, public SdkChargeProtocol
{
public:
    TalkingDataGameAnalyticsSdk();
    static TalkingDataGameAnalyticsSdk *getInstance();
    
    virtual void init() override;
    virtual void sdkCommand(const std::string &clazz, const std::string &method, const std::string &param) override;
    
    // TDCCAccount
    void setAccount(const char* accountId);
    void setAccountName(const char* accountName);
    void setAccountType(int accountType);
    void setLevel(int level);
    void setGender(int gender);
    void setAge(int age);
    void setGameServer(const char* gameServer);
    
    // TDCCVirtualCurrency
    void onChargeRequest(const char* orderId, const char* iapId, double currencyAmount, const char* currencyType, double virtualCurrencyAmount, const char* paymentType);
    void onChargeSuccess(const char* orderId);
    void onReward(double currencyAmount, const char* reason);
    
    // TDCCItem
    void onPurchase(const char* item, int number, double price);
    void onUse(const char* item, int number);
    
    // TDCCMission
    void onBegin(const char* missionId);
    void onCompleted(const char* missionId);
    void onFailed(const char* missionId, const char* failedCause);
    
private:
    TDCCAccount* _account;
};

#endif /* defined(__fate__TalkingDataGameAnalyticsSdk__) */
