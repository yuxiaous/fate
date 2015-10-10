#ifndef __QiKuPaySdk__
#define __QiKuPaySdk__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"

extern "C" {
    void QiKuPaySdk_init();
    void QiKuPaySdk_pay(const std::string &order, const std::string &identifier);
}

class QiKuPaySdk : public Sdk
{
public:

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
#endif
};

#endif /* defined(__QiKuPaySdk__) */