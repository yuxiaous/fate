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
    return 1
#elif defined(CHANNEL_CMCC_AND)
    return 2
#elif defined(CHANNEL_CMCC_MM)
    return 3
#endif
    
    return 0;
}