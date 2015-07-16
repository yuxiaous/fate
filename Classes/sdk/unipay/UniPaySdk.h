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

    virtual void init() override;
    virtual void charge(const std::string &order, const std::string &identifier) override;

    void moreGame();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnPause() override;
    virtual void activityOnResume() override;
#endif
};

#endif /* defined(__UniPaySdk__) */