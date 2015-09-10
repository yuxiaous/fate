/**
 * Created by yuxiao on 15/3/19.
 */


var BattleEndPanel = ui.GuiWindowBase.extend({
//    _guiFile: "ui/BattleEndPanel.json",
//
//    ctor: function(type_,reward_) {
//        this._super();
//
//        this._battleResult = type_;
//        this._battleReward = reward_;
//    },
//
//    onEnter: function() {
//        this._super();
//        this._victoryPanel = this.seekWidgetByName("victory_panel");
//        this._failurePanel = this.seekWidgetByName("fail_panel");
//
//
//        this._goldLabel = this.seekWidgetByName("lbl_gold");
//        this._expLabel = this.seekWidgetByName("lbl_exp");
//
//        this._goldLabel.setString("0");
//        this._expLabel.setString("0");
//
//
//        this._rewardItems = [];
//        var _item = new ShopScene.Good.Icon(0);
//        _item.setWidget(this.seekWidgetByName("ProjectNode_1"));
//        this._rewardItems.push(_item);
//
//        _item = new ShopScene.Good.Icon(0);
//        _item.setWidget(this.seekWidgetByName("ProjectNode_1_0"));
//        this._rewardItems.push(_item);
//
//        if(this._battleResult == BattleEndPanel.Type.Lose){
//            this._failurePanel.setVisible(true);
//            this._victoryPanel.setVisible(false);
//            this._activePanel = this._failurePanel;
//        }
//        else if(this._battleResult == BattleEndPanel.Type.Win){
//            this._victoryPanel.setVisible(true);
//            this._failurePanel.setVisible(false);
//            this._activePanel = this._victoryPanel;
//
//            this._refreshRewardItem();
//        }
//
//        this._creatPanelAction(this._activePanel);
//    },
//
//    _refreshRewardItem : function () {
//        if(this._battleReward.gold){
//            this._goldLabel.setString(this._battleReward.gold);
//        }
//        if(this._battleReward.exp){
//            this._expLabel.setString(this._battleReward.exp);
//        }
//
//        if(this._battleReward.items.length > 0){
//            _.each(this._battleReward.items, function (itemsData_, i) {
//                this._rewardItems[i].setItemId(itemsData_.item_id);
//            },this);
//        }
//    },
//
//    _creatPanelAction : function (actPanel_) {
//        if(actPanel_){
//            actPanel_.scale = 0.1;
//            actPanel_.runAction(cc.Sequence.create(
//                cc.scaleTo(0.3,1.1),
//                cc.scaleTo(0.2,1.0)
//            ));
//        }
//    },
//
//    onExit: function() {
//        this._victoryPanel = null;
//        this._failurePanel = null;
//        this._activePanel = null;
//        this._goldLabel = null;
//        this._expLabel = null;
//
//        _.each(this._rewardItems, function (item_) {
//            item_.setWidget(null);
//        });
//
//
//        this._super();
//    },
//
//    setType: function(type) {
//
//    },
//
//    _on_btn_back: function() {
//        this.close();
//    },
//
//    _on_btn_again: function () {
//        ui.popScene();
//        ui.pushScene(new BattleNorScene(BattleSystem.instance.cur_battle_map));
//        ui.replaceScene(new BattleNorScene(BattleSystem.instance.cur_battle_map))
//    },
//
//    _on_btn_use : function () {
//        LOG("USE SERVIVE");
//    },
//
//    _on_btn_enter : function(){
//        this.close();
//    }
});

BattleEndPanel.Type = {
    Win: 1,
    Lose: 2
};

