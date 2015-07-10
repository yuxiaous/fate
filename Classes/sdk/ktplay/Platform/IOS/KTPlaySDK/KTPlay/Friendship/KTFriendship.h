// KTFriendship.h
//
// Copyright (c) 2014 KTplay  All rights reserved.

#import <Foundation/Foundation.h>

@interface KTFriendship : NSObject


/**
 * @brief 打开添加好友窗口
 */

+(void)showFriendRequestsView;


/**
 *  @brief 发送好友邀请
 *  @param targetUserIds，可添加多人可用逗号分隔
 *  @param success 成功回调
 *  @param failure 失败回调
 */
+(void)sendFriendRequests:(NSArray *)targetUserIds success:(void (^)(int count))success failure:(void(^)(NSError * error))failure;



/**
 *  @brief 获取我的好友列表数据
 *  @param success 成功回调
 *  @param failure 失败回调
 */
+(void)friendList:(void (^)(NSArray* users))success failure:(void(^)(NSError * error))failure;
@end
