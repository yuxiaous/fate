#ifndef __MixSdk__
#define __MixSdk__

#include <stdio.h>
#include "Sdk.h"


class MixSdk : public Sdk
{
public:
    MixSdk();
    static MixSdk *getInstance();
};

#endif /* defined(__MixSdk__) */