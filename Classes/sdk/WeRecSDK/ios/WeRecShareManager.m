//
//  WeRecShareManager.m
//
//
//  Created by ymtx2 on 14-7-31.
//
//
#import "WeRecShareManager.h"
#import "WeRecRequestObject.h"
#import "WeRecManager.h"
#define YMTXDynamicCast(C, o) ({ __typeof__(o) YMTXDynamicCast__o = (o); [YMTXDynamicCast__o isKindOfClass:[C class]] ? (C*)YMTXDynamicCast__o : nil; })
TLShareMenuType menuType;//分享界面需要显示的方向按钮

@interface WeRecShareManager()<
NSObject
#ifdef TLQQApi
,TencentSessionDelegate
#endif
#ifdef TLWeiboSDK
,WeiboSDKDelegate
#endif
#ifdef TLWXApi
,WXApiDelegate
#endif
>
{
    BOOL isShareWxGroup;
}
@end
static NSInteger currentShareVideoId;
@implementation WeRecShareManager
+(WeRecShareManager *)shareManager
{
    static WeRecShareManager *share = nil;
    if (share == nil) {
        share = [[WeRecShareManager alloc]init];
    }
    return share;
}

+(void)setCurrentShareVideoId:(NSInteger)videoId
{
    currentShareVideoId = videoId;
}

-(BOOL)IsLanguageChinese
{
    NSArray *languages = [NSLocale preferredLanguages];
    NSString *currentLanguage = [languages objectAtIndex:0];
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];
    if ([languageCode isEqualToString:@"zh"])
    {
        return YES;
    }
    return NO;
}

-(id)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (UIImage *) scaleFromImage:(UIImage *) image toSize: (CGSize) size
{
    if (!image) {
        return nil;
    }
    CGSize imageSize = image.size;
    if (size.width/size.height > imageSize.width/imageSize.height) {
        if (size.height > imageSize.height) {
            size.height = imageSize.height;
        }
        size.width = size.height * imageSize.width/imageSize.height;
    }else{
        if (size.width > imageSize.width) {
            size.width = imageSize.width;
        }
        size.height = size.width *imageSize.height/imageSize.width;
    }
    UIGraphicsBeginImageContext(size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [[UIColor clearColor] CGColor]);
    UIRectFill(CGRectMake(0, 0, size.width, size.height));//clear background
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}

-(NSString *)appDisplayName
{
    NSDictionary *dataDic = [[NSBundle mainBundle]infoDictionary];
    if ([dataDic objectForKey:@"CFBundleDisplayName"]) {
        return [dataDic objectForKey:@"CFBundleDisplayName"];
    }else{
        return [dataDic objectForKey:@"CFBundleName"];
    }
}

-(void)shareMovieUrlByAPPType:(TLShareType)type url:(NSString *)movieUrl image:(UIImage *)shareImage imageUrl:(NSString *)imageUrl title:(NSString *)title
{
    if (title == nil) {
        if([self IsLanguageChinese]){
            title = @"精彩游戏视频！求扩散！";
        }else{
            title = @"Great mobile game video. Share!";
        }
    }
    title = [NSString stringWithFormat:@"#%@#%@",[self appDisplayName],title];
    __block UIImage *image = shareImage;
    __block NSData *imageData = nil;
    image = [self scaleFromImage:image toSize:CGSizeMake(85.f, 85.f)];
    if (!image) {
        extern NSData* webCacheDataForUrl(NSString *url);
        NSData *catchData = webCacheDataForUrl(imageUrl);
        if (catchData) {
            image = [UIImage imageWithData:catchData];
        }
        if (!image) {
            image = [UIImage imageNamed:@"werec_share_default_icon.png"];
        }
        if (!image) {
            NSLog(@"添加一个分享的默认图标以 werec_share_default_icon.png 为图片名（一般为app图标）");
            assert(0);
        }
    }
    imageData = UIImageJPEGRepresentation(image, 0.8f);
    switch (type) {
        case share_type_wx:
        case share_type_wx_group:
        {
#ifdef TLWXApi
            if (![WXApi isWXAppInstalled]) {
                if ([self IsLanguageChinese]) {
                    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"" message:@"未安装微信！" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles: nil]autorelease];
                    [alert show];
                }else{
                    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"" message:@"WeChat is not installed!" delegate:nil cancelButtonTitle:@"Done" otherButtonTitles: nil]autorelease];
                    [alert show];
                }
                
                return;
            }
            WXMediaMessage *message = [WXMediaMessage message];
            message.title = title;
            message.description = @"";
            [message setThumbData:imageData];
            WXVideoObject *video = [WXVideoObject object];
            video.videoUrl = movieUrl;
            message.mediaObject = video;
            SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
            req.bText = NO;
            req.message = message;
            if (type == share_type_wx_group) {
                req.scene = WXSceneTimeline;
                isShareWxGroup = YES;
            }else{
                req.scene = WXSceneSession;
                isShareWxGroup = NO;
            }
            [WXApi sendReq:req];
