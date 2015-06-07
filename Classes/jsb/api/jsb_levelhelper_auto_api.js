/**
 * @module jsb_levelhelper_auto
 */
var lh = lh || {};

/**
 * @class LHUserPropertyProtocol
 */
lh.LHUserPropertyProtocol = {

/**
 * @method getClassName
 * @return {String}
 */
getClassName : function (
)
{
    return ;
},

/**
 * @method setNode
 * @param {cc.Node} arg0
 */
setNode : function (
node 
)
{
},

/**
 * @method setPropertiesFromDictionary
 * @param {LHDictionary} arg0
 */
setPropertiesFromDictionary : function (
lhdictionary 
)
{
},

/**
 * @method getNode
 * @return {cc.Node}
 */
getNode : function (
)
{
    return cc.Node;
},

};

/**
 * @class LHNodeProtocol
 */
lh.LHNodeProtocol = {

/**
 * @method isRopeJointNode
 * @return {bool}
 */
isRopeJointNode : function (
)
{
    return false;
},

/**
 * @method setUuid
 * @param {String} arg0
 */
setUuid : function (
str 
)
{
},

/**
 * @method loadTransformationInfoFromDictionary
 * @param {LHDictionary} arg0
 */
loadTransformationInfoFromDictionary : function (
lhdictionary 
)
{
},

/**
 * @method isUINode
 * @return {bool}
 */
isUINode : function (
)
{
    return false;
},

/**
 * @method getChildNodeWithName
 * @param {String} arg0
 * @return {cc.Node}
 */
getChildNodeWithName : function (
str 
)
{
    return cc.Node;
},

/**
 * @method isRevoluteJointNode
 * @return {bool}
 */
isRevoluteJointNode : function (
)
{
    return false;
},

/**
 * @method getUuid
 * @return {String}
 */
getUuid : function (
)
{
    return ;
},

/**
 * @method setTags
 * @param {LHArray} arg0
 */
setTags : function (
lharray 
)
{
},

/**
 * @method isJoint
 * @return {bool}
 */
isJoint : function (
)
{
    return false;
},

/**
 * @method isLHWeldJointNode
 * @return {bool}
 */
isLHWeldJointNode : function (
)
{
    return false;
},

/**
 * @method isSprite
 * @return {bool}
 */
isSprite : function (
)
{
    return false;
},

/**
 * @method isShape
 * @return {bool}
 */
isShape : function (
)
{
    return false;
},

/**
 * @method isParallaxLayer
 * @return {bool}
 */
isParallaxLayer : function (
)
{
    return false;
},

/**
 * @method isDistanceJointNode
 * @return {bool}
 */
isDistanceJointNode : function (
)
{
    return false;
},

/**
 * @method isNode
 * @return {bool}
 */
isNode : function (
)
{
    return false;
},

/**
 * @method isParallax
 * @return {bool}
 */
isParallax : function (
)
{
    return false;
},

/**
 * @method lateLoading
 * @return {bool}
 */
lateLoading : function (
)
{
    return false;
},

/**
 * @method loadUserPropertyWithDictionary
 * @param {LHDictionary} arg0
 */
loadUserPropertyWithDictionary : function (
lhdictionary 
)
{
},

/**
 * @method loadGenericInfoFromDictionary
 * @param {LHDictionary} arg0
 */
loadGenericInfoFromDictionary : function (
lhdictionary 
)
{
},

/**
 * @method isWater
 * @return {bool}
 */
isWater : function (
)
{
    return false;
},

/**
 * @method isBackUINode
 * @return {bool}
 */
isBackUINode : function (
)
{
    return false;
},

/**
 * @method isGearJointNode
 * @return {bool}
 */
isGearJointNode : function (
)
{
    return false;
},

/**
 * @method isPulleyJointNode
 * @return {bool}
 */
isPulleyJointNode : function (
)
{
    return false;
},

/**
 * @method isWheelJointNode
 * @return {bool}
 */
isWheelJointNode : function (
)
{
    return false;
},

/**
 * @method isB2WorldDirty
 * @return {bool}
 */
isB2WorldDirty : function (
)
{
    return false;
},

/**
 * @method isCamera
 * @return {bool}
 */
isCamera : function (
)
{
    return false;
},

/**
 * @method getTags
 * @return {Array}
 */
getTags : function (
)
{
    return new Array();
},

/**
 * @method getChildrenWithTags
 * @param {Array} arg0
 * @param {bool} arg1
 * @return {cc.__Array}
 */
getChildrenWithTags : function (
array, 
bool 
)
{
    return cc.__Array;
},

/**
 * @method getUserProperty
 * @return {LHUserPropertyProtocol}
 */
getUserProperty : function (
)
{
    return LHUserPropertyProtocol;
},

/**
 * @method isGameWorldNode
 * @return {bool}
 */
isGameWorldNode : function (
)
{
    return false;
},

/**
 * @method containsTag
 * @param {String} arg0
 * @return {bool}
 */
containsTag : function (
str 
)
{
    return false;
},

/**
 * @method isAsset
 * @return {bool}
 */
isAsset : function (
)
{
    return false;
},

/**
 * @method isPrismaticJointNode
 * @return {bool}
 */
isPrismaticJointNode : function (
)
{
    return false;
},

/**
 * @method markAsB2WorldDirty
 */
markAsB2WorldDirty : function (
)
{
},

/**
 * @method isScene
 * @return {bool}
 */
isScene : function (
)
{
    return false;
},

/**
 * @method isGravityArea
 * @return {bool}
 */
isGravityArea : function (
)
{
    return false;
},

/**
 * @method getChildNodeWithUUID
 * @param {String} arg0
 * @return {cc.Node}
 */
getChildNodeWithUUID : function (
str 
)
{
    return cc.Node;
},

/**
 * @method isBezier
 * @return {bool}
 */
isBezier : function (
)
{
    return false;
},

/**
 * @method loadChildrenFromDictionary
 * @param {LHDictionary} arg0
 */
loadChildrenFromDictionary : function (
lhdictionary 
)
{
},

/**
 * @method positionForNode
 * @param {cc.Node} arg0
 * @param {vec2_object} arg1
 * @return {vec2_object}
 */
positionForNode : function (
node, 
vec2 
)
{
    return cc.Vec2;
},

/**
 * @method createLHNodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {cc.Node}
 */
createLHNodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return cc.Node;
},

