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


@interface WeRecSdkDelegate : NSObject <WeRecManagerDelegate>
+(WeRecSdkDelegate *)getInstance;
@end

@implementation WeRecSdkDelegate

+(WeRecSdkDelegate *)getInstance
{
    static WeRecSdkDelegate *instance = NULL;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[WeRecSdkDelegate alloc] init];
    });
    
    return instance;
}

-(void)entryWeRecUI
{
    //暂停游戏
//    cocos2d::CCDirector::sharedDirector()->pause();
//    cocos2d::CCDirector::sharedDirector()->stopAnimation();
}

-(void)exitWeRecUI
{
    //恢复游戏
//    cocos2d::CCDirector::sharedDirector()->resume();
//    cocos2d::CCDirector::sharedDirector()->startAnimation();
}

-(void)updateRecordTimeCount:(NSInteger)timeCount
{
    
}

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

void WeRecSdk::init()
{
    UIViewController *vc = (UIViewController*)SdkManager::viewController;
    
    [WeRecManager registerApp:@"10153"];
    [WeRecManager initWithDelegate:[WeRecSdkDelegate getInstance] andParentViewController:vc];
}


bool WeRecSdk::applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString)
{
    NSURL *url = (NSURL *)iosNSURL;
    
    return [[WeRecShareManager shareManager] handleOpenURL:url];
}

