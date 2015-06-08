/**
 * Created by yuxiao on 15/5/14.
 */


var EquipScene = ui.GuiSceneBase.extend({
    _guiFile: "ui/qianghua.json",

    ctor: function() {
        this._super();
        this._sel_type = EquipSystem.EquipSlotType.Weapon;
    },

    onEnter: function() {
        this._super();
        this._list_slots = this.seekWidgetByName("list_slots");
        this._info_cur = {
            lbl_type: this.seekWidgetByName("lbl_yuan_buwei"),
            lbl_level: this.seekWidgetByName("lbl_yuan_level"),
            lbl_score: this.seekWidgetByName("lbl_yuan_zhanli")
        };
        this._info_next = {
            lbl_type: this.seekWidgetByName("lbl_hou_buwei"),
            lbl_level: this.seekWidgetByName("lbl_hou_level"),
            lbl_score: this.seekWidgetByName("lbl_hou_zhanli")
        };
        this._lbl_cost = this.seekWidgetByName("lbl_xiaohao");
        this._lbl_gold = this.seekWidgetByName("lbl_dangqian_jinbi");

        this._ctrl_icon = new EquipScene.EquipIcon();
        this._ctrl_icon.setWidget(this.seekWidgetByName("ProjectNode_1"));

        this._bindings = [
            notification.createBinding(notification.event.PLAYER_INFO, this.refreshGoldInfo, this),
            notification.createBinding(notification.event.EQUIP_SLOT_UPGRADE_RESULT, this.refreshSelectedSlotInfo, this)
        ];

        this.createSlotList();
        this.refreshSelectedSlotInfo();
        this.refreshGoldInfo();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this.clearSlotList();
        this._ctrl_icon.setWidget(null);
        this._ctrl_icon = null;
        this._list_slots = null;
        this._info_cur = null;
        this._info_next = null;
        this._lbl_cost = null;
        this._lbl_gold = null;
        this._super();
    },

    clearSlotList: function() {
        _.each(this._slots, function(slot) {
            slot.setSelectCallback(null);
        }, this);
        this._slots = null;
        this._list_slots.removeAllItems();
    },

    createSlotList: function() {
        this.clearSlotList();

        this._slots = [];
        _.each(EquipSystem.instance.slots, function(info) {
            var slot = new EquipScene.EquipSlot(info.slot, info.level);
            slot.setSelectCallback(this.onSelectSlot, this);
            this._list_slots.pushBackCustomItem(slot);
            this._slots.push(slot);
        }, this);
    },

    refreshSelectedSlotInfo: function() {
        // set selected status
        _.each(this._slots, function(slot) {
            slot.setSelected(this._sel_type == slot.type);
        }, this);

        // selected slot icon
        this._ctrl_icon.setSlotType(this._sel_type);

        var info = EquipSystem.instance.slots[this._sel_type];
        if(info == undefined) {
            return;
        }

        // slot info
        var upgrade_id = EquipSystem.getEquipSlotUpgradeId(this._sel_type, info.level);
        var config = configdb.duanzao[upgrade_id];
        if(config == undefined) {
            return;
        }

        var prop = EquipSystem.getEquipProperty(config.prop_type);
        this._info_cur.lbl_type.setString(EquipSystem.getEquipSlotName(config.slot_type));
        this._info_cur.lbl_level.setString(this._info_cur.lbl_level._str_original.format(String(config.level)));
        this._info_cur.lbl_score.setString(this._info_cur.lbl_score._str_original.format(prop, String(config.prop_value)));
        this._lbl_cost.setString(this._lbl_cost._str_original.format(String(config.cost)));

        // top level
        if(config.next == undefined) {
            this._info_next.lbl_type.setString(EquipSystem.getEquipSlotName(config.slot_type));
            this._info_next.lbl_level.setString("已到最高级");
            this._info_next.lbl_score.setString(this._info_next.lbl_score._str_original.format(prop, String(config.prop_value)));
            return;
        }

        config = configdb.duanzao[config.next];
        if(config == undefined) {
            return;
        }

        prop = EquipSystem.getEquipProperty(config.prop_type);
        this._info_next.lbl_type.setString(EquipSystem.getEquipSlotName(config.slot_type));
        this._info_next.lbl_level.setString(this._info_next.lbl_level._str_original.format(String(config.level)));
        this._info_next.lbl_score.setString(this._info_next.lbl_score._str_original.format(prop, String(config.prop_value)));
    },

    onSelectSlot: function(slot) {
        this._sel_type = slot.type;
        this.refreshSelectedSlotInfo();
    },

    refreshGoldInfo: function() {
        this._lbl_gold.setString(String(PlayerSystem.instance.gold));
    },

    _on_btn_biaoqian_guanbi: function() {
        this.popScene();
    },

    _on_btn_qianghua: function() {
        //var win = MessageBoxOkCancel.show("确认升级？");
        //win.setOkCallback(function() {
        //    EquipSystem.instance.upgradeEquipSlot(this._sel_type);
        //}, this);

        EquipSystem.instance.upgradeEquipSlot(this._sel_type);
    }
});


