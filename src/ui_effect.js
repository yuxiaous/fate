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
    }
}