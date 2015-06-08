/*
* shilei
* 2015/04/20
* */

var DamageWorld = ccui.Layout.extend({
    ctor : function(damageValue_){
        this._super();
        this._damageValue = damageValue_;
    },

    onEnter : function () {
        this._super();
        this.tmpLabel = ccui.TextBMFont.create(this._damageValue,"res/fonts/fnt2.fnt");
        this.tmpLabel.setScale(0.5);
        this.addChild(this.tmpLabel);
    },

    onExit : function () {
        this._super();
        this.tmpLabel = null;
    },

    playDamageWorld : function (type_) {
        if(type_ == 1){
            var jumpAct = cc.jumpBy(0.8, cc.p(40, 100), 60, 1);
            var moveEnd = cc.callFunc(function () {
                this.tmpLabel.removeFromParent();
                this.removeFromParent();
            },this);
            this.tmpLabel.runAction(cc.sequence(jumpAct,moveEnd));
        }
        else{
            var moveAct = cc.moveBy(1.5,cc.p(0,150));
            var moveEnd = cc.callFunc(function () {
                this.tmpLabel.removeFromParent();
                this.removeFromParent();
            },this);
            this.tmpLabel.runAction(cc.sequence(moveAct,moveEnd));
        }
    }
});

DamageWorld.createDamage = function (value_,target_,targetSize_,CritTimes_) {
    var self = target_.getParent();
    if(self){
        var tmpDamageW = new DamageWorld(value_);
        tmpDamageW.setPosition(cc.pAdd(target_.getPosition(),cc.p(0,targetSize_.height * 0.6)));
        tmpDamageW.setLocalZOrder(self.getLocalZOrder()+1);
        self.addChild(tmpDamageW);

        tmpDamageW.playDamageWorld(1);
    }
}