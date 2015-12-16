//
//  Joybutton.cpp
//  fate
//
//  Created by yuxiao on 15/12/16.
//
//

#include "Joybutton.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"

Joybutton::Joybutton()
: _button(nullptr)
, _buttonSkin(nullptr)
, _value(false)
{
    this->scheduleUpdate();
}

Joybutton::~Joybutton()
{
    this->unscheduleUpdate();
}

void Joybutton::update(float delta)
{
    if(_button) {
        _value = _button->getValue();
    }
}

Joybutton *Joybutton::create(Size size)
{
    Joybutton *ret = new Joybutton();
    if(ret && ret->initWithSize(size)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Joybutton::initWithSize(Size size)
{
    _button = SneakyButton::create(size);
    _button->setIsHoldable(true);
    
    _buttonSkin = SneakyButtonSkinnedBase::create();
    
    _buttonSkin->setButton(_button);
    
    this->addChild(_buttonSkin);
    
    return true;
}

void Joybutton::setDefaultSprite(Sprite *aSprite)
{
    if(_buttonSkin) {
        _buttonSkin->setDefaultSprite(aSprite);
    }
}

void Joybutton::setPressSprite(Sprite *aSprite)
{
    if(_buttonSkin) {
        _buttonSkin->setPressSprite(aSprite);
    }
}

void Joybutton::setDisabledSprite(Sprite *aSprite)
{
    if(_buttonSkin) {
        _buttonSkin->setDisabledSprite(aSprite);
    }
}

void Joybutton::setIsEnable(bool var)
{
    _enable = var;
    
    if(_button) {
        _button->setIsEnable(var);
    }
}

bool Joybutton::getIsEnable()
{
    return _enable;
}