var BattleWinPanel = ui.GuiWindowBase.extend({
    _guiFile: "ui/battle_victory_panel.json",

    ctor: function() {
        this._super();

        this._allDetailITEM = null;
    },

    onEnter: function() {
        this._super();

        this._ui = {
            vicTitlePanel : this.seekWidgetByName("victory_title_panel"),
            contentPanel : this.seekWidgetByName("content_panel"),

            goldLabel : this.seekWidgetByName("lbl_gold"),
            expLabel  : this.seekWidgetByName("lbl_exp")
        }


        this._rewardItems = [];

        _.each(["ProjectNode_1",
                "ProjectNode_2",
                "ProjectNode_3",
                "ProjectNode_4"], function (str_) {
            //var _item = new ShopScene.Good.Icon(0);
             var _item =  new IconWidget();
            _item.setWidget(this.seekWidgetByName(str_));
            this._rewardItems.push(_item);
            _item.setVisible(false);
        },this);

        this.refreshRewardItem();

        //_.each(["ProjectNode_1",
        //    "ProjectNode_2",
        //    "ProjectNode_3",
        //    "ProjectNOde_4"], function (str_) {
        //    var _item = this.seekWidgetByName(str_);
        //    _item.setVisible(false);
        //},this);


        this._bindings = [
            //notification.createBinding(notification.event.BATTLE_USE_ITEM_RESULT, function (event_,itemType_) {
            //    if(itemType_ == BattleSystem.UseItemType.UseRevive){
            //        notification.emit(notification.event.BATTLE_HERO_REVIVE);
            //        this.close();
            //    }
            //},this)
        ];

        this._ui.vicTitlePanel.setVisible(false);
        this._ui.contentPanel.setVisible(false);
        UiEffect.iconOpenYEffect(this, function () {
            UiEffect.iconSealEffect(this._ui.vicTitlePanel, function () {
                this._ui.contentPanel.setVisible(true);
            },this,true);
        },this)
    },

    onExit: function() {
        _.each(this._rewardItems, function (item_) {
            item_.setWidget(null);
        });
        this._super();
    },

    deleteAllDetailItem : function () {
        //_.each(this._allDetailITEM);
    },

    refreshRewardItem : function () {

        var reward = BattleSystem.instance.battle_reward;

        this._ui.goldLabel.setString(String(reward.gold || 0));
        this._ui.expLabel.setString(String(reward.exp || 0));

        _.each(this._rewardItems, function (item_,i) {
            if(item_){
                item_.setVisible(false);
            }
        },this);
        if(reward.items && reward.items.length) {
            _.each(reward.items, function (item, i) {
                if(item.item_id) {
                    var itemType = BagSystem.getConfigType(item.item_id);

                    if(itemType == BagSystem.ConfigType.Equip){
                        itemType = IconWidget.Type.Equip;
                    }
                    else if(itemType == BagSystem.ConfigType.Item){
                        itemType =  IconWidget.Type.Item;
                    }
                    this._rewardItems[i].setIcon(item.item_id,itemType,item.item_num);
                    this._rewardItems[i].setVisible(true);
                    var rewardItemNode = this._rewardItems[i]._ui.btn_touch;

                    var that = this;
                    this._rewardItems[i].setTouchCallback(function () {
                        if(that._allDetailITEM != null){
                            that._allDetailITEM.removeFromParent();
                            that._allDetailITEM = null;
                        }
                        that._allDetailITEM = new EquipDetailPanel(item.item_id);
                        that._allDetailITEM._claimed = false;
                        that._allDetailITEM.setPosition(cc.p(0,rewardItemNode.getContentSize().height));
                        rewardItemNode.addChild(that._allDetailITEM);
                    });
                }
            },this);
        }
    },

    _on_btn_enter : function(){
        this.close();
    }
});

var BattleLosePanel = ui.GuiWindowBase.extend({
    _guiFile: "ui/battle_fail_layer.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();


        this._ui = {
                 _failTitlePanel : this.seekWidgetByName("fail_title_panel"),
                _contentPanel : this.seekWidgetByName("content_panel"),
                //this._goldLabel = this.seekWidgetByName("lbl_gold");
                //  this._expLabel = this.seekWidgetByName("lbl_exp");
                btn_zhizun    : this.seekWidgetByName("btn_1"),
                btn_jinbi     : this.seekWidgetByName("btn_2"),
                btn_jineng    : this.seekWidgetByName("btn_3"),
                btn_zhuangbei : this.seekWidgetByName("btn_4")
        }

        _.each([this._ui.btn_zhizun,
                this._ui.btn_jinbi,
                this._ui.btn_jineng,
                this._ui.btn_zhuangbei], function (btn_) {
            btn_.setPressedActionEnabled(true);
        });


        this._bindings = [
            //notification.createBinding(notification.event.BATTLE_USE_ITEM_RESULT, function (event_,itemType_) {
            //    if(itemType_ == BattleSystem.UseItemType.UseRevive){
            //        notification.emit(notification.event.BATTLE_HERO_REVIVE);
            //        this.close();
            //    }
            //},this)
        ];

        this._ui._failTitlePanel.setVisible(false);
        this._ui._contentPanel.setVisible(false);
        UiEffect.iconOpenYEffect(this, function () {
            UiEffect.iconSealEffect(this._ui._failTitlePanel, function () {
                this._ui._contentPanel.setVisible(true);
            },this,true);
        },this)
    },

    onExit: function() {
        //_.each(this._rewardItems, function (item_) {
        //    item_.setWidget(null);
        //});


        this._ui = null;
        notification.removeBinding(this._bindings);

        this._super();
    },

    _getReviveItemNum : function () {
        var reviveNum = 0;
        _.reduce(BagSystem.instance.items, function(sum, item) {
            if(item.id == 100001) {
                reviveNum += item.num || 1;
            }
        }, 0, this)
        return reviveNum;
    },

    _on_btn_back: function() {
        this.exit = true;
        this.close();
    },

    _on_btn_use : function () {
        //var reviveNum = this._getReviveItemNum();
        //if(reviveNum > 0){
        //    BattleSystem.instance.useBattleItem({
        //        itemId : 100001,
        //        num : 1
        //    });
        //}
    },

    _on_btn_restart : function(){
        BattleSystem.instance.needRestart = true;
        BattleSystem.instance.needRestartBattleType = BattleSystem.instance.curBattleType;

        this.close();
        ui.popScene();
    },

    //至尊
    _on_btn_1 : function () {
         var buy_panel = new GiftDetailZhiZun();
         buy_panel.pop();
         UiEffect.iconOpenEffect(buy_panel.seekWidgetByName("gift_panel"));
    },
    //金币
    _on_btn_2 : function () {

        if(!GuideSystem.instance.getCurFunctionIsOpenWithMapId(GuideSystem.Type.shangdian)){
            MessageBoxOk.show("通过第一章第二关开放");
            return;
        }
        ui.replaceScene(ShopScene);
    },
    //技能
    _on_btn_3 : function () {

        if(!GuideSystem.instance.getCurFunctionIsOpenWithMapId(GuideSystem.Type.jineng)){
            MessageBoxOk.show("通过第一章第四关开放");
            return;
        }
        //this.pushScene(SkillScene);
        var win = new SkillScene();
        win.pop();
    },
    //装备
    _on_btn_4 : function () {
        if(!GuideSystem.instance.getCurFunctionIsOpenWithMapId(GuideSystem.Type.duanzao)){
            MessageBoxOk.show("通过第一章第五关开放");
            return;
        }
        var win = new EquipScene();
        win.pop();
    }
});

