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

class TalkingDataGameAnalyticsSdk : public Sdk, public SdkAccountProtocol, public SdkChargeProtocol
{
public:
    TalkingDataGameAnalyticsSdk();
    static TalkingDataGameAnalyticsSdk *getInstance();
    
    virtual void init();
    
    // SdkAccountProtocol
    virtual void setAccount(const char* accountId) override;
    virtual void setAccountName(const char* accountName) override;
    virtual void setAccountType(SdkAccountProtocol::AccountType accountType) override;
    virtual void setLevel(int level) override;
    virtual void setGender(SdkAccountProtocol::Gender gender) override;
    virtual void setAge(int age) override;
    virtual void setGameServer(const char* gameServer) override;
    
    // SdkChargeProtocol
    virtual void charge(const std::string &order, const std::string &identifier) override;
    virtual void onChargeResult(int result, const std::string &order) override;
    virtual void onPurchase(const char* item, int number, double price) override;
    virtual void onUse(const char* item, int number) override;
    
private:
    TDCCAccount* _account;
};

#endif /* defined(__fate__TalkingDataGameAnalyticsSdk__) */
