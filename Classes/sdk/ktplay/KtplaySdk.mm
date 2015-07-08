//
//  KtplaySdk.mm
//  fate
//
//  Created by yuxiao on 15/7/8.
//
//

#include "KtplaySdk.h"
#import "KTPlay.h"


void KtplaySdk::initWithIos()
{
    [KTPlay startWithAppKey:@"2yipeBu5W7" appSecret:@"ad24d7d5ee7c86f3b266f8066f5549f67a3bae29"];
}