/**
 * Created by yuxiao on 15/1/30.
 */

var BattleUILayer = ui.GuiWidgetBase.extend({
    _guiFile : "res/ui/BattleUiLayer.json",

    ctor : function () {
        this._super();

    },

    onEnter : function () {
        this._super();

        this.bossP = this.seekWidgetByName("bossPanel");
        this._bossPanel = new BattleUILayer.BossPanel();
        this._bossPanel.setWidget(this.bossP);

        this.roleP = this.seekWidgetByName("rolePanel")
        this._rolePanel = new BattleUILayer.RolePanel();
        this._rolePanel.setWidget(this.roleP);


        this._magicBottleLable = this.seekWidgetByName("lbl_bottle_num");
        if(BattleSystem.instance.curIsTryBattle()){
            this._magicBottleLable.setString(String(configdb.property[112].value));
        }
        else{
            this.refreshBattleData();
        }


        //def Label
        this._roundPanel =  this.seekWidgetByName("roundPanel");
        this._roundLabelPanel = this.seekWidgetByName("roundLabelPanel");
        this._roundBg =this.seekWidgetByName("labelBg");
        this._roundLabel = this.seekWidgetByName("roundLabel");

        this._roundLabelPanel.setVisible(false);
        this._roundPanel.setVisible(false);



        this._bindings = [
            notification.createBinding(notification.event.BATTLE_USE_ITEM_RESULT, function () {
                this.refreshBattleData();
            },this),
            notification.createBinding(notification.event.ITEM_INFO, function () {
                this.refreshBattleData();
            }, this),
            notification.createBinding(notification.event.BATTLE_STOP_STATE, function () {
                this._on_btn_stopBattle();
            },this)
        ];
    },

    onExit : function () {
        this._bossPanel = null;
        this._rolePanel = null;
        this.bossP = null;
        this.roleP = null;

        this._roundBg = null;
        this._roundLabelPanel = null;
        this._roundPanel = null;

        this._magicBottleLable = null;

        notification.removeBinding(this._bindings);
        this._super();
    },

    refreshBattleData : function () {
        if(BattleSystem.instance.curIsTryBattle()){
            var lastNum = parseInt(this._magicBottleLable.getString())
            this._magicBottleLable.setString(String(--lastNum));
        }
        else{
            var magicBottleNum = BagSystem.instance.getItemNums(100007);
            this._magicBottleLable.setString(String(magicBottleNum));
        }
    },

    setBossRound : function (isBossRound_) {
        this.bossP.setVisible(isBossRound_);
    },

    _on_btn_stopBattle : function () {
        //cc.director.pause();
        var pausePanel = new PauseLayer();
        pausePanel.pop();
        notification.emit(notification.event.GAME_PAUSE);
    },

    _on_btn_bloodBottle : function () {
        if(Number(this._magicBottleLable.getString()) > 0){
            var target = cc.director.getRunningScene()._hero;
            if(target.roleDataManager.hp == target.roleDataManager.maxHp &&
                target.roleDataManager.mp == target.roleDataManager.maxMp){     //单加满血
                var label = cc.LabelTTF.create("血和蓝都是满的，无需补充 !")
                var winSize = cc.director.getWinSize();
                label.setFontSize(24);
                label.setPosition(cc.p(winSize.width/2,winSize.height/2));
                this.addChild(label);
                UiEffect.labelMoveUp(label);
                return;
            }

            if(BattleSystem.instance.curIsTryBattle()){
                this.refreshBattleData();
                ItemSystem.instance.useBottleItem();
            }
            else{
                BattleSystem.instance.useBattleItem({
                    itemId : 100007,
                    num : 1
                });
            }
        }
        else{
            if(BattleSystem.instance.curIsTryBattle()){
                UiEffect.showFloatLabel("血瓶已经用完");
            }
            else{
                var bottleId = 18002;
                var conf = ShopSystem.getConfig(bottleId);
                if(conf){
                    var str = "花费{0}{1}，购买{2}".format(conf.pay_cost, ShopSystem.getPayTypeString(conf.pay_type), conf.name);
                    var msg = new MessageBoxOkCancel(str,"购买","取消");
                    msg.setOkCallback(function () {
                        //cc.director.resume();
                        notification.emit(notification.event.GAME_RESUME);
                        if(UiEffect.blockShopItemWithRMB()){
                            return
                        }
                        ShopSystem.instance.buyGood(bottleId);
                        this._on_btn_stopBattle();
                    },this);
                    msg.setCancelCallback(function () {
                        //cc.director.resume();
                        notification.emit(notification.event.GAME_RESUME);
                    });
                    msg.pop();
                    //cc.director.pause();
                    notification.emit(notification.event.GAME_PAUSE);
                }
            }
        }
    },
    
    startActionRoundLabel : function (roundIdx_, callFunc_, target_) {
        this._roundPanel.setVisible(true);
        this._roundLabelPanel.setVisible(true);
        //this._roundBg.setVisible(true);
        this._roundBg.setOpacity(0);
        this._roundLabel.setString(String(roundIdx_));

        var winSize = cc.director.getWinSize();
        //this._roundPanel.setPosition(cc.p(winSize.width/2,460));
        //this._roundLabelPanel.setPosition(cc.p(winSize.width/2,460));
        //
        //
        //var oriPos = this._roundPanel.getPosition();
        var oriPos = cc.p(winSize.width/2,460);
        this._roundPanel.setPosition(cc.p(oriPos.x + winSize.width , oriPos.y));
        this._roundLabelPanel.setPosition(cc.p(oriPos.x - winSize.width,oriPos.y))


        var that = this;
        this._roundPanel.runAction(cc.Sequence.create(
            cc.MoveBy.create(0.8,cc.p(-winSize.width,0)),
            cc.DelayTime.create(1.0),
            cc.MoveBy.create(0.5,cc.p(-winSize.width,0))
        ))

        this._roundLabelPanel.runAction(cc.Sequence.create(
            cc.MoveBy.create(0.8,cc.p(winSize.width,0)),
            cc.CallFunc.create(function () {
                that._roundBg.runAction(cc.FadeIn.create(0.5));
            }),
            cc.DelayTime.create(1.0),
            cc.MoveBy.create(0.5,cc.p(winSize.width,0)),
            cc.CallFunc.create(function () {
                if(target_ && callFunc_){
                    callFunc_.apply(target_);
                }
            })
        ))


    }
});


