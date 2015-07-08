//
//  KtplaySdk.h
//  fate
//
//  Created by yuxiao on 15/7/8.
//
//

#ifndef __fate__KtplaySdk__
#define __fate__KtplaySdk__

#include <stdio.h>
#include "Sdk.h"

class KtplaySdk : public Sdk, public SdkAccountProtocol
{
public:
    static KtplaySdk *getInstance();
    
    virtual void init() override;
    
    virtual void login() override;
    
    void show();
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
private: void initWithIos();
#endif
};

#endif /* defined(__fate__KtplaySdk__) */
