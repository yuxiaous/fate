#include "SneakyButton.h"

void SneakyButton::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(SneakyButton::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SneakyButton::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SneakyButton::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(SneakyButton::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _touchListenerOneByOne = listener;
}

void SneakyButton::onExit()
{
    Node::onExit();
    
    _eventDispatcher->removeEventListener(_touchListenerOneByOne);
}

SneakyButton *SneakyButton::create(Size size)
{
    SneakyButton *ret = new SneakyButton();
    if(ret && ret->initWithSize(size)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool SneakyButton::initWithSize(Size size)
{
	bool pRet = false;
	//if(CCSprite::init()){
		
        _enable = true;
		_active = false;
		_value = 0;
		_isHoldable = 0;
		_isToggleable = 0;
		_radius = 32.0f;
		_rateLimit = 1.0f/120.0f;
		
		setPosition(size.width/2, size.height/2); //not sure about this
        setContentSize(size);
    
		pRet = true;
	//}
	return pRet;
}

void SneakyButton::limiter(float delta)
{
	_value = 0;
	this->unschedule(schedule_selector(SneakyButton::limiter));
	_active = false;
}

void SneakyButton::setRadius(float r)
{
	_radius = r;
	_radiusSq = r*r;
}

void SneakyButton::setIsEnable(bool var)
{
    _enable = var;
    
    if(_enable == false) {
        onTouchEnded(nullptr, nullptr);
    }
}

bool SneakyButton::getIsEnable()
{
    return _enable;
}

bool SneakyButton::onTouchBegan(Touch *touch, Event *event)
{
    if (!_enable) return false;
    if (_active) return false;
    
    Vec2 location = touch->getLocation();
    location = this->convertToNodeSpace(location);
    
    //Do a fast rect check before doing a circle hit check:
    if(location.x >= -_radius && location.x <= _radius &&
       location.y >= -_radius && location.y <= _radius){
        float dSq = location.x*location.x + location.y*location.y;
        if(_radiusSq > dSq){
            _active = true;
            if (!_isHoldable && !_isToggleable){
                _value = 1;
                this->schedule(schedule_selector(SneakyButton::limiter), _rateLimit);
            }
            else if (_isHoldable) {
                _value = 1;
            }
            else if (_isToggleable) {
                _value = !_value;
            }
            return true;
        }
    }
    return false;
}

void SneakyButton::onTouchMoved(Touch *touch, Event *event)
{
    if (!_enable) return;
    if (!_active) return;
    
    Vec2 location = touch->getLocation();
    location = this->convertToNodeSpace(location);
    
    //Do a fast rect check before doing a circle hit check:
    if(location.x >= -_radius && location.x <= _radius &&
       location.y >= -_radius && location.y <= _radius){
        float dSq = location.x*location.x + location.y*location.y;
        if(_radiusSq > dSq){
            if (_isHoldable) {
                _value = 1;
            }
        }
        else {
            if (_isHoldable) {
                _value = 0;
                _active = false;
            }
        }
    }
}

void SneakyButton::onTouchEnded(Touch *touch, Event *event)
{
	if (!_active) return;
	if (_isHoldable) _value = 0;
	if (_isHoldable || _isToggleable) _active = false;
}

void SneakyButton::onTouchCancelled(Touch *touch, Event *event)
{
	this->onTouchEnded(touch, event);
}
