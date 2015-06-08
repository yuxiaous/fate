

// LevelHelper
lh.LHScene.extend = cc.Class.extend;

lh.LHScene.prototype._ctor = function(plistLevelFile) {
    lh.LHScene.prototype.initWithContentOfFile.call(this, plistLevelFile);
};


//// DragonBones
//dragonBones.events = dragonBones.events || {};
//dragonBones.events.Z_ORDER_UPDATED = "zorderUpdate";
//dragonBones.events.ANIMATION_FRAME_EVENT = "animationFrameEvent";
//dragonBones.events.BONE_FRAME_EVENT = "boneFrameEvent";
//dragonBones.events.SOUND = "sound";
//dragonBones.events.FADE_IN = "fadeIn";
//dragonBones.events.FADE_OUT = "fadeOut";
//dragonBones.events.START = "start";
//dragonBones.events.COMPLETE = "complete";
//dragonBones.events.LOOP_COMPLETE = "loopComplete";
//dragonBones.events.FADE_IN_COMPLETE = "fadeInComplete";
//dragonBones.events.FADE_OUT_COMPLETE = "fadeOutComplete";
//
//dragonBones.EventData.prototype.getFrameData = function() {
//    var frameLabel = this.getFrameLabel();
//    var labelData = frameLabel.split('?');
//    var name = labelData[0];
//    var attr = undefined;
//
//    var labelAttr = labelData[1];
//    if(labelAttr != undefined) {
//        attr = {};
//
//        var attrData = labelAttr.split('&');
//        _.each(attrData, function(data) {
//            var pair = data.split('=');
//            var key = pair[0];
//            var value = pair[1];
//            var parse = parseInt(value);
//            attr[key] = isNaN(parse) ? value : parse;
//        }, this);
//    }
//    return {
//        name: name,
//        attr: attr
//    };
//};

