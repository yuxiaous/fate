//
//  GameUtils.m
//  fate
//
//  Created by yuxiao on 15/7/20.
//
//

#import <Foundation/Foundation.h>
#include "GameUtils.h"

#ifdef SDK_TALKING_DATA_GA
#include "TalkingData.h"
#else
#import "OpenUDID.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
std::string GameUtils::getUdidWithIos()
{
#ifdef SDK_TALKING_DATA_GA
    return TDCCTalkingDataGA::getDeviceId();
#else
    NSString *openUdid = [OpenUDID value];
    return [openUdid UTF8String];
    
#endif
}
#endif
