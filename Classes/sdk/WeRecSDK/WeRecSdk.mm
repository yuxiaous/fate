//
//  WeRecSdk.cpp
//  fate
//
//  Created by yuxiao on 15/8/5.
//
//

#include "WeRecSdk.h"
#import "WeRecManager.h"
#import "WeRecShareManager.h"


@interface WeRecSdkDelegate

@end





static WeRecSdk *instance = nullptr;

WeRecSdk::WeRecSdk()
{
    instance = this;
}

WeRecSdk *WeRecSdk::getInstance()
{
    return instance;
}
