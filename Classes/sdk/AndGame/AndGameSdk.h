#ifndef __AndGameSdk__
#define __AndGameSdk__

#include "Sdk.h"
#include "cocos2d.h"

class AndGameSdk : public cocos2d::Ref, public Sdk, public SdkChargeProtocol
{
public:
    AndGameSdk();
    static AndGameSdk *getInstance();

    virtual void init() override;
    virtual void update(float dt) override;

    // SdkChargeProtocol
    virtual void charge(const std::string &order, const std::string &identifier) override;

    static bool isMusicEnabled();

private:
};

#endif /* defined(__AndGameSdk__) */