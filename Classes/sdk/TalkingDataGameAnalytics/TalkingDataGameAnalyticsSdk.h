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

class TalkingDataGameAnalyticsSdk : public Sdk, public AccountProtocol
{
public:
    TalkingDataGameAnalyticsSdk();
    static TalkingDataGameAnalyticsSdk *getInstance();
    
    virtual void init();
    
    virtual void setAccount(const char* accountId);
    virtual void setAccountName(const char* accountName);
    virtual void setAccountType(AccountProtocol::AccountType accountType);
    virtual void setLevel(int level);
    virtual void setGender(AccountProtocol::Gender gender);
    virtual void setAge(int age);
    virtual void setGameServer(const char* gameServer);
    
private:
    TDCCAccount* _account;
};

#endif /* defined(__fate__TalkingDataGameAnalyticsSdk__) */
