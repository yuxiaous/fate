// KTUserC.h
//
// Copyright (c) 2014 KTplay  All rights reserved.
//

#ifndef ktplay_sdk_KTUserC_h
#define ktplay_sdk_KTUserC_h


#ifdef __cplusplus
extern "C" {
#endif
    
    /// 用户类
    class KTUserC
    {
    public:
        
        ///KT用户唯一标识符
        const char *userId;
        
        ///KT用户头像Url，如果想要获取头像缩率图请再url后面追加支持的缩率图大小。
        ///支持大小列表：_32x32,_50x50,_64x64,_80x80,_120x120,_128x128,_200x200,_256x256
        const char *headerUrl;
        
        ///KT用户昵称
        const char *nickname;
        
        ///性别  0:未知;1:男;2:女
        int gender;
        
        ///城市
        const char *city;
        
        ///扩展属性，获取排行榜时返回用户的积分
        const char *score;
        
        ///扩展属性，获取排行榜时返回用户的排行
        long long rank;
        
        ///保留字段
        const char *snsUserId;
        
        ///保留字段
        const char *loginType;
        
        ///游戏用户唯一标识符,网游登录用户有效
        const char *gameUserId;
        
        ///当前用户昵称是否为KTPlay平台生成
        bool needPresentNickname;
        
        KTUserC();
        ~KTUserC();
        
        
    };
    
#ifdef __cplusplus
}
#endif


#endif