/**
 * @method LHGetNode
 * @param {LHNodeProtocol} arg0
 * @return {cc.Node}
 */
LHGetNode : function (
lhnodeprotocol 
)
{
    return cc.Node;
},

/**
 * @method LHGetNodeProtocol
 * @param {cc.Node} arg0
 * @return {LHNodeProtocol}
 */
LHGetNodeProtocol : function (
node 
)
{
    return LHNodeProtocol;
},

};

/**
 * @class LHScene
 */
lh.LHScene = {

/**
 * @method setGlobalGravity
 * @param {vec2_object} arg0
 */
setGlobalGravity : function (
vec2 
)
{
},

/**
 * @method getGlobalGravity
 * @return {vec2_object}
 */
getGlobalGravity : function (
)
{
    return cc.Vec2;
},

/**
 * @method setGameWorldRect
 * @param {rect_object} arg0
 */
setGameWorldRect : function (
rect 
)
{
},

/**
 * @method getChildNodeWithName
 * @param {String} arg0
 * @return {cc.Node}
 */
getChildNodeWithName : function (
str 
)
{
    return cc.Node;
},

/**
 * @method getGameWorldRect
 * @return {rect_object}
 */
getGameWorldRect : function (
)
{
    return cc.Rect;
},

/**
 * @method initWithContentOfFile
 * @param {String} arg0
 * @return {bool}
 */
initWithContentOfFile : function (
str 
)
{
    return false;
},

/**
 * @method getGameWorldNode
 * @return {LHGameWorldNode}
 */
getGameWorldNode : function (
)
{
    return LHGameWorldNode;
},

/**
 * @method tracedFixturesWithUUID
 * @param {String} arg0
 * @return {cc.__Array}
 */
tracedFixturesWithUUID : function (
str 
)
{
    return cc.__Array;
},

/**
 * @method getDesignResolutionSize
 * @return {size_object}
 */
getDesignResolutionSize : function (
)
{
    return cc.Size;
},

/**
 * @method getDesignOffset
 * @return {vec2_object}
 */
getDesignOffset : function (
)
{
    return cc.Vec2;
},

/**
 * @method assetInfoForFile
 * @param {String} arg0
 * @return {cc.__Dictionary}
 */
assetInfoForFile : function (
str 
)
{
    return cc.__Dictionary;
},

/**
 * @method getUINode
 * @return {LHUINode}
 */
getUINode : function (
)
{
    return LHUINode;
},

/**
 * @method getCurrentDeviceSuffix
 * @return {String}
 */
getCurrentDeviceSuffix : function (
)
{
    return ;
},

/**
 * @method isScene
 * @return {bool}
 */
isScene : function (
)
{
    return false;
},

/**
 * @method getBackUINode
 * @return {LHBackUINode}
 */
getBackUINode : function (
)
{
    return LHBackUINode;
},

/**
 * @method createWithContentOfFile
 * @param {String} arg0
 * @return {LHScene}
 */
createWithContentOfFile : function (
str 
)
{
    return LHScene;
},

/**
 * @method isLHScene
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHScene : function (
node 
)
{
    return false;
},

/**
 * @method LHScene
 * @constructor
 */
LHScene : function (
)
{
},

};

