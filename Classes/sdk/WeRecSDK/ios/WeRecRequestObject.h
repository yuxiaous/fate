//
//  WeRecRequestObject.h
//  ParkourCPP
//
//  Created by 毛克斌 on 14-11-16.
//
//

#import <Foundation/Foundation.h>
#import "WeRecShareManager.h"
@interface WeRecRequestObject : NSObject
+(void)requestVideoShare:(TLShareType)type movieId:(NSInteger)movieId;
+(NSDictionary *)getShareKey;
@end
