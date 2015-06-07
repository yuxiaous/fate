#ifndef __SNEAKY_BUTTON_H__
#define __SNEAKY_BUTTON_H__

#include "cocos2d.h"
USING_NS_CC;

class SneakyButton : public Node
{
protected:
    EventListenerTouchOneByOne*  _touchListenerOneByOne;
    
	float _radiusSq;
    
    CC_PROPERTY(bool, _enable, IsEnable);
	CC_SYNTHESIZE_READONLY(bool, _active, IsActive);
	CC_SYNTHESIZE_READONLY(bool, _value, Value);
	CC_SYNTHESIZE(bool, _isHoldable, IsHoldable);
	CC_SYNTHESIZE(bool, _isToggleable, IsToggleable);
	CC_SYNTHESIZE(float, _rateLimit, RateLimit);
	CC_SYNTHESIZE_READONLY(float, _radius, Radius);

	//Public methods
#ifndef SKIP_BY_AUTO_BINDINGS
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
#endif
    
    static SneakyButton *create(Size size);
	bool initWithSize(Size size);
	void limiter(float delta);
	void setRadius(float r);
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);
	virtual void onTouchCancelled(Touch *touch, Event *event);
};

#endif