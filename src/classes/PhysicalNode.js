/**
 * Created by yuxiao on 15/4/16.
 */


var PhysicalNode = cc.Node.extend({
    ctor: function() {
        this._super();

        this.velocity = {x: 0, y: 0, z: 0};
        this.altitude = 0;

        this.physicalWorld = null;
    },

    dispose: function() {

    },

    advanceTime: function(dt) {
        if(this._shadow) {
            this._shadow.setPosition(0, -this.altitude);
        }

        if(this._guanghuan){
            this._guanghuan.setPosition(0, -this.altitude);
        }
    },

    getSpacePosition: function() {
        var pos = this.getPosition();
        return {x: pos.x, y: pos.y - this.altitude, z: this.altitude};
    },

    setSpacePosition: function(x, y, z) {
        var pos;
        if(y == undefined && z == undefined)
            pos = x;
        else
            pos = {x: x, y: y, z: z};

        if(this.physicalWorld != null) {
            var size = this.physicalWorld.getContentSize();
            var area = cc._rect(0, 0, size.width, size.height);

            if(pos.x < cc.rectGetMinX(area)) pos.x = cc.rectGetMinX(area);
            if(pos.x > cc.rectGetMaxX(area)) pos.x = cc.rectGetMaxX(area);
            if(pos.y < cc.rectGetMinY(area)) pos.y = cc.rectGetMinY(area);
            if(pos.y > cc.rectGetMaxY(area)) pos.y = cc.rectGetMaxY(area);
        }

        this.altitude = pos.z;
        this.setPosition(pos.x, pos.y + pos.z);
        this.setLocalZOrder(-pos.y);
    },

    setSpaceVelocity: function(x, y, z) {
        this.velocity.x = x;
        this.velocity.y = y;
        this.velocity.z = z;
    },

    setShadow: function(width) {
        var shadow = this._shadow;
        if(shadow == null) {
            shadow = cc.Sprite.create("images/shadow1.png");
            this._shadow = shadow;
        }

        shadow.setScale(width / shadow.getContentSize().width);
        this.addChild(shadow, -100);
    },

    hideShadow : function () {
        if(this._shadow){
            this._shadow.setVisible(false);
        }
    },

    setGuanghuan : function () {
        var _guanghuan = this._guanghuan;
        if(_guanghuan == null) {
            _guanghuan = dragonBones.DragonBonesHelper.buildArmatureNode("guanghuan");
            _guanghuan.gotoAndPlay("guanghuan");
            this._guanghuan = _guanghuan;
        }
        this.addChild(_guanghuan,-1);
    },

    removeFromPhysicalWorld: function() {
        if(this.physicalWorld) {
            this.physicalWorld.removePhysicalNode(this);
        }
    }
});

