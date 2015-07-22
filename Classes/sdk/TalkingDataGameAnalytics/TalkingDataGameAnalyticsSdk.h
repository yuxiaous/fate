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
    virtual void sdkCommand(const std::string &name, const std::string &cmd) override;
    
    
    // SdkChargeProtocol
    virtual void charge(const std::string &order, const std::string &identifier) override;
    virtual void onChargeResult(int result, const std::string &order) override;
    virtual void onPurchase(const char* item, int number, double price) override;
    virtual void onUse(const char* item, int number) override;
    
    
    virtual void setAccount(const char* accountId);
    virtual void setAccountName(const char* accountName);
    virtual void setAccountType(int accountType);
    virtual void setLevel(int level);
    virtual void setGender(int gender);
    virtual void setAge(int age);
    virtual void setGameServer(const char* gameServer);
    
private:
    TDCCAccount* _account;
};

#endif /* defined(__fate__TalkingDataGameAnalyticsSdk__) */
