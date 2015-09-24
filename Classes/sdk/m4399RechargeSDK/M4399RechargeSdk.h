#ifndef __M4399RechargeSdk__
#define __M4399RechargeSdk__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"


class M4399RechargeSdk : public Sdk, public SdkChargeProtocol
{
public:
    virtual void charge(const std::string &order, const std::string &identifier) override;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
//    virtual void activityOnPause() override;
//    virtual void activityOnResume() override;
#endif
};

#endif /* defined(__M4399RechargeSdk__) */