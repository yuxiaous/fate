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
        this.tmpLabel = ccui.TextBMFont.create(this._damageValue,"res/fonts/fnt7.fnt");
        this.addChild(this.tmpLabel);
    },

    onExit : function () {
        this._super();
        this.tmpLabel = null;
    },

    playDamageWorld : function (type_) {
        //if(cc.random0To1() > 0.5){
        //    type_ = true;
        //}
        if(type_){
            this.tmpLabel.setFntFile("res/fonts/fnt6.fnt");

            var moveUp = cc.moveBy(0.2,cc.p(0,110));
            var moveScale = cc.scaleTo(0.2,2.5);
            var jumpAncScale = cc.spawn(moveUp,moveScale);

            var moveUp_1 = cc.moveBy(0.2,cc.p(0,50));
            var fadeOut_1 = cc.fadeOut(0.2);
            var moveAndFade = cc.spawn(moveUp_1,fadeOut_1);

            var moveScale_1 = cc.scaleTo(0.3,1.7);

            var moveEnd = cc.callFunc(function () {
                this.tmpLabel.removeFromParent();
                this.removeFromParent();
            },this);

            this.tmpLabel.runAction(cc.sequence(jumpAncScale,moveScale_1,moveAndFade,moveEnd));
        }
        else{
            var jumpAct = cc.jumpBy(0.8, cc.p(30, 100), 80, 1);
            var moveEnd = cc.callFunc(function () {
                this.tmpLabel.removeFromParent();
                this.removeFromParent();
            },this);
            this.tmpLabel.runAction(cc.sequence(jumpAct,moveEnd));
        }
    }
});

DamageWorld.createDamage = function (value_,target_,targetSize_,isCrit_) {
    var self = target_.getParent();
    if(self){
        var tmpDamageW = new DamageWorld(value_);
        tmpDamageW.setPosition(cc.pAdd(target_.getPosition(),cc.p(0,targetSize_.height * 0.6)));
        tmpDamageW.setLocalZOrder(self.getLocalZOrder()+1);
        self.addChild(tmpDamageW);

        tmpDamageW.playDamageWorld(isCrit_);
    }
};

var CombatForcesEffect = ccui.Layout.extend({
    ctor : function (forcesValue_) {
        this._super();
        this._isUp = forcesValue_ > 0 ? true : false;
        this._forcesValue = forcesValue_;
    },

    onEnter : function () {
        this._super();

        var imageStr = "res/images/code_ui/ui_177.png";
        var labelStr = "res/fonts/fnt8.fnt";
        if(!this._isUp){
            imageStr = "res/images/code_ui/ui_178.png";
            labelStr = "res/fonts/fnt9.fnt";

            this._forcesValue *= -1;
        }

        this._imageTitle = ccui.ImageView.create(imageStr);
        var size = cc.director.getWinSize();
        this._imageTitle.setPosition(cc.p(size.width/2,size.height/2));
        this._imageTitle.setAnchorPoint(cc.p(0.5,0.5));
        this.addChild(this._imageTitle);
        var titleSize = this._imageTitle.getContentSize();

        this.tmpLabel = ccui.TextBMFont.create(this._forcesValue,labelStr);
        this.tmpLabel.setPosition(cc.p(titleSize.width -120,titleSize.height/2));
        this.tmpLabel.setAnchorPoint(cc.p(0,0.5));
        this._imageTitle.addChild(this.tmpLabel);
    },

    onExit : function () {
        this._super();

    },

    playCombatForcesEffect : function () {
        var moveUp = cc.MoveBy.create(0.5,cc.p(0,100));
        var actionEnd = cc.CallFunc.create(function () {
            this._imageTitle.removeFromParent();
            this.removeFromParent();
        },this);
        this._imageTitle.runAction(cc.Sequence.create(
            moveUp,actionEnd
        ));
    }

});

CombatForcesEffect.createForcesEffect = function (value_,target_) {
    var self = target_;
    if(self){
        var tmpCombatF = new CombatForcesEffect(value_);
        self.addChild(tmpCombatF);
        tmpCombatF.playCombatForcesEffect();
    }
};