/**
 * Created by yuxiao on 15/6/15.
 */


var IconWidget = ui.GuiController.extend({
    ctor: function(id, type) {
        this._super();
        this.id = id || 0;
        this.type = type || 0;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_num: this.seekWidgetByName("lbl_num"),
            img_sel: this.seekWidgetByName("img_sel")
        };

        this._ui.img_sel.setVisible(false);
        this._ui.lbl_num.setVisible(false);

        this.refreshIcon();
    },

    onExit: function() {
        this._ui = null;
        this._super();
    },

    setItemId: function(id, type) {
        this.id = id;
        this.type = type;
        this.refreshIcon();
    },

    refreshIcon: function() {
        if(this.id == 0 || this.type == 0) {
            return;
        }

        var config = null;
        if(this.type == IconWidget.Type.Equip) {
            config = configdb.equip[this.id];
        }
        else if(this.type == IconWidget.Type.Item) {
            config = configdb.item[this.id];
        }
        if(config == undefined) {
            return;
        }

        this._ui.sp_icon.setTexture(config.icon);
    },

    _on_btn_bg: function() {

    }
});

IconWidget.Type = {
    Equip: 1,
    Item: 2
};

