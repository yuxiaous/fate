/**
 * @module jsb_dragonbones_auto
 */
var dragonBones = dragonBones || {};

/**
 * @class DBCCArmatureNode
 */
dragonBones.DBCCArmatureNode = {

/**
 * @method registerMovementEventHandler
 * @param {function} arg0
 */
registerMovementEventHandler : function (
func 
)
{
},

/**
 * @method getCCEventDispatcher
 * @return {cc.EventDispatcher}
 */
getCCEventDispatcher : function (
)
{
    return cc.EventDispatcher;
},

/**
 * @method registerFrameEventHandler
 * @param {function} arg0
 */
registerFrameEventHandler : function (
func 
)
{
},

/**
 * @method unregisterMovementEventHandler
 */
unregisterMovementEventHandler : function (
)
{
},

/**
 * @method gotoAndPlay
 * @param {String} arg0
 * @return {bool}
 */
gotoAndPlay : function (
str 
)
{
    return false;
},

/**
 * @method getBoundingBox
* @param {String} str
* @return {rect_object|rect_object}
*/
getBoundingBox : function(
str 
)
{
    return cc.Rect;
},

/**
 * @method unregisterFrameEventHandler
 */
unregisterFrameEventHandler : function (
)
{
},

/**
 * @method initWithDBCCArmature
 * @param {dragonBones::DBCCArmature} arg0
 * @param {dragonBones::WorldClock} arg1
 * @return {bool}
 */
initWithDBCCArmature : function (
dbccarmature, 
worldclock 
)
{
    return false;
},

/**
 * @method getCCDisplay
 * @return {cc.Node}
 */
getCCDisplay : function (
)
{
    return cc.Node;
},

/**
 * @method advanceTime
 * @param {float} arg0
 */
advanceTime : function (
float 
)
{
},

/**
 * @method create
 * @param {dragonBones::DBCCArmature} arg0
 * @return {dragonBones::DBCCArmatureNode}
 */
create : function (
dbccarmature 
)
{
    return dragonBones::DBCCArmatureNode;
},

/**
 * @method createWithWorldClock
 * @param {dragonBones::DBCCArmature} arg0
 * @param {dragonBones::WorldClock} arg1
 * @return {dragonBones::DBCCArmatureNode}
 */
createWithWorldClock : function (
dbccarmature, 
worldclock 
)
{
    return dragonBones::DBCCArmatureNode;
},

/**
 * @method DBCCArmatureNode
 * @constructor
 */
DBCCArmatureNode : function (
)
{
},

};

/**
 * @class DragonBonesHelper
 */
dragonBones.DragonBonesHelper = {

/**
 * @method buildArmatureNode
 * @param {String} arg0
 * @return {dragonBones::DBCCArmatureNode}
 */
buildArmatureNode : function (
str 
)
{
    return dragonBones::DBCCArmatureNode;
},

/**
 * @method advanceWorldClock
 * @param {float} arg0
 */
advanceWorldClock : function (
float 
)
{
},

/**
 * @method removeDragonBones
 * @param {String} arg0
 */
removeDragonBones : function (
str 
)
{
},

/**
 * @method addDragonBones
 * @param {String} arg0
 * @return {bool}
 */
addDragonBones : function (
str 
)
{
    return false;
},

};
