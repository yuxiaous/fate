//
//  YMTXSdk.cpp
//  crows
//
//  Created by yuxiao on 15/4/7.
//
//

#include "YMTXSdk.h"

#import "YMTXRecordManager.h"
#import "YMTXShareManager.h"
#import "AppController.h"


//YMTXSdk *YMTXSdk::getInstance()
//{
//    static YMTXSdk *sdk = nullptr;
//    if(sdk == nullptr) {
//        sdk = new YMTXSdk();
//    }
//    return sdk;
//}


void YMTXSdk::applicationDidFinishLaunching()
{
    UIViewController *viewController = (UIViewController*)_viewController;
    UIWindow *window = (UIWindow*)_window;
    
#if defined __IPHONE_8_0
    //#error （此处是为调整横屏的游戏，如果是竖屏游戏或者XCODE sdk 在6.1以下，注释掉。）因为sdk需要显示竖屏的界面，因此需要在XCODE的Device Orientation 中添加一个Portrait 的方向。添加这个方向后，在XCODE 6.1 编译的软件在ios8.0 以上跑起来的时候。在近入游戏之前是竖屏的话，进入游戏后，界面会被截掉一部分。原因是系统没有主动旋转过来。需要手动旋转。添加如下代码。此代码需要添加在cocos2d::CCApplication::sharedApplication()->run()之前！
    NSDictionary *dic = [[NSBundle mainBundle]infoDictionary];
    NSArray *interfaceOrientations = [dic objectForKey:@"UISupportedInterfaceOrientations"];
    BOOL hasPortrait = NO;
    for(NSString *orientation in interfaceOrientations)
    {
        if ([orientation isEqualToString:@"UIInterfaceOrientationPortrait"]) {
            hasPortrait = YES;
        }
    }
    if (!hasPortrait) {
        /*
         需要添加对竖屏的支持
         然后在viewController 对应的类里添加
         - (NSUInteger) supportedInterfaceOrientations{
         return UIInterfaceOrientationMaskLandscape;
         }
         */
        assert(0);
    }
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0) {
        CGRect frame = window.frame;
        if (frame.size.height > frame.size.width) {
            float temp = frame.size.width;
            frame.size.width = frame.size.height;
            frame.size.height = temp;
            [window setFrame:frame];
            [viewController.view setFrame:frame];
        }
    }
#endif
}

void YMTXSdk::init()
{
    AppController *appController = (AppController*)_appController;
    UIViewController *viewController = (UIViewController*)_viewController;
    
    [YMTXRecordManager registerApp:@"10153"]; //命运之刃(10153)
    [YMTXRecordManager setHomeTitleString:@"命运之刃"];
    [YMTXRecordManager initWithDelegate:appController andParentViewController:viewController];
}
