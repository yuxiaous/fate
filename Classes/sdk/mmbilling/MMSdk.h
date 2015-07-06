#ifndef __MMSdk__
#define __MMSdk__

#include <stdio.h>
#include "Sdk.h"


class MMSdk : public Sdk, public SdkChargeProtocol
{
public:
    static MMSdk *getInstance();

    virtual void activityOnCreate() override;

    virtual void init() override;
    virtual void charge(const std::string &order, const std::string &identifier) override;
};

#endif /* defined(__MMSdk__) */