var EndlessBattelLosePanel = ui.GuiWindowBase.extend({
    _guiFile: "ui/endless_battle_fail_layer.json",

    ctor: function(curRound_) {
        this._super();
        this._curRound = curRound_;
    },

    onEnter: function() {
        this._super();


        this._ui = {
            _failTitlePanel : this.seekWidgetByName("fail_title_panel"),
            _contentPanel : this.seekWidgetByName("content_panel"),
            _lbl_endless : this.seekWidgetByName("lbl_fail_content"),
            _lbl_maxRound : this.seekWidgetByName("lbl_max_round"),
            goldLabel : this.seekWidgetByName("lbl_gold"),
            expLabel  : this.seekWidgetByName("lbl_exp")
        };


        var levelNum = BattleSystem.instance.endlessRound;
        //var lblMaxStr = "最高坚持到第" + levelNum + "关";
        this._ui._lbl_maxRound.setString(levelNum);

        //var lblStr = "恭喜您在无尽模式坚持到第" + this._curRound + "关";
        this._ui._lbl_endless.setString(this._curRound);

        var conf = configdb.endlessround[this._curRound];
        this._ui.goldLabel.setString(conf.gain_gold || 0);
        this._ui.expLabel.setString(conf.gain_exp || 0);

        this._ui._failTitlePanel.setVisible(false);
        this._ui._contentPanel.setVisible(false);
        UiEffect.iconOpenYEffect(this, function () {
            UiEffect.iconSealEffect(this._ui._failTitlePanel, function () {
                this._ui._contentPanel.setVisible(true);
            },this,true);
        },this)
    },

    onExit: function() {

        this._ui = null;

        this._super();
    },

    _on_btn_back: function() {
        this.exit = true;
        this.close();
    },

    _on_btn_restart : function(){
        BattleSystem.instance.needRestart = true;
        BattleSystem.instance.needRestartBattleType = BattleSystem.instance.curBattleType;

        this.close();
        ui.popScene();
    }
});

var BattleRevivePanel = ui.GuiWindowBase.extend({
    _guiFile : "ui/battle_revive_layer.json",
    _shop_id: 101013,

    ctor : function (curBattleType_,endlessRound_) {
        this._super();

        this._curBattleType = curBattleType_ || SceneBase.Type.NormalType;
        this._endlessRound = endlessRound_ || 1;
    },

    onEnter : function () {
        this._super();
        this._ui = {
            lbl_desc: this.seekWidgetByName("lbl_desc")
        };

        var config = ShopSystem.getConfig(this._shop_id);
        if(config) {
            var cost = config.pay_cost;
            var curr = ShopSystem.getPayTypeString(config.pay_type);
            this._ui.lbl_desc.setString(this._ui.lbl_desc._str_original.format({
                num: cost,
                curr: curr
            }));
        }
    },

    onExit : function () {
        this._ui = null;
        this._super();
    },

    _on_btn_buy : function(){
        if(UiEffect.blockShopItemWithRMB()){
            return;
        }

        if(BattleSystem.instance.buyBattleRevive(this._shop_id)){
            notification.emit(notification.event.GAME_PAUSE);
            this.close();
        }

        //notification.emit(notification.event.GAME_PAUSE);
        //ShopSystem.instance.buyGood(this._shop_id);
        //
        //this.close();
    },

    _on_btn_close : function () {
        if(this._curBattleType == SceneBase.Type.NormalType){
            this.close();
            // show lose window
            var lose = new BattleLosePanel();
            lose.setCloseCallback(function(w) {
                if(w.exit) {
                    cc.director.popScene();
                }
            }, this);
            lose.pop();

            sdk_manager.sendSdkCommand("TalkingDataGA", "onFailed",
                "map.{missionId},{failedCause}".format({
                    missionId: BattleSystem.instance.cur_battle_map,
                    failedCause: "战斗失败退出"
                }));
        }
        else if(this._curBattleType == SceneBase.Type.EndlessType){
            this.close();


            BattleSystem.instance.endlessBattleLose(this._endlessRound);
        }

    }
});

