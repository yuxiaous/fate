//
//  YMTXSdk.h
//  crows
//
//  Created by yuxiao on 15/4/7.
//
//

#ifndef __crows__YMTXSdk__
#define __crows__YMTXSdk__

#include <stdio.h>
#include "Sdk.h"

class YMTXSdk : public Sdk
{
public:
    YMTXSdk();
    static YMTXSdk *getInstance();
    
    virtual void init();
    
    virtual void applicationDidFinishLaunching();
};

#endif /* defined(__crows__YMTXSdk__) */
