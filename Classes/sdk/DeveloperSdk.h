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


class DeveloperSdk : public Sdk, public BuyProtocol
{
public:
    virtual void buy(const std::string &param);
};

#endif /* defined(__fate__DeveloperSdk__) */
