/**
 * Created by yuxiao on 15/8/17.
 */


var SelectHeroPanel = ui.GuiWindowBase.extend({
    _guiFile: "ui/select_hero_layer.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        this._ui = {
            list_heros: this.seekWidgetByName("list_heros"),
            cell_heros: []
        };

        this.createHeroList();
    },

    onExit: function() {
        this.clearHeroList();
        this._ui = null;
        this._super();
    },

    clearHeroList: function() {
        _.each(this._ui.cell_hero, function(cell) {

        }, this);
        this._ui.cell_heros.length = 0;
        this._ui.list_heros.removeAllItems();
    },

    createHeroList: function() {
        this.clearHeroList();

        _.each(configdb.skin, function(config) {
            var cell = new SelectHeroPanel.HeroSkinCell(config.key);
            this._ui.cell_heros.push(cell);
            this._ui.list_heros.pushBackCustomItem(cell);
        }, this);
    },

    _on_btn_close: function() {
        this.close();
    }
});

SelectHeroPanel.HeroSkinCell = ui.GuiWidgetBase.extend({
    _guiFile: "ui/select_hero_cell.json",

    ctor: function(id) {
        this._super();
        this.skinId = id;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            avatar: this.seekWidgetByName("Node_avatar"),
            lbl_using: this.seekWidgetByName("lbl_using"),
            lbl_unused: this.seekWidgetByName("lbl_unused"),
            lbl_locked: this.seekWidgetByName("lbl_locked"),
            lbl_name: this.seekWidgetByName("lbl_name"),
            lbl_score: this.seekWidgetByName("lbl_score")
        };
        this._bindings = [
            notification.createBinding(notification.event.SKIN_INFO, this.refreshUsingStatus, this)
        ];

        var config = configdb.skin[this.skinId];
        if(config == undefined) {
            return;
        }

        this._ui.lbl_name.setString(config.name);

        this.createAvatar();
        this.refreshUsingStatus();
    },

    onExit: function() {
        this.clearAvatar();
        notification.removeBinding(this._bindings);
        this._super();
    },

    clearAvatar: function() {
        this._ui.avatar.removeAllChildren();
    },

    createAvatar: function() {
        this.clearAvatar();

        var config = configdb.skin[this.skinId];
        if(config == undefined) {
            return;
        }

        var avatar = new ShowRole(config.role_id);
        this._ui.avatar.addChild(avatar);
    },

    refreshUsingStatus: function() {
        var has_used = (SkinSystem.instance.use_skin == this.skinId);
        var has_skin = false;
        _.each(SkinSystem.instance.skins, function(info) {
            if(info.skin_id == this.skinId) {
                has_skin = true;
            }
        }, this);

        if(has_used) {
            this._ui.lbl_using.setVisible(true);
            this._ui.lbl_unused.setVisible(false);
            this._ui.lbl_locked.setVisible(false);
        }
        else if(has_skin) {
            this._ui.lbl_using.setVisible(false);
            this._ui.lbl_unused.setVisible(true);
            this._ui.lbl_locked.setVisible(false);
        }
        else {
            this._ui.lbl_using.setVisible(false);
            this._ui.lbl_unused.setVisible(false);
            this._ui.lbl_locked.setVisible(true);
        }
    },

    _on_btn_touch: function() {
        var has_used = (SkinSystem.instance.use_skin == this.skinId);
        var has_skin = false;
        _.each(SkinSystem.instance.skins, function(info) {
            if(info.skin_id == this.skinId) {
                has_skin = true;
            }
        }, this);

        if(has_used) {
            // do nothing
        }
        else if(has_skin) {
            SkinSystem.instance.changeSkin(this.skinId);
        }
        else {
            var win = new SelectHeroPanel.ConfirmWindow();
            win.pop();
        }
    }

});

SelectHeroPanel.ConfirmWindow = ui.GuiWindowBase.extend({
    _guiFile: "ui/select_hero_confirm.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
    },

    onExit: function() {
        this._super();
    },

    _on_btn_cancel: function() {
        this.close();
    },

    _on_btn_play: function() {
        BattleSystem.instance.startTryBattle(Nero);
    },

    _on_btn_buy: function() {
        ui.pushScene(new ShopScene(ShopSystem.ShopType.Role))
    }
});

