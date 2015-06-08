/**
 * Created by yuxiao on 14/12/27.
 */


(function(){
    var sneaky = {},
        root = this;
    root.sneaky = sneaky;

    sneaky.Button = cc.Node.extend({
        onEnterTransitionDidFinish: function() {
            this._super();
            cc.registerTargetedDelegate(1, true, this);
        },

        onExit: function() {
            this._super();
            cc.unregisterTouchDelegate(this);
        },

        ctor: function(size) {
            this._super();

            // getter
            this.value = false; // 按钮的值
            this.active = false; // 手指是否按在上面

            // setter
            this.status = true;
            this.isHoldable = false;
            this.isToggleable = false;
            this.rateLimit = 1.0/120.0;

            this.radius = 32;
            this.radiusSq = 0;

            this.setPosition(size.width/2, size.height/2);
            this.setContentSize(size);
        },

        limiter: function(delta) {
            this.value = false;
            this.unschedule(this.limiter);
            this.active = false;
        },

        setRadius: function(r) {
            this.radius = r;
            this.radiusSq = r * r;
        },

        onTouchBegan: function(touch ,event) {
            if (this.active) return false;

            var location = touch.getLocation();
            location = this.convertToNodeSpace(location);
            //var size = this.getContentSize();
            //location = cc.pSub(location, cc.p(size.width/2, size.height/2));

            //Do a fast rect check before doing a circle hit check:
            var radius = this.radius;
            if(location.x >= -radius && location.x <= radius
                && location.y >= -radius && location.y <= radius) {
                var dSq = location.x * location.x + location.y * location.y;
                if(dSq < this.radiusSq){
                    this.active = true;
                    if (!this.isHoldable && !this.isToggleable){
                        this.value = true;
                        this.schedule(this.limiter, this.rateLimit);
                    }
                    if (this.isHoldable)
                        this.value = true;
                    if (this.isToggleable)
                        this.value = !this.value;

                    return true;
                }
            }
            return false;
        },

        onTouchMoved: function(touch, event) {
            if (!this.active) return;

            var location = touch.getLocation();
            location = this.convertToNodeSpace(location);

            //Do a fast rect check before doing a circle hit check:
            var radius = this.radius;
            if(location.x >= -radius && location.x <= radius
                && location.y >= -radius && location.y <= radius) {
                var dSq = location.x * location.x + location.y * location.y;
                if (this.isHoldable) {
                    if(this.radiusSq > dSq){
                        this.value = true;
                    }
                    else {
                        this.value = false;
                        this.active = false;
                    }
                }
            }
        },

        onTouchEnded: function(touch, event) {
            if (!this.active) return;

            if (this.isHoldable)
                this.value = false;
            if (this.isHoldable || this.isToggleable)
                this.active = false;
        },

        onTouchCancelled: function(touch, event) {
            this.onTouchEnded(touch, event);
        }
    });

    sneaky.ButtonSkinnedBase = cc.Sprite.extend({
        ctor: function() {
            this._super();

            this.defaultSprite = null;
            this.activatedSprite = null;
            this.disabledSprite = null;
            this.pressSprite = null;
            this.button = null;

            this.schedule(this.watchSelf);
        },

        watchSelf: function() {
            var button = this.button;
            if(button == null) return;

            function safeSetVisible(sprite, value) {
                if(sprite) sprite.setVisible(value);
            }

            if (!button.status){
                safeSetVisible(this.disabledSprite, true);
            }
            else {
                safeSetVisible(this.disabledSprite, false);

                if(!button.active){
                    safeSetVisible(this.pressSprite, false);

                    if(button.value == false){
                        safeSetVisible(this.activatedSprite, false);
                        safeSetVisible(this.defaultSprite, true);
                    }
                    else {
                        safeSetVisible(this.activatedSprite, true);
                    }
                }
                else {
                    safeSetVisible(this.defaultSprite, false);
                    safeSetVisible(this.pressSprite, true);
                }
            }
        },

        setContentSize: function(s) {
            this._super(s);
            if(this.button) {
                this.button.setRadius(s.width/2);
            }
        },

        setDefaultSprite: function(aSprite) {
            if(this.defaultSprite){
                this.defaultSprite.removeFromParent(true);
            }
            this.defaultSprite = aSprite;
            if(aSprite){
                var size = aSprite.getContentSize();
                aSprite.setPosition(size.width/2, size.height/2);

                this.setContentSize(size);
                this.addChild(aSprite, 0);
            }
        },

        setActivatedSprite: function(aSprite) {
            if(this.activatedSprite){
                this.activatedSprite.removeFromParent(true);
            }
            this.activatedSprite = aSprite;
            if(aSprite){
                var size = this.getContentSize();
                aSprite.setPosition(size.width/2, size.height/2);

                this.setContentSize(aSprite.getContentSize());
                this.addChild(aSprite, 1);
            }
        },

        setDisabledSprite: function(aSprite) {
            if(this.disabledSprite){
                this.disabledSprite.removeFromParent(true);
            }
            this.disabledSprite = aSprite;
            if(aSprite){
                var size = this.getContentSize();
                aSprite.setPosition(size.width/2, size.height/2);

                this.setContentSize(aSprite.getContentSize());
                this.addChild(aSprite, 2);
            }
        },

        setPressSprite: function(aSprite)
        {
            if(this.pressSprite){
                this.pressSprite.removeFromParent(true);
            }
            this.pressSprite = aSprite;
            if(aSprite){
                var size = this.getContentSize();
                aSprite.setPosition(size.width/2, size.height/2);

                this.setContentSize(aSprite.getContentSize());
                this.addChild(aSprite, 3);
            }
        },

        setButton: function(aButton) {
            if(this.button){
                this.button.removeFromParent(true);
            }
            this.button = aButton;
            if(aButton){
                var size = this.getContentSize();
                aButton.setPosition(size.width/2, size.height/2);

                if(this.defaultSprite)
                    aButton.setRadius(this.defaultSprite.getContentSize().width/2);

                this.addChild(aButton, 4);
            }
        }
    });

    sneaky.Joystick = cc.Node.extend({
        ctor: function(size) {
            this._super();

            // getter
            this.degrees = 0;//float degrees;
            this.velocity = cc.PointZero();//CGPoint velocity;

            // setter
            this.autoCenter = true;//BOOL autoCenter;
            this.isDPad = false;//BOOL isDPad;
            this.hasDeadzone = false; //Turns Deadzone on/off for joystick, always YES if ifDpad == YES
            this.numberOfDirections = 4; //Used only when isDpad == YES

            this.stickPosition = cc.p(size.width/2, size.height/2);
            this.joystickRadius = size.width/2;
            this.joystickRadiusSq = 0;//float joystickRadiusSq;
            this.thumbRadius = 32;
            this.thumbRadiusSq = 0; //float thumbRadiusSq;
            this.deadRadius = 0; //Size of deadzone in joystick (how far you must move before input starts). Automatically set if isDpad == YES
            this.deadRadiusSq = 0;//float deadRadiusSq;

            //Cocos node stuff
            this.setPosition(size.width/2, size.height/2);
            this.setContentSize(size);
        },

        onEnterTransitionDidFinish: function() {
            this._super();
            cc.registerTargetedDelegate(1, true, this);
        },

        onExit: function() {
            this._super();
            cc.unregisterTouchDelegate(this);
        },

        updateVelocity: function(point) {
            // Calculate distance and angle from the center.
            var size = this.getContentSize();
            var dx = point.x;
            var dy = point.y;
            var dSq = dx * dx + dy * dy;

            if(dSq <= this.deadRadiusSq) {
                this.velocity = cc.PointZero();
                this.degrees = 0.0;
                this.stickPosition = cc.p(size.width/2, size.height/2);
                return;
            }

            var angle = Math.atan2(dy, dx); // in radians
            if(angle < 0){
                angle += cc.PI * 2;
            }

            if(this.isDPad){
                var anglePerSector = 360.0 / this.numberOfDirections * cc.RAD;
                angle = Math.round(angle/anglePerSector) * anglePerSector;
            }

            var cosAngle = Math.cos(angle);
            var sinAngle = Math.sin(angle);

            // NOTE: Velocity goes from -1.0 to 1.0.
            if (dSq > this.joystickRadiusSq || this.isDPad) {
                dx = cosAngle * this.joystickRadius;
                dy = sinAngle * this.joystickRadius;
            }

            this.velocity = cc.p(dx/this.joystickRadius, dy/this.joystickRadius);
            this.degrees = angle * cc.DEG;

            // Update the thumb's position
            this.stickPosition = cc.p(dx + size.width/2, dy + size.height/2);
        },

        setIsDPad: function(b) {
            this.isDPad = b;
            if(this.isDPad){
                this.hasDeadzone = true;
                this.deadRadius = 10.0;
            }
        },

        setJoystickRadius: function(r) {
            this.joystickRadius = r;
            this.joystickRadiusSq = r * r;
        },

        setThumbRadius: function(r) {
            this.thumbRadius = r;
            this.thumbRadiusSq = r * r;
        },

        setDeadRadius: function(r) {
            this.deadRadius = r;
            this.deadRadiusSq = r * r;
        },

        onTouchBegan: function(touch ,event) {
            var location = touch.getLocation();
            location = this.convertToNodeSpace(location);

            //Do a fast rect check before doing a circle hit check:
            var joystickRadius = this.joystickRadius;
            if(location.x >= -joystickRadius && location.x <= joystickRadius
                && location.y >= -joystickRadius && location.y <= joystickRadius) {
                var dSq = location.x * location.x + location.y * location.y;
                if(dSq < this.joystickRadiusSq){
                    this.updateVelocity(location);
                    return true;
                }
            }
            return false;
        },

        onTouchMoved: function(touch, event) {
            var location = touch.getLocation();
            location = this.convertToNodeSpace(location);
            this.updateVelocity(location);
        },

        onTouchEnded: function(touch, event) {
            var size = this.getContentSize();
            var location = cc.p(0, 0);
            if(!this.autoCenter){
                location = touch.getLocation();
                location = this.convertToNodeSpace(location);
            }
            this.updateVelocity(location);
        },

        onTouchCancelled: function(touch, event) {
            this.onTouchEnded(touch, event);
        }
    });

    sneaky.JoystickSkinnedBase = cc.Sprite.extend({
        ctor: function() {
            this._super();

            this.backgroundSprite = null;
            this.thumbSprite = null;
            this.joystick = null;

            this.schedule(this.updatePositions);
        },

        updatePositions: function() {
            if(this.joystick && this.thumbSprite)
                this.thumbSprite.setPosition(this.joystick.stickPosition);
        },

        setContentSize: function(s) {
            this._super(s);
            if(this.backgroundSprite) {
                var size = this.getContentSize();
                this.backgroundSprite.setContentSize(s);
                this.backgroundSprite.setPosition(size.width/2, size.height/2);
            }
            if(this.joystick) {
                this.joystick.setJoystickRadius(s.width/2);
            }
        },

        setBackgroundSprite: function(aSprite) {
            if(this.backgroundSprite){
                this.backgroundSprite.removeFromParent(true);
            }
            this.backgroundSprite = aSprite;
            if(aSprite){
                this.setContentSize(aSprite.getContentSize());
                this.addChild(aSprite, 0);
            }
        },

        setThumbSprite: function(aSprite) {
            if(this.thumbSprite){
                this.thumbSprite.removeFromParent(true);
            }
            this.thumbSprite = aSprite;
            if(aSprite){
                var size = this.getContentSize();

                aSprite.setPosition(size.width/2, size.height/2);
                this.addChild(aSprite, 1);

                if(this.joystick) {
                    this.joystick.setThumbRadius(aSprite.getContentSize().width/2);
                }
            }
        },

        setJoystick: function(aJoystick) {
            if(this.joystick){
                this.joystick.removeFromParent(true);
            }
            this.joystick = aJoystick;
            if(aJoystick){
                this.addChild(aJoystick, 2);

                if(this.thumbSprite)
                    aJoystick.setThumbRadius(this.thumbSprite.getContentSize().width/2);
                else
                    aJoystick.setThumbRadius(0);

                if(this.backgroundSprite) {
                    aJoystick.setJoystickRadius(this.backgroundSprite.getContentSize().width/2);
                }
            }
        }
    });

}());