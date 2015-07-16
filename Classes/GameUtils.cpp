//
//  GameUtils.cpp
//  fate
//
//  Created by yuxiao on 15/7/1.
//
//

#include "GameUtils.h"

int GameUtils::getChannelId()
{
#if defined(CHANNEL_APPSTORE)
    return 1;
#elif defined(CHANNEL_CMCC_AND)
    return 2;
#elif defined(CHANNEL_CMCC_MM)
    return 3;
#elif defined(CHANNEL_CT) //电信
    return 4;
#elif defined(CHANNEL_UNICOM) //联通
    return 5;
#endif
    
    return 0;
}
