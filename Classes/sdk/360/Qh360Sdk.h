#ifndef __Qh360Sdk__
#define __Qh360Sdk__

#include "Sdk.h"
#include "cocos2d.h"

class Qh360Sdk : public Sdk, public SdkChargeProtocol
{
public:
    Qh360Sdk();
    static Qh360Sdk *getInstance();

    virtual void init() override;
    virtual void update(float dt) override;
    virtual void sdkCommand(const std::string &clazz, const std::string &method, const std::string &param) override;

    // SdkChargeProtocol
    virtual void charge(const std::string &order, const std::string &identifier) override;
};

#endif /* defined(__Qh360Sdk__) */
