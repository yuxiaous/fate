/**
 * Created by yuxiao on 15/5/14.
 */


var EquipScene = ui.GuiWindowBase.extend({
    _guiFile: "ui/equip_scene.json",

    ctor: function() {
        this._super();
        this._sel_type = EquipSystem.EquipSlotType.Weapon;
        this._last_score = PlayerSystem.instance.getPlayerBattleScore().score;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            ctrl_gold: (function() {
                var ctrl = new ResourcePanel(ResourcePanel.Type.Gold);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_gold"));
                ctrl.showAddButton(false);
                return ctrl;
            }.bind(this) ()),
            ctrl_diamond: (function() {
                var ctrl = new ResourcePanel(ResourcePanel.Type.Diamond);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_diamond"));
                ctrl.showAddButton(false);
                return ctrl;
            }.bind(this) ()),
            ctrl_equip_1: (function() {
                var ctrl = new EquipScene.EquipIcon(0);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_pre"));
                return ctrl;
            }.bind(this) ()),
            ctrl_equip_2: (function() {
                var ctrl = new EquipScene.EquipIcon(0);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_next"));
                return ctrl;
            }.bind(this) ()),

            list_equips: this.seekWidgetByName("list_equips"),
            cell_equips: [],

            lbl_name_1: this.seekWidgetByName("lbl_equip_name_1"),
            lbl_name_2: this.seekWidgetByName("lbl_equip_name_2"),
            lbl_part_1: this.seekWidgetByName("lbl_equip_part_1"),
            lbl_part_2: this.seekWidgetByName("lbl_equip_part_2"),
            lbl_level_1: this.seekWidgetByName("lbl_equip_level_1"),
            lbl_level_2: this.seekWidgetByName("lbl_equip_level_2"),
            lbl_prop_1: this.seekWidgetByName("lbl_equip_prop_1"),
            lbl_prop_2: this.seekWidgetByName("lbl_equip_prop_2"),
            lbl_price: this.seekWidgetByName("lbl_equip_price"),
            btn_leveup: this.seekWidgetByName("btn_duanzao")
        };
        this._bindings = [
            notification.createBinding(notification.event.EQUIP_SLOT_INFO, this.refreshSelectedSlotInfo, this),
            notification.createBinding(notification.event.EQUIP_PROPERTY_CHANGE, function () {
                var curScore = PlayerSystem.instance.getPlayerBattleScore().score;
                CombatForcesEffect.createForcesEffect(curScore - this._last_score,this)
                this._last_score = PlayerSystem.instance.getPlayerBattleScore().score;
                _.each(this._ui.cell_equips, function(cell) {
                    if(cell.type == this._sel_type){
                        cell.setRaiseEffect();
                    }
                }, this);


            }, this),
        ];

        this.createSlotList();
        this.refreshSelectedSlotInfo();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this.clearSlotList();
        this._ui.ctrl_gold.setWidget(null);
        this._ui.ctrl_diamond.setWidget(null);
        this._ui.ctrl_equip_1.setWidget(null);
        this._ui.ctrl_equip_2.setWidget(null);
        this._ui = null;
        this._super();
    },

    clearSlotList: function() {
        _.each(this._ui.cell_equips, function(cell) {
            cell.setSelectCallback(null);
        }, this);
        this._ui.cell_equips.length = 0;
        this._ui.list_equips.removeAllItems();
    },

    createSlotList: function() {
        this.clearSlotList();

        _.each(EquipSystem.instance.slots, function(info) {
            var id = EquipSystem.getEquipSlotUpgradeId(info.slot, info.level);
            var config = configdb.duanzao[id];
            if(config) {
                var cell = new EquipScene.EquipCell(info.slot);
                this._ui.list_equips.pushBackCustomItem(cell);
                this._ui.cell_equips.push(cell);
                cell.setSelectCallback(this.onSelectSlot, this);
            }
        }, this);
    },

    onSelectSlot: function(cell) {
        this._sel_type = cell.type;
        this.refreshSelectedSlotInfo();
    },

    refreshSelectedSlotInfo: function() {
        LOG("SELECT SLOT INFO");
        _.each(this._ui.cell_equips, function(cell) {
            cell.setSelected(cell.type == this._sel_type);
        }, this);

        // selected slot icon
        this._ui.ctrl_equip_1.setSlotType(this._sel_type);
        this._ui.ctrl_equip_2.setSlotType(this._sel_type);

        var info = EquipSystem.instance.slots[this._sel_type];
        if(info == undefined) {
            return;
        }

        // slot info
        var config = configdb.duanzao[EquipSystem.getEquipSlotUpgradeId(this._sel_type, info.level)];
        if(config == undefined) {
            return;
        }

        // name
        var name = EquipSystem.getEquipSlotName(config.slot_type);
        this._ui.lbl_name_1.setString(name);
        this._ui.lbl_name_2.setString(name);

        // part
        var part = EquipSystem.getEquipSlotName(config.slot_type);
        this._ui.lbl_part_1.setString(this._ui.lbl_part_1._str_original.format(part));
        this._ui.lbl_part_2.setString(this._ui.lbl_part_2._str_original.format(part));

        // level
        this._ui.lbl_level_1.setString(this._ui.lbl_level_1._str_original.format(config.level));

        // prop
        var prop = EquipSystem.getEquipProperty(config.prop_type);
        this._ui.lbl_prop_1.setString(this._ui.lbl_prop_1._str_original.format({prop: prop, val:config.prop_value}));

        // price
        this._ui.lbl_price.setString(this._ui.lbl_price._str_original.format(config.cost));

        // top level
        if(config.next) {
            config = configdb.duanzao[config.next];
            if(config == undefined) {
                return;
            }

            // level
            this._ui.lbl_level_2.setString(this._ui.lbl_level_2._str_original.format(config.level));

            // prop
            this._ui.lbl_prop_2.setString(this._ui.lbl_prop_2._str_original.format({prop: prop, val:config.prop_value}));

            this._ui.btn_leveup.setEnabled(true);
            this._ui.btn_leveup.setBright(true);
        }
        else {
            this._ui.lbl_price.setString("");
            this._ui.lbl_part_2.setString("");
            this._ui.lbl_level_2.setString("已到最高等级");
            this._ui.lbl_prop_2.setString("");
            this._ui.btn_leveup.setEnabled(false);
            this._ui.btn_leveup.setBright(false);
        }
    },

    _on_btn_close: function() {
        this.close();
    },

    _on_btn_duanzao: function() {
        //var win = MessageBoxOkCancel.show("确认升级？");
        //win.setOkCallback(function() {
        //    EquipSystem.instance.upgradeEquipSlot(this._sel_type);
        //}, this);

        EquipSystem.instance.upgradeEquipSlot(this._sel_type);
    }
});


