//
//  YMTXExternalManager.m
//
//
//  Created by ymtx2 on 14-8-27.
//
//

#import "YMTXExternalManager.h"
@interface YMTXExternalManager()
{
    
}
@end

@implementation YMTXExternalManager
+(void)pauseBackgroundMusic
{
#if defined TLCOCOS2D_X
    [[SimpleAudioEngine sharedEngine] pauseBackgroundMusic];
#elif defined  TLUNITY3D
    
#endif
    
}

+(void)resumeBackgroundMusic
{
#if defined TLCOCOS2D_X
    [[SimpleAudioEngine sharedEngine] resumeBackgroundMusic];
#elif defined  TLUNITY3D

#endif
}

+(void)pauseGame
{
#if defined TLCOCOS2D_X
    cocos2d::CCDirector::sharedDirector()->pause();
    cocos2d::CCDirector::sharedDirector()->stopAnimation();
#elif defined  TLUNITY3D
    UnityPause(true);
#endif
    [self pauseBackgroundMusic];
}

+(void)resumeGame
{
#if defined TLCOCOS2D_X
    cocos2d::CCDirector::sharedDirector()->resume();
    cocos2d::CCDirector::sharedDirector()->startAnimation();
#elif defined  TLUNITY3D
    UnityPause(false);
    _didResignActive = NO;
#endif
    [self resumeBackgroundMusic];
}
@end
