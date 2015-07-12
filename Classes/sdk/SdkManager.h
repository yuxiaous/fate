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
#ifndef SKIP_BY_AUTO_BINDINGS
public:
    static void addSdk(Sdk *sdk);
    static void removeSdk(Sdk *sdk);
    static void init();
#endif

public:
    static void sdkCommond(const std::string &cmd);
    
    // ChargeProtocol
    static void charge(const std::string &order, const std::string &identifier);
    static void setChargeCallback(const std::function<void(char *param)> &callback);
    static void onChargeResult(int result, const std::string &order);
    static void onPurchase(const char* item, int number, double price);
    static void onUse(const char* item, int number);
    
    // AccountProtocol
    static void login();
    static void setAccount(const char* accountId);
    static void setAccountName(const char* accountName);
    static void setAccountType(int accountType);
    static void setLevel(int level);
    static void setGender(int gender);
    static void setAge(int age);
    static void setGameServer(const char* gameServer);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
public:
    static void *appController;
    static void *viewController;
    static void *window;
    
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) && !defined(SKIP_BY_AUTO_BINDINGS)
public:
    static void *appActivity;

    static void activityOnCreate();
    static void activityOnPause();
    static void activityOnResume();
#endif
};

#endif /* defined(__crows__SdkManager__) */
