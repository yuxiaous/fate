//
//  AppStoreSdk.h
//  fate
//
//  Created by yuxiao on 15/7/30.
//
//

#ifndef __fate__AppStoreSdk__
#define __fate__AppStoreSdk__

#include <stdio.h>
#include "Sdk.h"

class AppStoreSdk : public Sdk, public SdkChargeProtocol
{
public:
    AppStoreSdk();
    static AppStoreSdk *getInstance();
    
    virtual void init() override;
    virtual void charge(const std::string &order, const std::string &identifier) override;
};

#endif /* defined(__fate__AppStoreSdk__) */
