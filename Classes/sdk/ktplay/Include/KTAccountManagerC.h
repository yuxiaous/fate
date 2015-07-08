// KTAccountManagerC.h
//
// Copyright (c) 2014 KTplay  All rights reserved.
//



#ifndef ktplay_sdk_KTAccountManagerC_h
#define ktplay_sdk_KTAccountManagerC_h
#include "KTUserC.h"
#include "KTErrorC.h"
#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     *    @brief    KTPlay登录状态变更回调
     *    @param    isLoggedIn  登录/登出
     *    @param    account 登录用户的个人信息，如果登出返回NULL
     */
    
    
    typedef void(*KTLoginStatusChangedCallBack) (bool isLoggedIn, KTUserC * account);
    
    /**
     *    @brief    KTPlay用户信息回调
     *    @param    isSuccess  是否成功
     *    @param    user    用户信息，未成功返回NULL
     *    @param    userId  请求的用户id
     *    @param    error   错误信息
     */
    
    typedef void(*KTUserProfileCallBack) (bool isSuccess ,const char *userId,KTUserC * user,KTErrorC *error);
    
    /**
     *    @brief    登录界面回调
     *    @param    isSuccess  是否成功
     *    @param    user    用户信息，未成功返回NULL
     *    @param    error   错误信息
     */
    
    typedef void(*KTLoginCallBack) (bool isSuccess ,KTUserC * user,KTErrorC *error);
    
    /**
     *    @brief    设置昵称回调
     *    @param    isSuccess  是否成功
     *    @param    nickName    设置的昵称
     *    @param    user        用户信息，未成功返回NULL
     *    @param    error       错误信息
     */
    
    typedef void(*KTSetNickNameCallBack) (bool isSuccess ,const char * nickName,KTUserC * user, KTErrorC *error);
    
    /**
     *    @brief    网游用户登录回调
     *    @param    isSuccess   是否成功
     *    @param    gameUserid  网游用户的游戏userid
     *    @param    user        KTPlay用户信息，未成功返回NULL
     *    @param    error       错误信息
     */
    typedef void(*KTGameLoginCallBack) (bool isSuccess ,const char * gameUserid, KTUserC * user,KTErrorC *error);
    
    
    class KTAccountManagerC
    {
    public:
        /**
         * @brief 设置监听者，监听KTPlay登录状态变更
         * @param ktLoginStatus KTPlay登录状态变更回调
         */
        
        static void setLoginStatusChangedCallback(KTLoginStatusChangedCallBack ktLoginStatus);
        
        
        /**
         *  @brief 打开KTPlay登录界面
         *  @param closeable 登录界面是否可由玩家关闭， YES 可以，NO 不可以
         *  @param ktLoginCallback 登录界面回调
         */
        static void showLoginView(bool closeable, KTLoginCallBack ktLoginCallback);
        
        
        /**
         *  @brief 获取任意KTplay用户信息
         *  @param userId  KTPlay用户的唯一标示符
         *  @param callback KTPlay用户信息回调
         *
         */
        
        static void  userProfile(const char *userId,KTUserProfileCallBack callback);
        
        /**
         * @brief 修改当前登录帐户昵称
         * @param nickname 新昵称
         * @param callback 设置昵称回调
         */
        static void setNickName(const char * nickName, KTSetNickNameCallBack callback);
        
        
        /**
         * @brief 使用网游帐户登录KTPlay平台
         * @param gameUserId 游戏用户ID
         * @param 网游用户登录回调
         */
        static void loginWithGameUser(const char * gameUserId, KTGameLoginCallBack callback);
        
        
        /**
         * @brief 判断是否已有用户登录
         * @return 是否已有用户登录
         *
         */
        
        static bool isLoggedIn();
        
        /**
         * @brief 登出当前用户
         */
        static void logout();
        
        
        /**
         * @brief 获取当前登录KTplay用户信息
         * @return 返回KTplay用户信息，如果用户未登录返回为NULL
         *
         */
        static KTUserC* currentAccount();
        
    };
    
#ifdef __cplusplus
}
#endif

#endif
