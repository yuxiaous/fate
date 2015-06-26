/**
 * @module jsb_bindings_auto
 */
var jsb = jsb || {};

/**
 * @class Shake
 */
jsb.Shake = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @return {bool}
 */
initWithDuration : function (
float, 
float, 
float 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {float} arg1
 * @return {Shake}
 */
create : function (
float, 
float 
)
{
    return Shake;
},

/**
 * @method createWithStrength
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @return {Shake}
 */
createWithStrength : function (
float, 
float, 
float 
)
{
    return Shake;
},

/**
 * @method Shake
 * @constructor
 */
Shake : function (
)
{
},

};

/**
 * @class FallOffShake
 */
jsb.FallOffShake = {

/**
 * @method create
 * @param {float} arg0
 * @param {float} arg1
 * @return {FallOffShake}
 */
create : function (
float, 
float 
)
{
    return FallOffShake;
},

/**
 * @method createWithStrength
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @return {FallOffShake}
 */
createWithStrength : function (
float, 
float, 
float 
)
{
    return FallOffShake;
},

/**
 * @method FallOffShake
 * @constructor
 */
FallOffShake : function (
)
{
},

};

/**
 * @class SneakyButton
 */
jsb.SneakyButton = {

/**
 * @method onTouchMoved
 * @param {cc.Touch} arg0
 * @param {cc.Event} arg1
 */
onTouchMoved : function (
touch, 
event 
)
{
},

/**
 * @method setRadius
 * @param {float} arg0
 */
setRadius : function (
float 
)
{
},

/**
 * @method onTouchEnded
 * @param {cc.Touch} arg0
 * @param {cc.Event} arg1
 */
onTouchEnded : function (
touch, 
event 
)
{
},

/**
 * @method setIsEnable
 * @param {bool} arg0
 */
setIsEnable : function (
bool 
)
{
},

/**
 * @method getIsActive
 * @return {bool}
 */
getIsActive : function (
)
{
    return false;
},

/**
 * @method getIsEnable
 * @return {bool}
 */
getIsEnable : function (
)
{
    return false;
},

/**
 * @method setRateLimit
 * @param {float} arg0
 */
setRateLimit : function (
float 
)
{
},

/**
 * @method onTouchCancelled
 * @param {cc.Touch} arg0
 * @param {cc.Event} arg1
 */
onTouchCancelled : function (
touch, 
event 
)
{
},

/**
 * @method onTouchBegan
 * @param {cc.Touch} arg0
 * @param {cc.Event} arg1
 * @return {bool}
 */
onTouchBegan : function (
touch, 
event 
)
{
    return false;
},

/**
 * @method getValue
 * @return {bool}
 */
getValue : function (
)
{
    return false;
},

/**
 * @method getRateLimit
 * @return {float}
 */
getRateLimit : function (
)
{
    return 0;
},

/**
 * @method getIsToggleable
 * @return {bool}
 */
getIsToggleable : function (
)
{
    return false;
},

/**
 * @method limiter
 * @param {float} arg0
 */
limiter : function (
float 
)
{
},

/**
 * @method initWithSize
 * @param {size_object} arg0
 * @return {bool}
 */
initWithSize : function (
size 
)
{
    return false;
},

/**
 * @method setIsHoldable
 * @param {bool} arg0
 */
setIsHoldable : function (
bool 
)
{
},

/**
 * @method setIsToggleable
 * @param {bool} arg0
 */
setIsToggleable : function (
bool 
)
{
},

/**
 * @method getIsHoldable
 * @return {bool}
 */
getIsHoldable : function (
)
{
    return false;
},

/**
 * @method getRadius
 * @return {float}
 */
getRadius : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {size_object} arg0
 * @return {SneakyButton}
 */
create : function (
size 
)
{
    return SneakyButton;
},

};

/**
 * @class SneakyButtonSkinnedBase
 */
