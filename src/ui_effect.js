/*
* 2015/06/18
* shilei@hdngame.com
* */
var UiEffect = {
    //文字向上飘,然后渐隐藏
    labelMoveUp : function (label_) {
        var moveUp = cc.MoveBy.create(0.8,cc.p(0,100));

        label_.runAction(cc.Sequence.create(
            moveUp,
            cc.CallFunc.create(function () {
                label_.removeFromParent();
            })
        ));
    },

    //盖章效果
    iconSealEffect : function (panel_,callfunc_,target_,sealSlow_) {
        if(!panel_){
            return;
        }

        var sealTime = 0.15;
        var sealValue = 5.0;
        if(sealSlow_ == true){
            sealTime = 0.4;
            sealValue = 10.0;
        }
        panel_.setVisible(true);
        panel_.setScale(sealValue);
        panel_.setOpacity(0);
        var act = cc.Spawn.create(
            cc.ScaleTo.create(sealTime,1.0),
            cc.FadeIn.create(sealTime)
        );
        panel_.runAction(cc.Sequence.create(
            act,
            cc.CallFunc.create(
                function () {
                    if(callfunc_ && target_){
                        callfunc_.apply(target_);
                    }
                }
            )
        ));
    },

    //盖章效果，附加旋转
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

    //放大显示
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
    },

    //按钮BBBBBB
    buttonBBB : function (btn_) {
        if(btn_){
            btn_.runAction(cc.RepeatForever.create(
                cc.Sequence.create(
                    cc.ScaleTo.create(0.5,1.2),
                    cc.ScaleTo.create(0.5,1.0)
                )
            ));
        }
    },

    //Y轴放大打开
    iconOpenYEffect : function (panel_,callfunc_,target_) {
        panel_.setScaleY(0.1);
        panel_.runAction(cc.Sequence.create(
            cc.scaleTo(0.2, 1.1),
            cc.scaleTo(0.1, 1.0),
            cc.CallFunc.create(function () {
                if(callfunc_ && target_){
                    callfunc_.apply(target_);
                }
            })
        ));
    },

    blockShopItemWithRMB : function () {
        //所有RMB购买的先屏蔽
        var label = cc.LabelTTF.create("功能暂未开启，敬请期待 !")
        var winSize = cc.director.getWinSize();
        label.setFontSize(30);
        label.setPosition(cc.p(winSize.width/2,winSize.height/2));
        cc.director.getRunningScene().addChild(label,100000);
        UiEffect.labelMoveUp(label);


        //var uiTxt =  new ccui.Text();
        //uiTxt.setString("功能暂未开启，敬请期待 !");
        //uiTxt.setColor(cc.Color(250,10,10));
        //var winSize = cc.director.getWinSize();
        //uiTxt.setPosition(cc.p(winSize.width/2,winSize.height/2));
        //cc.director.getRunningScene().addChild(uiTxt,100000);
        //cc.director.getRunningScene().addChild(uiTxt,100000);
        //UiEffect.labelMoveUp(uiTxt);

        return true;
    }

}