#include "MixSdk.h"
#include "GameUtils.h"


MixSdk::MixSdk()
{

}

void MixSdk::activityOnCreate()
{
    int sim = GameUtils::getSimOperator();
    cocos2d::log("MixSdk::activityOnCreate sim: %d", sim);
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
