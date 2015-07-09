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
                var buyAction = new BuyFullAction();
                buyAction.pop();
                UiEffect.iconOpenEffect(buyAction);
                break;
            case ResourcePanel.Type.Gold:
                if(!GuideSystem.instance.getCurFunctionIsOpenWithMapId(GuideSystem.Type.shangdian)){
                    MessageBoxOk.show("通过第一章第六关开放");
                    return;
                }
                ui.pushScene(new ShopScene(ShopSystem.ShopType.Charge));
                break;
            case ResourcePanel.Type.Diamond:

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

        this.close();

        if(UiEffect.blockShopItemWithRMB()){
            return;
        }
        this._on_btn_close();

        var itemId = 101012;
        if(util.getChannelId() == GameChannel.CmccMm) {
            itemId += 200000;
        }
        ShopSystem.instance.buyGood(itemId,1);


    },

    _on_btn_close : function () {

        this.close();
    }

});