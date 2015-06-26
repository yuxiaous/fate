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

class TalkingDataGameAnalyticsSdk : public Sdk, public AccountProtocol
{
public:
    static TalkingDataGameAnalyticsSdk *getInstance();
    
    virtual void init();
};

#endif /* defined(__fate__TalkingDataGameAnalyticsSdk__) */
