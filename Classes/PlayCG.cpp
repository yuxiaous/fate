//
//  PlayCG.cpp
//  crows
//
//  Created by shilei on 15/4/2.
//
//

#include "PlayCG.h"
//#include "Runtime.h"
//#include "ConfigParser.h"
#include "LHVideoPlayerImplCpp.h"

USING_NS_CC;

Scene* PlayCG::createScene(const movePlayFinishBack& playDone)
{
    auto scene = Scene::create();
    auto layer = PlayCG::create(playDone);
    scene->addChild(layer);
    
    return scene;
}

PlayCG* PlayCG::create(const movePlayFinishBack& playDone){
    PlayCG* pRet = new  PlayCG();
    
    if(pRet && pRet->init(playDone)){
        pRet->autorelease();
        return  pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return  NULL;
    }
}

bool PlayCG::init(const movePlayFinishBack& playDone)
{
    if ( !Layer::init() )
    {
        return false;
    }
    _moveDoneCallF = playDone;
    Director::getInstance()->pause();
    return true;
}

void PlayCG::onEnter(){
    Layer::onEnter();
    auto size = Director::getInstance()->getVisibleSize();
    LHVideoPlayerImplCpp::playMP4WithName("res/movie/suu", Rect(0,0,size.width,size.height));
    LHVideoPlayerImplCpp::setSkipTitle("SKIP MOVIE");
    
    this->scheduleUpdate();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
    
}

void PlayCG::onExit(){
    Layer::onExit();
    this->unscheduleUpdate();
}

void PlayCG::update(float dt){
    if(LHVideoPlayerImplCpp::getFinishState() == 0){
        this->unscheduleUpdate();
        _moveDoneCallF();
    }
}