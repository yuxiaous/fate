//
//  SdkManager.h
//  crows
//
//  Created by yuxiao on 15/4/7.
//
//

#ifndef __crows__SdkManager__
#define __crows__SdkManager__

#include <stdio.h>

class Sdk;

class SdkManager
{
public:
    static void addSdk(Sdk *sdk);
    static void removeSdk(Sdk *sdk);
    
    static void init();
    
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    static void setAppController(void *ac);
    static void setViewController(void *vc);
    static void setWindow(void *win);
    
    static void applicationDidFinishLaunching();
    static void applicationWillResignActive(void *iosUIApplication);
    static void applicationDidBecomeActive(void *iosUIApplication);
    static void applicationDidEnterBackground(void *iosUIApplication);
    static void applicationWillEnterForeground(void *iosUIApplication);
    static void applicationWillTerminate(void *iosUIApplication);
    static void applicationDidRegisterForRemoteNotificationsWithDeviceToken(void *iosNSData);
    static void applicationDidReceiveRemoteNotification(void *iosNSDictionary);
    static bool applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString);
#endif
};

#endif /* defined(__crows__SdkManager__) */
