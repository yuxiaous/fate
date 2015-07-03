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
            var _item = new ShopScene.Good.Icon(0);
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
            notification.createBinding(notification.event.BATTLE_USE_ITEM_RESULT, function (event_,itemType_) {
                if(itemType_ == BattleSystem.UseItemType.UseRevive){
                    notification.emit(notification.event.BATTLE_HERO_REVIVE);
                    this.close();
                }
            },this)
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
                    this._rewardItems[i].setItemId(item.item_id);
                    this._rewardItems[i].setVisible(true);
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
            notification.createBinding(notification.event.BATTLE_USE_ITEM_RESULT, function (event_,itemType_) {
                if(itemType_ == BattleSystem.UseItemType.UseRevive){
                    notification.emit(notification.event.BATTLE_HERO_REVIVE);
                    this.close();
                }
            },this)
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
        var reviveNum = this._getReviveItemNum();
        if(reviveNum > 0){
            BattleSystem.instance.useBattleItem({
                itemId : 100001,
                num : 1
            });
        }
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

    ctor : function () {
        this._super();
    },

    onEnter : function () {
        this._super();

    },

    onExit : function () {
        this._super();

    },

    _on_btn_buy : function(){
        //this.close();
        if(UiEffect.blockShopItemWithRMB()){
            return;
        }
    },
    
    _on_btn_close : function () {

        this.close();
        // show lose window
        var lose = new BattleLosePanel();
        lose.setCloseCallback(function(w) {
            if(w.exit) {
                cc.director.popScene();
            }
        }, this);
        lose.pop();

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