BattleUILayer.RolePanel = ui.GuiController.extend({
    _guiFile: "res/ui/TopLeft.json",

    ctor: function() {
        this._super();
        //LOG("ROLE BATTLE PANEL");
    },

    onEnter: function() {
        this._super();
        this._progress_hp = this.seekWidgetByName("loading_hp");
        this._progress_hp_droping = this.seekWidgetByName("loading_hp_droping");
        this._progress_mp = this.seekWidgetByName("loading_mp");
        this._progress_mp_droping = this.seekWidgetByName("loading_mp_droping");


        this._lbl_hp = this.seekWidgetByName("lbl_hp");
        this._lbl_mp = this.seekWidgetByName("lbl_mp");
        this._lbl_level = this.seekWidgetByName("lbl_level");

        // level
        this._lbl_level.setString(String(PlayerSystem.instance.level));

        cc.director.getScheduler().schedule(this.refresh,this,0.1,cc.REPEAT_FOREVER,0,false,"REFRESH");
        cc.director.getScheduler().schedule(this.refreshMp,this,4.0,cc.REPEAT_FOREVER,0,false,"MP");

    },

    onExit: function() {
        cc.director.getScheduler().unschedule("REFRESH", this);
        cc.director.getScheduler().unschedule("MP", this);
        this._progress_hp = null;
        this._progress_mp = null;
        this._progress_hp_droping = null;
        this._progress_mp_droping = null;
        this._lbl_hp = null;
        this._lbl_mp = null;
        this._lbl_level = null;
        this._super();
    },

    setRole: function(role) {
        this._role = role;
    },

    refreshMp : function (dt_) {
        if(this._role == null)
            return;

        var originData = this._role.roleDataManager;
        originData.mp += 1;
        if(originData.mp > originData.maxMp){
            originData.mp = originData.maxMp;
        }
    },

    refresh: function() {
        if(this._role == null)
            return;

        var originData = this._role.roleDataManager;

        // hp
        var percentHP = originData.hp / originData.maxHp * 100;
        this._progress_hp.setPercent(percentHP);
        RoleBloodBar.setPercentChangeTo(percentHP,this._progress_hp_droping);

        this._lbl_hp.setString(this._lbl_hp._str_original.format(originData.hp, originData.maxHp));

        //mp
        var percentMP = originData.mp / originData.maxMp * 100;
        this._progress_mp.setPercent(percentMP);
        RoleBloodBar.setPercentChangeTo(percentMP,this._progress_mp_droping);

        this._lbl_mp.setString(this._lbl_hp._str_original.format(originData.mp,originData.maxMp));


        _.each([RoleAction.Type.SKILL1,
                RoleAction.Type.SKILL2,
                RoleAction.Type.SKILL3,
                RoleAction.Type.SKILL4,
                RoleAction.Type.SKILL5],
                function (skillType_) {
                    //var actionData = actions[skillType_];

                    var curCost = SkillSystem.instance.getSkillUpMpcost(skillType_);
                    //LOG("cur cost = " + curCost);
                    var scene = cc.director.getRunningScene();
                    var isEnoughMp = true;

                    if(curCost > originData.mp){
                        isEnoughMp = false;
                    }
                    scene._operator.setBtnMpIsNotEnough(skillType_,isEnoughMp);
                }
        )
    }
});

BattleUILayer.BossPanel = ui.GuiController.extend({
    _guiFile : "res/ui/TopRight.json",

    ctor : function () {
        this._super();
       // LOG("BOSS BATTLE PANEL CTOR");
    },

    onEnter : function () {
        this._super();

        this._progress_hp = this.seekWidgetByName("loading_hp");
        this._progress_hp_droping = this.seekWidgetByName("loading_hp_droping");

        cc.director.getScheduler().scheduleCallbackForTarget(this, this.refresh);
    },

    onExit : function () {
        this._super();

        this._progress_hp = null;
        this._progress_hp_droping = null;

        this._boss = null;
        cc.director.getScheduler().unscheduleCallbackForTarget(this,this.refresh)
    },

    setBoss : function (boss_) {
        this._boss = boss_;

        this._bossIcon = this.seekWidgetByName("bossIconName");
        if(this._bossIcon && this._boss.iconName){
            this._bossIcon.initWithFile(this._boss.iconName);
        }
    },

    refresh : function () {
        if(this._boss == null){
            return;
        }
        var data = this._boss.roleDataManager;

        // hp
        var percent = data.hp / data.maxHp * 100;
        this._progress_hp.setPercent(percent);

        RoleBloodBar.setPercentChangeTo(percent,this._progress_hp_droping)
    }
});

