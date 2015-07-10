// KTLeaderboardC.h
//
// Copyright (c) 2014 KTplay  All rights reserved.
//



#ifndef ktplay_sdk_KTLeaderboardC_h
#define ktplay_sdk_KTLeaderboardC_h
#include "KTErrorC.h"
#include "KTLeaderboardPaginatorC.h"
#ifdef __cplusplus
extern "C" {
#endif
    
    
    /**
     *    @brief    获取排行榜数据回调
     *    @param    isSuccess  是否成功
     *    @param    leaderboardId  排行榜id
     *    @param    leaderboard 排行榜数据
     *    @param    error 错误信息
     */
    
    
    typedef void(*KTLeaderboardCallBack) (bool isSuccess,const char *leaderboardId ,KTLeaderboardPaginatorC *leaderboard,KTErrorC *error);
    
    
    
    /**
     *    @brief    上传得分回调
     *    @param    isSuccess  是否成功
     *    @param    leaderboardId  排行榜id
     *    @param    score 上传的分数
     *    @param    error 错误信息
     */
    typedef void(*KTReportScoreCallBack) (bool isSuccess,const char *leaderboardId,long long score,KTErrorC *error);
    
    
    /// 排行榜相关接口
    class KTLeaderboardC
    {
    public:
        
        /**
         *  @brief  获取好友排行榜数据
         *  @param leaderboardId 排行榜id，此数据在开发者网站获取
         *  @param startIndex  排行榜起始位置，如果传-1 返回当前登录用户排名所处位置的排行榜数据。
         *  @param count  获取排行榜单页数据记录条数。
         *  @param callback 获取排行榜数据回调
         *
         */
        static void friendsLeaderboard(const char *leaderboardId ,int startIndex,int count,KTLeaderboardCallBack callback);
        
        /**
         *  @brief  获取游戏排行榜数据
         *  @param leaderboardId 排行榜id，此数据在开发者网站获取
         *  @param startIndex  排行榜起始位置
         *  @param count  获取排行榜单页数据记录条数
         *  @param callback 获取排行榜数据回调
         *
         */
        static void globalLeaderboard(const char *leaderboardId ,int startIndex,int count,KTLeaderboardCallBack callback);
        
        /**
         *  @brief  获取上周好友排行榜数据
         *  @param leaderboardId 排行榜id，此数据在开发者网站获取
         *  @param startIndex  排行榜起始位置，如果传-1 返回当前登录用户排名所处位置的排行榜数据。
         *  @param count  获取排行榜单页数据记录条数。
         *  @param callback 获取排行榜数据回调
         *
         */
        
        
        
        static void lastFriendsLeaderboard(const char *leaderboardId ,int startIndex,int count,KTLeaderboardCallBack callback);
        
        
        /**
         *  @brief  获取上周游戏排行榜数据
         *  @param leaderboardId 排行榜id，此数据在开发者网站获取
         *  @param startIndex  排行榜起始位置
         *  @param count  获取排行榜单页数据记录条数
         *  @param callback 获取排行榜数据回调
         *
         */
        
        static void lastGlobalLeaderboard(const char *leaderboardId ,int startIndex,int count,KTLeaderboardCallBack callback);
        
        
        /**
         *  @brief  上传得分
         *  @param leaderboardId 排行榜id，，此数据在开发者网站获取
         *  @param score 游戏得分
         *  @param callback 上传得分回调
         *
         */
        static void reportScore(long long score ,const char *leaderboardId,KTReportScoreCallBack callback);
        
    };
    
#ifdef __cplusplus
}
#endif

#endif
