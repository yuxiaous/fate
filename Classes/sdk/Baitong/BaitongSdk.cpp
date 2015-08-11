//
//  BaitongSdk.cpp
//  fate
//
//  Created by yuxiao on 15/8/11.
//
//

#include "BaitongSdk.h"


static BaitongSdk *instance = nullptr;

BaitongSdk::BaitongSdk()
{
    instance = this;
}

BaitongSdk *BaitongSdk::getInstance()
{
    return instance;
}

void BaitongSdk::init()
{
    
}

