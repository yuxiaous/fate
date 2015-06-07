#include "SneakyJoystickSkinnedBase.h"

bool SneakyJoystickSkinnedBase::init()
{
	bool pRet = false;
	if(Node::init()){
		this->backgroundSprite = nullptr;
		this->thumbSprite = nullptr;
        this->joystick = nullptr;
		this->defaultBackgroundSprite = nullptr;
		this->defaultThumbSprite = nullptr;
        this->setAnchorPoint(Vec2(0.5f, 0.5f));
        this->schedule(schedule_selector(SneakyJoystickSkinnedBase::watchSelf));
		pRet = true;
	}
	return pRet;	
}

void SneakyJoystickSkinnedBase::watchSelf(float delta)
{
    if(joystick && thumbSprite) {
        thumbSprite->setPosition(joystick->getStickPosition());
    }
    
    if(joystick && defaultBackgroundSprite && defaultThumbSprite) {
        auto safeSetVisible = [](Sprite *sprite, bool value) {
            if(sprite) sprite->setVisible(value);
        };
        
        bool isActive = joystick->getIsActive();
        safeSetVisible(defaultBackgroundSprite, !isActive);
        safeSetVisible(defaultThumbSprite, !isActive);
        safeSetVisible(backgroundSprite, isActive);
        safeSetVisible(thumbSprite, isActive);
    }
}

void SneakyJoystickSkinnedBase::setBackgroundSprite(Sprite *aSprite, Sprite *bSprite)
{
	if(backgroundSprite){
        backgroundSprite->removeFromParent();
	}
    backgroundSprite = aSprite;
    if(backgroundSprite){
		this->addChild(backgroundSprite, 0);
	}
    
    if(defaultBackgroundSprite) {
        defaultBackgroundSprite->removeFromParent();
    }
    defaultBackgroundSprite = bSprite;
    if(defaultBackgroundSprite) {
        this->addChild(defaultBackgroundSprite, 0);
    }
    
    if(backgroundSprite && defaultBackgroundSprite) {
        backgroundSprite->setVisible(false);
    }
}

void SneakyJoystickSkinnedBase::setThumbSprite(Sprite *aSprite, Sprite *bSprite)
{
	if(thumbSprite){
		thumbSprite->removeFromParent();
	}
	thumbSprite = aSprite;
	if(thumbSprite){
        this->addChild(thumbSprite, 1);
	}
    
    if(defaultThumbSprite) {
        defaultThumbSprite->removeFromParent();
    }
    defaultThumbSprite = bSprite;
    if(defaultThumbSprite) {
        this->addChild(defaultThumbSprite, 1);
    }
    
    if(thumbSprite && defaultThumbSprite) {
        thumbSprite->setVisible(false);
    }
}

void SneakyJoystickSkinnedBase::setJoystick(SneakyJoystick *aJoystick)
{
	if(joystick){
		joystick->removeFromParent();
	}
	joystick = aJoystick;
	if(joystick){
		this->addChild(aJoystick, 2);
	}
}