#endif
        }
            break;
        case share_type_xl:
        {
#ifdef TLWeiboSDK
            if (![WeiboSDK isWeiboAppInstalled]) {
                if ([self IsLanguageChinese]) {
                    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"" message:@"未安装新浪微博！" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles: nil]autorelease];
                    [alert show];
                }else{
                    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"" message:@"Sina is not installed!" delegate:nil cancelButtonTitle:@"Done" otherButtonTitles: nil]autorelease];
                    [alert show];
                }
                
                return;
            }
            WBMessageObject *message = [WBMessageObject message];
            WBWebpageObject *webpage = [WBWebpageObject object];
            webpage.objectID = @"identifier1";
            webpage.title = title;
            webpage.description = @"";
            webpage.webpageUrl = movieUrl;
            
            webpage.thumbnailData = imageData;
            message.mediaObject = webpage;
            WBSendMessageToWeiboRequest *request = [WBSendMessageToWeiboRequest requestWithMessage:message];
            [WeiboSDK sendRequest:request];
#endif
        }
            break;
        case share_type_qq:
        case share_type_qzone:
        {
#ifdef TLQQApi
            if (![QQApi isQQInstalled]) {
                if ([[WeRecShareManager shareManager]IsLanguageChinese]) {
                    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"" message:@"未安装QQ！" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles: nil]autorelease];
                    [alert show];
                }else{
                    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"" message:@"QQ is not installed!" delegate:nil cancelButtonTitle:@"Done" otherButtonTitles: nil]autorelease];
                    [alert show];
                }
                return;
            }
            QQApiNewsObject *videoObj = nil;
            if (imageUrl) {
                videoObj = [QQApiNewsObject objectWithURL:[NSURL URLWithString:movieUrl]
                                                    title:title
                                              description:@""
                            
                                          previewImageURL:[NSURL URLWithString:imageUrl]];
            }else{
                videoObj = [QQApiNewsObject objectWithURL:[NSURL URLWithString:movieUrl]
                                                    title:title
                                              description:@""
                            
                                         previewImageData:imageData];
            }
            [videoObj setCflag:0];
            SendMessageToQQReq *req = [SendMessageToQQReq reqWithContent:videoObj];
            QQApiSendResultCode sent = 0;
            if (type == share_type_qq) {
                sent = [QQApiInterface sendReq:req];
            }else{
                sent = [QQApiInterface SendReqToQZone:req];
            }
#endif
        }
            break;
        case share_type_fb:
        {
        #ifdef TLFaceBook
            if (![SLComposeViewController class]) {
                return;
            }
          SLComposeViewController  *slComposerSheet = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeFacebook];
            [slComposerSheet setInitialText:title];
            [slComposerSheet addImage:image];
            [slComposerSheet addURL:[NSURL URLWithString:movieUrl]];
            UIViewController *root = [WeRecManager getSDKRootViewController];
            
            [root presentViewController:slComposerSheet animated:YES completion:nil];

            [slComposerSheet setCompletionHandler:^(SLComposeViewControllerResult result) {
                switch (result) {
                    case SLComposeViewControllerResultCancelled:
                        break;
                    case SLComposeViewControllerResultDone:
                        break;
                    default:
                        break;
                }
            }];
        #endif
        }
            break;
        case share_type_twitter:
        {
            #ifdef TLTwitter
            if (![SLComposeViewController class]) {
                return;
            }
          SLComposeViewController   *slComposerSheet = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeTwitter];
            [slComposerSheet setInitialText:title];
            [slComposerSheet addImage:image];
            [slComposerSheet addURL:[NSURL URLWithString:movieUrl]];
            UIViewController *root = [WeRecManager getSDKRootViewController];
            [root presentViewController:slComposerSheet animated:YES completion:nil];
            [slComposerSheet setCompletionHandler:^(SLComposeViewControllerResult result) {
                switch (result) {
                    case SLComposeViewControllerResultCancelled:
                        break;
                    case SLComposeViewControllerResultDone:
                        break;
                    default:
                        break;
                }
            }];
            #endif
        }
            break;
        default:
            break;
    }
}

-(void)initShareSdk
{
    NSDictionary *setting = nil;
    NSString *wxkey =WXAppKey;
    NSString *wbkey = XLAppKey;
    NSString *qqkey = QZoneAppId;
    NSString *description = WXDescription;
    TLShareMenuType type = 0;
    if (
#ifdef TLWXApi
        [WXAppKey isEqualToString:@"wxa27460f05622da9a"] ||
#endif
#ifdef TLWeiboSDK
        [XLAppKey isEqualToString:@"2045436852"] ||
#endif
        0
        ) {
        /*
         开放者需申请相应分享平台的key
         */
        UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"WeRec sdk 提示" message:@"别忘记更换分享Key" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles: nil]autorelease ];
        [alert show];
    }
#ifdef TLWXApi
    [WXApi registerApp:wxkey withDescription:description];
    type = type | menu_type_wx | menu_type_wx_group;
#endif
    
#ifdef TLWeiboSDK
    [WeiboSDK registerApp:wbkey];
    type = type | menu_type_xl;
