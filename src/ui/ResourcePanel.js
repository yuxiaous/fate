/**
 * Created by yuxiao on 15/6/26.
 */


var ResourcePanel = ui.GuiController.extend({
    ctor: function(type) {
        this._super();
        this.type = type;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_value: this.seekWidgetByName("lbl_value"),
            btn_add: this.seekWidgetByName("btn_add"),
            btn_bg : this.seekWidgetByName("img_bg")
        };
        this._bindings = [
            notification.createBinding(notification.event.PLAYER_INFO, this.refreshValue, this)
        ];

        this.refreshIcon();
        this.refreshValue();

        this._ui.btn_bg.setTouchEnabled(true);
        this._ui.btn_bg.addTouchEventListener(function (touch,event) {
            if(event == ccui.Widget.TOUCH_ENDED){
              this._on_btn_add();
            }
        },this)
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._ui = null;
        this._super();
    },

    refreshIcon: function() {
        var icon;
        switch (this.type) {
            case ResourcePanel.Type.Action:
                icon = "images/icon/icon_01.png";
                break;
            case ResourcePanel.Type.Gold:
                icon = "images/icon/icon_02.png";
                break;
            case ResourcePanel.Type.Diamond:
                icon = "images/icon/icon_03.png";
                break;
        }
        if(icon) {
            this._ui.sp_icon.setTexture(icon);
        }
    },

    refreshValue: function() {
        var system = PlayerSystem.instance;

        var value = 0;
        switch (this.type) {
            case ResourcePanel.Type.Action:
                value = system.action;
                break;
            case ResourcePanel.Type.Gold:
                value = system.gold;
                break;
            case ResourcePanel.Type.Diamond:
                value = system.diamond;
                break;
        }
        this._ui.lbl_value.setString(String(value));
    },

    showAddButton: function(val) {
        this._ui.btn_add.setVisible(val);
    },

    _on_btn_add: function() {
        //switch (this.type) {
        //    case ResourcePanel.Type.Action:
        //        LOG("add action");
        //        GmSystem.instance.sendCommand("ar 3 10");
        //        break;
        //    case ResourcePanel.Type.Gold:
        //        LOG("add gold");
        //        GmSystem.instance.sendCommand("ar 1 10000");
        //        break;
        //    case ResourcePanel.Type.Diamond:
        //        LOG("add diamond");
        //        GmSystem.instance.sendCommand("ar 2 100");
        //        break;
        //}

        switch (this.type){
            case  ResourcePanel.Type.Action:
                var curAction = PlayerSystem.instance.action;
                if(curAction >= 60){
                    MessageBoxOk.show("体力已满");
                    return;
                }
                else{
                    var buyAction = new BuyFullAction();
                    buyAction.pop();
                }
                break;
            case ResourcePanel.Type.Gold:
            case ResourcePanel.Type.Diamond:
                if(!GuideSystem.instance.getCurFunctionIsOpenWithMapId(GuideSystem.Type.shangdian)){
                    MessageBoxOk.show("通过第一章第二关开放");
                    return;
                }
                RechargePanel.show();
                break;
        }
    }
});

ResourcePanel.Type = {
    Action: 1,
    Gold: 2,
    Diamond: 3
};


var BuyFullAction = ui.GuiWindowBase.extend({
    _guiFile : "ui/buy_action.json",
    _shop_id: 101012,

    ctor : function () {
        this._super();

    },

    onEnter : function () {
        this._super();
        this._ui = {
            lbl_price_rmb: this.seekWidgetByName("lbl_price"),
            lbl_price_diamond: this.seekWidgetByName("lbl_price_0")
        };

        var channel_id = util.getChannelId();
        switch (channel_id) {
            case GameChannel.AppStore:
                this._ui.lbl_price_rmb.setVisible(false);
                this._ui.lbl_price_diamond.setVisible(true);
                this._ui.lbl_price = this._ui.lbl_price_diamond;
                break;
            default :
                this._ui.lbl_price_rmb.setVisible(true);
                this._ui.lbl_price_diamond.setVisible(false);
                this._ui.lbl_price = this._ui.lbl_price_rmb;
                break;
        }

        if(this._ui.lbl_price && this._shop_id) {
            var config = ShopSystem.getConfig(this._shop_id);
            if(config) {
                this._ui.lbl_price.setString(this._ui.lbl_price._str_original.format(config.pay_cost));
            }
        }
    },

    onExit : function () {
        this._ui = null;
        this._super();
    },

    _on_btn_buy : function(){

        this.close();

        if(UiEffect.blockShopItemWithRMB()){
            return;
        }

        ShopSystem.instance.buyGood(this._shop_id);

        this._on_btn_close();
    },

    _on_btn_close : function () {

        this.close();
    },

    pop: function() {
        this._super();
        UiEffect.iconOpenEffect(this);
    }

});

