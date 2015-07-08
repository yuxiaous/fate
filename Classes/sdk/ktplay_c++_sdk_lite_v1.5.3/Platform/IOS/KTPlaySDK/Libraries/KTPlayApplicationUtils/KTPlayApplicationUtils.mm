//
//  KryptaniumApplicationUtils.m
//
//  Created by ktplay on 13-11-25.
//  Copyright (c) 2013年 KTPlay. All rights reserved.
//

#import "KTPlayApplicationUtils.h"


#if !IS_PLATFORM_UNITY
#ifdef __cplusplus
extern "C" {
#endif
    
void UnitySendMessage(const char* obj, const char* method, const char* msg)
{
    assert(false);
}
    
#ifdef __cplusplus
}
#endif
#endif

@implementation KTPlayApplicationUtils

+(UIView *)rootView
{
    
    return [[[[UIApplication sharedApplication] keyWindow] rootViewController] view];
}

@end
