#include "MixSdk.h"


static MixSdk *instance = nullptr;

MixSdk::MixSdk()
{
    instance = this;
}

MixSdk *MixSdk::getInstance()
{
    return instance;
}

