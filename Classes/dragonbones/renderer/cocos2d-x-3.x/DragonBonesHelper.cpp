//
//  DragonBonesHelper.cpp
//  crows
//
//  Created by yuxiao on 15/2/5.
//
//

#include "DragonBonesHelper.h"
USING_NS_DB;

#define SKELETON_PATH "armatures/"
#define SKELETON_FILE_NAME "skeleton.xml"
#define TEXTURE_FILE_NAME "texture.xml"

bool DragonBonesHelper::addDragonBones(const std::string &name)
{
    bool loadDataFin  = loadDragonBonesData(name);
    bool loadAtlaSFin = loadTextureAtlas(name);

    return loadDataFin && loadAtlaSFin;
}

void DragonBonesHelper::removeDragonBones(const std::string &name)
{
    removeDragonBonesData(name);
    removeTextureAtlas(name);
}

DBCCArmatureNode *DragonBonesHelper::buildArmatureNode(const std::string &name)
{
    addDragonBones(name);
    
    DBCCFactory *factory = DBCCFactory::getInstance();
    DBCCArmature *armature = factory->buildArmature(name);
    DBCCArmatureNode *node = DBCCArmatureNode::createWithWorldClock(armature);
    return node;
}

bool DragonBonesHelper::loadDragonBonesData(const std::string &name)
{
    DBCCFactory *factory = DBCCFactory::getInstance();
    auto ret = factory->getDragonBonesData(name);
    if(ret == nullptr) {
        std::string path = SKELETON_PATH + name + "/";
        ret = factory->loadDragonBonesData(path + SKELETON_FILE_NAME, name);
    }
    return ret != nullptr;
}

void DragonBonesHelper::removeDragonBonesData(const std::string &name)
{
    DBCCFactory *factory = DBCCFactory::getInstance();
    factory->removeDragonBonesData(name);
}

bool DragonBonesHelper::loadTextureAtlas(const std::string &name)
{
    DBCCFactory *factory = DBCCFactory::getInstance();
    auto ret = factory->getTextureAtlas(name);
    if(ret == nullptr) {
        std::string path = SKELETON_PATH + name + "/";
        ret = factory->loadTextureAtlas(path + TEXTURE_FILE_NAME, name);
    }
    return ret != nullptr;
}

void DragonBonesHelper::removeTextureAtlas(const std::string &name)
{
    DBCCFactory *factory = DBCCFactory::getInstance();
    factory->removeTextureAtlas(name);
}

void DragonBonesHelper::advanceWorldClock(float dt)
{
    WorldClock::getInstance()->advanceTime(dt);
}
