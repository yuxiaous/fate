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
                slots.push(ctrl);
                return slots;
            }, [], this),

            list_view: this.seekWidgetByName("list_items"),
            ctrl_items: [],
            ctrl_gold: (function() {
                var ctrl = new BagScene.Resource(BagScene.Resource.Type.Gold);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_7"));
                return ctrl;
            }.bind(this) ()),
            ctrl_diamond: (function() {
                var ctrl = new BagScene.Resource(BagScene.Resource.Type.Diamond);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_8"));
                return ctrl;
            }.bind(this) ()),
            lbl_item_name: this.seekWidgetByName("lbl_item_name"),
            lbl_item_price: this.seekWidgetByName("lbl_item_price"),
            lbl_item_score: this.seekWidgetByName("lbl_item_score"),
            lbl_item_desc: this.seekWidgetByName("lbl_item_desc"),
            btn_use: this.seekWidgetByName("btn_use"),
            btn_sell: this.seekWidgetByName("btn_chushou")
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
            notification.createBinding(notification.event.SKIN_CHANGE_RESULT, this.createRoleAvatar, this)
        ];

        this.createItemList();
        this.createRoleAvatar();
        this.refreshItemPage();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this.clearItemList();
        this.clearRoleAvatar();

        _.each(this._ui.crtl_slots, function(ctrl) {
            ctrl.setWidget(null);
        }, this);
        this._ui.ctrl_gold.setWidget(null);
        this._ui.ctrl_diamond.setWidget(null);
        this._ui = null;

        this._super();
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

    refreshSelectedItemInfo: function() {
        _.each(this._ui.ctrl_items, function(item, i) {
            item.setSelected(i == this._sel_index);
        }, this);

        var item = this._ui.ctrl_items[this._sel_index];
        var info = BagSystem.instance.items[item.uid];
        if(info) {
            var config = BagSystem.getConfig(info.id);
            if(config) {
                // name
                this._ui.lbl_item_name.setString(config.name || "");

                // price
                this._ui.lbl_item_price.setString(this._ui.lbl_item_price._str_original.format(config.price || ""));

                // score
                if(config.sort) {
                    this._ui.lbl_item_score.setString(this._ui.lbl_item_score._str_original.format(config.sort));
                }

                // desc
                this._ui.lbl_item_desc.setString(config.desc || "");

                // use
                if(config.type) {
                    if(config.type == ItemSystem.ItemType.Item) {
                        this._ui.btn_use.setVisible(true);
                        this._ui.btn_use.setTitleText(BagSystem.getItemUseMethodName(info.id));
                    }
                    else {
                        this._ui.btn_use.setVisible(false);
                    }
                }
                else {
                    this._ui.btn_use.setVisible(true);
                    this._ui.btn_use.setTitleText(BagSystem.getItemUseMethodName(info.id));
                }

                // sell
                var enable = config.can_sale && config.price && config.price > 0;
                this._ui.btn_sell.setEnabled(enable);
                this._ui.btn_sell.setBright(enable);
                return;
            }
        }

        this._ui.lbl_item_name.setString("");
        this._ui.lbl_item_price.setString("");
        this._ui.lbl_item_score.setString("");
        this._ui.lbl_item_desc.setString("");
        this._ui.btn_use.setVisible(false);
        this._ui.btn_sell.setEnabled(false);
        this._ui.btn_sell.setBright(false);
    },

    //refreshRoleInfo: function(event_,attr_) {
    //    var system = PlayerSystem.instance;
    //
    //    var score = system.getPlayerBattleScore();
    //    this._role.lbl_hp.setString(this._role.lbl_hp._str_original.format(String(score.hp)));
    //    this._role.lbl_mp.setString(this._role.lbl_mp._str_original.format(String(score.mp)));
    //    this._role.lbl_atk.setString(this._role.lbl_atk._str_original.format(String(score.atk)));
    //    this._role.lbl_def.setString(this._role.lbl_def._str_original.format(String(score.def)));
    //    this._role.lbl_crit.setString(this._role.lbl_crit._str_original.format(String(score.crit)));
    //    this._role.lbl_sunder.setString(this._role.lbl_sunder._str_original.format(String(score.sunder)));
    //    this._role.lbl_score.setString(this._role.lbl_score._str_original.format(String(score.score)));
    //    if(attr_ && attr_.isRefresh){
    //        var tmpValue = score.score - this._role.lbl_score.lastValue;
    //
    //        if(tmpValue == 0){
    //            return;
    //        }
    //
    //        var tmpLblScore = this._role.lbl_score.getParent();
    //        var tmpLabel = cc.LabelTTF.create("");
    //
    //        var newString = String(tmpValue)
    //        var moveV = 30
    //        if(tmpValue > 0){
    //            tmpLabel.setColor(cc.color(10,200,10));
    //            newString = "+" + newString
    //        }
    //        else{
    //            tmpLabel.setColor(cc.color(200,10,10));
    //            moveV *= -1;
    //        }
    //        tmpLabel.setString(newString);
    //        tmpLabel.setFontSize(25);
    //        var tmpPos = cc.p(this._role.lbl_score.getPosition().x + this._role.lbl_score.getContentSize().width,this._role.lbl_score.getPosition().y);
    //        tmpLabel.setPosition(tmpPos);
    //
    //
    //        tmpLblScore.addChild(tmpLabel);
    //
    //        tmpLabel.runAction(cc.Sequence.create(
    //            cc.MoveBy.create(0.6,cc.p(0,moveV)),
    //            cc.CallFunc.create(function () {
    //                tmpLabel.removeFromParent();
    //            })
    //        ));
    //    }
    //    this._role.lbl_score.lastValue = score.score;
    //
    //    var exp = system.getPlayerExperience();
    //    this._role.lbl_level.setString(this._role.lbl_level._str_original.format(system.level));
    //    this._role.lbl_exp.setString(this._role.lbl_exp._str_original.format(exp.exp, exp.need));
    //    this._role.loading_exp.setPercent(100 * exp.exp / exp.need);
    //},

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
        var player_config = configdb.player[PlayerSystem.instance.playerId];
        if(player_config == undefined) {
            return;
        }

        var change_id;
        var system = SkinSystem.instance;
        if(system.use_skin == player_config.skin_id_1) {
            change_id = player_config.skin_id_2 || 0;
        }
        else {
            change_id = player_config.skin_id_1 || 0;
        }

        var info = system.skins[change_id];
        if(info == undefined) {
            var box = MessageBoxOkCancel.show("未购买该套装，是否购买？");
            box.setOkCallback(function() {
                this.close();
                //new ShopScene(ShopSystem.ShopType.Role)
                ui.pushScene(new ShopScene(ShopSystem.ShopType.Role))
            }, this);
        }
        else {
            var skins = _.reject(system.skins, function(skin) {
                return skin.skin_id == system.use_skin;
            });
            SkinSystem.instance.changeSkin(skins[0].skin_id);
        }
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
        var item = this._ui.ctrl_items[this._sel_index];
        if(item && item.uid) {
            BagSystem.instance.sell(item.uid, 1);
        }
    },

    _on_btn_prop: function() {
        var win = new RoleProperty();
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
            btn_touch: this.seekWidgetByName("btn_bg")
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
    },

    setSelected: function(val) {
        this._ui.img_sel.setVisible(val);
        this._ui.btn_touch.setEnabled(!val);
    },

    setRaiseEffect : function () {
        var tmpStr = "res/images/ui/ui_";
        var vin_ani = new cc.Sprite(tmpStr + "199.png");
        //var iconNode = this.seekWidgetByName("ProjectNode_icon")
        //var iconNode = this._ui.sp_icon;
        //var pos = cc.p(iconNode.getPosition().x + iconNode.getContentSize().width/2,iconNode.getPosition().y + iconNode.getContentSize().height/2);
        //vin_ani.setPosition(pos);
        this._ui.sp_icon.addChild(vin_ani);

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
            img_sel: this.seekWidgetByName("img_sel")
        };
        this._bindings = [
            notification.createBinding(notification.event.EQUIP_EQUIP_ITEM, this.refreshEquipSlot, this),
            notification.createBinding(notification.event.EQUIP_UNEQUIP_ITEM, this.refreshEquipSlot, this)
        ];

        this._ui.lbl_num.setVisible(false);
        this._ui.img_sel.setVisible(false);

        this.refreshEquipSlot();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._ui = null;
        this._super();
    },

    refreshEquipSlot: function() {
        this._ui.sp_icon.setVisible(false);

        var info = EquipSystem.instance.slots[this.slot];
        if(info == undefined) {
            return;
        }

        var config = BagSystem.getConfig(info.id);
        if(config == undefined) {
            return;
        }

        if(config.icon) {
            this._ui.sp_icon.setVisible(true);
            this._ui.sp_icon.setTexture(config.icon);
        }
    },

    _on_btn_bg: function() {
        LOG("touch equip slot " + this.slot);
    }
});

