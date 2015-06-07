//
//  PlayCG.h
//  crows
//
//  Created by shilei on 15/4/2.
//
//

#ifndef __crows__PlayCG__
#define __crows__PlayCG__

#include <stdio.h>
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ui/CocosGUI.h"
#endif

using namespace cocos2d;
using namespace experimental::ui;

class PlayCG : public cocos2d::Layer
{
public:
    typedef std::function<void()> movePlayFinishBack;
    
    static cocos2d::Scene* createScene(const movePlayFinishBack& playDone);

    static PlayCG* create(const movePlayFinishBack& playDone);
    
    virtual bool init(const movePlayFinishBack& playDone);
    
  //  CREATE_FUNC(PlayCG);
    
    void onEnter();
    void onExit();
    

    
private:    
    movePlayFinishBack _moveDoneCallF ;
    
    void playMovieFinish(Ref* mov,VideoPlayer::EventType type);
    
    void update(float dt);
};

#endif /* defined(__crows__PlayCG__) */
