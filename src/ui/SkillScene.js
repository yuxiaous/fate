/**
 * Created by yuxiao on 15/5/10.
 */


var SkillScene = ui.GuiSceneBase.extend({
    _guiFile: "ui/skill_scene.json",

    ctor: function() {
        this._super();

        this._selSkillIndex = 0;
    },

    onEnter: function() {
        this._super();
        this._skill_icon = [
            {
                img_icon: this.seekWidgetByName("img_skill_1"),
                lbl_name: this.seekWidgetByName("lbl_skill_1"),
                btn_sel: this.seekWidgetByName("btn_skill_1")
            },
            {
                img_icon: this.seekWidgetByName("img_skill_2"),
                lbl_name: this.seekWidgetByName("lbl_skill_2"),
                btn_sel: this.seekWidgetByName("btn_skill_2")
            },
            {
                img_icon: this.seekWidgetByName("img_skill_3"),
                lbl_name: this.seekWidgetByName("lbl_skill_3"),
                btn_sel: this.seekWidgetByName("btn_skill_3")
            },
            {
                img_icon: this.seekWidgetByName("img_skill_4"),
                lbl_name: this.seekWidgetByName("lbl_skill_4"),
                btn_sel: this.seekWidgetByName("btn_skill_4")
            }
        ];
        this._skill_desc = [
            {
                lbl_name: this.seekWidgetByName("lbl_skill_name_1"),
                lbl_level: this.seekWidgetByName("lbl_skill_level_1"),
                lbl_desc: this.seekWidgetByName("lbl_skill_desc_1")
            },
            {
                lbl_name: this.seekWidgetByName("lbl_skill_name_2"),
                lbl_level: this.seekWidgetByName("lbl_skill_level_2"),
                lbl_desc: this.seekWidgetByName("lbl_skill_desc_2")
            }
        ];
        this._lbl_cond_lv = this.seekWidgetByName("lbl_cond_lv");
        this._lbl_cond_cost = this.seekWidgetByName("lbl_cond_cost");
        this._lbl_gold = this.seekWidgetByName("lbl_cost_value");

        this._bindings = [
            notification.createBinding(notification.event.PLAYER_INFO, this.refreshGoldInfo, this),
            notification.createBinding(notification.event.SKILL_INFO, this.refreshSkillInfo, this)
        ];

        this.refreshSkillInfo();
        this.refreshGoldInfo();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._skill_icon = null;
        this._skill_desc = null;
        this._lbl_cond_lv = null;
        this._lbl_cond_cost = null;
        this._lbl_gold = null;
        this._super();
    },

    refreshSkillInfo: function() {
        _.each(SkillSystem.instance.skills, function(info, i) {
            var config = configdb.skill[info.skill_id];
            var widget = this._skill_icon[i];
            if(config != undefined && widget != undefined) {
                // icon
                //widget.img_icon

                // name
                widget.lbl_name.setString(widget.lbl_name._str_original.format(info.level, config.name));
            }
        }, this);

        this.refreshSelectedSkillInfo()
    },

    refreshSelectedSkillInfo: function() {
        // selected status
        _.each(this._skill_icon, function(widget, i) {
            var enable = (i != this._selSkillIndex);
            widget.btn_sel.setBright(enable);
            widget.btn_sel.setEnabled(enable);
        }, this);

        // info
        var info = SkillSystem.instance.skills[this._selSkillIndex];

        // seek skill config
        var config = configdb.skill[info.skill_id];
        if(config == undefined) {
            return;
        }

        // seek skill up config
        var skill_name = config.name;
        var skill_up_id = config.skillup_id;
        config = configdb.skillup[skill_up_id + info.level - 1];
        if(config == undefined || config.skill_id != info.skill_id) {
            return;
        }

        var widget = this._skill_desc[0];
        if(widget == undefined) {
            return;
        }

        function setSkillDescInfo(widget, config) {
            // skill name
            widget.lbl_name.setString(skill_name);
            // skill level
            widget.lbl_level.setString(widget.lbl_level._str_original.format(config.level));
            // skill desc
            widget.lbl_desc.setString(config.desc);
        }
        setSkillDescInfo(widget, config);

        // condition
        this._lbl_cond_lv.setString(this._lbl_cond_lv._str_original.format(config.req_level));
        this._lbl_cond_cost.setString(this._lbl_cond_cost._str_original.format(config.cost));

        // next skill up config
        config = configdb.skillup[config.next];
        if(config == undefined || config.skill_id != info.skill_id) {
            return;
        }

        widget = this._skill_desc[1];
        if(widget == undefined) {
            return;
        }

        setSkillDescInfo(widget, config);
    },

    refreshGoldInfo: function() {
        this._lbl_gold.setString(String(PlayerSystem.instance.gold));
    },

    _on_btn_back: function() {
        this.popScene();
    },

    _on_btn_skill_1: function() {
        this._selSkillIndex = 0;
        this.refreshSelectedSkillInfo();
    },

    _on_btn_skill_2: function() {
        this._selSkillIndex = 1;
        this.refreshSelectedSkillInfo();
    },

    _on_btn_skill_3: function() {
        this._selSkillIndex = 2;
        this.refreshSelectedSkillInfo();
    },

    _on_btn_skill_4: function() {
        this._selSkillIndex = 3;
        this.refreshSelectedSkillInfo();
    },

    _on_btn_skill_5: function() {
        //this._selSkillIndex = 4;
    },

    _on_btn_qianghua: function() {
        //var win = MessageBoxOkCancel.show("是否强化？");
        //win.setOkCallback(function () {
        //    var info = SkillSystem.instance.skills[this._selSkillIndex];
        //    SkillSystem.instance.requestSkillLevelUp(info.skill_id);
        //}, this);

        var info = SkillSystem.instance.skills[this._selSkillIndex];
        SkillSystem.instance.requestSkillLevelUp(info.skill_id);
    }
});

