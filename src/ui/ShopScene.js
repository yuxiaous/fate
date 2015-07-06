/**
 * Created by yuxiao on 15/5/11.
 */


var ShopScene = ui.GuiSceneBase.extend({
    _guiFile: "ui/shop_scene.json",

    ctor: function(shop_type) {
        this._super();
        this.shopType = shop_type || ShopSystem.ShopType.Item;
    },

    onEnter: function() {
        this._super();
        MusicManager.getInstance().playBackgroundMusic("sounds/shop.mp3");
        this._ui = {
            ctrl_gold: (function() {
                var ctrl = new ResourcePanel(ResourcePanel.Type.Gold);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_1"));
                ctrl.showAddButton(false);
                return ctrl;
            }.bind(this) ()),
            ctrl_diamond: (function() {
                var ctrl = new ResourcePanel(ResourcePanel.Type.Diamond);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_2"));
                ctrl.showAddButton(false);
                //appstore 显示
                ctrl.setVisible(util.getChannelId() == GameChannel.AppStore);
                return ctrl;
            }.bind(this) ()),


            tab_item: this.seekWidgetByName("btn_tab_1"),
            tab_equip: this.seekWidgetByName("btn_tab_2"),
            tab_role: this.seekWidgetByName("btn_tab_3"),
            tab_charge: this.seekWidgetByName("btn_tab_4"),
            list_goods: this.seekWidgetByName("list_items"),
            lbl_girl_say: this.seekWidgetByName("lbl_girl_say")
        };

        this._bindings = [
            notification.createBinding(notification.event.SHOP_BUY_RESULT, function (event,info) {
                if(info && info.good_id == 18000){
                    this.refreshShopTabStatus();
                    this.createGoodsList();
                    this._ui.list_goods.jumpToTop();
                }
            }.bind(this))
        ];

        this.refreshShopTabStatus();
        this.createGoodsList();
        this._on_btn_girl();

        LOG("CUR GUIDE TYPE = " + GuideSystem.instance._curGuideType);
        if(GuideSystem.instance._curGuideType == GuideSystem.Type.shangdian){
            this.shopType = ShopSystem.ShopType.Equip;
            this.refreshShopTabStatus();
            this.createGoodsList();
            this._ui.list_goods.jumpToTop();
        }
        else if(GuideSystem.instance._curGuideType == GuideSystem.Type.xueping){
            this.shopType = ShopSystem.ShopType.Item;
            this.refreshShopTabStatus();
            this.createGoodsList();
            this._ui.list_goods.jumpToTop();
        }
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this.clearGoodsList();
        this._ui = null;
        this._super();
    },

    clearGoodsList: function() {
        this._ui.list_goods.removeAllItems();
    },

    createGoodsList: function() {
        this.clearGoodsList();

        var shopType = this.shopType;
        _.each(configdb.shop, function(config) {
            if(config.shop == shopType && config.platform_id == 1) {
                var needDisplay = false;
                if(config.pay_cost >0){
                   needDisplay = true;
                }

                //LOG("xueping = " + GuideSystem.instance._curGuideType);

                if(GuideSystem.instance._curGuideType == GuideSystem.Type.xueping && config.pay_cost == 0){
                    needDisplay = true;
                }
                if(needDisplay){
                    var good = new ShopScene.Good(config.key);
                    this._ui.list_goods.pushBackCustomItem(good);
                }

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
        this.shopType = ShopSystem.ShopType.Item;
        this.refreshShopTabStatus();
        this.createGoodsList();
        this._ui.list_goods.jumpToTop();
    },

    _on_btn_tab_2: function() {
        this.shopType = ShopSystem.ShopType.Equip;
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
    },

    _on_keyboard_back: function() {
        this.popScene();
    }
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
            sp_curr: this.seekWidgetByName("Sprite_1"),
            sale_panel : this.seekWidgetByName("sale_panel"),
            lbl_sale : this.seekWidgetByName("lbl_sale_value")
        };
        this._ui.icon = new IconWidget();
        this._ui.icon.setWidget(this.seekWidgetByName("ProjectNode_1"));

        var config = configdb.shop[this._good_id];
        if(config == undefined) {
            return;
        }

        if(config.on_sale <= 0){
            this._ui.sale_panel.setVisible(false);
        }
        else{
            this._ui.sale_panel.setVisible(true);
            this._ui.lbl_sale.setString(String(config.on_sale));
        }

        if(config.buy_type == ShopSystem.GoodType.Equip) {
            this._ui.icon.setIcon(config.buy_id, IconWidget.Type.Equip, config.buy_count);
        }
        else if(config.buy_type == ShopSystem.GoodType.Skin) {
            this._ui.icon.setIcon(config.buy_id, IconWidget.Type.Skin, config.buy_count);
        }
        else if(config.buy_id) {
            this._ui.icon.setIcon(config.buy_id, IconWidget.Type.Item, config.buy_count);
        }

        if(config.name) {
            this._ui.lbl_name.setString(config.name);
        }

        if(config.desc) {
            this._ui.lbl_desc.setString(config.desc);
        }

        if(config.pay_cost != undefined) {
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

            case ShopSystem.PayType.RMB:
                this._ui.sp_curr.setTexture("images/icon/icon_04.png");
                this._ui.sp_curr.setVisible(false);

                var str = this._ui.lbl_cost.getString();
                this._ui.lbl_cost.setString(str + " 元");
                break;

            default:
                this._ui.sp_curr.setVisible(false);
                break;
        }



        LOG("gooid = " + this._good_id);
        if(GuideSystem.instance._curGuideType == GuideSystem.Type.shangdian && this._good_id ==12103){
            GuideSystem.AddGuidePanel(this.seekWidgetByName("btn_buy"),113);
        }

        if(GuideSystem.instance._curGuideType == GuideSystem.Type.xueping && this._good_id == 18000){
            GuideSystem.AddGuidePanel(this.seekWidgetByName("btn_buy"),122);
        }

    },

    onExit: function() {
        this._ui.icon.setWidget(null);
        this._ui = null;
        this._super();
    },

    _on_btn_buy: function() {
        //var win = new MessageBoxOkCancel("是否购买？");
        //win.setOkCallback(function() {
        //    LOG("购买商品"+this._good_id);
        //    ShopSystem.instance.buyGood(this._good_id, 1);
        //}, this);
        //win.pop();

        //var confi = configdb.shop[this._good_id]
        //if(this._good_id == 18000){
        //
        //}

        ShopSystem.instance.buyGood(this._good_id, 1);
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
            img_sel: this.seekWidgetByName("img_sel"),
            btn_bg : this.seekWidgetByName("btn_bg")
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

