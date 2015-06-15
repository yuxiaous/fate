/**
 * Created by yuxiao on 15/5/11.
 */


var ShopScene = ui.GuiSceneBase.extend({
    _guiFile: "ui/shop_scene.json",

    ctor: function() {
        this._super();
        this.shopType = ShopSystem.ShopType.Equip;
    },

    onEnter: function() {
        this._super();
        MusicManager.getInstance().playBackgroundMusic("sounds/shop.mp3");
        this._ui = {
            tab_equip: this.seekWidgetByName("btn_tab_1"),
            tab_item: this.seekWidgetByName("btn_tab_2"),
            tab_role: this.seekWidgetByName("btn_tab_3"),
            tab_charge: this.seekWidgetByName("btn_tab_4"),
            list_goods: this.seekWidgetByName("list_items"),
            lbl_gold: this.seekWidgetByName("lbl_gold_value"),
            lbl_diamond: this.seekWidgetByName("lbl_diamond_value"),
            lbl_girl_say: this.seekWidgetByName("lbl_girl_say")
        };

        this._bindings = [
            notification.createBinding(notification.event.PLAYER_INFO, this.updateCurrencyInfo, this)
        ];

        this.updateCurrencyInfo();
        this.refreshShopTabStatus();
        this.createGoodsList();
        this._on_btn_girl();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this.clearGoodsList();
        this._ui = null;
        this._super();
    },

    updateCurrencyInfo: function() {
        var system = PlayerSystem.instance;
        this._ui.lbl_gold.setString(String(system.gold));
        this._ui.lbl_diamond.setString(String(system.diamond));
    },

    clearGoodsList: function() {
        this._ui.list_goods.removeAllItems();
    },

    createGoodsList: function() {
        this.clearGoodsList();

        var shopType = this.shopType;
        _.each(configdb.shop, function(config) {
            if(config.shop == shopType) {
                var good = new ShopScene.Good(config.key);
                this._ui.list_goods.pushBackCustomItem(good);
            }
        }, this);
    },

    _on_btn_back: function() {
        this.popScene();
    },

    refreshShopTabStatus: function() {
        var type = this.shopType;
        this._ui.tab_equip.setBright(type != ShopSystem.ShopType.Equip);
        this._ui.tab_equip.setEnabled(type != ShopSystem.ShopType.Equip);
        this._ui.tab_item.setBright(type != ShopSystem.ShopType.Item);
        this._ui.tab_item.setEnabled(type != ShopSystem.ShopType.Item);
        this._ui.tab_role.setBright(type != ShopSystem.ShopType.Role);
        this._ui.tab_role.setEnabled(type != ShopSystem.ShopType.Role);
        this._ui.tab_charge.setBright(type != ShopSystem.ShopType.Charge);
        this._ui.tab_charge.setEnabled(type != ShopSystem.ShopType.Charge);
    },

    _on_btn_tab_1: function() {
        this.shopType = ShopSystem.ShopType.Equip;
        this.refreshShopTabStatus();
        this.createGoodsList();
        this._ui.list_goods.jumpToTop();
    },

    _on_btn_tab_2: function() {
        this.shopType = ShopSystem.ShopType.Item;
        this.refreshShopTabStatus();
        this.createGoodsList();
        this._ui.list_goods.jumpToTop();
    },

    _on_btn_tab_3: function() {
        this.shopType = ShopSystem.ShopType.Role;
        this.refreshShopTabStatus();
        this.createGoodsList();
        this._ui.list_goods.jumpToTop();
    },

    _on_btn_tab_4: function() {
        this.shopType = ShopSystem.ShopType.Charge;
        this.refreshShopTabStatus();
        this.createGoodsList();
        this._ui.list_goods.jumpToTop();
    },

    _on_btn_girl: function() {
        var say = _.sample([
            "这些东西都是魔术协会限量提供的，不买就乱动的话，我一定不会放过你！",
            "你说什么？想打折？这怎么可能！",
            "买东西挑挑拣拣的话，是不可能变成优秀的Master的！"
        ]);
        this._ui.lbl_girl_say.setString(say);
    }

    //scrollItemList: function(distance) {
    //    var list = this._ui.list_goods;
    //    var width = list.getInnerContainerSize().width - list.getContentSize().width;
    //    if(width > 0) {
    //        var posx = list.getInnerContainer().getPositionX();
    //        var percent = -(posx + -distance) * 100 / width;
    //
    //        if(percent < 0) percent = 0;
    //        else if(percent > 100) percent = 100;
    //
    //        list.scrollToPercentHorizontal(percent, 0.1, false);
    //    }
    //},
    //
    //_on_btn_backward: function() {
    //    this.scrollItemList(-150);
    //},
    //
    //_on_btn_forward: function() {
    //    this.scrollItemList(150);
    //}
});


ShopScene.Good = ui.GuiWidgetBase.extend({
    _guiFile: "ui/shop_item.json",

    ctor: function(id) {
        this._super();
        this._good_id = id;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            lbl_name: this.seekWidgetByName("lbl_name"),
            lbl_quality: this.seekWidgetByName("lbl_quality"),
            lbl_desc: this.seekWidgetByName("lbl_desc"),
            lbl_cost: this.seekWidgetByName("lbl_cost"),
            sp_curr: this.seekWidgetByName("Sprite_1")
        };
        this._ui.icon = new ShopScene.Good.Icon();
        this._ui.icon.setWidget(this.seekWidgetByName("ProjectNode_1"));

        var config = configdb.shop[this._good_id];
        if(config == undefined) {
            return;
        }

        if(config.buy_id) {
            this._ui.icon.setItemId(config.buy_id);
        }

        if(config.name) {
            this._ui.lbl_name.setString(config.name);
        }

        if(config.desc) {
            this._ui.lbl_desc.setString(config.desc);
        }

        if(config.pay_cost) {
            this._ui.lbl_cost.setString(String(config.pay_cost));
        }

        if(config.score) {
            this._ui.lbl_quality.setString(this._ui.lbl_quality._str_original.format(config.score));
        }

        switch (config.pay_type) {
            case ShopSystem.PayType.Gold:
                this._ui.sp_curr.setTexture("images/icon/icon_02.png");
                break;

            case ShopSystem.PayType.Diamond:
                this._ui.sp_curr.setTexture("images/icon/icon_03.png");
                break;

            default:
                this._ui.sp_curr.setVisible(false);
                break;
        }
    },

    onExit: function() {
        this._ui.icon.setWidget(null);
        this._ui = null;
        this._super();
    },

    _on_btn_buy: function() {
        var win = new MessageBoxOkCancel("是否购买？");
        win.setOkCallback(function() {
            LOG("购买商品"+this._good_id);
            ShopSystem.instance.buyGood(this._good_id, 1);
        }, this);
        win.pop();
    }
});

ShopScene.Good.Icon = ui.GuiController.extend({
    ctor: function(id) {
        this._super();
        this.id = id || 0;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_num: this.seekWidgetByName("lbl_num"),
            img_sel: this.seekWidgetByName("img_sel")
        };

        this._ui.img_sel.setVisible(false);
        this._ui.lbl_num.setVisible(false);

        this.refreshIcon();
    },

    onExit: function() {
        this._ui = null;
        this._super();
    },

    setItemId: function(id) {
        this.id = id;
        this.refreshIcon();
    },

    refreshIcon: function() {
        if(this.id == 0) {
            return;
        }

        var config = BagSystem.getConfig(this.id);
        if(config == undefined) {
            return;
        }

        this._ui.sp_icon.setTexture(config.icon);
    },

    _on_btn_bg: function() {

    }
});