/**
 * @class LHUINode
 */
lh.LHUINode = {

/**
 * @method isUINode
 * @return {bool}
 */
isUINode : function (
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHUINode}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHUINode;
},

/**
 * @method isLHUINode
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHUINode : function (
node 
)
{
    return false;
},

/**
 * @method LHUINode
 * @constructor
 */
LHUINode : function (
)
{
},

};

/**
 * @class LHBackUINode
 */
lh.LHBackUINode = {

/**
 * @method isBackUINode
 * @return {bool}
 */
isBackUINode : function (
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method isLHBackUINode
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHBackUINode : function (
node 
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHBackUINode}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHBackUINode;
},

/**
 * @method LHBackUINode
 * @constructor
 */
LHBackUINode : function (
)
{
},

};

/**
 * @class LHGameWorldNode
 */
lh.LHGameWorldNode = {

/**
 * @method setGravity
 * @param {vec2_object} arg0
 */
setGravity : function (
vec2 
)
{
},

/**
 * @method isGameWorldNode
 * @return {bool}
 */
isGameWorldNode : function (
)
{
    return false;
},

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method setScale
 * @param {float} arg0
 */
setScale : function (
float 
)
{
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method getGravity
 * @return {vec2_object}
 */
getGravity : function (
)
{
    return cc.Vec2;
},

/**
 * @method setPosition
 * @param {vec2_object} arg0
 */
setPosition : function (
vec2 
)
{
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHGameWorldNode}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHGameWorldNode;
},

/**
 * @method isLHGameWorldNode
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHGameWorldNode : function (
node 
)
{
    return false;
},

/**
 * @method LHGameWorldNode
 * @constructor
 */
LHGameWorldNode : function (
)
{
},

};

/**
 * @class LHPhysicsProtocol
 */
lh.LHPhysicsProtocol = {

/**
 * @method removeBody
 */
removeBody : function (
)
{
},

/**
 * @method visitPhysicsProtocol
 */
visitPhysicsProtocol : function (
)
{
},

/**
 * @method updatePhysicsScale
 */
updatePhysicsScale : function (
)
{
},

/**
 * @method loadPhysicsFromDictionary
 * @param {LHDictionary} arg0
 * @param {LHScene} arg1
 */
loadPhysicsFromDictionary : function (
lhdictionary, 
lhscene 
)
{
},

/**
 * @method updatePhysicsTransform
 */
updatePhysicsTransform : function (
)
{
},

/**
 * @method shouldRemoveBody
 */
shouldRemoveBody : function (
)
{
},

/**
 * @method LHGetNode
 * @param {LHPhysicsProtocol} arg0
 * @return {cc.Node}
 */
LHGetNode : function (
lhphysicsprotocol 
)
{
    return cc.Node;
},

};

/**
 * @class LHNodeAnimationProtocol
 */
