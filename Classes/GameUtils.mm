//
//  GameUtils.m
//  fate
//
//  Created by yuxiao on 15/7/20.
//
//

#import <Foundation/Foundation.h>
#import "OpenUDID.h"
#include "GameUtils.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
std::string GameUtils::getUdidWithIos()
{
    NSString *openUdid = [OpenUDID value];
    return [openUdid UTF8String];
}
#endif
