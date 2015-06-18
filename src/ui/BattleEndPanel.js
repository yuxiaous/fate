/**
 * Created by yuxiao on 15/3/19.
 */


var BattleEndPanel = ui.GuiWindowBase.extend({
    _guiFile: "ui/BattleEndPanel.json",

    ctor: function(type_,reward_) {
        this._super();

        this._battleResult = type_;
        this._battleReward = reward_;
    },

    onEnter: function() {
        this._super();
        this._victoryPanel = this.seekWidgetByName("victory_panel");
        this._failurePanel = this.seekWidgetByName("fail_panel");


        this._goldLabel = this.seekWidgetByName("lbl_gold");
        this._expLabel = this.seekWidgetByName("lbl_exp");

        this._goldLabel.setString("0");
        this._expLabel.setString("0");


        this._rewardItems = [];
        var _item = new ShopScene.Good.Icon(0);
        _item.setWidget(this.seekWidgetByName("ProjectNode_1"));
        this._rewardItems.push(_item);

        _item = new ShopScene.Good.Icon(0);
        _item.setWidget(this.seekWidgetByName("ProjectNode_1_0"));
        this._rewardItems.push(_item);

        if(this._battleResult == BattleEndPanel.Type.Lose){
            this._failurePanel.setVisible(true);
            this._victoryPanel.setVisible(false);
            this._activePanel = this._failurePanel;
        }
        else if(this._battleResult == BattleEndPanel.Type.Win){
            this._victoryPanel.setVisible(true);
            this._failurePanel.setVisible(false);
            this._activePanel = this._victoryPanel;

            this._refreshRewardItem();
        }

        this._creatPanelAction(this._activePanel);
    },

    _refreshRewardItem : function () {
        if(this._battleReward.gold){
            this._goldLabel.setString(this._battleReward.gold);
        }
        if(this._battleReward.exp){
            this._expLabel.setString(this._battleReward.exp);
        }

        if(this._battleReward.items.length > 0){
            _.each(this._battleReward.items, function (itemsData_, i) {
                this._rewardItems[i].setItemId(itemsData_.item_id);
            },this);
        }
    },

    _creatPanelAction : function (actPanel_) {
        if(actPanel_){
            actPanel_.scale = 0.1;
            actPanel_.runAction(cc.Sequence.create(
                cc.scaleTo(0.3,1.1),
                cc.scaleTo(0.2,1.0)
            ));
        }
    },

    onExit: function() {
        this._victoryPanel = null;
        this._failurePanel = null;
        this._activePanel = null;
        this._goldLabel = null;
        this._expLabel = null;

        _.each(this._rewardItems, function (item_) {
            item_.setWidget(null);
        });
                                             

        this._super();
    },

    setType: function(type) {

    },

    _on_btn_back: function() {
        this.close();
    },
    
    _on_btn_again: function () {
        ui.popScene();
        ui.pushScene(new BattleScene(BattleSystem.instance.cur_battle_map));
        ui.replaceScene(new BattleScene(BattleSystem.instance.cur_battle_map))
    },
    
    _on_btn_use : function () {
        LOG("USE SERVIVE");
    },
                                             
    _on_btn_enter : function(){
        this.close();
    }
});

BattleEndPanel.Type = {
    Win: 1,
    Lose: 2
};


var BattleWinPanel = ui.GuiWindowBase.extend({
    _guiFile: "ui/BattleEndPanel.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        this._victoryPanel = this.seekWidgetByName("victory_panel");
        this._victoryPanel.setVisible(true);

        this._failurePanel = this.seekWidgetByName("fail_panel");
        this._failurePanel.setVisible(false);

        this._goldLabel = this.seekWidgetByName("lbl_gold");
        this._expLabel = this.seekWidgetByName("lbl_exp");

        this._rewardItems = [];
        var _item = new ShopScene.Good.Icon(0);
        _item.setWidget(this.seekWidgetByName("ProjectNode_1"));
        this._rewardItems.push(_item);

        _item = new ShopScene.Good.Icon(0);
        _item.setWidget(this.seekWidgetByName("ProjectNode_1_0"));
        this._rewardItems.push(_item);

        this._victoryPanel.scale = 0.1;
        this._victoryPanel.runAction(cc.Sequence.create(
            cc.scaleTo(0.3, 1.1),
            cc.scaleTo(0.2, 1.0)
        ));

        this.refreshRewardItem();
    },

    onExit: function() {
        _.each(this._rewardItems, function (item_) {
            item_.setWidget(null);
        });
        this._victoryPanel = null;
        this._failurePanel = null;
        this._goldLabel = null;
        this._expLabel = null;
        this._super();
    },

    refreshRewardItem : function () {
        var reward = BattleSystem.instance.battle_reward;

        this._goldLabel.setString(String(reward.gold || 0));
        this._expLabel.setString(String(reward.exp || 0));

        this._rewardItems[0].setVisible(false);
        this._rewardItems[1].setVisible(false);
        if(reward.items) {
            _.each(reward.items, function (item, i) {
                if(item.item_id) {
                    this._rewardItems[i].setItemId(item.item_id);
                    this._rewardItems[i].setVisible(true);
                }
            },this);
        }
    },

    _on_btn_back: function() {
        this.close();
    },

    _on_btn_again: function () {
        ui.popScene();
        ui.pushScene(new BattleScene(BattleSystem.instance.cur_battle_map));
        ui.replaceScene(new BattleScene(BattleSystem.instance.cur_battle_map))
    },

    _on_btn_use : function () {
        LOG("USE SERVIVE");
    },

    _on_btn_enter : function(){
        this.close();
    }
});

var BattleLosePanel = ui.GuiWindowBase.extend({
    _guiFile: "ui/BattleEndPanel.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        this._victoryPanel = this.seekWidgetByName("victory_panel");
        this._victoryPanel.setVisible(false);

        this._failurePanel = this.seekWidgetByName("fail_panel");
        this._failurePanel.setVisible(true);

        this._goldLabel = this.seekWidgetByName("lbl_gold");
        this._expLabel = this.seekWidgetByName("lbl_exp");

        this._rewardItems = [];
        var _item = new ShopScene.Good.Icon(0);
        _item.setWidget(this.seekWidgetByName("ProjectNode_1"));
        this._rewardItems.push(_item);

        _item = new ShopScene.Good.Icon(0);
        _item.setWidget(this.seekWidgetByName("ProjectNode_1_0"));
        this._rewardItems.push(_item);

        this._victoryPanel.scale = 0.1;
        this._victoryPanel.runAction(cc.Sequence.create(
            cc.scaleTo(0.3, 1.1),
            cc.scaleTo(0.2, 1.0)
        ));
    },

    onExit: function() {
        _.each(this._rewardItems, function (item_) {
            item_.setWidget(null);
        });
        this._victoryPanel = null;
        this._failurePanel = null;
        this._goldLabel = null;
        this._expLabel = null;
        this._super();
    },

    _on_btn_back: function() {
        this.exit = true;
        this.close();
    },

    _on_btn_use : function () {
        LOG("USE SERVIVE");
    },

    _on_btn_enter : function(){
        this.close();
    }
});
