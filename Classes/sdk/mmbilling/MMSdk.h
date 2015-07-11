#ifndef __MMSdk__
#define __MMSdk__

#include <stdio.h>
#include "Sdk.h"
#include "cocos2d.h"


class MMSdk : public cocos2d::Ref, public Sdk, public SdkChargeProtocol
{
public:
    MMSdk();
    static MMSdk *getInstance();

    virtual void activityOnCreate() override;

    virtual void init() override;
    virtual void charge(const std::string &order, const std::string &identifier) override;

private:
    void update(float);
};

#endif /* defined(__MMSdk__) */
