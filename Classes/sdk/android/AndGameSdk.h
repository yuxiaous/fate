#ifndef __AndGameSdk__
#define __AndGameSdk__

#include "Sdk.h"

class AndGameSdk : public Sdk
{
public:
    virtual void init();


    static bool isMusicEnabled();
};

#endif /* defined(__AndGameSdk__) */