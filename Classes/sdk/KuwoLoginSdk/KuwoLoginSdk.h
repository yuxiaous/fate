#ifndef __KuwoLoginSdk__
#define __KuwoLoginSdk__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"


class KuwoLoginSdk : public Sdk
{
public:

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
//    virtual void activityOnPause() override;
//    virtual void activityOnResume() override;
#endif
};

#endif /* defined(__KuwoLoginSdk__) */