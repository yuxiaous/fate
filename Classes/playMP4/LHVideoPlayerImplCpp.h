//
//  LHVideoPlayerImplCpp.h
//  VideoDemo
//
//  Created by LiuYanghui on 14-5-5.
//
//

#ifndef __VideoDemo__LHVideoPlayerImplCpp__
#define __VideoDemo__LHVideoPlayerImplCpp__

#include "cocos2d.h"

class LHVideoPlayerImplCpp {
public:
    /**
     * 开始播放MP4视频
     * name 视频名称，不要带后缀".mp4"。(比如文件是test.mp4, 那么name就传"test")
     * frameRect 视频显示的区域。全屏(Rect(0, 0, visibleSize.width, visibleSize.height))
     */
    static void playMP4WithName(const char* name, cocos2d::Rect frameRect);
    
    /**
     * 设置跳过影片按钮title，默认无跳过影片功能
     */
    static void setSkipTitle(const char* title);
    
    static bool getFinishState();
};

#endif /* defined(__VideoDemo__LHVideoPlayerImplCpp__) */
