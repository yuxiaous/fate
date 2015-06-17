//
//  YMTXExternalManager.h
//  ParkourCPP
//
//  Created by ymtx2 on 14-8-27.
//
//

#define TLCOCOS2D_X   // cocos2d 项目宏
//#define TLUNITY3D     // unity3d 项目宏
#if defined TLCOCOS2D_X
    #include "cocos2d.h"
    #import "audio/ios/SimpleAudioEngine_objc.h"
#elif defined  TLUNITY3D
    extern void		UnityPause(bool pause);
    extern BOOL	    _didResignActive;
#endif

#import <Foundation/Foundation.h>
@interface YMTXExternalManager : NSObject
/*
 pauseBackgroundMusic:
 暂停声音
 */
+(void)pauseBackgroundMusic;

/*
 resumeBackgroundMusic:
 恢复声音
 */
+(void)resumeBackgroundMusic;

/*
 pauseGame:
 暂停游戏
 */
+(void)pauseGame;


/*
 pauseGame:
 恢复游戏
 */
+(void)resumeGame;
@end
