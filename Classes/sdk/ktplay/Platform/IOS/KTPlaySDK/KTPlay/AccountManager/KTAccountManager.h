// KTAccountManager.h
//
// Copyright (c) 2014 KTplay  All rights reserved.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class KTUser;


/**
 *    @brief    KTPlay登录状态变更回调
 *    @param    isLoggedIn  登录/登出
 *    @param    account 登录用户的个人信息，如果登出返回nil
 */

typedef  void (^KTLoginStatusChangedBlock)(BOOL isLoggedIn, KTUser * account);



@interface KTAccountManager : NSObject


/**
 * @brief 使用网游帐户登录KTPlay平台
 * @param gameUserId 游戏用户ID
 * @param success 成功回调
 * @param failure 失败回调
 */
+(void)loginWithGameUser:(NSString *)gameUserId success:(void (^)(KTUser *user))success failure:(void (^)(NSError *error))failure;


/**
 * @brief 修改当前登录帐户昵称
 * @param nickname 新昵称
 * @param success 成功回调
 * @param failure 失败回调
 */
+(void)setNickname:(NSString *)nickname  success:(void (^)(KTUser *user))success failure:(void (^)(NSError *error))failure;


/**
 * @brief 登出当前用户
 */
+(void)logout;


/**
 * @brief 设置监听者，监听KTPlay登录状态变更
 * @param ktLoginStatusChangedBlock KTPlay登录状态变更回调
 */

+(void)setLoginStatusChangedBlock:(KTLoginStatusChangedBlock)ktLoginStatusChangedBlock ;



/**
 *  @brief 打开KTPlay登录界面
 *  @param closeable 登录界面是否可由玩家关闭， YES 可以，NO 不可以
 *  @param success 成功回调
 *  @param failure 失败回调 （包含用户关闭登录界面）
 */

+(void)showLoginView:(BOOL)closeable success:(void (^)( KTUser * account))success
             failure:(void (^)(NSError *error))failure;


/**
 *  @brief 获取任意KTplay用户信息
 *  @param userId  KTPlay用户的唯一标示符
 *  @param success 成功回调
 *  @param failure 失败回调
 *
 */
+(void)userProfile:(NSString *)userId success:(void (^)(KTUser * user))success failure:(void(^)(NSError * error))failure;


/**
 * @brief 判断是否已有用户登录
 * @return 是否已有用户登录
 *
 */

+(BOOL)isLoggedIn;


/**
 * @brief 获取当前登录KTplay用户信息
 * @return 返回KTplay用户信息，如果用户未登录返回为nil
 *
 */
+(KTUser *)currentAccount;



@end
