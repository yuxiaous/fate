/**
 * Created by yuxiao on 15/5/7.
 */


var BagScene = ui.GuiSceneBase.extend({
    _guiFile: "ui/beibao.json",

    PAGE_NUMBER: 3,

    ctor: function() {
        this._super();
        this._sel_index = 0;
        this._avatar_id = 1001;
    },

    onEnter: function() {
        this._super();
        this._page_view = this.seekWidgetByName("page_items");
        this._lbl_page_num = this.seekWidgetByName("lbl_fanye");
        this._lbl_item_name = this.seekWidgetByName("lbl_item_name");
        this._lbl_item_desc = this.seekWidgetByName("lbl_item_desc");
        this._lbl_item_price = this.seekWidgetByName("lbl_item_price");
        this._btn_use = this.seekWidgetByName("btn_use");
        this._btn_sell = this.seekWidgetByName("btn_chushou");
        this._slot_equips = [];
        _.each([
            [EquipSystem.EquipSlotType.Weapon, "ProjectNode_1"],
            [EquipSystem.EquipSlotType.Coat, "ProjectNode_2"],
            [EquipSystem.EquipSlotType.Head, "ProjectNode_3"],
            [EquipSystem.EquipSlotType.Leg, "ProjectNode_4"],
            [EquipSystem.EquipSlotType.Shoe, "ProjectNode_5"],
            [EquipSystem.EquipSlotType.Amulet, "ProjectNode_6"]
        ], function(data) {
            var slot = data[0];
            var widget = this.seekWidgetByName(data[1]);
            var ctrl = new BagScene.EquipSlot(slot);
            ctrl.setWidget(widget);
            this._slot_equips.push(ctrl);
        }, this);
        this._role = {
            lbl_score: this.seekWidgetByName("lbl_zhanli"),
            lbl_hp: this.seekWidgetByName("lbl_hp"),
            lbl_mp: this.seekWidgetByName("lbl_mp"),
            lbl_atk: this.seekWidgetByName("lbl_atk"),
            lbl_def: this.seekWidgetByName("lbl_fang"),
            lbl_crit: this.seekWidgetByName("lbl_bao"),
            lbl_sunder: this.seekWidgetByName("lbl_po"),
            lbl_level: this.seekWidgetByName("lbl_level"),
            loading_exp: this.seekWidgetByName("loading_exp"),
            lbl_exp: this.seekWidgetByName("lbl_exp"),
            avatar: this.seekWidgetByName("Node_avatar"),
            lbl_name: this.seekWidgetByName("lbl_player_name")
        };

        this._bindings = [
            notification.createBinding(notification.event.ITEM_INFO, this.refreshItemPage, this),
            notification.createBinding(notification.event.EQUIP_EQUIP_ITEM, this.refreshRoleInfo, this),
            notification.createBinding(notification.event.EQUIP_UNEQUIP_ITEM, this.refreshRoleInfo, this)
        ];

        this._page_view.addEventListener(this.refreshPageIndex, this);

        this.createItemPage();
        this.createRoleAvatar();
        this.refreshItemPage();
        this.refreshPageIndex();
        this.refreshRoleInfo();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this.clearItemPage();
        this.clearRoleAvatar();
        _.each(this._slot_equips, function(ctrl) {
            ctrl.setWidget(null);
        }, this);
        this._slot_equips = null;
        this._page_view = null;
        this._lbl_page_num = null;
        this._lbl_item_name = null;
        this._lbl_item_desc = null;
        this._lbl_item_price = null;
        this._btn_use = null;
        this._btn_sell = null;
        this._role = null;
        this._super();
    },

    clearItemPage: function() {
        _.each(this.items, function(item) {
            item.setSelectCallback(null);
        }, this);
        this.items = null;
        this._page_view.removeAllPages();
    },

    createItemPage: function() {
        this.clearItemPage();

        this.items = [];
        for(var i = this.PAGE_NUMBER; i--;) {
            var page = new BagScene.ItemPage();
            this._page_view.addPage(page);

            _.each(page.items, function(item) {
                item.setSelectCallback(this.onSelectItem, this);
                this.items.push(item);
            }, this);
        }
    },

    refreshItemPage: function() {
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

        _.each(this.items, function(item, i) {
            var info = infos[i];
            if(info == undefined) {
                item.setUid(0);
                return;
            }
            item.setUid(info.uid);
        }, this);

        this.refreshSelectedItemInfo();
    },

    refreshPageIndex: function() {
        var idx = this._page_view.getCurPageIndex();
        var max = this.PAGE_NUMBER;
        this._lbl_page_num.setString(this._lbl_page_num._str_original.format(idx+1, max));
    },

    _on_btn_zuo: function() {
        var idx = this._page_view.getCurPageIndex();
        if(idx > 0) {
            this._page_view.scrollToPage(idx-1);
        }
    },

    _on_btn_you: function() {
        var idx = this._page_view.getCurPageIndex();
        var max = this.PAGE_NUMBER;
        if(idx < max-1) {
            this._page_view.scrollToPage(idx+1);
        }
    },

    onSelectItem: function(item) {
        this._sel_index = _.indexOf(this.items, item);
        this.refreshSelectedItemInfo();
    },

    refreshSelectedItemInfo: function() {
        _.each(this.items, function(item, i) {
            item.setSelected(i == this._sel_index);
        }, this);

        var item = this.items[this._sel_index];
        var info = BagSystem.instance.items[item.uid];
        if(info) {
            var config = BagSystem.getConfig(info.id);
            if(config) {
                this._lbl_item_name.setString(config.name || "");
                this._lbl_item_desc.setString(config.desc || "");

                // use
                this._btn_use.setVisible(true);
                this._btn_use.setTitleText(BagSystem.getItemUseMethodName(info.id));

                // sell
                if(config.price != undefined && config.price > 0) {
                    this._btn_sell.setVisible(true);
                    this._lbl_item_price.setString(String(config.price));
                }
                else {
                    this._btn_sell.setVisible(false);
                    this._lbl_item_price.setVisible(false);
                }
                return;
            }
        }

        this._lbl_item_name.setString("空");
        this._lbl_item_desc.setString("");
        this._lbl_item_price.setVisible(false);
        this._btn_use.setVisible(false);
        this._btn_sell.setVisible(false);
    },

    refreshRoleInfo: function(event_,attr_) {
        var system = PlayerSystem.instance;

        var score = system.getPlayerBattleScore();
        this._role.lbl_hp.setString(this._role.lbl_hp._str_original.format(String(score.hp)));
        this._role.lbl_mp.setString(this._role.lbl_mp._str_original.format(String(score.mp)));
        this._role.lbl_atk.setString(this._role.lbl_atk._str_original.format(String(score.atk)));
        this._role.lbl_def.setString(this._role.lbl_def._str_original.format(String(score.def)));
        this._role.lbl_crit.setString(this._role.lbl_crit._str_original.format(String(score.crit)));
        this._role.lbl_sunder.setString(this._role.lbl_sunder._str_original.format(String(score.sunder)));
        this._role.lbl_score.setString(this._role.lbl_score._str_original.format(String(score.score)));
        if(attr_ && attr_.isRefresh){
            var tmpValue = score.score - this._role.lbl_score.lastValue;

            if(tmpValue == 0){
                return;
            }

            var tmpLblScore = this._role.lbl_score.getParent();
            var tmpLabel = cc.LabelTTF.create("");

            var newString = String(tmpValue)
            var moveV = 30
            if(tmpValue > 0){
                tmpLabel.setColor(cc.color(10,200,10));
                newString = "+" + newString
            }
            else{
                tmpLabel.setColor(cc.color(200,10,10));
                moveV *= -1;
            }
            tmpLabel.setString(newString);
            tmpLabel.setFontSize(25);
            var tmpPos = cc.p(this._role.lbl_score.getPosition().x + this._role.lbl_score.getContentSize().width,this._role.lbl_score.getPosition().y);
            tmpLabel.setPosition(tmpPos);


            tmpLblScore.addChild(tmpLabel);

            tmpLabel.runAction(cc.Sequence.create(
                cc.MoveBy.create(0.6,cc.p(0,moveV)),
                cc.CallFunc.create(function () {
                    tmpLabel.removeFromParent();
                })
            ));
        }
        this._role.lbl_score.lastValue = score.score;

        var exp = system.getPlayerExperience();
        this._role.lbl_level.setString(this._role.lbl_level._str_original.format(system.level));
        this._role.lbl_exp.setString(this._role.lbl_exp._str_original.format(exp.exp, exp.need));
        this._role.loading_exp.setPercent(100 * exp.exp / exp.need);
    },

    clearRoleAvatar: function() {
        this._role.avatar.removeAllChildren();
    },

    createRoleAvatar: function() {
        this.clearRoleAvatar();

        var avatar = new ShowRole(this._avatar_id);
        this._role.avatar.addChild(avatar);

        if(this._avatar_id == 1001) {
            this._role.lbl_name.setString("Saber");
        }
        else if(this._avatar_id == 1101) {
            this._role.lbl_name.setString("Nero");
        }
    },

    _on_btn_huanyi: function() {
        if(this._avatar_id == 1001) {
            this._avatar_id = 1101;
        }
        else {
            this._avatar_id = 1001;
        }

        this.createRoleAvatar();
    },

    _on_btn_biaoqian_guanbi: function() {
        this.popScene();
    },

    _on_btn_chushou: function() {
        var item = this.items[this._sel_index];
        if(item && item.uid) {
            BagSystem.instance.sell(item.uid, 1);
        }
    },

    _on_btn_use: function() {
        var item = this.items[this._sel_index];
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
    }
});


