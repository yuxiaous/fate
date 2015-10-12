#ifndef __Qh360Sdk__
#define __Qh360Sdk__

#include "Sdk.h"
#include "cocos2d.h"

extern "C" {
    void Qh360Sdk_init();
    void Qh360Sdk_charge(const std::string &order, const std::string &identifier);
    void Qh360Sdk_destroy();
}

class Qh360Sdk : public Sdk, public SdkChargeProtocol
{
public:
    virtual void charge(const std::string &order, const std::string &identifier) override;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
    virtual void activityOnDestroy() override;
#endif
};

#endif /* defined(__Qh360Sdk__) */
