#include "MixSdk.h"
#include "GameUtils.h"
#include "AndGame/AndGameSdk.h"
#include "unipay/UniPaySdk.h"
#include "egame/EgameSdk.h"

//#ifdef MIX_M4399_RECHARGE
//#include "m4399RechargeSDK/M4399RechargeSdk.h"
//#endif

MixSdk::MixSdk()
{

}

void MixSdk::activityOnCreate()
{
    cocos2d::log("MixSdk::activityOnCreate");

    AndGameSdk_init();
    EgameSdk_init();

//#ifdef MIX_M4399_RECHARGE
//    M4399RechargeSdk_init();
//#endif
}

void MixSdk::activityOnPause()
{
    UniPaySdk_onPause();
}

void MixSdk::activityOnResume()
{
    UniPaySdk_onResume();
}

void MixSdk::activityOnDestroy()
{
//#ifdef MIX_M4399_RECHARGE
//    M4399RechargeSdk_destroy();
//#endif
}

void MixSdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("MixSdk::charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

    int sim = GameUtils::getSimOperator();
    switch(sim) {
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

