#ifndef __jsb_bindings_auto_h__
#define __jsb_bindings_auto_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_Shake_class;
extern JSObject *jsb_Shake_prototype;

bool js_jsb_bindings_auto_Shake_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_bindings_auto_Shake_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_bindings_auto_Shake(JSContext *cx, JS::HandleObject global);
void register_all_jsb_bindings_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_bindings_auto_Shake_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_Shake_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_Shake_createWithStrength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_Shake_Shake(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_FallOffShake_class;
extern JSObject *jsb_FallOffShake_prototype;

bool js_jsb_bindings_auto_FallOffShake_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_bindings_auto_FallOffShake_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_bindings_auto_FallOffShake(JSContext *cx, JS::HandleObject global);
void register_all_jsb_bindings_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_bindings_auto_FallOffShake_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_FallOffShake_createWithStrength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_FallOffShake_FallOffShake(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_SneakyButton_class;
extern JSObject *jsb_SneakyButton_prototype;

bool js_jsb_bindings_auto_SneakyButton_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_bindings_auto_SneakyButton_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_bindings_auto_SneakyButton(JSContext *cx, JS::HandleObject global);
void register_all_jsb_bindings_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_bindings_auto_SneakyButton_onTouchMoved(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_setRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_onTouchEnded(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_setIsEnable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_getIsActive(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_getIsEnable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_setRateLimit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_onTouchCancelled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_onTouchBegan(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_getValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_getRateLimit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_getIsToggleable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_limiter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_initWithSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_setIsHoldable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_setIsToggleable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_getIsHoldable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_getRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButton_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_SneakyButtonSkinnedBase_class;
extern JSObject *jsb_SneakyButtonSkinnedBase_prototype;

bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_bindings_auto_SneakyButtonSkinnedBase_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_bindings_auto_SneakyButtonSkinnedBase(JSContext *cx, JS::HandleObject global);
void register_all_jsb_bindings_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_getPressSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_getButton(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_getActivatedSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setButton(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_getDefaultSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDefaultSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setActivatedSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_watchSelf(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setPressSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setContentSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDisabledSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_getDisabledSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_SneakyJoystick_class;
extern JSObject *jsb_SneakyJoystick_prototype;

bool js_jsb_bindings_auto_SneakyJoystick_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_bindings_auto_SneakyJoystick_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_bindings_auto_SneakyJoystick(JSContext *cx, JS::HandleObject global);
void register_all_jsb_bindings_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_bindings_auto_SneakyJoystick_setNumberOfDirections(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_onTouchEnded(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getAutoCenter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getThumbRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getIsActive(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_setIsDPad(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getIsDPad(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getJoystickRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_setHasDeadzone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_setJoystickRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getTouchArea(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getDegrees(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_initWithSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getIsEnable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_onTouchMoved(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_setIsEnable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getNumberOfDirections(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_onTouchCancelled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_onTouchBegan(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_setTouchArea(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getIsConstantVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getStickPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_setDeadRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_setIsConstantVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getHasDeadzone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_getDeadRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_setAutoCenter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_setThumbRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystick_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_SneakyJoystickSkinnedBase_class;
extern JSObject *jsb_SneakyJoystickSkinnedBase_prototype;

bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_bindings_auto_SneakyJoystickSkinnedBase_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_bindings_auto_SneakyJoystickSkinnedBase(JSContext *cx, JS::HandleObject global);
void register_all_jsb_bindings_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setJoystick(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setThumbSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getDefaultBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getDefaultThumbSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getThumbSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getJoystick(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_JsonStorage_class;
extern JSObject *jsb_JsonStorage_prototype;

bool js_jsb_bindings_auto_JsonStorage_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_bindings_auto_JsonStorage_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_bindings_auto_JsonStorage(JSContext *cx, JS::HandleObject global);
void register_all_jsb_bindings_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_bindings_auto_JsonStorage_setIntegerForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_JsonStorage_getBoolForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_JsonStorage_setDoubleForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_JsonStorage_getStringForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_JsonStorage_setStringForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_JsonStorage_flush(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_JsonStorage_getIntegerForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_JsonStorage_getDoubleForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_JsonStorage_setBoolForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_JsonStorage_GetInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_SdkManager_class;
extern JSObject *jsb_SdkManager_prototype;

bool js_jsb_bindings_auto_SdkManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_bindings_auto_SdkManager_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_bindings_auto_SdkManager(JSContext *cx, JS::HandleObject global);
void register_all_jsb_bindings_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_bindings_auto_SdkManager_setGender(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_onChargeResult(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_onPurchase(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_setAccountName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_sdkCommond(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_charge(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_setAccount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_setSdkCommondCallback(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_setAccountType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_onUse(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_setGameServer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_login(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_setAge(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_setChargeCallback(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_bindings_auto_SdkManager_setLevel(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameUtils_class;
extern JSObject *jsb_GameUtils_prototype;

bool js_jsb_bindings_auto_GameUtils_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_bindings_auto_GameUtils_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_bindings_auto_GameUtils(JSContext *cx, JS::HandleObject global);
void register_all_jsb_bindings_auto(JSContext* cx, JS::HandleObject obj);
bool js_jsb_bindings_auto_GameUtils_getChannelId(JSContext *cx, uint32_t argc, jsval *vp);
#endif