lh.LHNodeAnimationProtocol = {

/**
 * @method createAnimationsFromDictionary
 * @param {LHDictionary} arg0
 */
createAnimationsFromDictionary : function (
lhdictionary 
)
{
},

/**
 * @method getActiveAnimation
 * @return {LHAnimation}
 */
getActiveAnimation : function (
)
{
    return LHAnimation;
},

/**
 * @method getAnimationWithName
 * @param {String} arg0
 * @return {LHAnimation}
 */
getAnimationWithName : function (
str 
)
{
    return LHAnimation;
},

/**
 * @method getAnimations
 * @return {cc.__Array}
 */
getAnimations : function (
)
{
    return cc.__Array;
},

/**
 * @method setActiveAnimation
 * @param {LHAnimation} arg0
 */
setActiveAnimation : function (
lhanimation 
)
{
},

/**
 * @method visitActiveAnimation
 */
visitActiveAnimation : function (
)
{
},

};

/**
 * @class LHSprite
 */
lh.LHSprite = {

/**
 * @method initWithSpriteName
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {cc.Node} arg3
 * @return {bool}
 */
initWithSpriteName : function (
str, 
str, 
str, 
node 
)
{
    return false;
},

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method isSprite
 * @return {bool}
 */
isSprite : function (
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method initWithFilename
 * @param {String} arg0
 * @param {String} arg1
 * @param {cc.Node} arg2
 * @return {bool}
 */
initWithFilename : function (
str, 
str, 
node 
)
{
    return false;
},

/**
 * @method createWithFile
 * @param {String} arg0
 * @param {String} arg1
 * @param {cc.Node} arg2
 * @return {LHSprite}
 */
createWithFile : function (
str, 
str, 
node 
)
{
    return LHSprite;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHSprite}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHSprite;
},

/**
 * @method isLHSprite
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHSprite : function (
node 
)
{
    return false;
},

/**
 * @method createWithSpriteName
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {cc.Node} arg3
 * @return {LHSprite}
 */
createWithSpriteName : function (
str, 
str, 
str, 
node 
)
{
    return LHSprite;
},

/**
 * @method LHSprite
 * @constructor
 */
LHSprite : function (
)
{
},

};

/**
 * @class LHCamera
 */