#endif
#ifdef TLQQApi
    [[TencentOAuth alloc] initWithAppId:qqkey
                            andDelegate:self];
    type = type | menu_type_qq | menu_type_qzone;
#endif
   
    if (NSClassFromString(@"SLComposeViewController")) {
        #ifdef TLFaceBook
                type = type | menu_type_fb;
        #endif
        #ifdef TLTwitter
                type = type | menu_type_twitter;
        #endif
    }

    [[self class]setShareMenuType:type];
}

+(void)setShareMenuType:(TLShareMenuType)type
{
    menuType = type;
}

+(TLShareMenuType)shareMenuType;
{
    return menuType;
}

-(BOOL)handleOpenURL:(NSURL *)url
{
    BOOL handle = NO;
#ifdef TLWXApi
    if ([WXApi handleOpenURL:url delegate:self]) {
        return YES;
    }
#endif
    
#ifdef TLWeiboSDK
    if ([WeiboSDK handleOpenURL:url delegate:self]) {
        return YES;
    }
#endif
#ifdef TLQQApi
    [QQApiInterface handleOpenURL:url delegate:(id<QQApiInterfaceDelegate>)[self class]];
    if (YES == [TencentOAuth CanHandleOpenURL:url])
    {
        return [TencentOAuth HandleOpenURL:url];
    }
#endif
    return handle;
}
#ifdef TLQQApi
- (void)tencentDidLogin;
{
    
}
- (void)tencentDidNotLogin:(BOOL)cancelled;
{
    
}

- (void)tencentDidNotNetWork;
{
    
}

+ (void)onResp:(QQBaseResp *)resp
{
    switch (resp.type)
    {
        case ESENDMESSAGETOQQRESPTYPE:
        {
            SendMessageToQQResp* sendResp = (SendMessageToQQResp*)resp;
            NSString *message = nil;
            if (sendResp.result.integerValue == 0) {
                
                if([[WeRecShareManager shareManager] IsLanguageChinese]){
                    message = @"\n分享成功";
                }else{
                    message = @"\nShare success";
                }
                [WeRecRequestObject requestVideoShare:share_type_qq movieId:currentShareVideoId];
            }else{
                if([[WeRecShareManager shareManager] IsLanguageChinese]){
                    message = @"\n分享失败";
                }else{
                    message = @"\nSharing failed";
                }
            }
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@""
                                                            message:message
                                                           delegate:nil
                                                  cancelButtonTitle:nil
                                                  otherButtonTitles:nil];
            [alert show];
            [alert release];
            [[WeRecShareManager shareManager] performSelector:@selector(dismissPopView:) withObject:alert afterDelay:2.f];
            break;
        }
        default:
        {
            break;
        }
    }
}
#endif
#pragma WXApiDelegate
#ifdef TLWXApi
-(void)onResp:(BaseResp*)resp
{
    if([resp isKindOfClass:[SendMessageToWXResp class]])
    {
        NSString *message = nil;
        if (resp.errCode == WXSuccess) {
            if ([self IsLanguageChinese]) {
                message = @"\n分享成功";
            }else{
                message = @"\nShare success";
            }
            if (isShareWxGroup) {
                [WeRecRequestObject requestVideoShare:share_type_wx_group movieId:currentShareVideoId];
            }else{
                [WeRecRequestObject requestVideoShare:share_type_wx movieId:currentShareVideoId];
            }
        }else{
            if([self IsLanguageChinese]){
                message = @"\n分享失败";
            }else{
                message = @"\nSharing failed";
                
            }
        }
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@""
                                                        message:message
                                                       delegate:nil
                                              cancelButtonTitle:nil
                                              otherButtonTitles:nil];
        [alert show];
        [alert release];
        [self performSelector:@selector(dismissPopView:) withObject:alert afterDelay:2.f];
    }
}
#endif


#pragma WeiboSdkDelegate
#ifdef TLWeiboSDK
- (void)didReceiveWeiboRequest:(WBBaseRequest *)request;
{
    
}

- (void)didReceiveWeiboResponse:(WBBaseResponse *)response
{
    if ([response isKindOfClass:WBSendMessageToWeiboResponse.class])
    {
        NSString *message = nil;
        if (response.statusCode >=0) {
            if ([self IsLanguageChinese]) {
                message = @"\n分享成功";
            }else{
                message = @"\nShare success";
            }
            [WeRecRequestObject requestVideoShare:share_type_xl movieId:currentShareVideoId];
        }else{
            if([self IsLanguageChinese]){
                message = @"\n分享失败";
            }else{
                message = @"\nSharing failed";
                
            }
        }
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@""
                                                        message:message
                                                       delegate:nil
                                              cancelButtonTitle:nil
                                              otherButtonTitles:nil];
        [alert show];
        [alert release];
        [self performSelector:@selector(dismissPopView:) withObject:alert afterDelay:2.f];
    }
}

#endif
-(void)dismissPopView:(UIAlertView *)alert
{
    [alert dismissWithClickedButtonIndex:0 animated:YES];
}
@end
