var RechargePanel = ui.GuiWindowBase.extend({
    _guiFile : "ui/rechargeLayer.json",

    ctor : function(goldAndDiamond_){
        this._super();

        this._goldAndDiamond = false;
        if(goldAndDiamond_ != undefined){
            this._goldAndDiamond = goldAndDiamond_;
        }

    },

    onEnter : function(){
        this._super();

        this._ui = {
            goldLabel : this.seekWidgetByName("lbl_gold"),
            diamondLabel : this.seekWidgetByName("lbl_diamond"),
            bgPanel : this.seekWidgetByName("bg_panel")
        };


        this._itemContainer = [];
        _.forEach(["ProjectNode_1",
            "ProjectNode_2",
            "ProjectNode_3",
            "ProjectNode_4",
            "ProjectNode_5",
            "ProjectNode_6",
            "ProjectNode_7",
            "ProjectNode_8"], function (nodeStr_,idx) {
            var widgetNode_ = this.seekWidgetByName(nodeStr_);
            var itemPanel = new RechargeItem(this._goldAndDiamond);
            itemPanel.setWidget(widgetNode_);
            this._itemContainer.push(itemPanel);
            itemPanel.setVisible(false);
        },this);

        this._bindings = [
            notification.createBinding(notification.event.PLAYER_INFO, this.refreshGoldLabel, this)
        ];

        this.refreshGoldLabel();
        UiEffect.iconOpenEffect(this._ui.bgPanel);

        var shopType = ShopSystem.ShopType.Charge;
        var itemIdx_ = 0;
        _.each(_.keys(configdb.shop), function(key) {
            var config = ShopSystem.getConfig(key);
            if(config && config.shop == shopType) {
                var chargeItem  = this._itemContainer[itemIdx_];
                LOG("key = " + key + "item idx = " + itemIdx_);
                chargeItem.setItemDataInfo(key,itemIdx_);
                chargeItem.setVisible(true);
                itemIdx_ = itemIdx_ + 1;
            }
        }, this);
    },

    refreshGoldLabel : function () {
        this._ui.goldLabel.setString(PlayerSystem.instance.gold);
        this._ui.diamondLabel.setString(PlayerSystem.instance.diamond);
    },

    onExit : function(){
        this._ui = null;
        notification.removeBinding(this._bindings);
        this._super();
    },

    _on_btn_close : function () {
        this.close();
    }

});

var RechargeItem = ui.GuiController.extend({
    ctor : function (goldAndDiamond_) {
        this._super();

        this.item_id = 0;
        this.item_idx = 0;

        this._goldAndDiamond = goldAndDiamond_;
    },

    onEnter : function(){
        this._super();

        this._ui = {
            getLabel : this.seekWidgetByName("lbl_get"),
            persentedLabel : this.seekWidgetByName("lbl_persented"),
            payLabel : this.seekWidgetByName("lbl_pay"),
            bgPanel : this.seekWidgetByName("bg_panel"),
            itemIcon : this.seekWidgetByName("item_icon"),
            persentedBg : this.seekWidgetByName("bg_persented"),
            diamondIcon : this.seekWidgetByName("diamond_icon")
        }

        this._bindings = [
            notification.createBinding(notification.event.SHOP_UPDATE_HISTORY_BUYINFO, this.refreshItemInfo, this)
        ];

    },

    refreshItemInfo : function () {
        var iconStrContainer = ["images/code_ui/ui_416.png",
            "images/code_ui/ui_417.png",
            "images/code_ui/ui_418.png",
            "images/code_ui/ui_419.png",
            "images/code_ui/ui_420.png",
            "images/code_ui/ui_421.png",
            "images/code_ui/ui_422.png",
            "images/code_ui/ui_423.png",];

        if(this._goldAndDiamond){
            iconStrContainer = ["images/code_ui/ui_420.png",
                "images/code_ui/ui_421.png",
                "images/code_ui/ui_422.png",
                "images/code_ui/ui_423.png",
                "images/code_ui/ui_436.png",
                "images/code_ui/ui_437.png",
                "images/code_ui/ui_438.png",
                "images/code_ui/ui_439.png",];
        }

        this._ui.itemIcon.loadTexture(iconStrContainer[this.item_idx]);

        var config = ShopSystem.getConfig(this.item_id);

        if(config){
            this._ui.bgPanel.setTouchEnabled(true);
            this._ui.bgPanel.addTouchEventListener(function (touch,event) {
                if(event == ccui.Widget.TOUCH_BEGAN){
                    this._ui.bgPanel.setScale(1.1);
                }
                else if(event == ccui.Widget.TOUCH_MOVED){
                    this._ui.bgPanel.setScale(1.0);
                }
                else if(event == ccui.Widget.TOUCH_ENDED){
                    this._ui.bgPanel.setScale(1.0);

                    this.buyGoldOrDiamond(this.item_id);
                }
            },this)

            if(config.pay_type == ShopSystem.PayType.RMB){
                this._ui.getLabel.setString(config.buy_count);

                this._ui.diamondIcon.setVisible(false);
                this._ui.payLabel.setString(this._ui.payLabel._str_original.format(config.pay_cost));
            }
            else if(config.pay_type == ShopSystem.PayType.Diamond){
                this._ui.getLabel.setString(this._ui.getLabel._str_original.format(config.buy_count/10000));

                this._ui.diamondIcon.setVisible(true);
                this._ui.payLabel.setString(config.pay_cost);
            }

            if(config.on_sale == 0){
                this._ui.persentedBg.setVisible(false);
            }
            else{
                if(config.sale_count > ShopSystem.instance.getHistoryBuyInfo(this.item_id)){
                    this._ui.persentedBg.setVisible(true);
                    var persentedValue = parseFloat( (config.buy_count / 10000 ) * (config.on_sale/10) );
                    this._ui.persentedLabel.setString(this._ui.persentedLabel._str_original.format(persentedValue.toFixed(1)));
                }
                else{
                    this._ui.persentedBg.setVisible(false);
                }

            }
        }


    },

    setItemDataInfo : function (item_id_,item_idx_) {
        this.item_id = item_id_;
        this.item_idx = item_idx_;

        this.refreshItemInfo();
    },

    buyGoldOrDiamond : function (goodId_) {
        var config = ShopSystem.getConfig(goodId_);
        if(config == undefined) {
            return false;
        }

        if(config.pay_type == ShopSystem.PayType.Diamond) {
            var ownDiamond = PlayerSystem.instance.diamond;
            if(config.pay_cost > ownDiamond){
                var  error = net_error_code[102];
                var mesWin = new MessageBoxOkCancel(error.desc,"购买");
                mesWin.setOkCallback(function () {

                },this);
                mesWin.pop();

                return false;
            }
        }
        else if(config.pay_type == ShopSystem.PayType.Gold){

        }

        ShopSystem.instance.buyGood(this.item_id, 1);
        return true;
    },

    onExit : function () {

        this._ui = null;
        notification.removeBinding(this._bindings);
        this._super();
    }
});

RechargePanel.show = function() {
    var channel_id = util.getChannelId();
    var allGold = (channel_id == GameChannel.Qh360) || (channel_id == GameChannel.TencentMidas);
    var rechargeGold = new RechargePanel(!allGold);
    rechargeGold.pop();
};

