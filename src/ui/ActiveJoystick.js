/**
 * Created by yuxiao on 15/1/14.
 */


var ActiveJoystick = cc.Layer.extend({
    _defaultJoystickPos: cc.p(190, 120),

    ctor: function() {
        this._super();
        this.setContentSize(400, 340);

        //var joystickBase = new sneaky.JoystickSkinnedBase();
        var joystickBase = new jsb.SneakyJoystickSkinnedBase();
        joystickBase.setPosition(this._defaultJoystickPos);
        joystickBase.setBackgroundSprite(new cc.Sprite("res/battle.png"));
        joystickBase.setThumbSprite(new cc.Sprite("res/CloseNormal.png"));
        joystickBase.setJoystick(new jsb.SneakyJoystick(cc.size(106, 106)));
        this.addChild(joystickBase);
        this._joystick = joystickBase.joystick;
        this._joystickBase = joystickBase;
    },

    onEnterTransitionDidFinish: function() {
        this._super();
        cc.unregisterTouchDelegate(this._joystick);
        cc.registerTargetedDelegate(2, true, this);
    },

    onExit: function() {
        this._super();
        cc.unregisterTouchDelegate(this);
    },

    onTouchBegan: function(touch ,event) {
        var location = touch.getLocation();
        location = this.convertToNodeSpace(location);

        var size = this.getContentSize();
        if(location.x >= 0 && location.x <= size.width
            && location.y >= 0 && location.y <= size.height) {
            this._joystickBase.setPosition(location);
            return this._joystick.onTouchBegan(touch ,event);
        }
        return false;
    },

    onTouchMoved: function(touch, event) {
        this._joystick.onTouchMoved(touch ,event);
    },

    onTouchEnded: function(touch, event) {
        this._joystick.onTouchEnded(touch ,event);
        this._joystickBase.setPosition(this._defaultJoystickPos);
    },

    onTouchCancelled: function(touch, event) {
        this.onTouchEnded(touch, event);
    }
});

