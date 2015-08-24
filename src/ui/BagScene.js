/**
 * Created by yuxiao on 15/5/7.
 */


var BagScene = ui.GuiWindowBase.extend({
    _guiFile: "ui/beibao.json",
    LINE_NUMBER: 10,

    ctor: function() {
        this._super();
        this._sel_index = 0;
        this._last_score = PlayerSystem.instance.getPlayerBattleScore().score;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            lbl_player_name: this.seekWidgetByName("lbl_player_name"),
            node_avatar: this.seekWidgetByName("Node_avatar"),
            ctrl_slots: _.reduce([
                [EquipSystem.EquipSlotType.Weapon, "ProjectNode_1"],
                [EquipSystem.EquipSlotType.Coat, "ProjectNode_2"],
                [EquipSystem.EquipSlotType.Head, "ProjectNode_3"],
                [EquipSystem.EquipSlotType.Glove, "ProjectNode_4"],
                [EquipSystem.EquipSlotType.Shield, "ProjectNode_5"],
                [EquipSystem.EquipSlotType.Amulet, "ProjectNode_6"]
            ], function(slots, data){
                var ctrl = new BagScene.EquipSlot(data[0]);
                ctrl.setWidget(this.seekWidgetByName(data[1]));
                ctrl.setSelectCallback(this.onSelectEquip, this);
                slots.push(ctrl);
                return slots;
            }, [], this),

            list_view: this.seekWidgetByName("list_items"),
            ctrl_items: [],
            ctrl_gold: (function() {
                var ctrl = new ResourcePanel(ResourcePanel.Type.Gold);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_7"));
                ctrl.showAddButton(false);
                return ctrl;
            }.bind(this) ()),
            ctrl_diamond: (function() {
                var ctrl = new ResourcePanel(ResourcePanel.Type.Diamond);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_8"));
                ctrl.showAddButton(false);
                //appstore 显示
                ctrl.setVisible(util.getChannelId() == GameChannel.AppStore);
                return ctrl;
            }.bind(this) ()),
            lbl_item_name: this.seekWidgetByName("lbl_item_name"),
            lbl_item_price: this.seekWidgetByName("lbl_item_price"),
            lbl_item_score: this.seekWidgetByName("lbl_item_score"),
            lbl_item_desc: this.seekWidgetByName("lbl_item_desc"),
            btn_use: this.seekWidgetByName("btn_use"),
            btn_sell: this.seekWidgetByName("btn_chushou"),
            btn_strengthen: this.seekWidgetByName("btn_strengthen"),
            lbl_score_change: this.seekWidgetByName("lbl_score_change"),
            sp_change_up: this.seekWidgetByName("sp_change_up"),
            sp_change_down: this.seekWidgetByName("sp_change_down"),

            lbl_prop_level: this.seekWidgetByName("lbl_prop_level"),
            lbl_prop_exp: this.seekWidgetByName("lbl_prop_exp"),
            lbl_prop_score: this.seekWidgetByName("lbl_prop_score"),
            lbl_prop_hp: this.seekWidgetByName("lbl_prop_hp"),
            lbl_prop_mp: this.seekWidgetByName("lbl_prop_mp"),
            lbl_prop_atk: this.seekWidgetByName("lbl_prop_atk"),
            lbl_prop_def: this.seekWidgetByName("lbl_prop_def"),
            lbl_prop_crit: this.seekWidgetByName("lbl_prop_crit"),
            lbl_prop_sunder: this.seekWidgetByName("lbl_prop_sunder")
        };

        this._bindings = [
            notification.createBinding(notification.event.ITEM_INFO, this.refreshItemPage, this),
            notification.createBinding(notification.event.EQUIP_PROPERTY_CHANGE, function () {
                var curScore = PlayerSystem.instance.getPlayerBattleScore().score;
                CombatForcesEffect.createForcesEffect(curScore - this._last_score,this)
                this._last_score = PlayerSystem.instance.getPlayerBattleScore().score;
                //_.each(this._ui.ctrl_items, function(item, i) {
                //    if(i == this._sel_index){
                //        item.setRaiseEffect();
                //    }
                //}, this);
            }, this),
            notification.createBinding(notification.event.SKIN_INFO, this.createRoleAvatar, this),
            notification.createBinding(notification.event.PLAYER_INFO, this.refreshProperty, this),
            notification.createBinding(notification.event.EQUIP_STRENGTHEN_RESULT, function() {
                this.refreshProperty();
                this.refreshItemPage();
                this.refreshSelectedItemInfo();
            }, this),
            notification.createBinding(notification.event.SKIN_INFO, this.refreshProperty, this)
        ];

        this.refreshProperty();
        this.createItemList();
        this.createRoleAvatar();
        this.refreshItemPage();

        GuideSystem.AddGuidePanel(this._ui.btn_use,104);
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this.clearItemList();
        this.clearRoleAvatar();

        _.each(this._ui.ctrl_slots, function(ctrl) {
            ctrl.setSelectCallback(null);
            ctrl.setWidget(null);
        }, this);
        this._ui.ctrl_gold.setWidget(null);
        this._ui.ctrl_diamond.setWidget(null);
        this._ui = null;

        this._super();
    },

    refreshProperty: function() {
        var system = PlayerSystem.instance;
        this._ui.lbl_prop_level.setString(this._ui.lbl_prop_level._str_original.format(system.level));

        var score = system.getPlayerBattleScore();
        this._ui.lbl_prop_score.setString(this._ui.lbl_prop_score._str_original.format(score.score));
        this._ui.lbl_prop_hp.setString(this._ui.lbl_prop_hp._str_original.format(score.hp));
        this._ui.lbl_prop_mp.setString(this._ui.lbl_prop_mp._str_original.format(score.mp));
        this._ui.lbl_prop_atk.setString(this._ui.lbl_prop_atk._str_original.format(score.atk));
        this._ui.lbl_prop_def.setString(this._ui.lbl_prop_def._str_original.format(score.def));
        this._ui.lbl_prop_crit.setString(this._ui.lbl_prop_crit._str_original.format(score.crit));
        this._ui.lbl_prop_sunder.setString(this._ui.lbl_prop_sunder._str_original.format(score.sunder));

        var level_config = configdb.levelup[system.level];
        if(level_config) {
            var pre_level_config = configdb.levelup[system.level-1];

            var pre_exp = pre_level_config ? pre_level_config.exp : 0;

            var need_exp = level_config.exp - pre_exp;
            var cur_exp = system.exp - pre_exp;

            this._ui.lbl_prop_exp.setString(this._ui.lbl_prop_exp._str_original.format(cur_exp, need_exp));
        }
    },

    clearItemList: function() {
        _.each(this._ui.ctrl_items, function(ctrl) {
            ctrl.setSelectCallback(null);
        }, this);
        this._ui.ctrl_items.length = 0;
        this._ui.list_view.removeAllItems();
    },

    createItemList: function() {
        this.clearItemList();

        for(var i = this.LINE_NUMBER; i--;) {
            var line = new BagScene.ItemLine();
            this._ui.list_view.pushBackCustomItem(line);
            this._ui.ctrl_items = this._ui.ctrl_items.concat(line.getItemSlots());
        }

        _.each(this._ui.ctrl_items, function(ctrl) {
            ctrl.setSelectCallback(this.onSelectItem, this);
        }, this);
    },

    refreshItemPage: function() {
        // sort items
        var infos = _.toArray(BagSystem.instance.items).sort(function(info1, info2){
            var type1 = Math.floor(info1.id/100000);
            var type2 = Math.floor(info2.id/100000);
            if(type1 != type2) {
                return type2 - type1;
            }

            var conf1 = BagSystem.getConfig(info1.id);
            var conf2 = BagSystem.getConfig(info2.id);
            if(conf1 && conf2) {
                return conf2.sort - conf1.sort;
            }
            return 0;
        });

        _.each(this._ui.ctrl_items, function(ctrl, i) {
            var info = infos[i];
            if(info == undefined) {
                ctrl.setUid(0);
                return;
            }
            ctrl.setUid(info.uid);
        }, this);

        this.refreshSelectedItemInfo();
    },

    onSelectItem: function(item) {
        this._sel_index = _.indexOf(this._ui.ctrl_items, item);
        this.refreshSelectedItemInfo();
    },

    onSelectEquip: function(equip) {
        this._sel_index = -equip.slot;
        this.refreshSelectedItemInfo();

    },

    refreshSelectedItemInfo: function() {
        _.each(this._ui.ctrl_items, function(item, i) {
            item.setSelected(i == this._sel_index);
        }, this);
        _.each(this._ui.ctrl_slots, function(equip) {
            equip.setSelected(equip.slot == -this._sel_index);
        }, this);

        var info;
        var config;
        if(this._sel_index >= 0) {
            var item = this._ui.ctrl_items[this._sel_index];
            info = BagSystem.instance.items[item.uid];
            if(info) {
                config = BagSystem.getConfig(info.id);
            }
        }
        else {
            var equip = _.find(this._ui.ctrl_slots, function(equip) {
                return equip.slot == -this._sel_index;
            }, this);
            info = EquipSystem.instance.slots[equip.slot];
            if(info) {
                config = BagSystem.getConfig(info.id);
            }
        }

        this._ui.lbl_item_name.setVisible(false);
        this._ui.lbl_item_price.setVisible(false);
        this._ui.lbl_item_score.setVisible(false);
        this._ui.lbl_item_desc.setVisible(false);
        this._ui.lbl_score_change.setVisible(false);
        this._ui.btn_sell.setVisible(false);
        this._ui.btn_use.setVisible(false);
        this._ui.btn_strengthen.setVisible(false);

        if(config) {
            var enable;

            // name
            this._ui.lbl_item_name.setVisible(true);
            this._ui.lbl_item_name.setString(config.name || "");

            // price
            this._ui.lbl_item_price.setVisible(true);
            this._ui.lbl_item_price.setString(this._ui.lbl_item_price._str_original.format(config.price || ""));

            // desc
            this._ui.lbl_item_desc.setVisible(true);
            this._ui.lbl_item_desc.setString(config.desc || "");

            // use button
            if(config.type == undefined || config.type == ItemSystem.ItemType.Item) {
                this._ui.btn_use.setTitleText(BagSystem.getItemUseMethodName(info.id));
                this._ui.btn_use.setVisible(true);
                enable = this._sel_index >= 0;
                this._ui.btn_use.setEnabled(enable);
                this._ui.btn_use.setBright(enable);
            }

            // sell button
            this._ui.btn_sell.setVisible(true);
            if(this._sel_index >= 0) {
                enable = config.can_sale && config.price && config.price > 0;
                this._ui.btn_sell.setEnabled(enable);
                this._ui.btn_sell.setBright(enable);
            }
            else {
                this._ui.btn_sell.setEnabled(false);
                this._ui.btn_sell.setBright(false);
            }

            // strengthen button
            this._ui.btn_strengthen.setVisible(true);
            enable = config.star != undefined;
            this._ui.btn_strengthen.setEnabled(enable);
            this._ui.btn_strengthen.setBright(enable);

            // score value
            if(config.type == undefined) {
                var score = Formula.calculateBattleScore(config.hp, config.mp,
                    config.atk, config.def,
                    config.crit, config.sunder);

                // score
                this._ui.lbl_item_score.setVisible(true);
                this._ui.lbl_item_score.setString(this._ui.lbl_item_score._str_original.format(score));

                // change value
                var equip_info = EquipSystem.instance.slots[config.slot];
                if(equip_info != undefined) {
                    var equip_config = configdb.equip[equip_info.id];
                    if(equip_config != undefined) {
                        score -= Formula.calculateBattleScore(equip_config.hp, equip_config.mp,
                            equip_config.atk, equip_config.def,
                            equip_config.crit, equip_config.sunder);
                    }
                }
                if(score > 0) {
                    this._ui.lbl_score_change.setColor(cc.color(12, 255, 0)); //0cff00
                    this._ui.sp_change_up.setVisible(true);
                    this._ui.sp_change_down.setVisible(false);
                }
                else if(score < 0) {
                    score = -score;
                    this._ui.lbl_score_change.setColor(cc.color(255, 0, 0)); //ff0000
                    this._ui.sp_change_up.setVisible(false);
                    this._ui.sp_change_down.setVisible(true);
                }
                else {
                    score = "";
                    this._ui.sp_change_up.setVisible(false);
                    this._ui.sp_change_down.setVisible(false);
                }
                this._ui.lbl_score_change.setVisible(true);
                this._ui.lbl_score_change.setString(String(score));
            }
        }

    },

    clearRoleAvatar: function() {
        this._ui.node_avatar.removeAllChildren();
    },

    createRoleAvatar: function() {
        this.clearRoleAvatar();

        var config = configdb.skin[SkinSystem.instance.use_skin];
        if(config == undefined) {
            return;
        }

        var avatar = new ShowRole(config.role_id);
        this._ui.node_avatar.addChild(avatar);

        this._ui.lbl_player_name.setString(config.name);
    },

    _on_btn_change: function() {
        var win = new SelectHeroPanel();
        win.pop();

        //if(!GuideSystem.instance.getCurFunctionIsOpenWithMapId(GuideSystem.Type.shangdian)){
        //    MessageBoxOk.show("通过第一章第六关开放");
        //    return;
        //}
        //
        //var player_config = configdb.player[PlayerSystem.instance.playerId];
        //if(player_config == undefined) {
        //    return;
        //}
        //
        //var change_id;
        //var system = SkinSystem.instance;
        //if(system.use_skin == player_config.skin_id_1) {
        //    change_id = player_config.skin_id_2 || 0;
        //}
        //else {
        //    change_id = player_config.skin_id_1 || 0;
        //}
        //
        //var info = system.skins[change_id];
        //if(info == undefined) {
        //    var box = MessageBoxOkCancel.show("未购买该套装，是否购买？");
        //    box.setOkCallback(function() {
        //        this.close();
        //        //new ShopScene(ShopSystem.ShopType.Role)
        //        ui.pushScene(new ShopScene(ShopSystem.ShopType.Role))
        //    }, this);
        //}
        //else {
        //    var skins = _.reject(system.skins, function(skin) {
        //        return skin.skin_id == system.use_skin;
        //    });
        //    SkinSystem.instance.changeSkin(skins[0].skin_id);
        //}
    },

    _on_btn_close: function() {
        //this.popScene();
        this.close();
    },

    _on_btn_use: function() {
        var item = this._ui.ctrl_items[this._sel_index];
        if(item == undefined || item.uid == 0) {
            return;
        }

        var info = BagSystem.instance.items[item.uid];
        if(info == undefined) {
            return;
        }

        var type = BagSystem.getConfigType(info.id);
        if(type == BagSystem.ConfigType.Equip) {
            EquipSystem.instance.equipItem(item.uid);
        }
        else {
            ItemSystem.instance.useItem(item.uid, 1);
        }
    },

    _on_btn_chushou: function() {
        var secondConfirm = new MessageBoxOkCancel("是否出售？");
        secondConfirm.setOkCallback(function() {
            var item = this._ui.ctrl_items[this._sel_index];
            if(item && item.uid) {
                BagSystem.instance.sell(item.uid, 1);
            }
        }, this);
        secondConfirm.pop();
    },

    _on_btn_prop: function() {
        var win = new RoleProperty();
        win.pop();
    },

    _on_btn_strengthen: function() {
        var info;
        var equip_id = 0;
        var value;
        if(this._sel_index >= 0) {
            var item = this._ui.ctrl_items[this._sel_index];
            info = BagSystem.instance.items[item.uid];
            if(info) {
                equip_id = info.id;
                value = item.uid;
            }
        }
        else {
            var equip = _.find(this._ui.ctrl_slots, function(equip) {
                return equip.slot == -this._sel_index;
            }, this);
            info = EquipSystem.instance.slots[equip.slot];
            if(info) {
                equip_id = info.id;
                value = equip.slot;
            }
        }
        if(equip_id == 0) {
            MessageBoxOk.show("表粗错辣！");
            return;
        }

        var win = new StrengthenPanel(equip_id);
        win.setCloseCallback(function(w) {
            if(w.canStrengthen == true) {
                if(this._sel_index >= 0) {
                    StrengthenSystem.instance.strengthenEquipInBag(value);
                }
                else {
                    StrengthenSystem.instance.strengthenEquipOnEquip(value);
                }
            }
        }, this);
        win.pop();
    }
});


