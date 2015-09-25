#include "MixSdk.h"
#include "GameUtils.h"
#include "AndGame/AndGameSdk.h"
#include "unipay/UniPaySdk.h"
#include "egame/EgameSdk.h"

MixSdk::MixSdk()
: _simType(0)
{

}

void MixSdk::activityOnCreate()
{
    cocos2d::log("MixSdk::activityOnCreate");

    _simType = GameUtils::getSimOperator();

    AndGameSdk_init();
    EgameSdk_init();
}

void MixSdk::activityOnPause()
{
    UniPaySdk_onPause();
}

void MixSdk::activityOnResume()
{
    UniPaySdk_onResume();
}

void MixSdk::charge(const std::string &order, const std::string &key)
{
    std::string identifier = getChargeIdentifier(key);
    cocos2d::log("MixSdk::charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

    switch(_simType) {
        case CMCC:
            AndGameSdk_charge(order, identifier);
            break;

        case UNICOM:
            UniPaySdk_charge(order, identifier);
            break;

        case TELECOM:
            EgameSdk_charge(order, identifier);
            break;
    }
}

void MixSdk::sdkCommand(const std::string &clazz, const std::string &method, const std::string &param)
{
    cocos2d::log("MixSdk::sdkCommand %s %s %s", clazz.c_str(), method.c_str(), param.c_str());
}

