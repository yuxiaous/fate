/**
 * Created by yuxiao on 15/8/18.
 */


var StrengthenPanel = ui.GuiWindowBase.extend({
    _guiFile: "ui/strengthen_layer.json",

    ctor: function(equip_id) {
        this._super();
        this._equip_id = equip_id;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            ctrl_equips: [],
            ctrl_needs: [],
            lbl_equip_name: [
                this.seekWidgetByName("lbl_name_1"),
                this.seekWidgetByName("lbl_name_2")
            ],
            lbl_equip_prop: [
                this.seekWidgetByName("lbl_prop_1"),
                this.seekWidgetByName("lbl_prop_2")
            ],
            lbl_cost: this.seekWidgetByName("lbl_cost"),
            lbl_gold: this.seekWidgetByName("lbl_gold"),
            lbl_need: [
                this.seekWidgetByName("lbl_need_1"),
                this.seekWidgetByName("lbl_need_2"),
                this.seekWidgetByName("lbl_need_3"),
                this.seekWidgetByName("lbl_need_4")
            ]
        };

        var config = configdb.equip[this._equip_id];
        if(config == undefined) {
            return;
        }

        var next_config = configdb.equip[config.qh_next];

        _.each([
            ["ProjectNode_1", this._equip_id],
            ["ProjectNode_2", config.qh_next]
        ], function(data) {
            var ctrl = new EquipIconWidget(data[1]);
            ctrl.setWidget(this.seekWidgetByName(data[0]));
            this._ui.ctrl_equips.push(ctrl);
        }, this);

        _.each([
            ["ProjectNode_3", config.qh_need_1],
            ["ProjectNode_4", config.qh_need_2],
            ["ProjectNode_5", config.qh_need_3],
            ["ProjectNode_6", config.qh_need_4]
        ], function(data) {
            var ctrl = new ItemIconWidget(data[1]);
            ctrl.setWidget(this.seekWidgetByName(data[0]));
            this._ui.ctrl_needs.push(ctrl);
        }, this);

        // equip name
        this._ui.lbl_equip_name[0].setString(config.name);
        if(next_config) {
            this._ui.lbl_equip_name[1].setString(next_config.name);
        }
        else {
            this._ui.lbl_equip_name[1].setVisible(false);
        }

        // equip property
        var prop_type = EquipSystem.getEquipPropertyType(config.slot);
        this._ui.lbl_equip_prop[0].setString(this._ui.lbl_equip_prop[0]._str_original.format({
            prop: EquipSystem.getEquipProperty(prop_type),
            value: config[EquipSystem.getEquipPropertyKey(prop_type)]
        }));
        if(next_config) {
            this._ui.lbl_equip_prop[1].setString(this._ui.lbl_equip_prop[1]._str_original.format({
                prop: EquipSystem.getEquipProperty(prop_type),
                value: next_config[EquipSystem.getEquipPropertyKey(prop_type)]
            }));
        }
        else {
            this._ui.lbl_equip_prop[1].setVisible(false);
        }

        // need gold
        this._ui.lbl_cost.setString(this._ui.lbl_cost._str_original.format(config.qh_gold));

        // current gold
        this._ui.lbl_gold.setString(this._ui.lbl_gold._str_original.format(PlayerSystem.instance.gold));

        // need item
        _.each([
            [config.qh_need_1, config.qh_num_1],
            [config.qh_need_2, config.qh_num_2],
            [config.qh_need_3, config.qh_num_3],
            [config.qh_need_4, config.qh_num_4]
        ], function(data, i) {
            var label = this._ui.lbl_need[i];
            if(data[0]) {
                var num = BagSystem.instance.getItemNums(data[0]);
                label.setString(label._str_original.format(num, data[1]));
                if(num < data[1]) {
                    label.setColor(cc.RED);
                }
            }
            else {
                label.setVisible(false);
            }
        }, this);
    },

    onExit: function() {
        _.each(this._ui.ctrl_equips, function(ctrl) {
            ctrl.setWidget(null);
        });
        _.each(this._ui.ctrl_needs, function(ctrl) {
            ctrl.setWidget(null);
        });
        this._ui = null;
        this._super();
    },

    _on_btn_close: function() {
        this.close();
    },

    _on_btn_strengthen: function() {

    }
});