lh.LHCamera = {

/**
 * @method resetLookAt
 */
resetLookAt : function (
)
{
},

/**
 * @method setSmoothMovement
 * @param {bool} arg0
 */
setSmoothMovement : function (
bool 
)
{
},

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method setRestrictedToGameWorld
 * @param {bool} arg0
 */
setRestrictedToGameWorld : function (
bool 
)
{
},

/**
 * @method lookAtPositionInSeconds
 * @param {vec2_object} arg0
 * @param {float} arg1
 */
lookAtPositionInSeconds : function (
vec2, 
float 
)
{
},

/**
 * @method setUsePinchOrScrollWheelToZoom
 * @param {bool} arg0
 */
setUsePinchOrScrollWheelToZoom : function (
bool 
)
{
},

/**
 * @method zoomToValueInSeconds
 * @param {float} arg0
 * @param {float} arg1
 */
zoomToValueInSeconds : function (
float, 
float 
)
{
},

/**
 * @method setPosition
 * @param {vec2_object} arg0
 */
setPosition : function (
vec2 
)
{
},

/**
 * @method usePinchOrScrollWheelToZoom
 * @return {bool}
 */
usePinchOrScrollWheelToZoom : function (
)
{
    return false;
},

/**
 * @method resetLookAtInSeconds
 * @param {float} arg0
 */
resetLookAtInSeconds : function (
float 
)
{
},

/**
 * @method followedNode
 * @return {cc.Node}
 */
followedNode : function (
)
{
    return cc.Node;
},

/**
 * @method setActive
 * @param {bool} arg0
 */
setActive : function (
bool 
)
{
},

/**
 * @method getImportantAreaUnit
 * @return {size_object}
 */
getImportantAreaUnit : function (
)
{
    return cc.Size;
},

/**
 * @method setZoomValue
 * @param {float} arg0
 */
setZoomValue : function (
float 
)
{
},

/**
 * @method lookAtNodeInSeconds
 * @param {cc.Node} arg0
 * @param {float} arg1
 */
lookAtNodeInSeconds : function (
node, 
float 
)
{
},

/**
 * @method getZoomValue
 * @return {float}
 */
getZoomValue : function (
)
{
    return 0;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method setLockY
 * @param {bool} arg0
 */
setLockY : function (
bool 
)
{
},

/**
 * @method setLockX
 * @param {bool} arg0
 */
setLockX : function (
bool 
)
{
},

/**
 * @method getSmoothMovement
 * @return {bool}
 */
getSmoothMovement : function (
)
{
    return false;
},

/**
 * @method getOffsetUnit
 * @return {vec2_object}
 */
getOffsetUnit : function (
)
{
    return cc.Vec2;
},

/**
 * @method isLookingAt
 * @return {bool}
 */
isLookingAt : function (
)
{
    return false;
},

/**
 * @method followNode
 * @param {cc.Node} arg0
 */
followNode : function (
node 
)
{
},

/**
 * @method isActive
 * @return {bool}
 */
isActive : function (
)
{
    return false;
},

/**
 * @method isCamera
 * @return {bool}
 */
isCamera : function (
)
{
    return false;
},

/**
 * @method restrictedToGameWorld
 * @return {bool}
 */
restrictedToGameWorld : function (
)
{
    return false;
},

/**
 * @method setOffsetUnit
 * @param {vec2_object} arg0
 */
setOffsetUnit : function (
vec2 
)
{
},

/**
 * @method setImportantAreaUnit
 * @param {size_object} arg0
 */
setImportantAreaUnit : function (
size 
)
{
},

/**
 * @method getLockY
 * @return {bool}
 */
getLockY : function (
)
{
    return false;
},

/**
 * @method getLockX
 * @return {bool}
 */
getLockX : function (
)
{
    return false;
},

/**
 * @method zoomByValueInSeconds
 * @param {float} arg0
 * @param {float} arg1
 */
zoomByValueInSeconds : function (
float, 
float 
)
{
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHCamera}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHCamera;
},

/**
 * @method isLHCamera
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHCamera : function (
node 
)
{
    return false;
},

/**
 * @method LHCamera
 * @constructor
 */
LHCamera : function (
)
{
},

};

/**
 * @class LHAsset
 */
lh.LHAsset = {

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method initWithName
 * @param {String} arg0
 * @param {String} arg1
 * @param {cc.Node} arg2
 * @return {bool}
 */
initWithName : function (
str, 
str, 
node 
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method isAsset
 * @return {bool}
 */
isAsset : function (
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHAsset}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHAsset;
},

/**
 * @method createWithName
 * @param {String} arg0
 * @param {String} arg1
 * @param {cc.Node} arg2
 * @return {LHAsset}
 */
createWithName : function (
str, 
str, 
node 
)
{
    return LHAsset;
},

/**
 * @method isLHAsset
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHAsset : function (
node 
)
{
    return false;
},

/**
 * @method LHAsset
 * @constructor
 */
LHAsset : function (
)
{
},

};

/**
 * @class LHParallax
 */
lh.LHParallax = {

/**
 * @method followedNode
 * @return {cc.Node}
 */
followedNode : function (
)
{
    return cc.Node;
},

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method followNode
 * @param {cc.Node} arg0
 */
followNode : function (
node 
)
{
},

/**
 * @method isParallax
 * @return {bool}
 */
isParallax : function (
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHParallax}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHParallax;
},

/**
 * @method isLHParallax
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHParallax : function (
node 
)
{
    return false;
},

/**
 * @method LHParallax
 * @constructor
 */
LHParallax : function (
)
{
},

};

/**
 * @class LHParallaxLayer
 */
lh.LHParallaxLayer = {

/**
 * @method getInitialPosition
 * @return {vec2_object}
 */
getInitialPosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method getRatioX
 * @return {float}
 */
getRatioX : function (
)
{
    return 0;
},

/**
 * @method getRatioY
 * @return {float}
 */
getRatioY : function (
)
{
    return 0;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method isParallaxLayer
 * @return {bool}
 */
isParallaxLayer : function (
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHParallaxLayer}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHParallaxLayer;
},

/**
 * @method isLHParallaxLayer
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHParallaxLayer : function (
node 
)
{
    return false;
},

/**
 * @method LHParallaxLayer
 * @constructor
 */
LHParallaxLayer : function (
)
{
},

};

