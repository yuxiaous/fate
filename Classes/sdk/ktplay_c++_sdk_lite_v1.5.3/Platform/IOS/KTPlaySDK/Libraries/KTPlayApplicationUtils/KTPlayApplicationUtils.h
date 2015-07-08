//
//  KTPlayApplicationUtils.h
//
//  Created by ktplay on 13-11-25.
//  Copyright (c) 2013年 KTPlay. All rights reserved.
//



#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#endif

#define IS_PLATFORM_UNITY 0


#if !IS_PLATFORM_UNITY
#ifdef __cplusplus
extern "C" {
#endif
    void UnitySendMessage(const char* obj, const char* method, const char* msg);
#ifdef __cplusplus
}
#endif
#endif

@interface KTPlayApplicationUtils:NSObject

+(UIView *)rootView;

@end
