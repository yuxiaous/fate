#ifndef __UgpSdk__
#define __UgpSdk__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"


class UgpSdk : public Sdk, public SdkChargeProtocol
{
public:
    virtual void charge(const std::string &order, const std::string &identifier) override;
    virtual void sdkCommand(const std::string &clazz, const std::string &method, const std::string &param) override;

    static void exit();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
    virtual void activityOnPause() override;
    virtual void activityOnResume() override;
    virtual void activityOnDestroy() override;
	virtual void activityOnStart() override;
	virtual void activityOnRestart() override;
	virtual void activityOnStop() override;
	virtual void activityOnNewIntent(void *intent) override;
#endif
};

#endif /* defined(__UgpSdk__) */