EquipScene.EquipSlot = ui.GuiWidgetBase.extend({
    _guiFile: "ui/qianghua_zhuangbei.json",

    ctor: function(type) {
        this._super();
        this.type = type;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            img_sel: this.seekWidgetByName("img_selected"),
            lbl_name: this.seekWidgetByName("lbl_zhuangbei"),
            lbl_level: this.seekWidgetByName("lbl_level"),
            btn_select: this.seekWidgetByName("btn_enter")
        };
        this._bindings = [
            notification.createBinding(notification.event.EQUIP_SLOT_UPGRADE_RESULT, this.refreshSlotLevel, this)
        ];

        this._ui.icon = new EquipScene.EquipIcon(this.type);
        this._ui.icon.setWidget(this.seekWidgetByName("ProjectNode_icon"));

        this._ui.lbl_name.setString(EquipSystem.getEquipSlotName(this.type));

        this.refreshSlotLevel();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._ui.icon.setWidget(null);
        this._ui = null;
        this._super();
        this._selectCallback = null;
    },

    refreshSlotLevel: function() {
        var info = EquipSystem.instance.slots[this.type];
        if(info) {
            this._ui.lbl_level.setString(this._ui.lbl_level._str_original.format(String(info.level)));
        }
    },

    setSelected: function(val) {
        this._ui.img_sel.setVisible(val);
        this._ui.btn_select.setEnabled(!val);
    },

    setSelectCallback: function (selector, target) {
        if(target === undefined)
            this._selectCallback = selector;
        else
            this._selectCallback = selector.bind(target);
    },

    _on_btn_enter: function() {
        if (this._selectCallback) {
            this._selectCallback(this);
        }
    }
});

EquipScene.EquipIcon = ui.GuiController.extend({
    ctor: function(slot) {
        this._super();
        this.slot = slot;
    },

    onEnter: function() {
        this._super();
        this._img_sel = this.seekWidgetByName("img_enter");
        this._btn_sel = this.seekWidgetByName("btn_sel");
        this._lbl_num = this.seekWidgetByName("lbl_num");
        this._img_icon = this.seekWidgetByName("img_icon");

        this._img_sel.setVisible(false);
        this._lbl_num.setVisible(false);
        this._btn_sel.setEnabled(false);

        this.refreshEquipSlot();
    },

    onExit: function() {
        this._img_icon = null;
        this._img_sel = null;
        this._btn_sel = null;
        this._lbl_num = null;
        this._super();
    },

    setSlotType: function(slot) {
        this.slot = slot;
        this.refreshEquipSlot();
    },

    refreshEquipSlot: function() {
        var info = EquipSystem.instance.slots[this.slot];
        if(info == undefined) {
            return;
        }

        var config = configdb.equip[info.id];
        if(config && config.icon) {
            this._img_icon.loadTexture(config.icon);
        }
        else {
            this._img_icon.loadTexture("images/ui/ui_14.png");
        }
    }
});

