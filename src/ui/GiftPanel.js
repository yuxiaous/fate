

var Gift_Panel = ui.GuiController.extend({
    ctor: function() {
        this._super();

    },

    onEnter: function() {
        this._super();

        this._ui = {
            btn_1 : this.seekWidgetByName("btn_1"),
            btn_2 : this.seekWidgetByName("btn_2"),
            btn_3 : this.seekWidgetByName("btn_3"),
            btn_4 : this.seekWidgetByName("btn_4")
        }

        _.each([this._ui.btn_1,
                this._ui.btn_2,
                this._ui.btn_3,
                this._ui.btn_4], function (btn_,idx_) {
            var btnSelectImg = btn_.setPressedActionEnabled(true);

            btn_.addTouchEventListener(function (touch,event) {
                if(event == ccui.Widget.TOUCH_ENDED){
                    LOG("idx = " + idx_);

                    var giftType = 0;
                    switch (idx_){
                        case 0 :
                            giftType = Gift_Panel.GiftType.Vip;
                            break;
                        case 1 :
                            giftType = Gift_Panel.GiftType.ZhiZun;
                            break;
                        case 2 :
                            giftType = Gift_Panel.GiftType.ZhuangBei;
                            break;
                        case 3 :
                            giftType = Gift_Panel.GiftType.WuQi;
                            break;
                    }
                    var buy_panel = new Gift_Buy_Detail(giftType);
                    buy_panel.pop();
                    UiEffect.iconOpenEffect(buy_panel.seekWidgetByName("gift_panel"));
                }
            },this)
        },this);
    },

    onExit: function() {

        this._ui = null;
        this._super();
    }
});

Gift_Panel.GiftType = {
    ZhuangBei : 1,
    WuQi : 2,
    ZhiZun : 3,
    Vip : 4
}

var Gift_Buy_Detail = ui.GuiWindowBase.extend({
    _guiFile : "ui/gift_detail_panel.json",

    ctor : function (type_) {
        this._super();

        this._giftType = type_;
    },

    onEnter : function () {
        this._super();


        var gift_detail_img = "";
        var gift_title_img = "";
        switch (this._giftType){
            case Gift_Panel.GiftType.ZhuangBei :
                gift_title_img = "ui_295.png";
                gift_detail_img = "ui_296.png";
                break;
            case  Gift_Panel.GiftType.WuQi :
                gift_title_img = "ui_297.png";
                gift_detail_img = "ui_298.png";
                break;
            case Gift_Panel.GiftType.ZhiZun :
                gift_title_img = "ui_293.png";
                gift_detail_img = "ui_294.png";
                break;
            case Gift_Panel.GiftType.Vip:
                gift_title_img = "ui_299.png";
                gift_detail_img = "ui_300.png";
                break;
        }

        var baseString = "images/code_ui/";
        gift_detail_img = String(baseString+gift_detail_img);
        gift_title_img = String(baseString+gift_title_img);

        this._title_img = this.seekWidgetByName("item_title");
        this._detail_img = this.seekWidgetByName("item_detail_img");


        this._title_img.loadTexture(gift_title_img);
        this._detail_img.loadTexture(gift_detail_img);

    },

    onExit : function () {
        this._super();

    },

    _on_btn_buy : function(){

    },

    _on_btn_close : function () {

        this.close();

    }

});