/**
 * @class LHAnimation
 */
lh.LHAnimation = {

/**
 * @method totalTime
 * @return {float}
 */
totalTime : function (
)
{
    return 0;
},

/**
 * @method node
 * @return {LHNodeAnimationProtocol}
 */
node : function (
)
{
    return LHNodeAnimationProtocol;
},

/**
 * @method repetitions
 * @return {int}
 */
repetitions : function (
)
{
    return 0;
},

/**
 * @method name
 * @return {String}
 */
name : function (
)
{
    return ;
},

/**
 * @method currentTime
 * @return {float}
 */
currentTime : function (
)
{
    return 0;
},

/**
 * @method restart
 */
restart : function (
)
{
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {LHNodeAnimationProtocol} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
lhnodeanimationprotocol 
)
{
    return false;
},

/**
 * @method currentFrame
 * @return {float}
 */
currentFrame : function (
)
{
    return 0;
},

/**
 * @method setActive
 * @param {bool} arg0
 */
setActive : function (
bool 
)
{
},

/**
 * @method animating
 * @return {bool}
 */
animating : function (
)
{
    return false;
},

/**
 * @method setAnimating
 * @param {bool} arg0
 */
setAnimating : function (
bool 
)
{
},

/**
 * @method setCurrentFrame
 * @param {float} arg0
 */
setCurrentFrame : function (
float 
)
{
},

/**
 * @method isActive
 * @return {bool}
 */
isActive : function (
)
{
    return false;
},

/**
 * @method createWithDictionary
 * @param {LHDictionary} arg0
 * @param {LHNodeAnimationProtocol} arg1
 * @return {LHAnimation}
 */
createWithDictionary : function (
lhdictionary, 
lhnodeanimationprotocol 
)
{
    return LHAnimation;
},

/**
 * @method LHAnimation
 * @constructor
 */
LHAnimation : function (
)
{
},

};

/**
 * @class LHGravityArea
 */
lh.LHGravityArea = {

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method getForce
 * @return {float}
 */
getForce : function (
)
{
    return 0;
},

/**
 * @method isRadial
 * @return {bool}
 */
isRadial : function (
)
{
    return false;
},

/**
 * @method getDirection
 * @return {vec2_object}
 */
getDirection : function (
)
{
    return cc.Vec2;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method isGravityArea
 * @return {bool}
 */
isGravityArea : function (
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHGravityArea}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHGravityArea;
},

/**
 * @method isLHGravityArea
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHGravityArea : function (
node 
)
{
    return false;
},

/**
 * @method LHGravityArea
 * @constructor
 */
LHGravityArea : function (
)
{
},

};

/**
 * @class LHJointsProtocol
 */
lh.LHJointsProtocol = {

/**
 * @method getNodeA
 * @return {cc.Node}
 */
getNodeA : function (
)
{
    return cc.Node;
},

/**
 * @method getNodeB
 * @return {cc.Node}
 */
getNodeB : function (
)
{
    return cc.Node;
},

/**
 * @method findConnectedNodes
 */
findConnectedNodes : function (
)
{
},

/**
 * @method removeJoint
 */
removeJoint : function (
)
{
},

/**
 * @method shouldRemoveJoint
 */
shouldRemoveJoint : function (
)
{
},

/**
 * @method getLocalAnchorA
 * @return {vec2_object}
 */
getLocalAnchorA : function (
)
{
    return cc.Vec2;
},

/**
 * @method getCollideConnected
 * @return {bool}
 */
getCollideConnected : function (
)
{
    return false;
},

/**
 * @method getLocalAnchorB
 * @return {vec2_object}
 */
getLocalAnchorB : function (
)
{
    return cc.Vec2;
},

/**
 * @method getAnchorB
 * @return {vec2_object}
 */
getAnchorB : function (
)
{
    return cc.Vec2;
},

/**
 * @method getAnchorA
 * @return {vec2_object}
 */
getAnchorA : function (
)
{
    return cc.Vec2;
},

/**
 * @method loadJointInfoFromDictionary
 * @param {LHDictionary} arg0
 */
loadJointInfoFromDictionary : function (
lhdictionary 
)
{
},

};

