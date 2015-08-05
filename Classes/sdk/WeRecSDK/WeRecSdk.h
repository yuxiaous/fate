//
//  WeRecSdk.h
//  fate
//
//  Created by yuxiao on 15/8/5.
//
//

#ifndef __fate__WeRecSdk__
#define __fate__WeRecSdk__

#include <stdio.h>
#include "Sdk.h"

class WeRecSdk : public Sdk
{
public:
    WeRecSdk();
    static WeRecSdk *getInstance();
    
    virtual void init() override;
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    virtual bool applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString) override;
#endif
};

#endif /* defined(__fate__WeRecSdk__) */
