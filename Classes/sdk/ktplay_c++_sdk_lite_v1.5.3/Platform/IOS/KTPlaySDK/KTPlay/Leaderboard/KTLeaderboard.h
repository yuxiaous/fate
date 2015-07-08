// KTLeaderboard.h
//
// Copyright (c) 2014 KTplay  All rights reserved.


#import <Foundation/Foundation.h>
@interface KTLeaderboardPaginator : NSObject
/// 上榜人数
@property (nonatomic) int total;

/// 下一页起始位置
@property (nonatomic, copy) NSString * nextCursor;

/// 上一页起始位置
@property (nonatomic, copy) NSString * previousCursor;

/// KTUser数组
@property (nonatomic, copy) NSArray * items;

/// 排行榜名字
@property (nonatomic, copy) NSString * leaderboardName;

/// 排行榜图标
@property (nonatomic, copy) NSString * leaderboardIcon;

/// 排行榜ID
@property (nonatomic, copy) NSString * leaderboardId;

/// 排行榜单唯一标示符
@property (nonatomic, copy) NSString * periodicalSummaryId;

/// 我的排名
@property (nonatomic) NSInteger myRank;

/// 我的积分
@property (nonatomic,copy) NSString *myScore;

@end

@interface KTLeaderboard : NSObject

/**
 *  @brief  获取好友排行榜数据
 *  @param leaderboardId 排行榜id，此数据在开发者网站获取
 *  @param startIndex  排行榜起始位置，如果传-1 返回当前登录用户排名所处位置的排行榜数据。
 *  @param count  获取排行榜数据记录条数
 *  @param success 成功回调
 *  @param failure 失败回调
 *
 */
+(void)friendsLeaderboard:(NSString *)leaderboardId startIndex:(int)startIndex count:(int)count success:(void (^)(KTLeaderboardPaginator * leaderboard))success failure:(void(^)(NSError * error))failure;

/**
 *  @brief  获取游戏排行榜数据
 *  @param leaderboardId 排行榜id，此数据在开发者网站获取
 *  @param startIndex  排行榜起始位置
 *  @param count  获取排行榜数据记录条数
 *  @param success 成功回调
 *  @param failure 失败回调。
 *
 */
+(void)globalLeaderboard:(NSString *)leaderboardId startIndex:(int)startIndex count:(int)count success:(void (^)(KTLeaderboardPaginator * leaderboard))success failure:(void(^)(NSError * error))failure;

/**
 *  @brief  上传得分
 *  @param leaderboardId 排行榜id，，此数据在开发者网站获取
 *  @param score 游戏得分
 *  @param success 成功回调
 *  @param failure 失败回调
 *
 */
+(void)reportScore:(long long)score leaderboardId:(NSString *)leaderboardId success:(void (^)())success failure:(void(^)(NSError * error))failure;




/**
 *  @brief  获取上周好友排行
 *  @param leaderboardId 排行榜id，此数据在开发者网站获取
 *  @param startIndex  排行榜起始位置
 *  @param count  获取排行榜数据记录条数
 *  @param success 成功回调
 *  @param failure 失败回调。
 *
 */

+(void)lastFriendsLeaderboard:(NSString *)leaderboardId startIndex:(int)startIndex count:(int)count success:(void (^)(KTLeaderboardPaginator * leaderboard))success failure:(void(^)(NSError * error))failure;


/**
 *  @brief  获取上周游戏排行榜数据
 *  @param leaderboardId 排行榜id，此数据在开发者网站获取
 *  @param startIndex  排行榜起始位置
 *  @param count  获取排行榜数据记录条数
 *  @param success 成功回调
 *  @param failure 失败回调。
 *
 */

+(void)lastGlobalLeaderboard:(NSString *)leaderboardId startIndex:(int)startIndex count:(int)count success:(void (^)(KTLeaderboardPaginator * leaderboard))success failure:(void(^)(NSError * error))failure;

@end
