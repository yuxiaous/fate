#ifndef __AndGameSdk__
#define __AndGameSdk__

#include "Sdk.h"

class AndGameSdk : public Sdk, public BuyProtocol
{
public:
    static AndGameSdk *getInstance();

    virtual void init();
    virtual void buy(const std::string &param);

    static bool isMusicEnabled();
};

#endif /* defined(__AndGameSdk__) */