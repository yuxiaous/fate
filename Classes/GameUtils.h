//
//  GameUtils.h
//  fate
//
//  Created by yuxiao on 15/7/1.
//
//

#ifndef __fate__GameUtils__
#define __fate__GameUtils__

#include <stdio.h>


class GameUtils
{
public:
    static int getChannelId();
    static const char *getUdid();
    
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    static const char *getUdidWithIos();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static const char *getUdidWithAndroid();
#endif
};

#endif /* defined(__fate__GameUtils__) */
