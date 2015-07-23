#ifndef __EgameSdk__
#define __EgameSdk__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"

class EgameSdk : public Sdk, public SdkChargeProtocol
{
public:
    EgameSdk();
    static EgameSdk *getInstance();
    virtual void update(float dt) override;

    virtual void charge(const std::string &order, const std::string &identifier) override;

    void moreGame();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate();
#endif
};

#endif /* defined(__EgameSdk__) */

