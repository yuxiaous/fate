/**
 * Created by yuxiao on 15/10/26.
 */


var MissionScene = ui.GuiWindowBase.extend({
    _guiFile: "ui/mission.json",

    ctor: function() {
        this._super();
        this._class = MissionSystem.Class.Daily;
    },

    onEnter: function() {
        this._super();

        this._ui = {
            tab_daily: this.seekWidgetByName("btn_tab_1"),
            tab_achievement: this.seekWidgetByName("btn_tab_2"),
            list_missions: this.seekWidgetByName("list_missions"),
            cell_missions: []
        };
        this._bindings = [

        ];

        this.refreshTab();
        this.createList();
    },

    onExit: function() {
        this.clearList();
        notification.removeBinding(this._bindings);
        this._ui = null;
        this._super();
    },

    _on_btn_back: function() {
        this.close();
    },

    _on_btn_tab_1: function() {
        this._class = MissionSystem.Class.Daily;
        this.refreshTab();
        this.createList();
    },

    _on_btn_tab_2: function() {
        this._class = MissionSystem.Class.Achievement;
        this.refreshTab();
        this.createList();
    },

    refreshTab: function() {
        var enable = (this._class == MissionSystem.Class.Daily);
        this._ui.tab_daily.setEnabled(!enable);
        this._ui.tab_daily.setBright(!enable);

        enable = (this._class == MissionSystem.Class.Achievement);
        this._ui.tab_achievement.setEnabled(!enable);
        this._ui.tab_achievement.setBright(!enable);
    },

    clearList: function() {
        this._ui.cell_missions.length = 0;
        this._ui.list_missions.removeAllItems();
    },

    createList: function() {
        this.clearList();

        _.each(configdb.renwu, function(config) {
            if(config.class != this._class) {
                return;
            }

            var cell = new MissionScene.Cell(config.key);
            this._ui.cell_missions.push(cell);
            this._ui.list_missions.pushBackCustomItem(cell);
        }, this);
    }
});

MissionScene.Cell = ui.GuiWidgetBase.extend({
    _guiFile: "ui/mission_cell.json",

    ctor: function(mission_id) {
        this._super();
        this._mission_id = mission_id;
    },

    onEnter: function() {
        this._super();

        this._ui = {
            lbl_name: this.seekWidgetByName("lbl_name"),
            lbl_desc: this.seekWidgetByName("lbl_desc")
        };

        this.refreshView();
    },

    onExit: function() {
        this._super();
    },

    refreshView: function() {
        var config = configdb.renwu[this._mission_id];
        if(config == undefined) {
            return;
        }

        // name
        this._ui.lbl_name.setString(config.name);

        // desc
        this._ui.lbl_desc.setString(config.desc);
    }
});

