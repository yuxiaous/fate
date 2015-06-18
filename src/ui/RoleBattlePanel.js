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


        this.refreshBattleData();

        this._bindings = [
            notification.createBinding(notification.event.BATTLE_USE_ITEM_RESULT, function () {
                this.refreshBattleData();
            },this)
        ];
    },

    onExit : function () {
        this._bossPanel = null;
        this._rolePanel = null;
        this.bossP = null;
        this.roleP = null;

        this._magicBottleLable = null;

        notification.removeBinding(this._bindings);
        this._super();
    },

    refreshBattleData : function () {
        var magicBottleNum = 0;
        _.reduce(BagSystem.instance.items, function(sum, item) {
            if(item.id == 100007) {
                magicBottleNum += item.num || 1;
            }
        }, 0, this)

        this._magicBottleLable.setString(String(magicBottleNum));
    },

    setBossRound : function (isBossRound_) {
        this.bossP.setVisible(isBossRound_);
    },

    _on_btn_stopBattle : function () {
        cc.director.pause();
        var pausePanel = new PauseLayer();
        this.addChild(pausePanel);
    },

    _on_btn_bloodBottle : function () {
        var target = cc.director.getRunningScene()._hero;
        if(target.roleDataManager.hp == target.roleDataManager.maxHp &&
            target.roleDataManager.mp == target.roleDataManager.maxMp){     //单加满血
            //MessageBoxOk.show("血和蓝都是满的，无需补充 !");
            var label = cc.LabelTTF.create("血和蓝都是满的，无需补充 !")
            var winSize = cc.director.getWinSize();
            label.setFontSize(24);
            label.setPosition(cc.p(winSize.width/2,winSize.height/2));
            this.addChild(label);
            UiEffect.labelMoveUp(label);
            return;
        }

        if(Number(this._magicBottleLable.getString()) > 0){
            BattleSystem.instance.useBattleItem({
                itemId : 100007,
                num : 1
            });
        }
        else{
            MessageBoxOk.show("瓶子都没有了，还点什么点，快滚去去商城买 !");
        }
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
        this._progress_mp = this.seekWidgetByName("loading_mp");
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
        this._lbl_hp.setString(this._lbl_hp._str_original.format(originData.hp, originData.maxHp));

        //mp
        var percentMP = originData.mp / originData.maxMp * 100;
        this._progress_mp.setPercent(percentMP);
        this._lbl_mp.setString(this._lbl_hp._str_original.format(originData.mp,originData.maxMp));

        //if(originData.mp < originData.maxMp){
        //    cc.director.getScheduler().schedule(this.refreshMp,this,4.0,cc.REPEAT_FOREVER,0,false,"MP");
        //}
        //else{
        //    cc.director.getScheduler().unschedule("MP",this);
        //}

        var actions = this._role.roleActionManager.actions;
        _.each([RoleAction.Type.SKILL1,
                RoleAction.Type.SKILL2,
                RoleAction.Type.SKILL3,
                RoleAction.Type.SKILL4,
                RoleAction.Type.SKILL5],
                function (skillType_) {
                    var actionData = actions[skillType_];
                    var scene = cc.director.getRunningScene();
                    var isEnoughMp = true;
                    if(actionData && actionData.mpCost > originData.mp){
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

        cc.director.getScheduler().scheduleCallbackForTarget(this, this.refresh);

    },

    onExit : function () {
        this._super();

        this._progress_hp = null;
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
    }
});

