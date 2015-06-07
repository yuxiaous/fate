//
//  LHVideoPlayerImpl.h
//  VideoDemo
//
//  Created by LiuYanghui on 14-5-5.
//
//

#import <Foundation/Foundation.h>

@interface LHVideoPlayerImpl : NSObject

+ (void)playMP4WithName: (NSString *)name VideoFrame:(CGRect)rect;
+ (void)skipVideo;
+ (void)setSkipTitle: (NSString *)title;
+ (BOOL)getFinishState;

@end
