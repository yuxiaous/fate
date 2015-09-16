#include "MixSdk.h"
#include "GameUtils.h"
#include "AndGame/AndGameSdk.h"

extern "C" {
    extern void AndGameSdk_init();
    extern void AndGameSdk_charge(const std::string &order, const std::string &identifier);
}

MixSdk::MixSdk()
: _simType(0)
{

}

void MixSdk::activityOnCreate()
{
    cocos2d::log("MixSdk::activityOnCreate");

    _simType = GameUtils::getSimOperator();
    switch(_simType) {
        case CMCC: // 移动
            cocos2d::log("移动");
            AndGameSdk_init();
            break;
        case UNICOM: // 联通
            cocos2d::log("联通");
            break;
        case TELECOM: // 电信
            cocos2d::log("电信");
            break;
        default:
            break;
    }
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
                break;

            case TELECOM:
                break;
        }
}

void MixSdk::sdkCommand(const std::string &clazz, const std::string &method, const std::string &param)
{
    cocos2d::log("MixSdk::sdkCommand %s %s %s", clazz.c_str(), method.c_str(), param.c_str());
}

