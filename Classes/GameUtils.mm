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


std::string GameUtils::getUdidWithIos()
{
    NSString *openUdid = [OpenUDID value];
    return [openUdid UTF8String];
}
