#ifndef __JOYSTICK_SKINNED_H__
#define __JOYSTICK_SKINNED_H__

#include "cocos2d.h"
#include "SneakyJoystick.h"
USING_NS_CC;

class SneakyJoystickSkinnedBase : public Node
{
	CC_SYNTHESIZE_READONLY(Sprite *, backgroundSprite, BackgroundSprite);
    CC_SYNTHESIZE_READONLY(Sprite *, thumbSprite, ThumbSprite);
    CC_SYNTHESIZE_READONLY(Sprite *, defaultBackgroundSprite, DefaultBackgroundSprite);
    CC_SYNTHESIZE_READONLY(Sprite *, defaultThumbSprite, DefaultThumbSprite);
	CC_SYNTHESIZE_READONLY(SneakyJoystick *, joystick, Joystick);
    
	CREATE_FUNC(SneakyJoystickSkinnedBase);
    virtual bool init();
    
	void setBackgroundSprite(Sprite *aSprite, Sprite *bSprite = nullptr);
    void setThumbSprite(Sprite *aSprite, Sprite *bSprite = nullptr);
	void setJoystick(SneakyJoystick *aJoystick);
    
protected:
    void watchSelf(float delta);
};
#endif