/**
 * @class LHRopeJointNode
 */
lh.LHRopeJointNode = {

/**
 * @method lateLoading
 * @return {bool}
 */
lateLoading : function (
)
{
    return false;
},

/**
 * @method isRopeJointNode
 * @return {bool}
 */
isRopeJointNode : function (
)
{
    return false;
},

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method canBeCut
 * @return {bool}
 */
canBeCut : function (
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method cutWithLineFromPointA
 * @param {vec2_object} arg0
 * @param {vec2_object} arg1
 */
cutWithLineFromPointA : function (
vec2, 
vec2 
)
{
},

/**
 * @method isLHRopeJointNode
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHRopeJointNode : function (
node 
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHRopeJointNode}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHRopeJointNode;
},

/**
 * @method LHRopeJointNode
 * @constructor
 */
LHRopeJointNode : function (
)
{
},

};

/**
 * @class LHRevoluteJointNode
 */
lh.LHRevoluteJointNode = {

/**
 * @method lateLoading
 * @return {bool}
 */
lateLoading : function (
)
{
    return false;
},

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method getUpperAngle
 * @return {float}
 */
getUpperAngle : function (
)
{
    return 0;
},

/**
 * @method getMaxMotorTorque
 * @return {float}
 */
getMaxMotorTorque : function (
)
{
    return 0;
},

/**
 * @method getEnableLimit
 * @return {bool}
 */
getEnableLimit : function (
)
{
    return false;
},

/**
 * @method getLowerAngle
 * @return {float}
 */
getLowerAngle : function (
)
{
    return 0;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method getMotorSpeed
 * @return {float}
 */
getMotorSpeed : function (
)
{
    return 0;
},

/**
 * @method isRevoluteJointNode
 * @return {bool}
 */
isRevoluteJointNode : function (
)
{
    return false;
},

/**
 * @method getEnableMotor
 * @return {bool}
 */
getEnableMotor : function (
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHRevoluteJointNode}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHRevoluteJointNode;
},

/**
 * @method isLHRevoluteJointNode
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHRevoluteJointNode : function (
node 
)
{
    return false;
},

/**
 * @method LHRevoluteJointNode
 * @constructor
 */
LHRevoluteJointNode : function (
)
{
},

};

/**
 * @class LHDistanceJointNode
 */
lh.LHDistanceJointNode = {

/**
 * @method getFrequency
 * @return {float}
 */
getFrequency : function (
)
{
    return 0;
},

/**
 * @method lateLoading
 * @return {bool}
 */
lateLoading : function (
)
{
    return false;
},

/**
 * @method getDamping
 * @return {float}
 */
getDamping : function (
)
{
    return 0;
},

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method isDistanceJointNode
 * @return {bool}
 */
isDistanceJointNode : function (
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHDistanceJointNode}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHDistanceJointNode;
},

/**
 * @method isLHDistanceJointNode
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHDistanceJointNode : function (
node 
)
{
    return false;
},

/**
 * @method LHDistanceJointNode
 * @constructor
 */
LHDistanceJointNode : function (
)
{
},

};

/**
 * @class LHWeldJointNode
 */
lh.LHWeldJointNode = {

/**
 * @method getFrequency
 * @return {float}
 */
getFrequency : function (
)
{
    return 0;
},

/**
 * @method lateLoading
 * @return {bool}
 */
lateLoading : function (
)
{
    return false;
},

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method getDampingRatio
 * @return {float}
 */
getDampingRatio : function (
)
{
    return 0;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method isWeldJointNode
 * @return {bool}
 */
isWeldJointNode : function (
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHWeldJointNode}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHWeldJointNode;
},

/**
 * @method isLHWeldJointNode
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHWeldJointNode : function (
node 
)
{
    return false;
},

/**
 * @method LHWeldJointNode
 * @constructor
 */
LHWeldJointNode : function (
)
{
},

};

/**
 * @class LHPrismaticJointNode
 */