BagScene.ItemLine = ui.GuiWidgetBase.extend({
    _guiFile: "ui/beibao_ye.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();

        this._ui = {
            ctrl_items: _.reduce([
                "ProjectNode_0_0",
                "ProjectNode_0_1",
                "ProjectNode_0_2",
                "ProjectNode_0_3"
            ], function(items, name){
                var ctrl = new BagScene.ItemSlot();
                ctrl.setWidget(this.seekWidgetByName(name));
                items.push(ctrl);
                return items;
            }, [], this)
        };
    },

    onExit: function() {
        _.each(this._ui.ctrl_items, function(ctrl) {
            ctrl.setWidget(null);
        }, this);
        this._ui = null;
        this._super();
    },

    getItemSlots: function() {
        return this._ui.ctrl_items;
    }
});


BagScene.ItemSlot = ui.GuiController.extend({
    ctor: function() {
        this._super();
        this.uid = 0;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_num: this.seekWidgetByName("lbl_num"),
            img_sel: this.seekWidgetByName("img_sel"),
            btn_touch: this.seekWidgetByName("btn_bg"),
            sp_star: this.seekWidgetByName("sp_star"),
            lbl_star: this.seekWidgetByName("lbl_star")
        };
        this.setUid(this.uid);
        this.setSelected(false);
    },

    onExit: function() {
        this._ui = null;
        this._super();
    },

    setUid: function(uid) {
        this.uid = uid;
        this._ui.lbl_num.setVisible(false);
        this._ui.sp_icon.setVisible(false);
        this._ui.sp_star.setVisible(false);

        var info = BagSystem.instance.items[uid];
        if(info == undefined) {
            return;
        }

        var config = BagSystem.getConfig(info.id);
        if(config == undefined) {
            return;
        }

        // icon
        if(config.icon) {
            this._ui.sp_icon.setVisible(true);
            this._ui.sp_icon.setTexture(config.icon);
        }

        // number
        if(info.num > 1) {
            this._ui.lbl_num.setVisible(true);
            this._ui.lbl_num.setString(String(info.num));
        }

        // star
        if(config.star != undefined) {
            this._ui.sp_star.setVisible(true);
            this._ui.lbl_star.setString(String(config.star));
        }
    },

    setSelected: function(val) {
        this._ui.img_sel.setVisible(val);
        this._ui.btn_touch.setEnabled(!val);
    },

    setRaiseEffect : function () {
        var tmpStr = "res/images/code_ui/ui_";
        var vin_ani = new cc.Sprite(tmpStr + "199.png");
        //var iconNode = this.seekWidgetByName("ProjectNode_icon")
        //var iconNode = this._ui.sp_icon;
        //var pos = cc.p(iconNode.getPosition().x + iconNode.getContentSize().width/2,iconNode.getPosition().y + iconNode.getContentSize().height/2);
        //vin_ani.setPosition(pos);
        this._ui.sp_icon.addChild(vin_ani);

        var animFrames = [];
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

    _on_btn_bg: function() {
        if (this._selectCallback) {
            this._selectCallback(this);
        }
    }
});

