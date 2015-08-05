//
//  WeRecShareManager.h
//
//
//  Created by ymtx2 on 15-7-01.
//
//
#import <Foundation/Foundation.h>
//#define TLWeiboSDK
//#define TLWXApi
//#define TLQQApi

//#define TLFaceBook
//#define TLTwitter

#if (defined TLFaceBook || defined TLTwitter)
#import <Twitter/Twitter.h>
#import <Social/Social.h>
#import <Accounts/Accounts.h>
#endif

#ifdef TLWeiboSDK
#import "WeiboSDK.h"
#endif

#ifdef TLWXApi
#import "WXApi.h"
#endif

#ifdef TLQQApi
#import <TencentOpenAPI/QQApiInterface.h>
#import <TencentOpenAPI/TencentOAuth.h>
#endif

typedef enum {
    share_type_wx = 0,          //微信
    share_type_xl,              //新浪微博
    share_type_qq,              //qq 好友
    share_type_qzone,           //QQ空间
    share_type_wx_group,        //微信朋友圈
    share_type_fb,              //facebook
    share_type_twitter          //twitter
}TLShareType;

typedef enum {
    menu_type_wx            = 1 << 0,
    menu_type_wx_group      = 1 << 1,
    menu_type_qq            = 1 << 2,
    menu_type_qzone         = 1 << 3,
    menu_type_xl            = 1 << 4,
    menu_type_fb            = 1 << 5,
    menu_type_twitter       = 1 << 6
}TLShareMenuType;

//微信
#define WXAppKey         @"wxa27460f05622da9a"
#define WXDescription    @"WeRec"
//新浪微博
#define XLAppKey         @"2045436852"
#define XLRedirectURI    @"http://www.sina.com"
//Qzone
#define QZoneAppId       @"1103378845"

@interface WeRecShareManager : NSObject
+(WeRecShareManager *)shareManager;
+(TLShareMenuType)shareMenuType;//分享界面需要显示的分享按钮
+(void)setCurrentShareVideoId:(NSInteger)videoId;
-(void)shareMovieUrlByAPPType:(TLShareType)type url:(NSString *)movieUrl image:(UIImage *)shareImage imageUrl:(NSString *)imageUrl title:(NSString *)title;
-(BOOL)handleOpenURL:(NSURL *)url;
-(void)initShareSdk;
@end
