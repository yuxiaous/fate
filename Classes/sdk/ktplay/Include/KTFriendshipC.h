// KTFriendshipC.h
//
// Copyright (c) 2014 KTplay  All rights reserved.
//


#ifndef ktplay_sdk_KTFriendship_h
#define ktplay_sdk_KTFriendship_h
#include "KTUserC.h"
#include "KTErrorC.h"


#ifdef __cplusplus
extern "C" {
#endif
    ///
    
    /**
     *    @brief    好友邀请回调
     *    @param    isSuccess 是否成功
     *    @param    successCount 成功数量
     *    @param    error 错误信息
     */
    typedef void(*KTFriendRequestsCallBack) (bool isSuccess, int successCount, KTErrorC *error);
    
    /**
     *    @brief    好友列表回调
     *    @param    isSuccess 是否成功
     *    @param    userArray 成功时返回好友列表数据，失败时为NULL
     *    @param    userArrayCount 成功时好友列表内好友数量
     *    @param    error 错误信息
     */
    typedef void(*KTFriendListCallBack) (bool isSuccess,KTUserC *userArray,int userArrayCount,KTErrorC *error);
    
    
    /// 好友相关接口
    class KTFriendshipC
    {
    public:
        
        /**
         * @brief 打开添加好友窗口
         */
        
        static void showFriendRequestsView();
        
        /**
         *  @brief 发送好友邀请
         *  @param targetUserIds，可添加多人可用逗号分隔
         *  @param success 成功回调
         *  @param failure 失败回调
         *
         *  错误码：
         *
         * + 150701	不能加自己为好友
         * + 150702	你们已经是好友
         * + 150703	你已经达到好友数量上限
         * + 150704	对方已经达到好友数量上限
         * + 150705	你已经邀请过他了
         */
        
        static void sendFriendRequests(char *targetUserIdsArray[],int targetUserIdCount, KTFriendRequestsCallBack callback);
        
        /**
         *  @brief 获取我的好友列表数据
         *  @param success 成功回调
         *  @param failure 失败回调
         */
        static void friendList(KTFriendListCallBack callback);
        
        
    };
    
#ifdef __cplusplus
}
#endif


#endif
