/**
 * Created by yuxiao on 15/5/10.
 */


var SkillScene = ui.GuiWindowBase.extend({
    _guiFile: "ui/skill_scene.json",

    ctor: function() {
        this._super();

        this._sel_skill_id = 0;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            ctrl_gold: (function() {
                var ctrl = new BagScene.Resource(BagScene.Resource.Type.Gold);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_1"));
                return ctrl;
            }.bind(this) ()),
            ctrl_diamond: (function() {
                var ctrl = new BagScene.Resource(BagScene.Resource.Type.Diamond);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_2"));
                return ctrl;
            }.bind(this) ()),

            list_skills: this.seekWidgetByName("list_skills"),
            cell_skills: [],

            lbl_name_1: this.seekWidgetByName("lbl_skill_name_1"),
            lbl_name_2: this.seekWidgetByName("lbl_skill_name_2"),
            lbl_level_1: this.seekWidgetByName("lbl_skill_level_1"),
            lbl_level_2: this.seekWidgetByName("lbl_skill_level_2"),
            lbl_desc_1: this.seekWidgetByName("lbl_skill_desc_1"),
            lbl_desc_2: this.seekWidgetByName("lbl_skill_desc_2"),
            lbl_price: this.seekWidgetByName("lbl_skill_price"),
            sp_icon_1: this.seekWidgetByName("sp_skill_icon_1"),
            sp_icon_2: this.seekWidgetByName("sp_skill_icon_2"),
            btn_leveup: this.seekWidgetByName("btn_qianghua")
        };
        this._bindings = [
            notification.createBinding(notification.event.SKILL_INFO, this.refreshSelectedSkillInfo, this)
        ];

        this.createSkillList();
        this._sel_skill_id = this._ui.cell_skills[0].skillId;
        this.refreshSelectedSkillInfo();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this.clearSkillList();
        this._ui.ctrl_gold.setWidget(null);
        this._ui.ctrl_diamond.setWidget(null);
        this._ui = null;
        this._super();
    },

    clearSkillList: function() {
        _.each(this._ui.cell_skills, function(cell) {
            cell.setSelectCallback(null);
        }, this);
        this._ui.cell_skills.length = 0;
        this._ui.list_skills.removeAllItems();
    },

    createSkillList: function() {
        this.clearSkillList();

        _.each(SkillSystem.instance.skills, function(info) {
            var config = configdb.skill[info.skill_id];
            if(config) {
                var cell = new SkillScene.SkillCell(info.skill_id);
                this._ui.list_skills.pushBackCustomItem(cell);
                this._ui.cell_skills.push(cell);
                cell.setSelectCallback(this.onSelectSkill, this);
            }
        }, this);
    },

    onSelectSkill: function(cell) {
        this._sel_skill_id = cell.skillId;
        this.refreshSelectedSkillInfo();
    },

    refreshSelectedSkillInfo: function() {
        // selected status
        _.each(this._ui.cell_skills, function(cell) {
            cell.setSelected(cell.skillId == this._sel_skill_id);
        }, this);

        // info
        var info = SkillSystem.instance.skills[this._sel_skill_id];
        if(info == undefined) {
            return;
        }

        var skill_config = configdb.skill[info.skill_id];
        if(skill_config == undefined) {
            return;
        }

        // seek skill up config
        var skill_up_id = skill_config.skillup_id;
        var skillup_config = configdb.skillup[skill_up_id + info.level - 1];
        if(skillup_config == undefined || skillup_config.skill_id != info.skill_id) {
            return;
        }

        // icon
        this._ui.sp_icon_1.setTexture(skill_config.icon);
        this._ui.sp_icon_2.setTexture(skill_config.icon);

        // name
        this._ui.lbl_name_1.setString(skill_config.name);
        this._ui.lbl_name_2.setString(skill_config.name);

        // level
        this._ui.lbl_level_1.setString(this._ui.lbl_level_1._str_original.format(skillup_config.level));

        // desc
        this._ui.lbl_desc_1.setString(skillup_config.desc);

        // price
        this._ui.lbl_price.setString(this._ui.lbl_price._str_original.format(skillup_config.cost));

        if(skillup_config.next) {
            skillup_config = configdb.skillup[skillup_config.next];
            if(skillup_config == undefined || skillup_config.skill_id != info.skill_id) {
                return;
            }

            // level
            this._ui.lbl_level_2.setString(this._ui.lbl_level_2._str_original.format(skillup_config.level));

            // desc
            this._ui.lbl_desc_2.setString(skillup_config.desc);

            this._ui.btn_leveup.setEnabled(true);
            this._ui.btn_leveup.setBright(true);
        }
        else {
            this._ui.lbl_price.setString("");
            this._ui.lbl_level_2.setString("");
            this._ui.lbl_desc_2.setString("已到最高等级");
            this._ui.btn_leveup.setEnabled(false);
            this._ui.btn_leveup.setBright(false);
        }
    },

    _on_btn_close: function() {
        //this.popScene();
        this.close();
    },

    _on_btn_qianghua: function() {
        SkillSystem.instance.requestSkillLevelUp(this._sel_skill_id);
    }
});

SkillScene.SkillCell = ui.GuiWidgetBase.extend({
    _guiFile: "ui/skill_cell.json",

    ctor: function(id) {
        this._super();
        this.skillId = id;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_name: this.seekWidgetByName("lbl_name"),
            lbl_level: this.seekWidgetByName("lbl_level"),
            img_sel: this.seekWidgetByName("img_sel"),
            btn_touch: this.seekWidgetByName("btn_touch")
        };
        this._bindings = [
            notification.createBinding(notification.event.SKILL_INFO, this.refreshSkillInfo, this)
        ];

        this.refreshSkillInfo();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._ui = null;
        this._super();
    },

    refreshSkillInfo: function() {
        var info = SkillSystem.instance.skills[this.skillId];
        if(info == undefined) {
            return;
        }

        var config = configdb.skill[info.skill_id];
        if(config == undefined) {
            return;
        }

        if(config) {
            // icon
            this._ui.sp_icon.setTexture(config.icon);

            // name
            this._ui.lbl_name.setString(config.name);

            // level
            this._ui.lbl_level.setString(this._ui.lbl_level._str_original.format(info.level));
        }
    },

    setSelected: function(val) {
        this._ui.img_sel.setVisible(val);
        this._ui.btn_touch.setEnabled(!val);
    },

    setSelectCallback: function (selector, target) {
        if(target === undefined)
            this._selectCallback = selector;
        else
            this._selectCallback = selector.bind(target);
    },

    _on_btn_touch: function() {
        if (this._selectCallback) {
            this._selectCallback(this);
        }
    }
});