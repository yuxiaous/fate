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
#include "cocos2d.h"

class GameUtils
{
public:
    static int getChannelId();
    static std::string getUdid();
    static bool isLegalCopy();
    static int getSimOperator();
    
#ifndef SKIP_BY_AUTO_BINDINGS
    static void split(const std::string &s, const std::string &delim, std::vector<std::string> &ret);
#endif
    
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    static std::string getUdidWithIos();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static std::string getUdidWithAndroid();
#endif
};

#endif /* defined(__fate__GameUtils__) */
