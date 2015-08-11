//
//  BaitongSdk.h
//  fate
//
//  Created by yuxiao on 15/8/11.
//
//

#ifndef __fate__BaitongSdk__
#define __fate__BaitongSdk__

#include <stdio.h>
#include "Sdk.h"

class BaitongSdk : public Sdk
{
public:
    BaitongSdk();
    static BaitongSdk *getInstance();
    
    virtual void init() override;
};

#endif /* defined(__fate__BaitongSdk__) */
