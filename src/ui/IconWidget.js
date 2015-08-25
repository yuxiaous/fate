/**
 * Created by yuxiao on 15/6/15.
 */


var IconWidget = ui.GuiController.extend({
    ctor: function(id, type, num) {
        this._super();
        this.id = id || 0;
        this.type = type || IconWidget.Type.Item;
        this.num = num || 0;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_num: this.seekWidgetByName("lbl_num"),
            img_sel: this.seekWidgetByName("img_sel"),
            btn_touch: this.seekWidgetByName("btn_bg"),
            sp_star: this.seekWidgetByName("sp_star"),
            lbl_star: this.seekWidgetByName("lbl_star")
        };

        this._ui.img_sel.setVisible(false);
        this._ui.lbl_num.setVisible(false);
        this._ui.btn_touch.setEnabled(false);
        this._ui.sp_star.setVisible(false);

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
        this._ui.sp_icon.setVisible(false);
        this._ui.sp_star.setVisible(false);
        this._ui.lbl_num.setVisible(false);

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

        // icon
        if(config.icon) {
            this._ui.sp_icon.setVisible(true);
            this._ui.sp_icon.setTexture(config.icon);
        }

        // star
        if(config.star != undefined) {
            this._ui.sp_star.setVisible(true);
            this._ui.lbl_star.setString(String(config.star));
        }

        // number
        if(this._num > 1) {
            this._ui.lbl_num.setVisible(true);

            if(this.num >= 10000 && this.num % 10000 == 0) {
                this._ui.lbl_num.setString(String(Math.floor(this.num/10000)) + "万");
            }
            else {
                this._ui.lbl_num.setString(String(this.num));
            }
        }
    },

    _on_btn_bg: function() {
        if(this._touchCallback) {
            this._touchCallback(this);
        }
    },

    setTouchCallback: function(selector, target) {
        if(target === undefined)
            this._touchCallback = selector;
        else
            this._touchCallback = selector.bind(target);
    }
});

IconWidget.Type = {
    Equip: 1,
    Item: 2,
    Skin: 3
};



var EquipIconWidget = ui.GuiController.extend({
    ctor: function(equip_id) {
        this._super();
        this._equip_id = equip_id || 0;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_num: this.seekWidgetByName("lbl_num"),
            img_sel: this.seekWidgetByName("img_sel"),
            btn_touch: this.seekWidgetByName("btn_bg"),
            sp_star: this.seekWidgetByName("sp_star"),
            lbl_star: this.seekWidgetByName("lbl_star")
        };

        this._ui.lbl_num.setVisible(false);
        this._ui.img_sel.setVisible(false);
        this._ui.btn_touch.setEnabled(false);

        this.refreshIcon();
    },

    onExit: function() {
        this._ui = null;
        this._super();
    },

    refreshIcon: function() {
        this._ui.sp_icon.setVisible(false);
        this._ui.sp_star.setVisible(false);

        if(this._equip_id == 0) {
            return;
        }

        var config = BagSystem.getConfig(this._equip_id);
        if(config == undefined) {
            return;
        }

        // icon
        if(config.icon) {
            this._ui.sp_icon.setVisible(true);
            this._ui.sp_icon.setTexture(config.icon);
        }

        // star
        if(config.star != undefined) {
            this._ui.sp_star.setVisible(true);
            this._ui.lbl_star.setString(String(config.star));
        }
    },

    setEquipId: function(id) {
        this._equip_id = id || 0;
        this.refreshIcon();
    }
});


var ItemIconWidget = ui.GuiController.extend({
    ctor: function(item_id, num) {
        this._super();
        this._item_id = item_id || 0;
        this._num = num || 0;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_num: this.seekWidgetByName("lbl_num"),
            img_sel: this.seekWidgetByName("img_sel"),
            btn_touch: this.seekWidgetByName("btn_bg"),
            sp_star: this.seekWidgetByName("sp_star"),
            lbl_star: this.seekWidgetByName("lbl_star")
        };

        this._ui.img_sel.setVisible(false);
        this._ui.btn_touch.setEnabled(false);
        this._ui.sp_star.setVisible(false);

        this.refreshIcon();
    },

    onExit: function() {
        this._ui = null;
        this._super();
    },

    refreshIcon: function() {
        this._ui.sp_icon.setVisible(false);
        this._ui.lbl_num.setVisible(false);

        var config = BagSystem.getConfig(this._item_id);
        if(config == undefined) {
            return;
        }

        // icon
        if(config.icon) {
            this._ui.sp_icon.setVisible(true);
            this._ui.sp_icon.setTexture(config.icon);
        }

        // number
        if(this._num > 1) {
            this._ui.lbl_num.setVisible(true);
            this._ui.lbl_num.setString(String(this._num));
        }
    }
});