BagScene.ItemPage = ui.GuiWidgetBase.extend({
    _guiFile: "ui/beibao_ye.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();

        this.items = [];
        _.each([
            "ProjectNode_0_0", "ProjectNode_0_1", "ProjectNode_0_2", "ProjectNode_0_3",
            "ProjectNode_1_0", "ProjectNode_1_1", "ProjectNode_1_2", "ProjectNode_1_3",
            "ProjectNode_2_0", "ProjectNode_2_1", "ProjectNode_2_2", "ProjectNode_2_3"
        ], function(name) {
            var widget = this.seekWidgetByName(name);
            var item = new BagScene.Item();
            item.setWidget(widget);
            this.items.push(item);
        }, this);
    },

    onExit: function() {
        _.each(this.items, function(item) {
            item.setWidget(null);
        }, this);
        this.items = null;
        this._super();
    }
});


BagScene.Item = ui.GuiController.extend({
    ctor: function() {
        this._super();
        this.uid = 0;
    },

    onEnter: function() {
        this._super();
        this._img_sel = this.seekWidgetByName("img_enter");
        this._btn_sel = this.seekWidgetByName("btn_sel");
        this._img_icon = this.seekWidgetByName("img_icon");
        this._lbl_num = this.seekWidgetByName("lbl_num");

        this.setUid(0);
    },

    onExit: function() {
        this._img_icon = null;
        this._img_sel = null;
        this._btn_sel = null;
        this._lbl_num = null;
        this._super();
        this._selectCallback = null;
    },

    setUid: function(uid) {
        this.uid = uid;
        this._lbl_num.setVisible(false);
        this._img_icon.loadTexture("images/ui/ui_14.png");

        var info = BagSystem.instance.items[uid];
        if(info == undefined) {
            return;
        }

        var config = BagSystem.getConfig(info.id);
        if(config && config.icon) {
            this._img_icon.loadTexture(config.icon);
        }

        if(info.num > 1) {
            this._lbl_num.setVisible(true);
            this._lbl_num.setString(String(info.num));
        }
    },

    setSelected: function(val) {
        this._img_sel.setVisible(val);
        this._btn_sel.setEnabled(!val);
    },

    setSelectCallback: function (selector, target) {
        if(target === undefined)
            this._selectCallback = selector;
        else
            this._selectCallback = selector.bind(target);
    },

    _on_btn_sel: function() {
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
        this._img_sel = this.seekWidgetByName("img_enter");
        this._btn_sel = this.seekWidgetByName("btn_sel");
        this._img_icon = this.seekWidgetByName("img_icon");
        this._lbl_num = this.seekWidgetByName("lbl_num");

        this._bindings = [
            notification.createBinding(notification.event.EQUIP_EQUIP_ITEM, this.refreshEquipSlot, this),
            notification.createBinding(notification.event.EQUIP_UNEQUIP_ITEM, this.refreshEquipSlot, this)
        ];

        this._lbl_num.setVisible(false);
        this._img_sel.setVisible(false);
        this._btn_sel.setEnabled(false);

        this.refreshEquipSlot();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._img_icon = null;
        this._img_sel = null;
        this._btn_sel = null;
        this._lbl_num = null;
        this._super();
    },

    refreshEquipSlot: function() {
        var info = EquipSystem.instance.slots[this.slot];
        if(info == undefined) {
            return;
        }

        var config = BagSystem.getConfig(info.id);
        if(config && config.icon) {
            this._img_icon.loadTexture(config.icon);
        }
        else {
            this._img_icon.loadTexture("images/ui/ui_14.png");
        }
    }
});

