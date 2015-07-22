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
class SdkManagerUpdate;

class SdkManager
{
    friend Sdk;
    friend SdkManagerUpdate;
    
public:
    static void init();
    
    static void setSdkCommandCallback(const std::function<void(char*, char*)> &cb) {_sdkCmdCallback = cb;}
    static void sendSdkCommand(const std::string &name, const std::string &cmd);
    static void recvSdkCommand(const std::string &name, const std::string &cmd);\
    
    // AccountProtocol
    static void login();
    
    // ChargeProtocol
    static void charge(const std::string &order, const std::string &identifier);
    static void setChargeCallback(const std::function<void(char *param)> &callback);
    
private:
    static void addSdk(Sdk *sdk);
    static void removeSdk(Sdk *sdk);
    static void update(float dt);
    static std::function<void(char*, char*)> _sdkCmdCallback;
    
    
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
