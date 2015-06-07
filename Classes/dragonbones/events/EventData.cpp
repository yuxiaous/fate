#include "EventData.h"

NAME_SPACE_DRAGON_BONES_BEGIN

const std::string EventData::Z_ORDER_UPDATED = "zorderUpdate";
const std::string EventData::ANIMATION_FRAME_EVENT = "animationFrameEvent";
const std::string EventData::BONE_FRAME_EVENT = "boneFrameEvent";
const std::string EventData::SOUND = "sound";
const std::string EventData::FADE_IN = "fadeIn";
const std::string EventData::FADE_OUT = "fadeOut";
const std::string EventData::START = "start";
const std::string EventData::COMPLETE = "complete";
const std::string EventData::LOOP_COMPLETE = "loopComplete";
const std::string EventData::FADE_IN_COMPLETE = "fadeInComplete";
const std::string EventData::FADE_OUT_COMPLETE = "fadeOutComplete";

const std::string EventData::_ERROR = "error";

const std::string& EventData::typeToString(EventData::EventType eventType)
{
    switch (eventType)
    {
        case EventType::Z_ORDER_UPDATED:
            return Z_ORDER_UPDATED;
            
        case EventType::ANIMATION_FRAME_EVENT:
            return ANIMATION_FRAME_EVENT;
            
        case EventType::BONE_FRAME_EVENT:
            return BONE_FRAME_EVENT;
            
        case EventType::SOUND:
            return SOUND;
            
        case EventType::FADE_IN:
            return FADE_IN;
            
        case EventType::FADE_OUT:
            return FADE_OUT;
            
        case EventType::START:
            return START;
            
        case EventType::COMPLETE:
            return COMPLETE;
            
        case EventType::LOOP_COMPLETE:
            return LOOP_COMPLETE;
            
        case EventType::FADE_IN_COMPLETE:
            return FADE_IN_COMPLETE;
            
        case EventType::FADE_OUT_COMPLETE:
            return FADE_OUT_COMPLETE;
            
        default:
            break;
    }
    
    // throw
    return _ERROR;
}

std::vector<EventData*> EventData::_pool;

EventData* EventData::borrowObject(EventType eventType)
{
    if (_pool.empty())
    {
        return new EventData(eventType, nullptr);
    }

    EventData *eventData = _pool.back();
    eventData->_type = eventType;
    _pool.pop_back();
    return eventData;
}

void EventData::returnObject(EventData *eventData)
{
    auto iterator = std::find(_pool.cbegin(), _pool.cend(), eventData);

    if (iterator == _pool.end())
    {
        _pool.push_back(eventData);
    }

    eventData->clear();
}

void EventData::clearObjects()
{
    for (size_t i = 0, l = _pool.size(); i < l; ++i)
    {
        _pool[i]->clear();
        delete _pool[i];
    }

    _pool.clear();
}

EventData::EventType EventData::getType() const
{
    return _type;
}

const std::string& EventData::getStringType() const
{
    return typeToString(_type);
}

EventData::EventData()
{
    _type = EventType::_ERROR;
    armature = nullptr;
    bone = nullptr;
    animationState = nullptr;
    frame = nullptr;
    frameLabelData = nullptr;
}
EventData::EventData(EventType type, Armature *armatureTarget)
{
    _type = type;
    armature = armatureTarget;
    bone = nullptr;
    animationState = nullptr;
    frame = nullptr;
    frameLabelData = nullptr;
}
EventData::~EventData()
{
    clear();
}
void EventData::clear()
{
    armature = nullptr;
    bone = nullptr;
    animationState = nullptr;
    frame = nullptr;

    frameLabel.clear();
    sound.clear();
    
    if(frameLabelData) {
        delete frameLabelData;
        frameLabelData = nullptr;
    }
}

void EventData::copy(const EventData &copyData)
{
    _type = copyData._type;
    frameLabel = copyData.frameLabel;
    sound = copyData.sound;
    armature = copyData.armature;
    bone = copyData.bone;
    animationState = copyData.animationState;
    frame = copyData.frame;
}

const FrameLabelData *EventData::getFrameLabelData()
{
    if(frameLabelData == nullptr) {
        frameLabelData = new FrameLabelData();
    }
    frameLabelData->parseWithFrameLabel(this->frameLabel);
    return frameLabelData;
}

void FrameLabelData::parseWithFrameLabel(const std::string &frameLabel)
{
    // split "?"
    size_t pos = frameLabel.find("?");
    this->name = frameLabel.substr(0, pos);
    
    if(pos != std::string::npos) {
        std::vector<std::string> attrList;
        size_t pre = pos + 1;
        
        // split "&"
        while ((pos = frameLabel.find("&", pre)) != std::string::npos) {
            size_t len = pos - pre;
            if(len > 0) {
                attrList.push_back(frameLabel.substr(pre, len));
            }
            pre = pos + 1;
        }
        std::string endstr = frameLabel.substr(pre);
        if(!endstr.empty())
            attrList.push_back(endstr);
        
        // split "="
        for(std::vector<std::string>::iterator it = attrList.begin(); it != attrList.end(); ++it) {
            const std::string &attrLabel = *it;
            
            pos = attrLabel.find("=");
            std::string attrKey = attrLabel.substr(0, pos);
            std::string attrValue = attrLabel.substr(pos + 1);
            this->attr.insert(std::make_pair(attrKey, attrValue));
        }
    }
}

NAME_SPACE_DRAGON_BONES_END