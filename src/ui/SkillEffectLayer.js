var SkillEffectLayer = ui.GuiWindowBase.extend({
    _guiFile: "ui/skillEffectLayer.json",

    ctor: function (curBattleScene_) {
        this._super();
        this._curBattleScene = curBattleScene_;


    },

    onEnter: function () {
        this._super();

        this._bg = this.seekWidgetByName("effect_bg");
        this._roleHead = this.seekWidgetByName("role_head");
        this._roleHead.setVisible(false);
        //this._roleHead.loadTexture("res/images/ui/ui_139.png");
        //this._roleHead.setGlobalZOrder(1000);

        this._skillLabelNode =[];
        _.each(["Image_1",
                "Image_2",
                "Image_3",
                "Image_4",
                "Image_5",
                "Image_6"],function (str_) {
            var skillName = this.seekWidgetByName(str_);
            if(skillName){
                skillName.setVisible(false);
                this._skillLabelNode.push(skillName);
            }
        },this);

        this._skillStrings =[];
        _.each(["res/images/ui/ui_262.png",
            "res/images/ui/ui_263.png",
            "res/images/ui/ui_264.png",
            "res/images/ui/ui_265.png",
            "res/images/ui/ui_266.png",
            "res/images/ui/ui_267.png"],function (str_) {
                this._skillStrings.push(str_);
        },this);

        var rolePicName = "res/images/ui/ui_139.png";
        if(1){
            rolePicName = "res/images/ui/ui_256.png";
        }
        var rolePic = cc.Sprite.create(rolePicName);
        rolePic.setPosition(cc.p(0,0));
        rolePic.setAnchorPoint(cc.p(0,0));
        rolePic.setScaleX(-1);
        cc.director.getRunningScene().addChild(rolePic);

        this._skillNameCont = []
        var rolePicSize = rolePic.getContentSize();
        rolePic.runAction(cc.Sequence.create(
            cc.EaseOut.create(cc.MoveBy.create(0.9,cc.p(rolePicSize.width,0)),10),
            cc.CallFunc.create(function () {
                _.each(this._skillLabelNode, function (skill_pic_,idx_) {
                    var skillName = cc.Sprite.create(this._skillStrings[idx_]);

                    var pos = skill_pic_.convertToWorldSpace();
                    skillName.setPosition(cc.p(pos.x,pos.y + 100));

                    skillName.skillValue = 2.2;
                    if(idx_ > 1){
                        skillName.skillValue = 2.0;
                    }
                    cc.director.getRunningScene().addChild(skillName);
                    this._skillNameCont.push(skillName);
                    skillName.setScale(10.0);
                    skillName.setVisible(false);

                    skillName.runAction(cc.Sequence.create(
                        cc.DelayTime.create(idx_ * 0.1),
                        cc.CallFunc.create(function () {
                            skillName.setVisible(true);
                            skillName.setOpacity(0);
                            skillName.runAction(cc.Spawn.create(
                                cc.FadeIn.create(0.2),
                                cc.ScaleTo.create(0.2,skillName.skillValue)
                            ))
                        },this)
                    ));

                },this);
            },this),
            cc.DelayTime.create(0.2),
            cc.EaseIn.create(cc.MoveBy.create(0.8,cc.p(-rolePicSize.width,0)),10),
            cc.CallFunc.create(function (target_) {
                target_.removeFromParent();
                target_ = null;
            })
        ));

        this.startAddSkillEffect();
    },

    startAddSkillEffect : function () {
        _.each(this._curBattleScene._monsters, function(monster) {
            if(monster){
                monster.setRoleAi(RoleAi.Type.Stake);
            }
        }, this);

        if(this._curBattleScene._boss){
            this._curBattleScene._boss.setRoleAi(RoleAi.Type.Stake);
        }

        //front ui
        var streetZorder = this._curBattleScene._street.getLocalZOrder();
        this._curBattleScene._foreUI.setLocalZOrder(streetZorder - 1);

        this._curBattleScene._frontUi.setLocalZOrder(-10);

        cc.director.getScheduler().schedule(this.addRefreshLine,this,0.5,cc.REPEAT_FOREVER,0,false,"addLine");

        //this.runAction(cc.Sequence.create(
        //    cc.DelayTime.create(4.0),
        //    cc.CallFunc.create(function (target_) {
        //            target_.delSkillEffect();
        //            target_.removeFromParent();
        //            //target_ = null;
        //    })
        //));
    },

    delSkillEffect : function () {
        _.each(this._curBattleScene._monsters, function(monster) {
            if(monster){
                var data = monster.aiData;
                monster.setRoleAi(RoleAi.Type.XiaoGuai,{
                    atkPer    : data.ai.atkPer,
                    restPer   : data.ai.restPer,
                    rangeActW : data.ai.rangeActW,
                    rangeActH : data.ai.rangeActH,
                    followAtk : data.ai.followAtk,
                    isRemote  : data.ai.isRemote
                });
            }
        }, this);

        if(this._curBattleScene._boss){
            var data = this._curBattleScene._boss.aiData;
            this._curBattleScene._boss.setRoleAi(RoleAi.Type.XiaoGuai,{
                atkPer    : data.ai.atkPer,
                restPer   : data.ai.restPer,
                rangeActW : data.ai.rangeActW,
                rangeActH : data.ai.rangeActH,
                followAtk : data.ai.followAtk,
                isRemote  : data.ai.isRemote
            });
        }


        _.each(this._skillNameCont, function (pic_) {
            if(pic_){
                pic_.removeFromParent();
            }
        })

        cc.director.getScheduler().unschedule("addLine",this);

        this._bg.removeAllChildren();

        //front ui
        var streetZorder = this._curBattleScene._street.getLocalZOrder();
        this._curBattleScene._foreUI.setLocalZOrder(streetZorder + 1);

        this._curBattleScene._frontUi.setLocalZOrder(0);
    },

    addRefreshLine: function () {
        var lineNameCon = [
            "res/images/ui/ui_259.png",
            "res/images/ui/ui_260.png",
            "res/images/ui/ui_261.png"
        ]
        var winSize = cc.director.getWinSize();
        var minY = 100;
        var maxY = winSize.height - 100;
        var moveLineNum = _.random(8,14);

        for(var idx = 0 ; idx < moveLineNum; idx++){
            var lineName  = lineNameCon[_.random(0,2)];
            var lineSp = cc.Sprite.create(lineName);
            lineSp.setPosition(cc.p( - lineSp.getContentSize().width, _.random(minY,maxY)));
            this._bg.addChild(lineSp);

            lineSp.runAction(cc.Sequence.create(
                cc.DelayTime.create(_.random(1,3) * 0.1),
                cc.MoveBy.create(0 + _.random(1,3) * 0.1,cc.p(winSize.width + lineSp.getContentSize().width,0)),
                cc.CallFunc.create(function (target_) {
                    target_.removeFromParent();
                    target_ = null;
                })
            ));
        }

    },

    onExit : function () {
        this._super();

        this._bg = null;
        this._roleHead = null;
        this._curBattleScene = null;
        this._skillNameCont = null;
        this._skillLabelNode = null;
        this._skillStrings = null;

    }
});