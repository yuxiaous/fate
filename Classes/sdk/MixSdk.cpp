#include "MixSdk.h"
#include "GameUtils.h"
#include "AndGame/AndGameSdk.h"

extern "C" {
    extern void AndGameSdk_init();
    extern void AndGameSdk_charge(const std::string &order, const std::string &identifier);
    extern void UniPaySdk_charge(const std::string &order, const std::string &identifier);
    extern void EgameSdk_init();
    extern void EgameSdk_charge(const std::string &order, const std::string &identifier);
}

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

}

void MixSdk::activityOnResume()
{

}

void MixSdk::activityOnDestroy()
{

}

void MixSdk::charge(const std::string &order, const std::string &identifier)
{
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

