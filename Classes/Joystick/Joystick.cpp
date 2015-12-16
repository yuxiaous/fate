//
//  Joystick.cpp
//  fate
//
//  Created by yuxiao on 15/12/16.
//
//

#include "Joystick.h"
#include <SneakyJoystick.h>
#include <SneakyJoystickSkinnedBase.h>

Joystick::Joystick()
: _joystick(nullptr)
{
}


Joystick *Joystick::create(Size joystickSize, Size thumbSize)
{
    Joystick *ret = new Joystick();
    if(ret && ret->initWithSize(joystickSize, thumbSize)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


bool Joystick::initWithSize(Size joystickSize, Size thumbSize)
{
    _joystickSize = joystickSize;
    _thumbSize = thumbSize;
    return true;
}

void Joystick::onEnter()
{
    Super::onEnter();
    
    _joystick = SneakyJoystick::create(_joystickSize, _thumbSize);
    _joystick->setIsConstantVelocity(true);
    
    _joystickBase = SneakyJoystickSkinnedBase::create();
    
    _joystickBase->setJoystick(_joystick);
    
    this->addChild(_joystickBase);
}

void Joystick::setBackgroundSprite(Sprite *aSprite, Sprite *bSprite)
{
    if(_joystickBase) {
        _joystickBase->setBackgroundSprite(aSprite, bSprite);
    }
}

void Joystick::setThumbSprite(Sprite *aSprite, Sprite *bSprite)
{
    if(_joystickBase) {
        _joystickBase->setThumbSprite(aSprite, bSprite);
    }
}

void Joystick::setTouchArea(const Rect &area)
{
    if(_joystick) {
        _joystick->setTouchArea(area);
    }
}