var BattleWinGiftPanel = ui.GuiWindowBase.extend({
    _guiFile : "ui/battle_win_buy.json",

    ctor : function () {
        this._super();
    },

    onEnter : function () {
        this._super();

    },

    onExit : function () {
        this._super();

    },

    _on_btn_enter : function(){

    },

    _on_btn_close : function () {

        this.close();
        //// show lose window
        //var lose = new BattleLosePanel();
        //lose.setCloseCallback(function(w) {
        //    if(w.exit) {
        //        cc.director.popScene();
        //    }
        //}, this);
        //lose.pop();
    }
});

var EquipDetailPanel = ui.GuiWindowBase.extend({
    _guiFile: "ui/equip_detail.json",

    ctor: function(equipId_) {
        this._super();

        this._curItemID = equipId_;
    },

    onEnter: function() {
        this._super();

        this._ui = {
            lbl_item_name : this.seekWidgetByName("lbl_item_name"),
            lbl_item_desc: this.seekWidgetByName("lbl_item_desc"),
            sp_change_up: this.seekWidgetByName("sp_change_up"),
            sp_change_down: this.seekWidgetByName("sp_change_down"),
            lbl_item_score: this.seekWidgetByName("lbl_item_score"),
            lbl_score_change : this.seekWidgetByName("lbl_score_change"),
            panel : this.seekWidgetByName("panel")
        }

        var itemType = BagSystem.getConfigType(this._curItemID);
        if(itemType == BagSystem.ConfigType.Item){
            this._ui.lbl_item_score.setVisible(false);
            this._ui.sp_change_up.setVisible(false);
            this._ui.sp_change_down.setVisible(false);
        }

        var config = BagSystem.getConfig(this._curItemID);
        if(config) {
            // name
            this._ui.lbl_item_name.setString(config.name || "");

            // desc
            this._ui.lbl_item_desc.setString(config.desc || "");
            // score value
            if(config.type == undefined) {
                var score = Formula.calculateBattleScore(config.hp, config.mp,
                    config.atk, config.def,
                    config.crit, config.sunder);

                // score
                this._ui.lbl_item_score.setString(this._ui.lbl_item_score._str_original.format(score));

                // change value
                var equip_info = EquipSystem.instance.slots[config.slot];
                if(equip_info != undefined) {
                    var equip_config = configdb.equip[equip_info.id];
                    if(equip_config != undefined) {
                        score -= Formula.calculateBattleScore(equip_config.hp, equip_config.mp,
                            equip_config.atk, equip_config.def,
                            equip_config.crit, equip_config.sunder);
                    }
                }
                if(score > 0) {
                    this._ui.sp_change_up.setVisible(true);
                    this._ui.sp_change_down.setVisible(false);
                }
                else if(score < 0) {
                    score = -score;
                    this._ui.sp_change_up.setVisible(false);
                    this._ui.sp_change_down.setVisible(true);
                }
                else {
                    score = "";
                    this._ui.sp_change_up.setVisible(false);
                    this._ui.sp_change_down.setVisible(false);
                }
            }
            else {
                this._ui.lbl_score_change.setVisible(false);
                this._ui.lbl_item_score.setString("");
            }
        }

        //this._ui.panel.setTouchEnabled(true);
        //
        //this._ui.panel.addTouchEventListener(function (touch,event) {
        //    LOG("1111");
        //
        //    this.removeFromParent();
        //
        //
        //},this)
    },

    onExit : function(){

        this._ui = null;

        this._super();
    },

    refreshSelectedItemInfo: function() {

        var config = BagSystem.getConfig(this._curItemID);

        if(config) {
            // name
            this._ui.lbl_item_name.setString(config.name || "");

            // price
            this._ui.lbl_item_price.setString(this._ui.lbl_item_price._str_original.format(config.price || ""));

            // desc
            this._ui.lbl_item_desc.setString(config.desc || "");

        }
    }
});


