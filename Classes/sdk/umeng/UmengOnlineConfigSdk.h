#ifndef __UmengOnlineConfigSdk__
#define __UmengOnlineConfigSdk__

#include <stdio.h>
#include "Sdk.h"


class UmengOnlineConfigSdk : public Sdk
{
public:
    virtual void init() override;
    std::string getConfigParams(const std::string &key);

    static bool isFree() { return _free; }

private:
    static bool _free;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    virtual void activityOnCreate() override;
//    virtual void activityOnPause() override;
//    virtual void activityOnResume() override;
//    virtual void activityOnDestroy() override;
private:
    void *_jinstance;
#endif
};

#endif /* defined(__UmengOnlineConfigSdk__) */
