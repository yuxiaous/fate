//
//  YMTXRecordManager.h
//
//
//  Created by ymtx2 on 14-8-16.
//
//
#import <Foundation/Foundation.h>
/*
    YMTXVideoQualityType 录制游戏视频的清晰度类型
 */
typedef enum{
    ymtx_video_quality_standard_definition = 0,
    ymtx_video_quality_high_definition,
}YMTXVideoQualityType;

@interface YMTXRecordManager : NSObject
/*
 初始化唯一的实例
 */
+ (YMTXRecordManager *)initWithDelegate:(id)delegate andParentViewController:(UIViewController *)viewController;


/*
 registerApp：
 appKey:
 */
+ (BOOL)registerApp:(NSString *)appKey;


/*
 entryRootViewAction:
 进入sdk界面
 */
+(void)entryRootViewAction;


/*
    showRecordMenu:
    显示桌面按钮
 */
+(void)showRecordMenu;


/*
 hideRecordMenu:
 隐藏桌面按钮
 */
+(void)hideRecordMenu;


/*
 startRecordAction:
 开发者调用接口开始录制：
 */
+(BOOL)startRecordAction;


/*
 stopRecordAction:
 开发者调用接口停止录制
 */
+(void)stopRecordAction;


/*
 stopRecordAndPlayBackAction:
 开发者调用接口停止录制并且跳转到回放界面
 */
+(void)stopRecordAndPlayBackAction;

/*
 playLastRecordVideo:
 开发者调用接口回放最近一次录制的视频
 */
+(void)playLastRecordVideo;


/*
 setRecordQualityType:
 开发者调用接口设置录制视频的清晰度，默认设置为标清
 */
+(void)setRecordQualityType:(YMTXVideoQualityType)type;


/*
 isInYMTXSDKView:
 判断当前是否在SDK的界面
 */
+(BOOL)isInYMTXSDKView;


/*
 isInRecord:
 判断当前是否在录制
 */
+(BOOL)isInRecord;



/*
 setHomeTitleString:
 设置werec主界面的标题，不设置默认为WeRec 图标
 */
+(void)setHomeTitleString:(NSString *)title;


/*
 setGameCPID:
 cpid为确定游戏玩家身份的一串字符串，在游戏玩家登陆游戏成功的时候设置。这样sdk可以游戏玩家上传视频，评论，点赞，等行为。便于运营开展玩家活动。
 */
+(void)setGameCPID:(NSString *)cpid;

+(UIViewController *)getSDKRootViewController;
@end
