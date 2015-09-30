#ifndef __UgpSdk__
#define __UgpSdk__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"


extern "C" {
}

class UgpSdk : public Sdk, public SdkChargeProtocol
{
public:

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
#endif
};

#endif /* defined(__UgpSdk__) */

