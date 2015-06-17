//
//  YMTXRequestObject.h
//
//
//  Created by ymtx2 on 14-11-16.
//
//

#import <Foundation/Foundation.h>
#import "YMTXShareManager.h"
@interface YMTXRequestObject : NSObject
+(void)requestVideoShare:(TLShareType)type movieId:(NSInteger)movieId;
+(NSDictionary *)getShareKey;
@end
