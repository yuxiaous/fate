#ifndef __UniPaySdk__
#define __UniPaySdk__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"


extern "C" {
    void UniPaySdk_init();
    void UniPaySdk_charge(const std::string &order, const std::string &identifier);
    void UniPaySdk_onPause();
    void UniPaySdk_onResume();
    void UniPaySdk_moreGame();
}

class UniPaySdk : public Sdk, public SdkChargeProtocol
{
public:
    UniPaySdk();
    static UniPaySdk *getInstance();

    virtual void init() override;
    virtual void charge(const std::string &order, const std::string &key) override;

    static void moreGame();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
    virtual void activityOnPause() override;
    virtual void activityOnResume() override;
#endif
};

#endif /* defined(__UniPaySdk__) */