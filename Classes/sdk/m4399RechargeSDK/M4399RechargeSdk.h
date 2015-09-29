#ifndef __M4399RechargeSdk__
#define __M4399RechargeSdk__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"


extern "C" {
    void M4399RechargeSdk_init();
    void M4399RechargeSdk_charge(const std::string &order, const std::string &name, int cost);
    void M4399RechargeSdk_charge2(const std::string &order, const std::string &identifier);
    void M4399RechargeSdk_destroy();
}


class M4399RechargeSdk : public Sdk, public SdkChargeProtocol
{
public:
    virtual void charge(const std::string &order, const std::string &identifier) override;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
    virtual void activityOnDestroy() override;
#endif
};

#endif /* defined(__M4399RechargeSdk__) */
