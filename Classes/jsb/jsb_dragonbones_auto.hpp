#ifndef __jsb_dragonbones_auto_h__
#define __jsb_dragonbones_auto_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_dragonBones_DBCCArmatureNode_class;
extern JSObject *jsb_dragonBones_DBCCArmatureNode_prototype;

bool js_jsb_dragonbones_auto_DBCCArmatureNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_dragonbones_auto_DBCCArmatureNode_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_dragonbones_auto_DBCCArmatureNode(JSContext *cx, JS::HandleObject global);
void register_all_jsb_dragonbones_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_registerMovementEventHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_getCCEventDispatcher(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_registerFrameEventHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_unregisterMovementEventHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_gotoAndPlay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_getBoundingBox(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_unregisterFrameEventHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_initWithDBCCArmature(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_getCCDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_advanceTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_createWithWorldClock(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DBCCArmatureNode_DBCCArmatureNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_DragonBonesHelper_class;
extern JSObject *jsb_DragonBonesHelper_prototype;

bool js_jsb_dragonbones_auto_DragonBonesHelper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_dragonbones_auto_DragonBonesHelper_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_dragonbones_auto_DragonBonesHelper(JSContext *cx, JS::HandleObject global);
void register_all_jsb_dragonbones_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_dragonbones_auto_DragonBonesHelper_buildArmatureNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DragonBonesHelper_advanceWorldClock(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DragonBonesHelper_removeDragonBones(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_dragonbones_auto_DragonBonesHelper_addDragonBones(JSContext *cx, uint32_t argc, jsval *vp);
#endif

