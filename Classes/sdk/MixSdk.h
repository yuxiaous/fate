#ifndef __MixSdk__
#define __MixSdk__

#include <stdio.h>
#include "Sdk.h"


class MixSdk : public Sdk
{
public:
    MixSdk();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
    virtual void activityOnPause() override;
    virtual void activityOnResume() override;
    virtual void activityOnDestroy() override;
#endif
};

#endif /* defined(__MixSdk__) */