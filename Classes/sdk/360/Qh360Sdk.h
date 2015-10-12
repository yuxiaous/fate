#ifndef __Qh360Sdk__
#define __Qh360Sdk__

#include "Sdk.h"
#include "cocos2d.h"

extern "C" {
    void Qh360Sdk_init();
    void Qh360Sdk_destroy();
    void Qh360Sdk_login();
    void Qh360Sdk_pay();
}

class Qh360Sdk : public Sdk, public SdkAccountProtocol, public SdkChargeProtocol
{
public:
    virtual void login() override;
    virtual void charge(const std::string &order, const std::string &identifier) override;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
    virtual void activityOnDestroy() override;
#endif
};

#endif /* defined(__Qh360Sdk__) */
