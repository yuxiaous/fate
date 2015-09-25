#ifndef __MMSdk__
#define __MMSdk__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"


class MMSdk : public Sdk, public SdkChargeProtocol
{
public:
    MMSdk();
    static MMSdk *getInstance();

    virtual void update(float dt) override;

    virtual void activityOnCreate() override;

    // SdkChargeProtocol
    virtual void charge(const std::string &order, const std::string &key) override;
};

#endif /* defined(__MMSdk__) */
