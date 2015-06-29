/**
 * Created by yuxiao on 15/6/15.
 */


var IconWidget = ui.GuiController.extend({
    ctor: function(id, type, num) {
        this._super();
        this.id = id || 0;
        this.type = type || 0;
        this.num = num || 0;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_num: this.seekWidgetByName("lbl_num"),
            img_sel: this.seekWidgetByName("img_sel")
        };

        this._ui.img_sel.setVisible(false);

        this.refreshIcon();
    },

    onExit: function() {
        this._ui = null;
        this._super();
    },

    setIcon: function(id, type, num) {
        this.id = id;
        this.type = type || IconWidget.Type.Item;
        this.num = num || 0;
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
        else if(this.type == IconWidget.Type.Skin) {
            config = configdb.skin[this.id];
            if(config == undefined) {
                return;
            }
            config = configdb.item[config.item_id]
        }
        if(config == undefined) {
            return;
        }

        this._ui.sp_icon.setTexture(config.icon);

        this._ui.lbl_num.setVisible(this.num > 1);
        if(this.num >= 10000 && this.num % 10000 == 0) {
            this._ui.lbl_num.setString(String(Math.floor(this.num/10000)) + "万");
        }
        else {
            this._ui.lbl_num.setString(String(this.num));
        }
    },

    _on_btn_bg: function() {

    }
});

IconWidget.Type = {
    Equip: 1,
    Item: 2,
    Skin: 3
};

