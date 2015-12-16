//
//  Joystick.hpp
//  fate
//
//  Created by yuxiao on 15/12/16.
//
//

#ifndef Joystick_hpp
#define Joystick_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class SneakyJoystick;
class SneakyJoystickSkinnedBase;

class Joystick : public Node
{
    typedef Node Super;
    
    Joystick();
    virtual ~Joystick();
    bool initWithSize(Size joystickSize, Size thumbSize);
    virtual void update(float delta) override;
    
public:
    static Joystick *create(Size joystickSize, Size thumbSize);
    
    // setter
    CC_PROPERTY(bool, _enable, IsEnable);
    void setBackgroundSprite(Sprite *aSprite, Sprite *bSprite = nullptr);
    void setThumbSprite(Sprite *aSprite, Sprite *bSprite = nullptr);
    void setTouchArea(const Rect &area);
    
    // getter
    CC_SYNTHESIZE_READONLY(Vec2, _velocity, Velocity);
    
private:
    SneakyJoystick *_joystick;
    SneakyJoystickSkinnedBase *_joystickBase;
};

#endif /* Joystick_hpp */
