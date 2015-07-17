//
//  KtplaySdk.cpp
//  fate
//
//  Created by yuxiao on 15/7/8.
//
//

#include "KtplaySdk.h"
#include "ktplay/Include/KTPlayC.h"
#include "ktplay/Include/KTAccountManagerC.h"
#include "ktplay/Include/KTFriendshipC.h"


/*
 * ktplay version 1.6.1
 */

extern "C" {
    
    void dispatchRewards (KTRewardItemC *rewards, int length)
    {
        std::string rewardsStr = "KTPlayRewards";
        
        for ( int i = 0; i < length; i ++) {
            KTRewardItemC *item = &rewards[i];
            
//            if (strcmp(item->typeId, "Gold") == 0) {
//                Game.appendGold( item->value)
//            } else if (strcmp(item->typeId, "Diamond") == 0) {
//                Game.appendGold( item->value)
//            }
            
        }
        
        SdkManager::recvSdkCommand("KTPlay", rewardsStr);
    }
    
    void activityStatusChanged(bool hasNewActivities) {
//        if(hasNewActivities) {
//            Game::showKTTip(); //显示新动态提示
//        } else {
//            Game::hideKTTip(); //隐藏新动态提示
//        }
    }
    
    void availabilityChangedCallback(bool isEnabled){
        //isEnabled 为当前KTPlay实时状态
    }
    
    void deepLinkCallback (const char *linkSchemas){
//        Game::processDeepLink(linkSchemas)
        //linkSchemas内容为"GoToLeaderboard"，游戏接收到此字符串后，跳转到游戏排行版界面
    }
    
    static void showLoginViewCallback(bool isSuccess ,KTUserC * user,KTErrorC *error)
    {
        if (isSuccess) {
            //登录成功
            cocos2d::log("showLoginViewCallback login success");
        } else {
            //登录失败
            cocos2d::log("showLoginViewCallback login fail");
        }
    }
}


static KtplaySdk *instance = nullptr;

KtplaySdk::KtplaySdk()
{
    instance = this;
}

KtplaySdk *KtplaySdk::getInstance()
{
    return instance;
}

void KtplaySdk::init()
{
    cocos2d::log("KtplaySdk::init");

    const char *appKey = "2yipeBu5W7";
    const char *appSecret = "ad24d7d5ee7c86f3b266f8066f5549f67a3bae29";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    initWithIos(appKey, appSecret);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    initWithAndroid(appKey, appSecret);
#endif
    
    // 设置监听者，监听奖励发放事件
    KTPlayC::setDidDispatchRewardsCallback(dispatchRewards);
    // 设置监听者，监听用户新动态
    KTPlayC::setActivityStatusChangedCallback(activityStatusChanged);
    // 设置监听者，监听KTPlay SDK的可用状态变更
    KTPlayC::setAvailabilityChangedCallback(availabilityChangedCallback);

    KTPlayC::showInterstitialNotification();

    // 设置监听者，监听深度链接发放事件
    KTPlayC::setDeepLinkCallback(deepLinkCallback);
}

void KtplaySdk::login()
{
    showLoginView();
}

void KtplaySdk::sdkCommand(const std::string &name, const std::string &cmd)
{
    if(name != "Ktplay") {
        return;
    }
    if(cmd == "showRedemptionView") {
        showRedemptionView();
    }
    else if(cmd == "showKTPlay") {
        showKTPlay();
    }
    else if(cmd == "showFriendRequestsView") {
        showFriendRequestsView();
    }
    else if(cmd == "showLoginView") {
        showLoginView();
    }
}

void KtplaySdk::showKTPlay()
{
    KTPlayC::show();
}

void KtplaySdk::showLoginView()
{
    KTAccountManagerC::showLoginView(false, showLoginViewCallback);
}

void KtplaySdk::showFriendRequestsView()
{
    KTFriendshipC::showFriendRequestsView();
}

void KtplaySdk::showRedemptionView()
{
    KTPlayC::showRedemptionView();
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
USING_NS_CC;

void KtplaySdk::initWithAndroid(const char *appKey, const char *appSecret)
{
    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
        "com/ktplay/open/KTPlay",
        "startWithAppKey",
        "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V")) {

        jobject jactivity = (jobject)SdkManager::appActivity;
        jstring jappKey = minfo.env->NewStringUTF(appKey);
        jstring jappSecret = minfo.env->NewStringUTF(appSecret);

        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jactivity, jappKey, jappSecret);

        minfo.env->DeleteLocalRef(jappKey);
        minfo.env->DeleteLocalRef(jappSecret);
    }
}

void KtplaySdk::activityOnPause()
{
    cocos2d::log("KtplaySdk::activityOnPause");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
        "com/ktplay/open/KTPlay",
        "onPause",
        "(Landroid/content/Context;)V")) {

        jobject jactivity = (jobject)SdkManager::appActivity;
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jactivity);
    }
}

void KtplaySdk::activityOnResume()
{
    cocos2d::log("KtplaySdk::activityOnResume");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
        "com/ktplay/open/KTPlay",
        "onResume",
        "(Landroid/content/Context;)V")) {

        jobject jactivity = (jobject)SdkManager::appActivity;
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jactivity);
    }
}
#endif