jsb.SneakyButtonSkinnedBase = {

/**
 * @method getPressSprite
 * @return {cc.Sprite}
 */
getPressSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method getButton
 * @return {SneakyButton}
 */
getButton : function (
)
{
    return SneakyButton;
},

/**
 * @method getActivatedSprite
 * @return {cc.Sprite}
 */
getActivatedSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method setButton
 * @param {SneakyButton} arg0
 */
setButton : function (
sneakybutton 
)
{
},

/**
 * @method getDefaultSprite
 * @return {cc.Sprite}
 */
getDefaultSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method setDefaultSprite
 * @param {cc.Sprite} arg0
 */
setDefaultSprite : function (
sprite 
)
{
},

/**
 * @method setActivatedSprite
 * @param {cc.Sprite} arg0
 */
setActivatedSprite : function (
sprite 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method watchSelf
 * @param {float} arg0
 */
watchSelf : function (
float 
)
{
},

/**
 * @method setPressSprite
 * @param {cc.Sprite} arg0
 */
setPressSprite : function (
sprite 
)
{
},

/**
 * @method setContentSize
 * @param {size_object} arg0
 */
setContentSize : function (
size 
)
{
},

/**
 * @method setDisabledSprite
 * @param {cc.Sprite} arg0
 */
setDisabledSprite : function (
sprite 
)
{
},

/**
 * @method getDisabledSprite
 * @return {cc.Sprite}
 */
getDisabledSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method create
 * @return {SneakyButtonSkinnedBase}
 */
create : function (
)
{
    return SneakyButtonSkinnedBase;
},

};

/**
 * @class SneakyJoystick
 */
jsb.SneakyJoystick = {

/**
 * @method setNumberOfDirections
 * @param {int} arg0
 */
setNumberOfDirections : function (
int 
)
{
},

/**
 * @method onTouchEnded
 * @param {cc.Touch} arg0
 * @param {cc.Event} arg1
 */
onTouchEnded : function (
touch, 
event 
)
{
},

/**
 * @method getAutoCenter
 * @return {bool}
 */
getAutoCenter : function (
)
{
    return false;
},

/**
 * @method getThumbRadius
 * @return {float}
 */
getThumbRadius : function (
)
{
    return 0;
},

/**
 * @method getIsActive
 * @return {bool}
 */
getIsActive : function (
)
{
    return false;
},

/**
 * @method setIsDPad
 * @param {bool} arg0
 */
setIsDPad : function (
bool 
)
{
},

/**
 * @method getIsDPad
 * @return {bool}
 */
getIsDPad : function (
)
{
    return false;
},

/**
 * @method getJoystickRadius
 * @return {float}
 */
getJoystickRadius : function (
)
{
    return 0;
},

/**
 * @method setHasDeadzone
 * @param {bool} arg0
 */
setHasDeadzone : function (
bool 
)
{
},

/**
 * @method setJoystickRadius
 * @param {float} arg0
 */
setJoystickRadius : function (
float 
)
{
},

/**
 * @method getTouchArea
 * @return {rect_object}
 */
getTouchArea : function (
)
{
    return cc.Rect;
},

/**
 * @method getVelocity
 * @return {vec2_object}
 */
getVelocity : function (
)
{
    return cc.Vec2;
},

/**
 * @method getDegrees
 * @return {float}
 */
getDegrees : function (
)
{
    return 0;
},

/**
 * @method initWithSize
 * @param {size_object} arg0
 * @param {size_object} arg1
 * @return {bool}
 */
initWithSize : function (
size, 
size 
)
{
    return false;
},

/**
 * @method getIsEnable
 * @return {bool}
 */
getIsEnable : function (
)
{
    return false;
},

/**
 * @method onTouchMoved
 * @param {cc.Touch} arg0
 * @param {cc.Event} arg1
 */
onTouchMoved : function (
touch, 
event 
)
{
},

/**
 * @method setIsEnable
 * @param {bool} arg0
 */
setIsEnable : function (
bool 
)
{
},

/**
 * @method getNumberOfDirections
 * @return {int}
 */
getNumberOfDirections : function (
)
{
    return 0;
},

/**
 * @method onTouchCancelled
 * @param {cc.Touch} arg0
 * @param {cc.Event} arg1
 */
onTouchCancelled : function (
touch, 
event 
)
{
},

/**
 * @method onTouchBegan
 * @param {cc.Touch} arg0
 * @param {cc.Event} arg1
 * @return {bool}
 */
onTouchBegan : function (
touch, 
event 
)
{
    return false;
},

/**
 * @method setTouchArea
 * @param {rect_object} arg0
 */
setTouchArea : function (
rect 
)
{
},

/**
 * @method getIsConstantVelocity
 * @return {bool}
 */
getIsConstantVelocity : function (
)
{
    return false;
},

/**
 * @method getStickPosition
 * @return {vec2_object}
 */
getStickPosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method setDeadRadius
 * @param {float} arg0
 */
setDeadRadius : function (
float 
)
{
},

/**
 * @method setIsConstantVelocity
 * @param {bool} arg0
 */
setIsConstantVelocity : function (
bool 
)
{
},

/**
 * @method getHasDeadzone
 * @return {bool}
 */
getHasDeadzone : function (
)
{
    return false;
},

/**
 * @method getDeadRadius
 * @return {float}
 */
getDeadRadius : function (
)
{
    return 0;
},

/**
 * @method setAutoCenter
 * @param {bool} arg0
 */
setAutoCenter : function (
bool 
)
{
},

/**
 * @method setThumbRadius
 * @param {float} arg0
 */
setThumbRadius : function (
float 
)
{
},

/**
 * @method create
 * @param {size_object} arg0
 * @param {size_object} arg1
 * @return {SneakyJoystick}
 */
create : function (
size, 
size 
)
{
    return SneakyJoystick;
},

};

/**
 * @class SneakyJoystickSkinnedBase
 */
jsb.SneakyJoystickSkinnedBase = {

/**
 * @method setJoystick
 * @param {SneakyJoystick} arg0
 */
setJoystick : function (
sneakyjoystick 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setThumbSprite
 * @param {cc.Sprite} arg0
 * @param {cc.Sprite} arg1
 */
setThumbSprite : function (
sprite, 
sprite 
)
{
},

/**
 * @method getDefaultBackgroundSprite
 * @return {cc.Sprite}
 */
getDefaultBackgroundSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method getDefaultThumbSprite
 * @return {cc.Sprite}
 */
getDefaultThumbSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method getBackgroundSprite
 * @return {cc.Sprite}
 */
getBackgroundSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method getThumbSprite
 * @return {cc.Sprite}
 */
getThumbSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method setBackgroundSprite
 * @param {cc.Sprite} arg0
 * @param {cc.Sprite} arg1
 */
setBackgroundSprite : function (
sprite, 
sprite 
)
{
},

/**
 * @method getJoystick
 * @return {SneakyJoystick}
 */
getJoystick : function (
)
{
    return SneakyJoystick;
},

/**
 * @method create
 * @return {SneakyJoystickSkinnedBase}
 */
create : function (
)
{
    return SneakyJoystickSkinnedBase;
},

};

/**
 * @class JsonStorage
 */
jsb.JsonStorage = {

/**
 * @method setIntegerForKey
 * @param {String} arg0
 * @param {int} arg1
 */
setIntegerForKey : function (
str, 
int 
)
{
},

/**
 * @method getBoolForKey
 * @param {String} arg0
 * @param {bool} arg1
 * @return {bool}
 */
getBoolForKey : function (
str, 
bool 
)
{
    return false;
},

/**
 * @method setDoubleForKey
 * @param {String} arg0
 * @param {double} arg1
 */
setDoubleForKey : function (
str, 
double 
)
{
},

/**
 * @method getStringForKey
 * @param {String} arg0
 * @param {String} arg1
 * @return {String}
 */
getStringForKey : function (
str, 
str 
)
{
    return ;
},

/**
 * @method setStringForKey
 * @param {String} arg0
 * @param {String} arg1
 */
setStringForKey : function (
str, 
str 
)
{
},

/**
 * @method flush
 */
flush : function (
)
{
},

/**
 * @method getIntegerForKey
 * @param {String} arg0
 * @param {int} arg1
 * @return {int}
 */
getIntegerForKey : function (
str, 
int 
)
{
    return 0;
},

/**
 * @method getDoubleForKey
 * @param {String} arg0
 * @param {float} arg1
 * @return {double}
 */
getDoubleForKey : function (
str, 
float 
)
{
    return 0;
},

/**
 * @method setBoolForKey
 * @param {String} arg0
 * @param {bool} arg1
 */
setBoolForKey : function (
str, 
bool 
)
{
},

/**
 * @method GetInstance
 * @param {String} arg0
 * @return {JsonStorage}
 */
GetInstance : function (
str 
)
{
    return JsonStorage;
},

};

/**
 * @class SdkManager
 */
jsb.SdkManager = {

/**
 * @method init
 */
init : function (
)
{
},

/**
 * @method buy
 * @param {String} arg0
 */
buy : function (
str 
)
{
},

/**
 * @method configureSdk
 */
configureSdk : function (
)
{
},

/**
 * @method setBuyCallback
 * @param {function} arg0
 */
setBuyCallback : function (
func 
)
{
},

};
