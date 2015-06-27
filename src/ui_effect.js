/*
* 2015/06/18
* shilei@hdngame.com
* */
var UiEffect = {
    labelMoveUp : function (label_) {
        var moveUp = cc.MoveBy.create(0.8,cc.p(0,100));

        label_.runAction(cc.Sequence.create(
            moveUp,
            cc.CallFunc.create(function () {
                label_.removeFromParent();
            })
        ));
    },

    iconSealEffect : function (panel_) {
        if(!panel_){
            return;
        }
        panel_.setScale(5.0);
        panel_.setOpacity(0);
        panel_.runAction(cc.Spawn.create(
            cc.ScaleTo.create(0.15,1.0),
            cc.FadeIn.create(0.15)
        ));
    },

    iconSealEffect_Rotate : function (panel_,callfunc_,target_) {
        if(!panel_){
            return;
        }
        panel_.setScale(5.0);
        panel_.setOpacity(0);
        var act = cc.Spawn.create(
            cc.ScaleTo.create(0.3,1.0),
            cc.FadeIn.create(0.3),
            cc.RotateBy.create(0.3,360 * 4)
        );
        panel_.runAction(cc.Sequence.create(
            act,
            cc.DelayTime.create(0.5),
            cc.CallFunc.create(function () {
                callfunc_.apply(target_);
            })
        ));
    },

    iconOpenEffect : function (panel_,callfunc_,target_) {
        panel_.scale = 0.1;
        panel_.runAction(cc.Sequence.create(
            cc.scaleTo(0.2, 1.1),
            cc.scaleTo(0.1, 1.0),
            cc.CallFunc.create(function () {
                if(callfunc_ && target_){
                    callfunc_.apply(target_);
                }
            })
        ));
    }
}