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

        // score
        var score = PlayerSystem.instance.getPlayerBattleScore(this.skinId);
        if(score) {
            this._ui.lbl_score.setString(this._ui.lbl_score._str_original.format(score.score));
        }

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
            var win = new SelectHeroPanel.ConfirmWindow(this.skinId);
            win.pop();
        }
    }

});

SelectHeroPanel.ConfirmWindow = ui.GuiWindowBase.extend({
    _guiFile: "ui/select_hero_confirm.json",

    ctor: function(skin_id) {
        this._super();
        this._skin_id = skin_id;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            lbl_content: this.seekWidgetByName("lbl_content"),
            lbl_content_2: this.seekWidgetByName("lbl_content_2")
        };

        this.refreshContent();
    },

    onExit: function() {
        this._ui = null;
        this._super();
    },

    refreshContent: function() {
        this._ui.lbl_content.setVisible(false);
        this._ui.lbl_content_2.setVisible(false);

        var config = configdb.skin[this._skin_id];
        if(config == undefined) {
            return;
        }

        config = ShopSystem.getConfig(config.shop_id);
        if(config == undefined) {
            return;
        }

        if(this._skin_id == 103) {
            this._ui.lbl_content_2.setVisible(true);
            this._ui.lbl_content_2.setString(this._ui.lbl_content_2._str_original.format({
                lv: configdb.property[115].value,
                num: config.pay_cost,
                curr: ShopSystem.getPayTypeString(config.pay_type),
                what: config.name
            }));
        }
        else {
            this._ui.lbl_content.setVisible(true);
            this._ui.lbl_content.setString(this._ui.lbl_content._str_original.format({
                num: config.pay_cost,
                curr: ShopSystem.getPayTypeString(config.pay_type),
                what: config.name
            }));
        }
    },

    _on_btn_cancel: function() {
        this.close();
    },

    _on_btn_play: function() {
        BattleSystem.instance.startTryBattle(Nero);
        this.close();
    },

    _on_btn_buy: function() {
        ui.pushScene(new ShopScene(ShopSystem.ShopType.Role));
        this.close();
    }
});