BagScene.EquipSlot = ui.GuiController.extend({
    ctor: function(slot) {
        this._super();
        this.slot = slot;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_num: this.seekWidgetByName("lbl_num"),
            img_sel: this.seekWidgetByName("img_sel"),
            btn_touch: this.seekWidgetByName("btn_bg"),
            sp_star: this.seekWidgetByName("sp_star"),
            lbl_star: this.seekWidgetByName("lbl_star")
        };
        this._bindings = [
            notification.createBinding(notification.event.EQUIP_EQUIP_ITEM, this.refreshEquipSlot, this),
            notification.createBinding(notification.event.EQUIP_UNEQUIP_ITEM, this.refreshEquipSlot, this),
            notification.createBinding(notification.event.EQUIP_STRENGTHEN_RESULT, this.refreshEquipSlot, this)
        ];

        this._ui.lbl_num.setVisible(false);
        this.setSelected(false);

        this.refreshEquipSlot();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._ui = null;
        this._super();
    },

    refreshEquipSlot: function() {
        this._ui.sp_icon.setVisible(false);
        this._ui.sp_star.setVisible(false);

        var info = EquipSystem.instance.slots[this.slot];
        if(info == undefined) {
            return;
        }

        var config = BagSystem.getConfig(info.id);
        if(config == undefined) {
            return;
        }

        // icon
        if(config.icon) {
            this._ui.sp_icon.setVisible(true);
            this._ui.sp_icon.setTexture(config.icon);
        }

        // star
        if(config.star != undefined) {
            this._ui.sp_star.setVisible(true);
            this._ui.lbl_star.setString(String(config.star));
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

    _on_btn_bg: function() {
        LOG("touch equip slot " + this.slot);
        if (this._selectCallback) {
            this._selectCallback(this);
        }
    }
});

