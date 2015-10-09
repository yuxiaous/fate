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
    static int getSignatureCode();
    static int getSimOperator();
    
    static bool isDebugMode();
    static bool isReleaseMode();
    
#ifndef SKIP_BY_AUTO_BINDINGS
    typedef std::function<const char* (const char*, const char*)> ConfigGetter;
    static ConfigGetter _configGetter;
    static void setConfigGetter(const ConfigGetter &getter);
    static const ConfigGetter &getConfigGetter();
    
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
