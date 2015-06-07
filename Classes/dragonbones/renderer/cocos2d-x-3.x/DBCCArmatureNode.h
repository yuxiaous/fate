#ifndef DBCC_ARMATURE_NODE_H
#define DBCC_ARMATURE_NODE_H

#include "dbccMacro.h"
#include "DragonBonesHeaders.h"
#include "cocos2d.h"
#include "DBCCSlot.h"
#include "DBCCArmature.h"

#if (DRAGON_BONES_ENABLE_LUA == 1)
#include "CCLuaValue.h"
#endif // DRAGON_BONES_ENABLE_LUA



NAME_SPACE_DRAGON_BONES_BEGIN
class DBCCArmatureNode : public cocos2d::Node, public IAnimatable
{
public:
//    virtual DBCCSlot* getCCSlot(const std::string &slotName) const { return _armature->getCCSlot(slotName); };
	virtual cocos2d::Node* getCCDisplay() const { return _armature->getCCDisplay(); };
	virtual cocos2d::EventDispatcher* getCCEventDispatcher() const { return _armature->getCCEventDispatcher(); };
    virtual cocos2d::Rect getBoundingBox() const;
    virtual cocos2d::Rect getBoundingBox(const std::string &slotName) const;
    
    
    virtual void registerFrameEventHandler(const std::function<void(DBCCArmatureNode*, char*)>& callback);
    virtual void registerMovementEventHandler(const std::function<void(DBCCArmatureNode*, char*)> callback);
    virtual void unregisterFrameEventHandler();
    virtual void unregisterMovementEventHandler();


public:
    // create DBCCArmatureNode without WorldClock
    static DBCCArmatureNode* create(DBCCArmature *armature);
    /**
     * create DDCCArmatureNode with WorldClock
     * @param armature
     * @param clock if null, use WorldClock::getInstance()
     * @return 
     */
    static DBCCArmatureNode* createWithWorldClock(DBCCArmature *armature, WorldClock *clock = nullptr);
    virtual bool initWithDBCCArmature(DBCCArmature *armature, WorldClock *clock);
    
    DBCCArmatureNode();
    virtual ~DBCCArmatureNode();

//	DBCCArmature* getArmature() const { return _armature; };
//	Animation* getAnimation() const { return _armature->getAnimation(); };
    bool gotoAndPlay(const std::string &animationName);

	virtual void update(float dt) override;
    virtual void advanceTime(float dt) override;

protected:
    DBCCArmature *_armature;
    WorldClock *_clock;
    
private:
	int _frameEventHandler;
	int _movementEventHandler;
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(DBCCArmatureNode);
    
    std::function<void(DBCCArmatureNode*, char*)> _frameEventCallback;
    std::function<void(DBCCArmatureNode*, char*)> _movementEventCallback;
};
NAME_SPACE_DRAGON_BONES_END
#endif  // DBCC_ARMATURE_NODE_H
