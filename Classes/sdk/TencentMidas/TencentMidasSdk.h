#ifndef __TencentMidasSdk__
#define __TencentMidasSdk__

#include "Sdk.h"
#include "cocos2d.h"

extern "C" {
    void TencentMidasSdk_init();
    void TencentMidasSdk_pay(const std::string &order, const std::string &identifier);
}

class TencentMidasSdk : public Sdk, public SdkChargeProtocol
{
public:
//    virtual void init() override;
    virtual void charge(const std::string &order, const std::string &identifier) override;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
//    virtual void activityOnDestroy() override;
#endif
};

#endif /* defined(__TencentMidasSdk__) */
