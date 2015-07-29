/**
 * Created by yuxiao on 15/4/16.
 */


var PhysicalWorld = cc.Layer.extend({
    ctor: function() {
        //LOG("PhysicalWorld.ctor")
        this._super();

        this.physicalNodes = [];
        this.shakingNode = null;

        this._pauseTime = 0;

        this._slowMultiple = 1;
        //this.scheduleUpdate();

    },

    onEnter: function() {
        //LOG("PhysicalWorld.onEnter")
        this._super();

        this._bindings = [
            notification.createBinding(notification.event.PHYSICAL_PAUSE, function(event, time) {
                if(time != undefined) {
                    this.pause(time);
                }
                else {
                    this.pause();
                }
            }, this),
            notification.createBinding(notification.event.PHYSICAL_RESUME, function() {
                this.resume();
            }, this),
            notification.createBinding(notification.event.PHYSICAL_QUAKE, function(event, attr) {
                if(attr && attr.intensity && attr.time) {
                    this.quake(attr.intensity, attr.time)
                }
            }, this)
        ];

        this.schedule(this.advanceTime);
    },

    onExit: function() {
        //LOG("PhysicalWorld.onExit")
        notification.removeBinding(this._bindings);

        this.shakingNode = null;
        this.removeAllPhysicalNodes();
        this.unschedule(this.advanceTime);

        this._super();
    },

    setSlowPlay : function (slowMultiple_) {
        this._slowMultiple = slowMultiple_;
    },

    advanceTime: function(dt) {
        dt = dt / this._slowMultiple;

        if(this._pauseTime > 0) {
            this._pauseTime -= dt;
            return;
        }

        dragonBones.DragonBonesHelper.advanceWorldClock(dt);

        _.each(this.physicalNodes, function(node) {
            var offset = {x: 0, y: 0, z: 0};
            var dv, v0, vt, dl, dir;

            var drag = (node.drag == undefined ? PhysicalWorld.drag : node.drag);

            // calculate offset z
            if(node.velocity.z != 0 || node.altitude > 0) {
                var tmpGravity = (node.gravity == undefined ? PhysicalWorld.gravity : node.gravity);
                dv = tmpGravity * dt;

                v0 = node.velocity.z;
                vt = v0 + dv;
                dl = (v0 + vt) * dt * 0.5;

                if(node.altitude + dl < 0) {
                    dv = -node.velocity.z;
                    dl = -node.altitude;
                }

                node.velocity.z += dv;
                offset.z = dl;
            }

            // calculate offset x
            if(node.altitude > 0) {
                offset.x = node.velocity.x * dt;
            }
            else if(node.velocity.x != 0) {
                dir = node.velocity.x < 0 ? -1 : 1;
                dv = drag * dt * dir;
                v0 = node.velocity.x;
                vt = v0 + dv;
                dl = (v0 + vt) * dt * 0.5;

                if((node.velocity.x + dv) * dir < 0) {
                    dv = -node.velocity.x;
                    dl = 0.5 * node.velocity.x * node.velocity.x * dir / -drag;
                }

                node.velocity.x += dv;
                offset.x = dl;
            }

            // calculate offset y
            if(node.altitude > 0) {
                offset.y = node.velocity.y * dt;
            }
            else if(node.velocity.y != 0) {
                dir = node.velocity.y < 0 ? -1 : 1;
                dv = drag * dt * dir;
                v0 = node.velocity.y;
                vt = v0 + dv;
                dl = (v0 + vt) * dt * 0.5;

                if((node.velocity.y + dv) * dir < 0) {
                    dv = -node.velocity.y;
                    dl = 0.5 * node.velocity.y * node.velocity.y * dir / -drag;
                }

                node.velocity.y += dv;
                offset.y = dl;
            }
            var pos = node.getSpacePosition();
            node.setSpacePosition(pos.x + offset.x, pos.y + offset.y, pos.z + offset.z);

            node.advanceTime(dt);
        }, this);
    },

    pause: function(time) {
        if(time == undefined) time = 3600 * 24 * 30;

        this.scheduleOnce(function() {
            this._pauseTime = time;
        }.bind(this));
    },

    resume: function() {
        this._pauseTime = 0;
    },

    quake: function(intensity, duration) {
        if(this.shakingNode != null) {
            var action = jsb.FallOffShake.create(duration, intensity);
            this.shakingNode.runAction(action);
        }
    },

    addPhysicalNode: function(node) {
        if(!_.contains(this.physicalNodes, node)) {
            this.physicalNodes.push(node);
            node.physicalWorld = this;

            this.addChild(node);
        }
    },

    removePhysicalNode: function(node) {
        this.physicalNodes = _.without(this.physicalNodes, node);
        node.physicalWorld = null;

        this.removeChild(node);
    },

    removeAllPhysicalNodes: function() {
        _.each(this.physicalNodes, function(node) {
            node.physicalWorld = null;

            this.removeChild(node);
        }, this);

        this.physicalNodes = [];
    }
});


PhysicalWorld.gravity = -1500;
PhysicalWorld.drag = -1500;

