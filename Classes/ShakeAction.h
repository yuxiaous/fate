/**
 desc:让指定控件抖动
 一个CCNode同时执行多个CCShake动作,或者一个CCShake没有完又执行一个CCShake的话就会出现问题,会出现偏移的现象!
 
 解决方案:
 1).不要同时执行多个CCShake动作.
 2.自己外部记录这个CCNode的位置,执行完成后手动setPosition();
 */
#ifndef __SHAKE_H__
#define __SHAKE_H__

#include "cocos2d.h"
#include "CCActionInterval.h"
USING_NS_CC;

/**
 * 按指定频度范围内抖动[-strength_x,strength_x][-strength_y, strength_y]
 */
class Shake : public ActionInterval
{
public:
    Shake();
    
    // Create the action with a time and a strength (same in x and y)
    static Shake* create(float d, float strength );
    // Create the action with a time and strengths (different in x and y)
    static Shake* createWithStrength(float d, float strength_x, float strength_y );
    bool initWithDuration(float d, float strength_x, float strength_y );
    
protected:
    
    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);
    virtual void stop(void);
    
    
    // Initial position of the shaked node
    float m_initial_x, m_initial_y;
    // Strength of the action
    float m_strength_x, m_strength_y;
};


/**
 * 线性抖动(剩余时间越短，抖动范围越小)
 */
class FallOffShake : public Shake
{
public:
    FallOffShake();
    
    // Create the action with a time and a strength (same in x and y)
    static FallOffShake* create(float d, float strength );
    // Create the action with a time and strengths (different in x and y)
    static FallOffShake* createWithStrength(float d, float strength_x, float strength_y );
    
protected:
    virtual void update(float time);
};

#endif //__SHAKE_H__

