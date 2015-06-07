#ifndef __jsb_levelhelper_auto_h__
#define __jsb_levelhelper_auto_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_LHUserPropertyProtocol_class;
extern JSObject *jsb_LHUserPropertyProtocol_prototype;

bool js_jsb_levelhelper_auto_LHUserPropertyProtocol_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHUserPropertyProtocol_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHUserPropertyProtocol(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHUserPropertyProtocol_getClassName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHUserPropertyProtocol_setNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHUserPropertyProtocol_setPropertiesFromDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHUserPropertyProtocol_getNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHNodeProtocol_class;
extern JSObject *jsb_LHNodeProtocol_prototype;

bool js_jsb_levelhelper_auto_LHNodeProtocol_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHNodeProtocol_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHNodeProtocol(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isRopeJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_setUuid(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_loadTransformationInfoFromDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isUINode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isRevoluteJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_getUuid(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_setTags(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isJoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isLHWeldJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isShape(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isParallaxLayer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isDistanceJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isParallax(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_lateLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_loadUserPropertyWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_loadGenericInfoFromDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isWater(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isBackUINode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isGearJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isPulleyJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isWheelJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isB2WorldDirty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isCamera(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_getTags(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_getChildrenWithTags(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_getUserProperty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isGameWorldNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_containsTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isAsset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isPrismaticJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_markAsB2WorldDirty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isScene(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isGravityArea(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithUUID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_isBezier(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_loadChildrenFromDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_positionForNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_createLHNodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_LHGetNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeProtocol_LHGetNodeProtocol(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHScene_class;
extern JSObject *jsb_LHScene_prototype;

bool js_jsb_levelhelper_auto_LHScene_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHScene_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHScene(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHScene_setGlobalGravity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_getGlobalGravity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_setGameWorldRect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_getChildNodeWithName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_getGameWorldRect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_initWithContentOfFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_getGameWorldNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_tracedFixturesWithUUID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_getDesignResolutionSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_getDesignOffset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_assetInfoForFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_getUINode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_getCurrentDeviceSuffix(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_isScene(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_getBackUINode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_createWithContentOfFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_isLHScene(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHScene_LHScene(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHUINode_class;
extern JSObject *jsb_LHUINode_prototype;

bool js_jsb_levelhelper_auto_LHUINode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHUINode_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHUINode(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHUINode_isUINode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHUINode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHUINode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHUINode_isLHUINode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHUINode_LHUINode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHBackUINode_class;
extern JSObject *jsb_LHBackUINode_prototype;

bool js_jsb_levelhelper_auto_LHBackUINode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHBackUINode_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHBackUINode(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHBackUINode_isBackUINode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHBackUINode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHBackUINode_isLHBackUINode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHBackUINode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHBackUINode_LHBackUINode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHGameWorldNode_class;
extern JSObject *jsb_LHGameWorldNode_prototype;

bool js_jsb_levelhelper_auto_LHGameWorldNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHGameWorldNode_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHGameWorldNode(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHGameWorldNode_setGravity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGameWorldNode_isGameWorldNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGameWorldNode_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGameWorldNode_update(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGameWorldNode_setScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGameWorldNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGameWorldNode_getGravity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGameWorldNode_setPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGameWorldNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGameWorldNode_isLHGameWorldNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGameWorldNode_LHGameWorldNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHPhysicsProtocol_class;
extern JSObject *jsb_LHPhysicsProtocol_prototype;

bool js_jsb_levelhelper_auto_LHPhysicsProtocol_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHPhysicsProtocol_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHPhysicsProtocol(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_removeBody(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_visitPhysicsProtocol(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_updatePhysicsScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_loadPhysicsFromDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_updatePhysicsTransform(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_shouldRemoveBody(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_LHGetNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHNodeAnimationProtocol_class;
extern JSObject *jsb_LHNodeAnimationProtocol_prototype;

bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHNodeAnimationProtocol_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHNodeAnimationProtocol(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_createAnimationsFromDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getActiveAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getAnimationWithName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getAnimations(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_setActiveAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_visitActiveAnimation(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHSprite_class;
extern JSObject *jsb_LHSprite_prototype;

bool js_jsb_levelhelper_auto_LHSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHSprite_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHSprite(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHSprite_initWithSpriteName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHSprite_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHSprite_isSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHSprite_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHSprite_initWithFilename(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHSprite_createWithFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHSprite_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHSprite_isLHSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHSprite_createWithSpriteName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHSprite_LHSprite(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHCamera_class;
extern JSObject *jsb_LHCamera_prototype;

bool js_jsb_levelhelper_auto_LHCamera_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHCamera_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHCamera(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHCamera_resetLookAt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_setSmoothMovement(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_setRestrictedToGameWorld(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_lookAtPositionInSeconds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_setUsePinchOrScrollWheelToZoom(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_zoomToValueInSeconds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_setPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_usePinchOrScrollWheelToZoom(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_resetLookAtInSeconds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_followedNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_setActive(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_getImportantAreaUnit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_setZoomValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_lookAtNodeInSeconds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_getZoomValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_setLockY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_setLockX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_getSmoothMovement(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_getOffsetUnit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_isLookingAt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_followNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_isActive(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_isCamera(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_restrictedToGameWorld(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_setOffsetUnit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_setImportantAreaUnit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_getLockY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_getLockX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_zoomByValueInSeconds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_isLHCamera(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHCamera_LHCamera(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHAsset_class;
extern JSObject *jsb_LHAsset_prototype;

bool js_jsb_levelhelper_auto_LHAsset_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHAsset_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHAsset(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHAsset_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAsset_initWithName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAsset_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAsset_isAsset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAsset_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAsset_createWithName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAsset_isLHAsset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAsset_LHAsset(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHParallax_class;
extern JSObject *jsb_LHParallax_prototype;

bool js_jsb_levelhelper_auto_LHParallax_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHParallax_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHParallax(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHParallax_followedNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallax_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallax_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallax_followNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallax_isParallax(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallax_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallax_isLHParallax(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallax_LHParallax(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHParallaxLayer_class;
extern JSObject *jsb_LHParallaxLayer_prototype;

bool js_jsb_levelhelper_auto_LHParallaxLayer_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHParallaxLayer_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHParallaxLayer(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHParallaxLayer_getInitialPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallaxLayer_getRatioX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallaxLayer_getRatioY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallaxLayer_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallaxLayer_isParallaxLayer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallaxLayer_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallaxLayer_isLHParallaxLayer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHParallaxLayer_LHParallaxLayer(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHAnimation_class;
extern JSObject *jsb_LHAnimation_prototype;

bool js_jsb_levelhelper_auto_LHAnimation_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHAnimation_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHAnimation(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHAnimation_totalTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_node(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_repetitions(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_name(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_currentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_restart(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_currentFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_setActive(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_animating(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_setAnimating(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_setCurrentFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_isActive(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHAnimation_LHAnimation(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHGravityArea_class;
extern JSObject *jsb_LHGravityArea_prototype;

bool js_jsb_levelhelper_auto_LHGravityArea_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHGravityArea_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHGravityArea(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHGravityArea_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGravityArea_getForce(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGravityArea_isRadial(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGravityArea_getDirection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGravityArea_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGravityArea_isGravityArea(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGravityArea_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGravityArea_isLHGravityArea(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHGravityArea_LHGravityArea(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHJointsProtocol_class;
extern JSObject *jsb_LHJointsProtocol_prototype;

bool js_jsb_levelhelper_auto_LHJointsProtocol_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHJointsProtocol_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHJointsProtocol(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHJointsProtocol_getNodeA(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHJointsProtocol_getNodeB(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHJointsProtocol_findConnectedNodes(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHJointsProtocol_removeJoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHJointsProtocol_shouldRemoveJoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHJointsProtocol_getLocalAnchorA(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHJointsProtocol_getCollideConnected(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHJointsProtocol_getLocalAnchorB(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHJointsProtocol_getAnchorB(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHJointsProtocol_getAnchorA(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHJointsProtocol_loadJointInfoFromDictionary(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHRopeJointNode_class;
extern JSObject *jsb_LHRopeJointNode_prototype;

bool js_jsb_levelhelper_auto_LHRopeJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHRopeJointNode_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHRopeJointNode(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHRopeJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRopeJointNode_isRopeJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRopeJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRopeJointNode_canBeCut(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRopeJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRopeJointNode_cutWithLineFromPointA(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRopeJointNode_isLHRopeJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRopeJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRopeJointNode_LHRopeJointNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHRevoluteJointNode_class;
extern JSObject *jsb_LHRevoluteJointNode_prototype;

bool js_jsb_levelhelper_auto_LHRevoluteJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHRevoluteJointNode_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHRevoluteJointNode(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getUpperAngle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getMaxMotorTorque(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getEnableLimit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getLowerAngle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getMotorSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_isRevoluteJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getEnableMotor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_isLHRevoluteJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_LHRevoluteJointNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHDistanceJointNode_class;
extern JSObject *jsb_LHDistanceJointNode_prototype;

bool js_jsb_levelhelper_auto_LHDistanceJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHDistanceJointNode_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHDistanceJointNode(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHDistanceJointNode_getFrequency(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHDistanceJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHDistanceJointNode_getDamping(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHDistanceJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHDistanceJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHDistanceJointNode_isDistanceJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHDistanceJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHDistanceJointNode_isLHDistanceJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHDistanceJointNode_LHDistanceJointNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHWeldJointNode_class;
extern JSObject *jsb_LHWeldJointNode_prototype;

bool js_jsb_levelhelper_auto_LHWeldJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHWeldJointNode_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHWeldJointNode(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHWeldJointNode_getFrequency(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWeldJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWeldJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWeldJointNode_getDampingRatio(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWeldJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWeldJointNode_isWeldJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWeldJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWeldJointNode_isLHWeldJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWeldJointNode_LHWeldJointNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHPrismaticJointNode_class;
extern JSObject *jsb_LHPrismaticJointNode_prototype;

bool js_jsb_levelhelper_auto_LHPrismaticJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHPrismaticJointNode_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHPrismaticJointNode(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getUpperTranslation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getAxis(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getMaxMotorForce(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getLowerTranslation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getEnableLimit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_isPrismaticJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getMotorSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getEnableMotor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_isLHPrismaticJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_LHPrismaticJointNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHWheelJointNode_class;
extern JSObject *jsb_LHWheelJointNode_prototype;

bool js_jsb_levelhelper_auto_LHWheelJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHWheelJointNode_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHWheelJointNode(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHWheelJointNode_getFrequency(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_getAxis(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_getMaxMotorTorque(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_getDampingRatio(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_getMotorSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_isWheelJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_getEnableMotor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_isLHWheelJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHWheelJointNode_LHWheelJointNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_LHPulleyJointNode_class;
extern JSObject *jsb_LHPulleyJointNode_prototype;

bool js_jsb_levelhelper_auto_LHPulleyJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_levelhelper_auto_LHPulleyJointNode_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_levelhelper_auto_LHPulleyJointNode(JSContext *cx, JS::HandleObject global);
void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_levelhelper_auto_LHPulleyJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPulleyJointNode_isPulleyJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPulleyJointNode_getGroundAnchorA(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPulleyJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPulleyJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPulleyJointNode_getGroundAnchorB(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPulleyJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPulleyJointNode_isLHPulleyJointNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_levelhelper_auto_LHPulleyJointNode_LHPulleyJointNode(JSContext *cx, uint32_t argc, jsval *vp);
#endif

