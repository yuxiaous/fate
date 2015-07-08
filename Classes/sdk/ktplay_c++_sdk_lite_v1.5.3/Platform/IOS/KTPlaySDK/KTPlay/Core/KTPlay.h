// KTPlay.h
//
// Copyright (c) 2014 KTplay  All rights reserved.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class KTUser;

@interface KTRewardItem : NSObject

/// 奖励名称
@property (nonatomic,copy) NSString * name;

/// 奖励ID
@property (nonatomic,copy) NSString * typeId;

/// 奖励值
@property (nonatomic) long long value;
@end


/**
 *    @brief    KTPlay奖励回调
 *    @param    rewards 奖励内容（KTRewardItem数组）
 *    @see      KTRewardItem
 */
typedef  void (^KTDidDispatchRewardsBlock)(NSArray * rewards);

/**
 *    @brief    打开KTPlay主窗口回调
 */
typedef  void (^KTViewDidAppearBlock)();

/**
 *    @brief    关闭KTPlay主窗口回调
 */
typedef  void (^KTViewDidDisappearBlock)();

/**
 *    @brief   用户新动态回调（新动态包含话题被回复，被称赞，有新的好友邀请等
 *    @param   hasNewActivity 有未读的新动态
 */

typedef  void (^KTActivityStatusChangedBlock)(BOOL hasNewActivity);

/**
 *    @brief   KTPlay SDK的可用状态变更回调
 *    @param   isEnabled 当前状态
 */
typedef  void (^KTAvailabilityChangedBlock)(BOOL isEnabled);


/**
 *    @brief   KTPlay SDK 深度链接回调
 *    @param   linkScheme 深度链接方案
 */
typedef void(^KTDeepLinkBlock)(NSString *linkScheme);


/**
 * KTPlay
 */
@interface KTPlay : NSObject



/**
 *  @brief 初始化 KTPlaySDK
 *  @param appKey KTPlay App Key，在KTPlay开发者网站新建应用后获取
 *  @param appSecret KTPlay App Secret，在KTPlay开发者网站新建应用后获取
 *
 *  startWithAppKey方法必须在游戏AppDelgate的didFinishLaunchingWithOptions方法中调用
 **/

+(void)startWithAppKey:(NSString *)appKey appSecret:(NSString *)appSecret;

/**
 *  @brief 设置用于显示KTPlay窗口的父容器
 *  @param parentView KTPlay窗口的父容器
 *
 *  默认情况下,KTPlay会使用[[[[UIApplication sharedApplication] keyWindow] rootViewController] view]作为父容器，
 */

+(void)setKTParentView:(UIView *)parentView;

/**
 *  @brief 打开KTPlay主窗口
 */
+(void)show;

/**
 *  @brief 关闭KTPlay主窗口
 *
 *  通常情况下不需要调用此方法，KTPlay窗口由玩家主动关闭
 */

+(void)dismiss;




/**
 *  @brief 设置监听者，监听奖励发放事件
 *  @param block KTPlay奖励回调
 */
+(void)setDidDispatchRewardsBlock:(KTDidDispatchRewardsBlock)block;


/**
 *  @brief 设置监听者，监听打开KTPlay主窗口事件
 *  @param block 打开KTPlay主窗口回调
 */

+(void)setViewDidAppearBlock:(KTViewDidAppearBlock)block;


/**
 *  @brief 设置监听者，监听关闭KTPlay主窗口事件
 *  @param block 关闭KTPlay主窗口回调
 */

+(void)setViewDidDisappearBlock:(KTViewDidDisappearBlock)block;


/**
 *  @brief 设置监听者，监听用户新动态
 *  @param block 用户新动态回调
 */
+(void)setActivityStatusChangedBlock:(KTActivityStatusChangedBlock)block;

/**
 *  @brief 设置监听者，监听KTPlay SDK的可用状态变更
 *  @param block KTPlay SDK的可用状态变更回调
 */

+(void)setAvailabilityChangedBlock:(KTAvailabilityChangedBlock)block;

/** @brief 设置监听者，监听DeepLink事件
 *
 */

+(void)setDeepLinkBlock:(KTDeepLinkBlock)block;
/**
 * @brief 判断KTplay是否可用
 * @return KTplay是否可用
 *
 *  KTPlay不可用的情况包括：<br/>
 *  1、设备不被支持<br/>
 *  2、在Portal上关闭 <br/>
 *  3、未获取到服务器配置信息（断网） <br/>
 */
+(BOOL)isEnabled;


/**
 * @brief 判断KTplay主窗口是否处于打开状态
 * @return KTplay主窗口是否打开
 *
 */

+(BOOL)isShowing;


/**
 *  @brief 处理SNS客户端返回的信息
 *  @param url AppDelegate的openURL方法中传入的url。
 *
 *
 *  为确保SNS（微信，QQ，新浪微博等）功能正确使用，请确保该方法在- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation中被调用
 *
 */
+(void)handleOpenURL:(NSURL *)url;


/**
 * @brief 启用/禁用通知功能
 * @param enabled YES/NO 启用/禁用
 *
 *
 */


+(void)setNotificationEnabled:(BOOL)enabled;


/** @brief 打开KTPlay强通知窗口（插屏通知窗口）
 *
 */
+(void)showInterstitialNotification;

@end





