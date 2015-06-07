#ifndef __SNEAKY_JOYSTICK_H__
#define __SNEAKY_JOYSTICK_H__

#include "cocos2d.h"
USING_NS_CC;

class SneakyJoystick : public Node
{
protected:
    EventListenerTouchOneByOne*  _touchListenerOneByOne;
    
	float _joystickRadiusSq;
	float _thumbRadiusSq;
	float _deadRadiusSq;

    CC_PROPERTY(bool, _enable, IsEnable);
	CC_SYNTHESIZE_READONLY(Vec2, _stickPosition, StickPosition);
	CC_SYNTHESIZE_READONLY(float, _degrees, Degrees);
	CC_SYNTHESIZE_READONLY(Vec2, _velocity, Velocity);
	CC_SYNTHESIZE(bool, _autoCenter, AutoCenter);
	CC_SYNTHESIZE_READONLY(bool, _isDPad, IsDPad);
	CC_SYNTHESIZE(bool, _hasDeadzone, HasDeadzone);
    CC_SYNTHESIZE(int, _numberOfDirections, NumberOfDirections);
    CC_SYNTHESIZE(Rect, _touchArea, TouchArea);
    CC_SYNTHESIZE(bool, _isConstantVelocity, IsConstantVelocity);
    CC_SYNTHESIZE_READONLY(bool, _active, IsActive);

	CC_SYNTHESIZE_READONLY(float, joystickRadius, JoystickRadius);
	CC_SYNTHESIZE_READONLY(float, thumbRadius, ThumbRadius);
	CC_SYNTHESIZE_READONLY(float, deadRadius, DeadRadius);
    
#ifndef SKIP_BY_AUTO_BINDINGS
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
#endif

    static SneakyJoystick *create(Size joystickSize, Size thumbSize);
	bool initWithSize(Size joystickSize, Size thumbSize);
	void setIsDPad(bool b);
	void setJoystickRadius(float r);
	void setThumbRadius(float r);
	void setDeadRadius(float r);
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);
	virtual void onTouchCancelled(Touch *touch, Event *event);

private:
	void updateVelocity(Vec2 point);
	void setTouchRadius();

};
#endif
