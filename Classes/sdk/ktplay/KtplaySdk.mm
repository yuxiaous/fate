//
//  KtplaySdk.mm
//  fate
//
//  Created by yuxiao on 15/7/8.
//
//

#include "KtplaySdk.h"
#import "KTPlay.h"


void KtplaySdk::initWithIos(const char *appKey, const char *appSecret)
{
    [KTPlay startWithAppKey:[NSString stringWithUTF8String:appKey]
                  appSecret:[NSString stringWithUTF8String:appSecret]];
}