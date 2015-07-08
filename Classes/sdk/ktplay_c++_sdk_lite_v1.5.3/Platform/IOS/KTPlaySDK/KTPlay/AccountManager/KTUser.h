// KTUser.h
//
// Copyright (c) 2014 KTplay  All rights reserved.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "KTPlay.h"


@interface KTUser : NSObject
///KT用户唯一标识符
@property (nonatomic, copy) NSString * userId;

///KT用户头像Url，如果想要获取头像缩率图请再url后面追加支持的缩率图大小。
///支持大小列表：_32x32,_50x50,_64x64,_80x80,_120x120,_128x128,_200x200,_256x256
@property (nonatomic, copy) NSString * headerUrl;

///KT用户昵称
@property (nonatomic, copy) NSString * nickname;

///性别  0:未知;1:男;2:女
@property (nonatomic) NSInteger  gender;

///城市
@property (nonatomic, copy) NSString * city;

///扩展属性，获取排行榜时返回用户的积分
@property (nonatomic, copy) NSString * score;

///扩展属性，获取排行榜时返回用户的排行
@property (nonatomic) long long rank;

///保留字段
@property (nonatomic,copy) NSString *           snsUserId;

///保留字段
@property (nonatomic,copy) NSString *           loginType;

///游戏用户唯一标识符,网游登录用户有效
@property (nonatomic,copy) NSString *           gameUserId;

///当前用户昵称是否为KTPlay平台生成
@property (nonatomic,assign) BOOL          needPresentNickname;
@end


