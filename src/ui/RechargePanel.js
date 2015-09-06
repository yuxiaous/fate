var RechargePanel = ui.GuiWindowBase.extend({
    _guiFile : "ui/rechargeLayer.json",

    ctor : function(){
        this._super();

    },

    onEnter : function(){
        this._super();

        this._ui = {
            goldLabel : this.seekWidgetByName("lbl_gold"),
            bgPanel : this.seekWidgetByName("bg_panel")
        };

        _.forEach(["ProjectNode_1",
            "ProjectNode_2",
            "ProjectNode_3",
            "ProjectNode_4",
            "ProjectNode_5",
            "ProjectNode_6",
            "ProjectNode_7",
            "ProjectNode_8"], function (nodeStr_,idx) {
            var widgetNode_ = this.seekWidgetByName(nodeStr_);
            var itemPanel = new RechargeItem(idx);
            itemPanel.setWidget(widgetNode_);
        },this);

        this._bindings = [
            notification.createBinding(notification.event.PLAYER_INFO, this.refreshGoldLabel, this)
        ];


        this.refreshGoldLabel();

        UiEffect.iconOpenEffect(this._ui.bgPanel);
    },

    refreshGoldLabel : function () {

        this._ui.goldLabel.setString(PlayerSystem.instance.gold);
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
    ctor : function (item_idx,item_id) {
        this._super();

        this.item_id = item_id;
        this.item_idx = item_idx;
    },

    onEnter : function(){
        this._super();

        this._ui = {
            getLabel : this.seekWidgetByName("lbl_get"),
            persentedLabel : this.seekWidgetByName("lbl_persented"),
            payLabel : this.seekWidgetByName("lbl_pay"),
            bgPanel : this.seekWidgetByName("bg_panel"),
            itemIcon : this.seekWidgetByName("item_icon")
        }

        var iconStrContainer = ["images/code_ui/ui_416.png",
            "images/code_ui/ui_417.png",
            "images/code_ui/ui_418.png",
            "images/code_ui/ui_419.png",
            "images/code_ui/ui_420.png",
            "images/code_ui/ui_421.png",
            "images/code_ui/ui_422.png",
            "images/code_ui/ui_423.png",];

        this._ui.itemIcon.loadTexture(iconStrContainer[this.item_idx]);

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
            }
        },this)

        this.refreshItemInfo();
    },

    refreshItemInfo : function () {
        this._ui.getLabel.setString(this._ui.getLabel._str_original.format("999"));
        this._ui.persentedLabel.setString(this._ui.persentedLabel._str_original.format("888"));
        this._ui.payLabel.setString(this._ui.payLabel._str_original.format("777"));
    },

    onExit : function () {

        this._ui = null;
        this._super();
    }
});