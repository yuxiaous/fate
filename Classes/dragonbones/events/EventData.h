﻿#ifndef EVENTS_EVENT_DATA_H
#define EVENTS_EVENT_DATA_H

#include "../DragonBones.h"

NAME_SPACE_DRAGON_BONES_BEGIN

class Armature;
class Bone;
class AnimationState;
class Frame;
class FrameLabelData;

class EventData
{
public:
    static const std::string Z_ORDER_UPDATED;
    static const std::string ANIMATION_FRAME_EVENT;
    static const std::string BONE_FRAME_EVENT;
    static const std::string SOUND;
    static const std::string FADE_IN;
    static const std::string FADE_OUT;
    static const std::string START;
    static const std::string COMPLETE;
    static const std::string LOOP_COMPLETE;
    static const std::string FADE_IN_COMPLETE;
    static const std::string FADE_OUT_COMPLETE;
    
    static const std::string _ERROR;
    
    enum class EventType
    {
        Z_ORDER_UPDATED,
        ANIMATION_FRAME_EVENT,
        BONE_FRAME_EVENT,
        SOUND,
        FADE_IN, FADE_OUT, START, COMPLETE, LOOP_COMPLETE, FADE_IN_COMPLETE, FADE_OUT_COMPLETE,
        _ERROR
    };
    
    static const std::string& typeToString(EventType eventType);

    static EventData* borrowObject(EventType eventType);
    static void returnObject(EventData *eventData);
    static void clearObjects();

private:
    static std::vector<EventData*> _pool;
    
public:
    std::string frameLabel;
    std::string sound;
    
    Armature *armature;
    Bone *bone;
    AnimationState *animationState;
    Frame *frame;
    FrameLabelData *frameLabelData;
    
    const std::string &getFrameLabel() const { return frameLabel; }
    const std::string &getSound() const { return sound; }
    const Armature *getArmature() const { return armature; }
    const Bone *getBone() const { return bone; }
    const AnimationState *getAnimationState() const { return animationState; }
    const Frame *getFrame() const { return frame; }
    const FrameLabelData *getFrameLabelData();
    
    
private:
    EventType _type;
    
public:
    EventType getType() const;
    
    const std::string& getStringType() const;
    
public:
    EventData();
    EventData(EventType type, Armature *armatureTarget);
    virtual ~EventData();
    void clear();
    void copy(const EventData &copyData);

private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(EventData);
};


class FrameLabelData
{
public:
    std::string name;
    std::map<std::string, std::string> attr;
    
    inline int getIntAttr(const std::string &attrName) const
    {
        return atoi(attr.at(attrName).c_str());
    }
    inline double getDoubleAttr(const std::string &attrName) const
    {
        return atof(attr.at(attrName).c_str());
    }
    inline const std::string &getStringAttr(const std::string &attrName) const
    {
        return attr.at(attrName);
    }
    inline const char *getCStringAttr(const std::string &attrName) const
    {
        return attr.at(attrName).c_str();
    }
    
    void parseWithFrameLabel(const std::string &frameLabel);
};


NAME_SPACE_DRAGON_BONES_END
#endif  // EVENTS_EVENT_DATA_H
