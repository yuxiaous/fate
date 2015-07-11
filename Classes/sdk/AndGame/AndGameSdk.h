#ifndef __AndGameSdk__
#define __AndGameSdk__

#include "Sdk.h"

class AndGameSdk : public Sdk, public SdkChargeProtocol
{
public:
    AndGameSdk();
    static AndGameSdk *getInstance();

    virtual void init();
    virtual void charge(const std::string &order, const std::string &identifier) override;

    static bool isMusicEnabled();
};

#endif /* defined(__AndGameSdk__) */