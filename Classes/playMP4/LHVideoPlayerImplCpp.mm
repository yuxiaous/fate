//
//  LHVideoPlayerImplCpp.cpp
//  VideoDemo
//
//  Created by LiuYanghui on 14-5-5.
//
//

#include "LHVideoPlayerImplCpp.h"
#import "LHVideoPlayerImpl.h"

void LHVideoPlayerImplCpp::playMP4WithName(const char* name, cocos2d::Rect frameRect)
{
    frameRect.origin =frameRect.origin * .5;
    frameRect.size =frameRect.size * .5;
    [LHVideoPlayerImpl playMP4WithName:[NSString stringWithUTF8String:name] VideoFrame:CGRectMake(frameRect.origin.x, frameRect.origin.y, frameRect.size.width, frameRect.size.height)];
}

void LHVideoPlayerImplCpp::setSkipTitle(const char* title)
{
    [LHVideoPlayerImpl setSkipTitle:[NSString stringWithUTF8String:title]];
}

bool LHVideoPlayerImplCpp::getFinishState(){
    
    return [LHVideoPlayerImpl getFinishState];
}