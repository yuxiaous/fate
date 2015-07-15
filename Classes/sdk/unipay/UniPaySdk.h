#ifndef __UniPaySdk__
#define __UniPaySdk__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"


class UniPaySdk : public Sdk, public SdkChargeProtocol
{
public:
    UniPaySdk();
    static UniPaySdk *getInstance();

//    virtual void activityOnCreate() override;

    virtual void init() override;
    virtual void charge(const std::string &order, const std::string &identifier) override;
};

#endif /* defined(__UniPaySdk__) */