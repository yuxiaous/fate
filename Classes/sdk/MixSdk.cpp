#include "MixSdk.h"
#include "GameUtils.h"
#include "AndGame/AndGameSdk.h"
#include "unipay/UniPaySdk.h"
#include "egame/EgameSdk.h"
#include "GameUtils.h"

#ifdef MIX_M4399_RECHARGE
#include "m4399RechargeSDK/M4399RechargeSdk.h"
#endif

#ifdef MIX_COOLPAD_QIKUPAY
#include "coolpad/QiKuPaySdk.h"
#endif

#ifdef MIX_TENCENT_MIDAS
#include "TencentMidas/TencentMidasSdk.h"
#endif

#ifdef MIX_360
#include "360/Qh360Sdk.h"
#endif

MixSdk::MixSdk()
{

}

void MixSdk::activityOnCreate()
{
    cocos2d::log("MixSdk::activityOnCreate");

    AndGameSdk_init();
    EgameSdk_init();

#ifdef MIX_M4399_RECHARGE
    M4399RechargeSdk_init();
#endif

#ifdef MIX_COOLPAD_QIKUPAY
    QiKuPaySdk_init();
#endif

#ifdef MIX_TENCENT_MIDAS
    TencentMidasSdk_init();
#endif

#ifdef MIX_360
    Qh360Sdk_init();
#endif
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
#ifdef MIX_M4399_RECHARGE
    M4399RechargeSdk_destroy();
#endif
#ifdef MIX_360
    Qh360Sdk_destroy();
#endif
}

void MixSdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("MixSdk::charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

    std::vector<std::string> ret;
    GameUtils::split(order, "-", ret);

    int sdk = atoi(ret[1].c_str());
    switch(sdk) {
        case 4: AndGameSdk_charge(order, identifier); break;
        case 5: UniPaySdk_charge(order, identifier); break;
        case 6: EgameSdk_charge(order, identifier); break;
#ifdef MIX_M4399_RECHARGE
        case 11: M4399RechargeSdk_charge2(order, identifier); break;
#endif
#ifdef MIX_COOLPAD_QIKUPAY
        case 10: QiKuPaySdk_pay(order, identifier); break;
#endif
#ifdef MIX_TENCENT_MIDAS
        case 8: TencentMidasSdk_pay(order, identifier); break;
#endif
#ifdef MIX_360
        case 7: Qh360Sdk_charge(order, identifier); break;
#endif
    }
}

void MixSdk::sdkCommand(const std::string &clazz, const std::string &method, const std::string &param)
{
    cocos2d::log("MixSdk::sdkCommand %s %s %s", clazz.c_str(), method.c_str(), param.c_str());

#ifdef MIX_360
    if(clazz == "Qh360"){
        if(method == "exit") {
            Qh360Sdk_quit();
        }
    }
#endif
}

