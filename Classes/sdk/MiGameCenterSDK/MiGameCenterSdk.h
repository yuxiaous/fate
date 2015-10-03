#ifndef __MiGameCenterSdk__
#define __MiGameCenterSdk__

#include "Sdk.h"
#include "cocos2d.h"


class MiGameCenterSdk : public Sdk, public SdkChargeProtocol
{
public:
    virtual void charge(const std::string &order, const std::string &identifier) override;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
#endif
};

#endif /* defined(__MiGameCenterSdk__) */