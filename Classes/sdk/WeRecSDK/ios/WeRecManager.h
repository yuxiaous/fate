//
//  WeRecManager.h
//
//
//  Created by ymtx2 on 15-7-1.
//
//
#import <Foundation/Foundation.h>
/*
 WeRecVideoQualityType 录制游戏视频的清晰度类型
 */
typedef enum{
    werec_video_quality_standard_definition = 0,
    werec_video_quality_high_definition,
}WeRecVideoQualityType;

@protocol WeRecManagerDelegate <NSObject>
@optional
/*
 entryWeRecUI
 进入WeRec 专区回调。在回调里设置暂停游戏！
 */
-(void)entryWeRecUI;


/*
 exitWeRecUI
 退出WeRec 专区回调。在回调里恢复游戏！
 */
-(void)exitWeRecUI;



/*
 updateRecordTimeCount
 录制视频每隔一秒回调一次！
 timeCount：当前录制时长，单位秒
 */
-(void)updateRecordTimeCount:(NSInteger)timeCount;
@end



@interface WeRecManager : NSObject
/*
 初始化唯一的实例
 */
+ (WeRecManager *)initWithDelegate:(id<WeRecManagerDelegate>)delegate andParentViewController:(UIViewController *)viewController;


/*
 registerApp：
 appKey:
 */
+ (BOOL)registerApp:(NSString *)appKey;


/*
 entryWeRecMainUI:
 进入WeRec 专区界面
 */
+(void)entryWeRecMainUI;


/*
 showWeRecSdkMenu:
 显示桌面按钮
 */
+(void)showWeRecSdkMenu;


/*
 hideWeRecSdkMenu:
 隐藏桌面按钮
 */
+(void)hideWeRecSdkMenu;


/*
 startRecordAction:
 开发者调用接口开始录制：
 */
+(BOOL)startRecordAction;


/*
 stopRecordAction:
 开发者调用接口停止录制
 result 是否录制成功
 limitTimeCallBack 录制时间少于最小录制时间，回调提示！继续录制视频
 */
+(void)stopRecordAction:(void(^)(BOOL result))finishBlock limitTimeCallBack:(void (^)(void)) callBack;



/*
 stopRecordAndPlayBackAction:
 开发者调用接口停止录制并且跳转到回放界面
 result 是否录制成功
 limitTimeCallBack 停止录制失败，提示最少录制时间
 */
+(void)stopRecordAndPlayBackAction:(void(^)(BOOL result))finishBlock  limitTimeCallBack:(void (^)(void)) callBack;



/*
 setRecordTimeOutCallBack:
 设置录制超时回调
 result  视频录制是否成功
 filePath 视频路径
 */
+(void)setRecordTimeOutCallBack:(void(^)(BOOL result,NSString *filePath))timeOut;




/*
 playLastRecordVideo:
 开发者调用接口回放最近一次录制的视频
 */
+(void)playLastRecordVideo;


/*
 setRecordQualityType:
 开发者调用接口设置录制视频的清晰度，默认设置为标清
 */
+(void)setRecordQualityType:(WeRecVideoQualityType)type;



/*
 setMinRecordTimeCount:
 设置视频最短录制时间
 timeCount 单位为秒
 */
+(void)setMinRecordTimeCount:(NSInteger)timeCount;



/*
 setMaxRecordTimeCount:
 设置视频最长录制时间
 timeCount 单位为秒
 */
+(void)setMaxRecordTimeCount:(NSInteger)timeCount;



/*
 isInRecord:
 判断当前是否在录制
 */
+(BOOL)isInRecord;



+(UIViewController *)getSDKRootViewController;
@end
