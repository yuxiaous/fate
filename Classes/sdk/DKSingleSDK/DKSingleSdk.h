#ifndef __DKSingleSDK__
#define __DKSingleSDK__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"

class DKSingleSdk : public Sdk
{
public:
    virtual void init() override;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
//    virtual void activityOnPause() override;
//    virtual void activityOnResume() override;
#endif
};

#endif /* defined(__DKSingleSDK__) */