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

class KtplaySdk : public Sdk
{
public:
    static KtplaySdk *getInstance();
    
    virtual void init();
};

#endif /* defined(__fate__KtplaySdk__) */
