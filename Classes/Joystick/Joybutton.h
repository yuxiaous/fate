//
//  Joybutton.hpp
//  fate
//
//  Created by yuxiao on 15/12/16.
//
//

#ifndef Joybutton_hpp
#define Joybutton_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class SneakyButton;
class SneakyButtonSkinnedBase;

class Joybutton : public Node
{
    typedef Node Super;
    
    Joybutton();
    virtual ~Joybutton();
    bool initWithSize(Size size);
    virtual void update(float delta) override;
    
public:
    static Joybutton *create(Size size);
    
    // setter
    CC_PROPERTY(bool, _enable, IsEnable);
    void setDefaultSprite(Sprite *aSprite);
    void setPressSprite(Sprite *aSprite);
    void setDisabledSprite(Sprite *aSprite);
    
    // getter
    CC_SYNTHESIZE_READONLY(bool, _value, Value);
    
private:
    SneakyButton *_button;
    SneakyButtonSkinnedBase * _buttonSkin;
};

#endif /* Joybutton_hpp */
