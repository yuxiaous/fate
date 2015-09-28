//
//  DeveloperSdk.h
//  fate
//
//  Created by yuxiao on 15/6/26.
//
//

#ifndef __fate__DeveloperSdk__
#define __fate__DeveloperSdk__

#include <stdio.h>
#include "Sdk.h"


class DeveloperSdk : public Sdk, public SdkChargeProtocol
{
public:
    DeveloperSdk();
    static DeveloperSdk *getInstance();
    
    // SdkChargeProtocol
    virtual void charge(const std::string &order, const std::string &identifier) override;
};

#endif /* defined(__fate__DeveloperSdk__) */
