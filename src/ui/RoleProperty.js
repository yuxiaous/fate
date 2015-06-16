/**
 * Created by yuxiao on 15/6/16.
 */


var RoleProperty = ui.GuiWindowBase.extend({
    _guiFile: "ui/role_property.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        this._ui = {
            lbl_level: this.seekWidgetByName("lbl_level"),
            lbl_exp: this.seekWidgetByName("lbl_exp"),
            lbl_score: this.seekWidgetByName("lbl_score"),
            lbl_hp: this.seekWidgetByName("lbl_hp"),
            lbl_mp: this.seekWidgetByName("lbl_mp"),
            lbl_atk: this.seekWidgetByName("lbl_atk"),
            lbl_def: this.seekWidgetByName("lbl_def"),
            lbl_crit: this.seekWidgetByName("lbl_crit"),
            lbl_sunder: this.seekWidgetByName("lbl_sunder")
        };

        this.refreshRoleInfo();
    },

    onExit: function() {
        this._ui = null;
        this._super();
    },

    refreshRoleInfo: function() {
        var system = PlayerSystem.instance;
        this._ui.lbl_level.setString(this._ui.lbl_level._str_original.format(system.level));

        var score = system.getPlayerBattleScore();
        this._ui.lbl_score.setString(this._ui.lbl_score._str_original.format(score.score));
        this._ui.lbl_hp.setString(this._ui.lbl_hp._str_original.format(score.hp));
        this._ui.lbl_mp.setString(this._ui.lbl_mp._str_original.format(score.mp));
        this._ui.lbl_atk.setString(this._ui.lbl_atk._str_original.format(score.atk));
        this._ui.lbl_def.setString(this._ui.lbl_def._str_original.format(score.def));
        this._ui.lbl_crit.setString(this._ui.lbl_crit._str_original.format(score.crit));
        this._ui.lbl_sunder.setString(this._ui.lbl_sunder._str_original.format(score.sunder));

        var level_config = configdb.levelup[system.level];
        if(level_config) {
            var pre_level_config = configdb.levelup[system.level-1];

            var pre_exp = pre_level_config ? pre_level_config.exp : 0;

            var need_exp = level_config.exp - pre_exp;
            var cur_exp = system.exp - pre_exp;

            this._ui.lbl_exp.setString(this._ui.lbl_exp._str_original.format(cur_exp, need_exp));
        }

    },

    _on_btn_confirm: function() {
        this.close();
    }
});

