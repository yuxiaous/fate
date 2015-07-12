//
//  KtplaySdk.h
//  fate
//
//  Created by yuxiao on 15/7/8.
//
//

#ifndef __fate__KtplaySdk__
#define __fate__KtplaySdk__

#include <stdio.h>
#include "Sdk.h"

class KtplaySdk : public Sdk, public SdkAccountProtocol
{
public:
    KtplaySdk();
    static KtplaySdk *getInstance();
    
    virtual void init() override;
    
    virtual void login() override;
    
    void showKTPlay();
    void showLoginView();
    void showFriendRequestsView();
    void showRedemptionView();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
private: void initWithIos(const char *appKey, const char *appSecret);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
private: void initWithAndroid(const char *appKey, const char *appSecret);
#endif
};

#endif /* defined(__fate__KtplaySdk__) */