EquipScene.EquipCell = ui.GuiWidgetBase.extend({
    _guiFile: "ui/equip_cell.json",

    ctor: function(type) {
        this._super();
        this.type = type;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            icon: (function() {
                var ctrl = new EquipScene.EquipIcon(this.type);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_icon"));
                return ctrl;
            }.bind(this) ()),

            btn_select: this.seekWidgetByName("btn_touch"),
            lbl_name: this.seekWidgetByName("lbl_name"),
            lbl_level: this.seekWidgetByName("lbl_level"),
            img_sel: this.seekWidgetByName("img_sel")
        };
        this._bindings = [
            notification.createBinding(notification.event.EQUIP_SLOT_INFO, this.refreshEquipInfo, this)
        ];

        this.refreshEquipInfo();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        //this._ui.icon.setWidget(null);
        this._ui = null;
        this._super();
    },

    refreshEquipInfo: function() {
        var info = EquipSystem.instance.slots[this.type];
        if(info) {
            this._ui.lbl_name.setString(EquipSystem.getEquipSlotName(this.type));

            this._ui.lbl_level.setString(this._ui.lbl_level._str_original.format(String(info.level)));
        }
    },

    setSelected: function(val) {
        this._ui.img_sel.setVisible(val);
        this._ui.btn_select.setEnabled(!val);
    },

    setRaiseEffect : function () {
        var tmpStr = "res/images/code_ui/ui_";
        var vin_ani = new cc.Sprite(tmpStr + "199.png");
        var iconNode = this.seekWidgetByName("ProjectNode_icon")
        var pos = cc.p(iconNode.getPosition().x + iconNode.getContentSize().width/2,iconNode.getPosition().y + iconNode.getContentSize().height/2);
        vin_ani.setPosition(pos);
        this.addChild(vin_ani);
        var animFrames = []
        for(var i = 1; i <= 8; i++){
            var strName = tmpStr + (199+i) + ".png";
            var size = cc.Sprite(strName).getContentSize();
            var frame = cc.SpriteFrame.create(strName,cc.rect(0,0,size.width,size.height));
            animFrames.push(frame);
        }
        var animation = new cc.Animation(animFrames,0.1,2);
        var animationAction = new cc.Animate(animation);
        vin_ani.runAction(animationAction);
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

EquipScene.EquipIcon = ui.GuiController.extend({
    ctor: function(slot) {
        this._super();
        this.slot = slot;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_num: this.seekWidgetByName("lbl_num"),
            img_sel: this.seekWidgetByName("img_sel")
        };

        this._ui.lbl_num.setVisible(false);
        this._ui.img_sel.setVisible(false);

        this.refreshEquipIcon();
    },

    onExit: function() {
        this._ui = null;
        this._super();
    },

    setSlotType: function(slot) {
        this.slot = slot;
        this.refreshEquipIcon();
    },

    refreshEquipIcon: function() {
        this._ui.sp_icon.setVisible(false);

        var info = EquipSystem.instance.slots[this.slot];
        if(info == undefined) {
            return;
        }

        var config = configdb.equip[info.id];
        if(config == undefined) {
            return;
        }

        if(config.icon) {
            this._ui.sp_icon.setVisible(true);
            this._ui.sp_icon.setTexture(config.icon);
        }
    }
});

