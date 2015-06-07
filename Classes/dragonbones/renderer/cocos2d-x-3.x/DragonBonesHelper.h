//
//  DragonBonesHelper.h
//  crows
//
//  Created by yuxiao on 15/2/5.
//
//

#ifndef __crows__DragonBonesHelper__
#define __crows__DragonBonesHelper__

#include "cocos2d.h"
#include "DragonBonesHeaders.h"
#include "DBCCRenderHeaders.h"

class DragonBonesHelper
{
public:
    static bool addDragonBones(const std::string &name);
    static void removeDragonBones(const std::string &name);
    
    static dragonBones::DBCCArmatureNode *buildArmatureNode(const std::string &name);
    
    static void advanceWorldClock(float dt);
    
private:
    static bool loadDragonBonesData(const std::string &name);
    static void removeDragonBonesData(const std::string &name);
    
    static bool loadTextureAtlas(const std::string &name);
    static void removeTextureAtlas(const std::string &name);
};

#endif /* defined(__crows__DragonBonesHelper__) */
