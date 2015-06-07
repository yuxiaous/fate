#include "SneakyJoystick.h"

using namespace cocos2d;

#define SJ_PI 3.14159265359f
#define SJ_PI_X_2 6.28318530718f
#define SJ_RAD2DEG 180.0f/SJ_PI
#define SJ_DEG2RAD SJ_PI/180.0f

void SneakyJoystick::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(SneakyJoystick::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SneakyJoystick::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SneakyJoystick::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(SneakyJoystick::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _touchListenerOneByOne = listener;
}

void SneakyJoystick::onExit()
{
    Node::onExit();
    _eventDispatcher->removeEventListener(_touchListenerOneByOne);
}

SneakyJoystick *SneakyJoystick::create(Size joystickSize, Size thumbSize)
{
    SneakyJoystick *ret = new SneakyJoystick();
    if(ret && ret->initWithSize(joystickSize, thumbSize)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool SneakyJoystick::initWithSize(Size joystickSize, Size thumbSize)
{
    _enable = true;
    _stickPosition = Vec2::ZERO;
    _degrees = 0.0f;
    _velocity = Vec2::ZERO;
    _autoCenter = true;
    _isDPad = false;
    _hasDeadzone = false;
    _numberOfDirections = 4;
    _isConstantVelocity = false;
    _active = false;
    
    this->setJoystickRadius(joystickSize.width/2);
    this->setThumbRadius(thumbSize.width/2);
    this->setDeadRadius(0.0f);
    
	return true;
}

/*
static float round(float r) {
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}
*/

void SneakyJoystick::updateVelocity(Vec2 point)
{
    // Calculate distance and angle from the center.
	float dx = point.x;
	float dy = point.y;
	float dSq = dx * dx + dy * dy;
	
	if(dSq <= _deadRadiusSq){
		_velocity = Vec2::ZERO;
		_degrees = 0.0f;
        _stickPosition = Vec2::ZERO;
		return;
	}

	float angle = atan2f(dy, dx); // in radians
	if(angle < 0){
		angle += SJ_PI_X_2;
	}
	
	if(_isDPad){
		float anglePerSector = 360.0f / _numberOfDirections * SJ_DEG2RAD;
		angle = round(angle/anglePerSector) * anglePerSector;
	}
	
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	
	// NOTE: Velocity goes from -1.0 to 1.0.
	if (dSq > _joystickRadiusSq || _isDPad) {
		dx = cosAngle * joystickRadius;
		dy = sinAngle * joystickRadius;
	}
	
    if(_isConstantVelocity) {
        _velocity = Vec2(cosAngle, sinAngle);
    }
    else {
        _velocity = Vec2(dx/joystickRadius, dy/joystickRadius);
    }
	_degrees = angle * SJ_RAD2DEG;
	
	// Update the thumb's position
    _stickPosition = Vec2(dx, dy);
}

void SneakyJoystick::setIsDPad(bool b)
{
	_isDPad = b;
	if(_isDPad){
		_hasDeadzone = true;
		this->setDeadRadius(10.0f);
	}
}

void SneakyJoystick::setJoystickRadius(float r)
{
	joystickRadius = r;
	_joystickRadiusSq = r*r;
}

void SneakyJoystick::setThumbRadius(float r)
{
	thumbRadius = r;
	_thumbRadiusSq = r*r;
}

void SneakyJoystick::setDeadRadius(float r)
{
	deadRadius = r;
	_deadRadiusSq = r*r;
}


void SneakyJoystick::setIsEnable(bool var)
{
    _enable = var;
    
    if(_enable == false) {
        onTouchEnded(nullptr, nullptr);
    }
}

bool SneakyJoystick::getIsEnable()
{
    return _enable;
}

bool SneakyJoystick::onTouchBegan(Touch *touch, Event *event)
{
    if (!_enable) return false;
    
    Vec2 location = touch->getLocation();
	location = this->convertToNodeSpace(location);
    
    //Do a fast rect check before doing a circle hit check:
    if(_touchArea.containsPoint(location)) {
        _active = true;
        this->updateVelocity(location);
        return true;
    }
    else if(location.x >= -joystickRadius && location.x <= joystickRadius &&
            location.y >= -joystickRadius && location.y <= joystickRadius) {
        float dSq = location.x*location.x + location.y*location.y;
        if(_joystickRadiusSq > dSq){
            _active = true;
            this->updateVelocity(location);
            return true;
        }
    }
    return false;
}

void SneakyJoystick::onTouchMoved(Touch *touch, Event *event)
{
    if (!_enable) return;
    if (!_active) return;
    
    Vec2 location = touch->getLocation();
	location = this->convertToNodeSpace(location);
	this->updateVelocity(location);
}

void SneakyJoystick::onTouchEnded(Touch *touch, Event *event)
{
    if (!_active) return;
    
	Vec2 location = Vec2::ZERO;
	if(!_autoCenter && touch){
        Vec2 location = touch->getLocation();
		location = this->convertToNodeSpace(location);
	}
    _active = false;
	this->updateVelocity(location);
}

void SneakyJoystick::onTouchCancelled(Touch *touch, Event *event)
{
	this->onTouchEnded(touch, event);
}