BagScene.Resource = ui.GuiController.extend({
    ctor: function(type) {
        this._super();
        this.type = type;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            btn_add: this.seekWidgetByName("btn_add"),
            lbl_value: this.seekWidgetByName("lbl_value")
        };
        this._bindings = [
            notification.createBinding(notification.event.PLAYER_INFO, this.refreshValue, this)
        ];

        this._ui.sp_icon.setVisible(false);
        this._ui.btn_add.setVisible(false);

        this.refreshValue();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._ui = null;
        this._super();
    },

    refreshValue: function() {
        var system = PlayerSystem.instance;

        var value = 0;
        switch (this.type) {
            case BagScene.Resource.Type.Action:
                value = system.action;
                break;
            case BagScene.Resource.Type.Gold:
                value = system.gold;
                break;
            case BagScene.Resource.Type.Diamond:
                value = system.diamond;
                break;
        }
        this._ui.lbl_value.setString(String(value));
    },

    _on_btn_add: function() {
        switch (this.type) {
            case BagScene.Resource.Type.Action:
                LOG("add action");
                GmSystem.instance.sendCommand("ar 3 10");
                break;
            case BagScene.Resource.Type.Gold:
                LOG("add gold");
                GmSystem.instance.sendCommand("ar 1 100");
                break;
            case BagScene.Resource.Type.Diamond:
                LOG("add diamond");
                GmSystem.instance.sendCommand("ar 2 100");
                break;
        }
    }
});
BagScene.Resource.Type = {
    Action: 1,
    Gold: 2,
    Diamond: 3
};

