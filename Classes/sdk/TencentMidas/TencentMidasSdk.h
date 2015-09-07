#ifndef __TencentMidasSdk__
#define __TencentMidasSdk__

#include "Sdk.h"
#include "cocos2d.h"

class TencentMidasSdk : public Sdk, public SdkAccountProtocol, public SdkChargeProtocol
{
public:
    TencentMidasSdk();
    static TencentMidasSdk *getInstance();

//    virtual void init() override;
//    virtual void update(float dt) override;
//    virtual void sdkCommand(const std::string &clazz, const std::string &method, const std::string &param) override;
//
//    // SdkAccountProtocol
//    virtual void login() override;
//
//    // SdkChargeProtocol
//    virtual void charge(const std::string &order, const std::string &identifier) override;


//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//public:
//    virtual void activityOnCreate() override;
//    virtual void activityOnDestroy() override;
//#endif
};

#endif /* defined(__TencentMidasSdk__) */
