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
        var enable = (this._class != MissionSystem.Class.Daily);
        this._ui.tab_daily.setEnabled(enable);
        this._ui.tab_daily.setBright(enable);

        enable = (this._class != MissionSystem.Class.Achievement);
        this._ui.tab_achievement.setEnabled(enable);
        this._ui.tab_achievement.setBright(enable);
    },

    clearList: function() {
        this._ui.cell_missions.length = 0;
        this._ui.list_missions.removeAllItems();
    },

    createList: function() {
        this.clearList();

        _.each(MissionSystem.instance.mission_list, function(info) {
            var config = configdb.renwu[info.mission_id];
            if(config == undefined) {
                return;
            }

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
            lbl_desc: this.seekWidgetByName("lbl_desc"),
            status_1: this.seekWidgetByName("img_status_1"),
            status_2: this.seekWidgetByName("img_status_2"),
            status_3: this.seekWidgetByName("img_status_3"),
            lbl_progress_1: this.seekWidgetByName("lbl_progress_1"),
            lbl_progress_2: this.seekWidgetByName("lbl_progress_2"),
            lbl_progress_3: this.seekWidgetByName("lbl_progress_3")
        };

        this.refreshView();
    },

    onExit: function() {
        this._ui = null;
        this._super();
    },

    refreshView: function() {
        var config = configdb.renwu[this._mission_id];
        if(config == undefined) {
            return;
        }

        var info = MissionSystem.instance.mission_list[this._mission_id];

        // status
        var count = info ? info.count : 0;
        var reward = info ? info.reward : 0;
        if(reward == 1) {
            this._ui.status_1.setVisible(false);
            this._ui.status_2.setVisible(false);
            this._ui.status_3.setVisible(true);
        }
        else if(count >= config.need_num) {
            this._ui.status_1.setVisible(false);
            this._ui.status_2.setVisible(true);
            this._ui.status_3.setVisible(false);
        }
        else {
            this._ui.status_1.setVisible(true);
            this._ui.status_2.setVisible(false);
            this._ui.status_3.setVisible(false);
        }

        // name
        this._ui.lbl_name.setString(config.name);

        // desc
        this._ui.lbl_desc.setString(config.desc);

        // reward

        // progress
        this._ui.lbl_progress_1.setString(this._ui.lbl_progress_1._str_original.format(count, config.need_num));
        this._ui.lbl_progress_2.setString(this._ui.lbl_progress_2._str_original.format(count, config.need_num));
        this._ui.lbl_progress_3.setString(this._ui.lbl_progress_3._str_original.format(count, config.need_num));
    },

    _on_btn_goto: function() {

    },

    _on_btn_get_reward: function() {
        MissionSystem.instance.getMissionReward(this._mission_id);
    }
});

