var RechargePanel = ui.GuiWindowBase.extend({
    _guiFile : "ui/rechargeLayer.json",

    ctor : function(){
        this._super();
    },

    onEnter : function(){
        this._super();

        this._ui = {
            goldLabel : this.seekWidgetByName("lbl_gold"),
            diamondLabel : this.seekWidgetByName("lbl_diamond"),
            bgPanel : this.seekWidgetByName("bg_panel"),

            goldPanel : this.seekWidgetByName("gold_panel"),
            diamondPanel : this.seekWidgetByName("diamond_panel")
        };

        this._ui.diamondPanel.setVisible(false);
        if(util.getChannelId() == GameChannel.AppStore){
            this._ui.diamondPanel.setVisible(true);
        }

        this._itemContainer = [];
        _.forEach([
            "ProjectNode_1",
            "ProjectNode_2",
            "ProjectNode_3",
            "ProjectNode_4",
            "ProjectNode_5",
            "ProjectNode_6",
            "ProjectNode_7",
            "ProjectNode_8"
        ], function (nodeStr_,idx) {
            var widgetNode_ = this.seekWidgetByName(nodeStr_);
            var itemPanel = new RechargeItem();
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
    ctor : function () {
        this._super();

        this.item_id = 0;
        this.item_idx = 0;
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
        };

        this._bindings = [
            notification.createBinding(notification.event.SHOP_UPDATE_HISTORY_BUYINFO, this.refreshItemInfo, this)
        ];

    },

    refreshItemInfo : function () {
        var goldIconStrContainer = [
            "images/code_ui/ui_416.png",
            "images/code_ui/ui_417.png",
            "images/code_ui/ui_418.png",
            "images/code_ui/ui_419.png",
            "images/code_ui/ui_420.png",
            "images/code_ui/ui_421.png",
            "images/code_ui/ui_422.png",
            "images/code_ui/ui_423.png"];

        var diamodIconStrContainer = [
            "images/code_ui/ui_420.png",
            "images/code_ui/ui_421.png",
            "images/code_ui/ui_422.png",
            "images/code_ui/ui_423.png",
            "images/code_ui/ui_436.png",
            "images/code_ui/ui_437.png",
            "images/code_ui/ui_438.png",
            "images/code_ui/ui_439.png"];


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
            },this);

            var item_idx = 0;
            switch (this.item_id) {
                case '15001':
                case '16001': item_idx = 0; break;
                case '15002':
                case '16002': item_idx = 1; break;
                case '15003':
                case '16003': item_idx = 2; break;
                case '15004':
                case '16004': item_idx = 3; break;
                case '16006': item_idx = 4; break;
                case '16007': item_idx = 5; break;
                case '16008': item_idx = 6; break;
                case '16009': item_idx = 7; break;
            }

            if(config.buy_type == ShopSystem.GoodType.Gold) {
                this._ui.itemIcon.loadTexture(goldIconStrContainer[item_idx]);
                this._ui.getLabel.setString(this._ui.getLabel._str_original.format(config.buy_count/10000));
            }
            else if(config.buy_type == ShopSystem.GoodType.Diamond) {
                this._ui.itemIcon.loadTexture(diamodIconStrContainer[item_idx]);
                this._ui.getLabel.setString(config.buy_count+"钻石");
            }

            if(config.pay_type == ShopSystem.PayType.RMB){
                this._ui.diamondIcon.setVisible(false);
                this._ui.payLabel.setString(this._ui.payLabel._str_original.format(config.pay_cost));
            }
            else if(config.pay_type == ShopSystem.PayType.Diamond){
                this._ui.diamondIcon.setVisible(true);
                this._ui.payLabel.setString(config.pay_cost);
            }

            if(config.on_sale == 0){
                this._ui.persentedBg.setVisible(false);
            }
            else{
                if(config.sale_count > ShopSystem.instance.getHistoryBuyInfo(this.item_id)){
                    this._ui.persentedBg.setVisible(true);
                    var org_value = 10 * (config.buy_count / 10000 ) / (20 - config.on_sale);
                    var persentedValue = parseFloat( (config.buy_count/10000) - org_value );
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
    var rechargeGold = new RechargePanel();
    rechargeGold.pop();
};

