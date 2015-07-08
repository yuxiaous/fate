// KTPlayC.h
//
// Copyright (c) 2014 KTplay  All rights reserved.
//

#ifndef __ktplay_sdk__KTPlayC__
#define __ktplay_sdk__KTPlayC__

#ifdef __cplusplus
extern "C" {
#endif
    
    
    class KTRewardItemC
    {
    public:
        
        /// 奖励名称
        const char *name;
        
        /// 奖励ID
        const char *typeId;
        
        
        /// 奖励值
        unsigned long value;
        KTRewardItemC();
        ~KTRewardItemC();
        
        
    };
    
    /**
     *    @brief    KTPlay奖励回调
     *    @param    pRewardArray 奖励内容（KTRewardItem数组）
     *    @param    length 奖励数量
     *    @see      KTRewardItemC
     */
    
    typedef void (*KTDispatchRewardsCallback)(KTRewardItemC * pRewardArray, int length);
    
    /**
     *    @brief    打开KTPlay主窗口回调
     */
    typedef void (*KTViewDidAppearCallback)();
    
    /**
     *    @brief    关闭KTPlay主窗口回调
     */
    typedef void (*KTViewDidDisappearCallback)();
    
    /**
     *    @brief   用户新动态回调（新动态包含话题被回复，被称赞，有新的好友邀请等
     *    @param   hasNewActivity 有未读的新动态
     */
    
    typedef void (*KTActivityStatusChangedCallback)(bool activityStatusChanged);
    
    /**
     *    @brief   KTPlay SDK的可用状态变更回调
     *    @param   isEnabled 当前状态
     */
    typedef void (*KTAvailabilityChangedCallback)(bool isEnabled);
    
    /**
     *    @brief   KTPlay SDK 深度链接回调
     *    @param   linkScheme 深度链接方案
     */
    typedef void (*KTDeepLinkCallback)(const char * linkScheme);
    
    /// KTPlay主类
    class KTPlayC
    {
    public:
        
        /**
         *  @brief 设置监听者，监听打开KTPlay主窗口事件
         *  @param appearCallback 打开KTPlay主窗口回调
         */
        static void setViewDidAppearCallback(KTViewDidAppearCallback appearCallback);
        
        /**
         *  @brief 设置监听者，监听关闭KTPlay主窗口事件
         *  @param disappearCallback 关闭KTPlay主窗口回调
         */
        static void setViewDidDisappearCallback(KTViewDidDisappearCallback disappearCallback);
        
        /**
         *  @brief 设置监听者，监听奖励发放事件
         *  @param dispatchRewardsCallback KTPlay奖励回调
         */
        static void setDidDispatchRewardsCallback(KTDispatchRewardsCallback dispatchRewardsCallback);
        
        /**
         *  @brief 设置监听者，监听用户新动态
         *  @param activityStatusChangedCallback 用户新动态回调
         */
        static void setActivityStatusChangedCallback(KTActivityStatusChangedCallback activityStatusChangedCallback);
        
        
        /**
         *  @brief 设置监听者，监听KTPlay SDK的可用状态变更
         *  @param availabilityChangedCallback KTPlay SDK的可用状态变更回调
         */
        static void setAvailabilityChangedCallback(KTAvailabilityChangedCallback availabilityChangedCallback);
        
        
        /**
         *  @brief 设置监听者，监听KTPlay深度链接事件
         *  @param availabilityChangedCallback 深度链接回调
         */
        static void setDeepLinkCallback(KTDeepLinkCallback deepLinkCallback);
        
        /**
         *  @brief 打开KTPlay主窗口
         */
        static void show();
        
        /** @brief 显示强通知（插屏通知）
         *
         */
        static void showInterstitialNotification();
        
        /**
         *  @brief 关闭KTPlay主窗口
         *
         *  通常情况下不需要调用此方法，KTPlay窗口由玩家主动关闭
         */
        
        static void dismiss();
        
        /**
         * @brief 判断KTplay是否可用
         * @return KTplay是否可用
         *
         *  KTPlay不可用的情况包括：<br/>
         *  1、设备不被支持<br/>
         *  2、在Portal上关闭 <br/>
         *  3、未获取到服务器配置信息（断网） <br/>
         */
        
        static bool isEnabled();
        
        /**
         * @brief 判断KTplay主窗口是否处于打开状态
         * @return KTplay主窗口是否打开
         *
         */
        static bool isShowing();
        
        
        

        /**
         * @brief 启用/禁用通知功能
         * @param enabled YES/NO 启用/禁用
         *
         *
         */
        static void setNotificationEnabled(bool isEnabled);
        
        /*!
         @abstract update (Android only)
         */
        static void update();
    };
    
#ifdef __cplusplus
}
#endif

#endif