lh.LHPrismaticJointNode = {

/**
 * @method getUpperTranslation
 * @return {float}
 */
getUpperTranslation : function (
)
{
    return 0;
},

/**
 * @method lateLoading
 * @return {bool}
 */
lateLoading : function (
)
{
    return false;
},

/**
 * @method getAxis
 * @return {vec2_object}
 */
getAxis : function (
)
{
    return cc.Vec2;
},

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method getMaxMotorForce
 * @return {float}
 */
getMaxMotorForce : function (
)
{
    return 0;
},

/**
 * @method getLowerTranslation
 * @return {float}
 */
getLowerTranslation : function (
)
{
    return 0;
},

/**
 * @method getEnableLimit
 * @return {bool}
 */
getEnableLimit : function (
)
{
    return false;
},

/**
 * @method isPrismaticJointNode
 * @return {bool}
 */
isPrismaticJointNode : function (
)
{
    return false;
},

/**
 * @method getMotorSpeed
 * @return {float}
 */
getMotorSpeed : function (
)
{
    return 0;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method getEnableMotor
 * @return {bool}
 */
getEnableMotor : function (
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHPrismaticJointNode}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHPrismaticJointNode;
},

/**
 * @method isLHPrismaticJointNode
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHPrismaticJointNode : function (
node 
)
{
    return false;
},

/**
 * @method LHPrismaticJointNode
 * @constructor
 */
LHPrismaticJointNode : function (
)
{
},

};

/**
 * @class LHWheelJointNode
 */
lh.LHWheelJointNode = {

/**
 * @method getFrequency
 * @return {float}
 */
getFrequency : function (
)
{
    return 0;
},

/**
 * @method lateLoading
 * @return {bool}
 */
lateLoading : function (
)
{
    return false;
},

/**
 * @method getAxis
 * @return {vec2_object}
 */
getAxis : function (
)
{
    return cc.Vec2;
},

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method getMaxMotorTorque
 * @return {float}
 */
getMaxMotorTorque : function (
)
{
    return 0;
},

/**
 * @method getDampingRatio
 * @return {float}
 */
getDampingRatio : function (
)
{
    return 0;
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method getMotorSpeed
 * @return {float}
 */
getMotorSpeed : function (
)
{
    return 0;
},

/**
 * @method isWheelJointNode
 * @return {bool}
 */
isWheelJointNode : function (
)
{
    return false;
},

/**
 * @method getEnableMotor
 * @return {bool}
 */
getEnableMotor : function (
)
{
    return false;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHWheelJointNode}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHWheelJointNode;
},

/**
 * @method isLHWheelJointNode
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHWheelJointNode : function (
node 
)
{
    return false;
},

/**
 * @method LHWheelJointNode
 * @constructor
 */
LHWheelJointNode : function (
)
{
},

};

/**
 * @class LHPulleyJointNode
 */
lh.LHPulleyJointNode = {

/**
 * @method lateLoading
 * @return {bool}
 */
lateLoading : function (
)
{
    return false;
},

/**
 * @method isPulleyJointNode
 * @return {bool}
 */
isPulleyJointNode : function (
)
{
    return false;
},

/**
 * @method getGroundAnchorA
 * @return {vec2_object}
 */
getGroundAnchorA : function (
)
{
    return cc.Vec2;
},

/**
 * @method visit
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method initWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithDictionary : function (
lhdictionary, 
node 
)
{
    return false;
},

/**
 * @method getGroundAnchorB
 * @return {vec2_object}
 */
getGroundAnchorB : function (
)
{
    return cc.Vec2;
},

/**
 * @method nodeWithDictionary
 * @param {LHDictionary} arg0
 * @param {cc.Node} arg1
 * @return {LHPulleyJointNode}
 */
nodeWithDictionary : function (
lhdictionary, 
node 
)
{
    return LHPulleyJointNode;
},

/**
 * @method isLHPulleyJointNode
 * @param {cc.Node} arg0
 * @return {bool}
 */
isLHPulleyJointNode : function (
node 
)
{
    return false;
},

/**
 * @method LHPulleyJointNode
 * @constructor
 */
LHPulleyJointNode : function (
)
{
},

};
