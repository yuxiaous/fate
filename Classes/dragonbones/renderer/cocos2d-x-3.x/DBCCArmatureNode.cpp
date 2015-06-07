#include "dbccMacro.h"
#include "DBCCArmatureNode.h"
#include "DBCCEventDispatcher.h"


#if (DRAGON_BONES_ENABLE_LUA == 1)
#include "CCLuaEngine.h"
#endif // DRAGON_BONES_ENABLE_LUA


NAME_SPACE_DRAGON_BONES_BEGIN

DBCCArmatureNode* DBCCArmatureNode::create(DBCCArmature *armature)
{
    DBCCArmatureNode *ret = new DBCCArmatureNode();
    
    if (ret && ret->initWithDBCCArmature(armature, nullptr))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

DBCCArmatureNode* DBCCArmatureNode::createWithWorldClock(DBCCArmature *armature, WorldClock *clock)
{
    DBCCArmatureNode *ret = new DBCCArmatureNode();
    if (!clock)
        clock = WorldClock::getInstance();

    if (ret && ret->initWithDBCCArmature(armature, clock))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool DBCCArmatureNode::initWithDBCCArmature(DBCCArmature *armature, WorldClock *clock)
{
    if (armature != nullptr)
    {
        _armature = armature;
        _clock = clock;
        if (clock)
        {
            clock->add(this);
        }else
        {
            scheduleUpdate();
        }
        addChild(armature->getCCDisplay());
        setCascadeOpacityEnabled(true);
        setCascadeColorEnabled(true);
        return true;
    }

	return false;
}


DBCCArmatureNode::DBCCArmatureNode()
    :_armature(nullptr)
    ,_clock(nullptr)
	,_frameEventHandler(0)
	,_movementEventHandler(0)
{
}
DBCCArmatureNode::~DBCCArmatureNode()
{
    unregisterFrameEventHandler();
    unregisterMovementEventHandler();

    if (_clock)
    {
        _clock->remove(this);
        _clock = nullptr;
    } else
    {
        unscheduleUpdate();
    }

    if (_armature)
    {
        delete _armature;
        _armature = nullptr;
    }
}

cocos2d::Rect DBCCArmatureNode::getBoundingBox() const
{
    return _armature->getCCBoundingBox();
}

cocos2d::Rect DBCCArmatureNode::getBoundingBox(const std::string &slotName) const
{
    DBCCSlot *slot = _armature->getCCSlot(slotName);
    if(slot) {
        cocos2d::Rect box = slot->getCCBoundingBox();
        return box;
    }
    return cocos2d::Rect::ZERO;
}

void DBCCArmatureNode::update(float dt)
{
    DBASSERT(!_clock, "can not has clock when update!");
    advanceTime(dt);
}

void DBCCArmatureNode::advanceTime(float dt)
{
    retain();
    _armature->advanceTime(dt);
    release();
}

bool DBCCArmatureNode::gotoAndPlay(const std::string &animationName)
{
    auto animation = _armature->getAnimation();
    if(animation) {
        if(animation->hasAnimation(animationName)) {
            auto ret = animation->gotoAndPlay(animationName);
            return ret != nullptr;
        }
    }
    return false;
}

void DBCCArmatureNode::registerFrameEventHandler(const std::function<void(DBCCArmatureNode*, char*)>& callback)
{
    unregisterFrameEventHandler();
    _frameEventCallback = callback;
    
    auto f = [this](cocos2d::EventCustom *event)
    {
        EventData *eventData = (EventData*)(event->getUserData());
        _frameEventCallback(this, (char*)eventData->getFrameLabel().c_str());
    };
    
    auto dispatcher = getCCEventDispatcher();
//    dispatcher->addCustomEventListener(EventData::ANIMATION_FRAME_EVENT, f);
    dispatcher->addCustomEventListener(EventData::BONE_FRAME_EVENT, f);
}

void DBCCArmatureNode::registerMovementEventHandler(const std::function<void(DBCCArmatureNode*, char*)> callback)
{
    unregisterMovementEventHandler();
    _movementEventCallback = callback;
    
    auto f = [this](cocos2d::EventCustom *event)
    {
        EventData* eventData = (EventData*)(event->getUserData());
        _movementEventCallback(this, (char*)eventData->getStringType().c_str());
    };
    
    auto dispatcher = getCCEventDispatcher();
    dispatcher->addCustomEventListener(EventData::COMPLETE, f);
    dispatcher->addCustomEventListener(EventData::FADE_IN_COMPLETE, f);
//    dispatcher->addCustomEventListener(EventData::LOOP_COMPLETE, f);
}

void DBCCArmatureNode::unregisterFrameEventHandler()
{
    if (_frameEventCallback != nullptr)
    {
        auto dispatcher = getCCEventDispatcher();
        dispatcher->removeCustomEventListeners(EventData::ANIMATION_FRAME_EVENT);
        dispatcher->removeCustomEventListeners(EventData::BONE_FRAME_EVENT);
		_frameEventCallback = nullptr;
    }
}

void DBCCArmatureNode::unregisterMovementEventHandler()
{
	if (_movementEventCallback != nullptr)
    {
        auto dispatcher = getCCEventDispatcher();
        dispatcher->removeCustomEventListeners(EventData::COMPLETE);
        dispatcher->removeCustomEventListeners(EventData::LOOP_COMPLETE);
		_movementEventCallback = nullptr;
    }
}



NAME_SPACE_DRAGON_BONES_END
