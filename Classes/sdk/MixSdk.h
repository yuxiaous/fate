#ifndef __MixSdk__
#define __MixSdk__

#include <stdio.h>
#include "Sdk.h"


class MixSdk : public Sdk, public SdkChargeProtocol
{
public:
    MixSdk();

    virtual void charge(const std::string &order, const std::string &key) override;
    virtual void sdkCommand(const std::string &clazz, const std::string &method, const std::string &param) override;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
    virtual void activityOnPause() override;
    virtual void activityOnResume() override;
#endif

private:
    enum SimType {
        CMCC = 1,
        UNICOM = 2,
        TELECOM = 3
    };
    int _simType;
};

#endif /* defined(__MixSdk__) */