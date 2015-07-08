//
//  KtplaySdk.cpp
//  fate
//
//  Created by yuxiao on 15/7/8.
//
//

#include "KtplaySdk.h"
#include "KTPlayC.h"
#include "KTAccountManagerC.h"
#include "KTFriendshipC.h"


/*
 * ktplay version 1.5.3
 */

extern "C" {
    
    void dispatchRewards (KTRewardItemC * rewards, int length)
    {
        KTRewardItemC *item = NULL;
        for ( int i = 0; i < length; i ++) {
//            item = &pRewardArray[i];
//            if (strcmp(item->typeId, "Gold") == 0) {
//                Game.appendGold( item->value)
//            } else if (strcmp(item->typeId, "Diamond") == 0) {
//                Game.appendGold( item->value)
//            }
        }
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
        } else {
            //登录失败
        }
    }
}


KtplaySdk *KtplaySdk::getInstance()
{
    static KtplaySdk *instance = nullptr;
    if(instance == nullptr) {
        instance = new KtplaySdk();
    }
    return instance;
}

void KtplaySdk::init()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    initWithIos();
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

