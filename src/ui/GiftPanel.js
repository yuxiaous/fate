

var GiftPanel = ui.GuiController.extend({
    ctor: function() {
        this._super();

    },

    onEnter: function() {
        this._super();

        this._ui = {
        };

        this._ui = {
            btn_1 : this.seekWidgetByName("btn_1"),
            btn_2 : this.seekWidgetByName("btn_2"),
            btn_3 : this.seekWidgetByName("btn_3"),
            btn_4 : this.seekWidgetByName("btn_4"),
            lbl_time: this.seekWidgetByName("lbl_time")
        };

        this._bindings =[
            notification.createBinding(notification.event.REFRESH_GIFT_INFO, this.refreshGiftNodeDisplay, this)
        ];

        this.addBtnEffect(this._ui.btn_1);
        UiEffect.buttonBBB(this._ui.btn_2);
        this.addBtnEffect(this._ui.btn_3);
        this.addBtnEffect(this._ui.btn_4);

        // gift time
        this.refreshGiftTime();
        cc.director.getScheduler().schedule(function () {
            this.refreshGiftTime();
        }, this, 1.0, cc.REPEAT_FOREVER, 0, false, "refresh_label");


        this.refreshGiftNodeDisplay();

        GiftSystem.instance.getGiftItemTime();
    },

    addBtnEffect : function (btn_) {
        var tmpStr = "res/images/code_ui/ui_";
        var vin_ani = new cc.Sprite(tmpStr + "286.png");
        //var iconNode = this.seekWidgetByName("ProjectNode_icon")
        //var pos = cc.p(iconNode.getPosition().x + iconNode.getContentSize().width/2,iconNode.getPosition().y + iconNode.getContentSize().height/2);
        var pos = cc.p(0,0);
        vin_ani.setPosition(pos);
        vin_ani.setAnchorPoint(cc.p(0,0));
        btn_.addChild(vin_ani);

        var animFrames = []
        for(var i = 1; i <= 5; i++){
            var strName = tmpStr + (286+i) + ".png";
            var size = cc.Sprite(strName).getContentSize();
            var frame = cc.SpriteFrame.create(strName,cc.rect(0,0,size.width,size.height));
            animFrames.push(frame);
        }
        var animation = new cc.Animation(animFrames,0.2,1);
        var animationAction = new cc.Animate(animation);
        vin_ani.runAction(cc.RepeatForever.create(animationAction));
    },

    refreshGiftNodeDisplay : function () {
        _.each([this._ui.btn_1,
            this._ui.btn_2,
            this._ui.btn_3,
            this._ui.btn_4], function (btn_,idx_) {
            var giftData = GiftSystem.instance._giftData;
            var giftType = 0;
            switch (idx_){
                case 0 :
                    giftType = GiftSystem.GiftType.Vip;
                    break;
                case 1 :
                    giftType = GiftSystem.GiftType.ZhiZun;
                    break;
                case 2 :
                    giftType = GiftSystem.GiftType.ZhuangBei;
                    break;
                case 3 :
                    giftType = GiftSystem.GiftType.WuQi;
                    break;
            }

            var tmpGiftData = null;
            _.each(giftData, function (GD_) {
                if(GD_.giftType == giftType){
                    tmpGiftData = GD_;
                }
            })
            if(tmpGiftData.buy_num > 0){
                btn_.setVisible(false);
            }
            else{
                btn_.setVisible(true);
            }

            if(tmpGiftData.giftType == GiftSystem.GiftType.ZhiZun || tmpGiftData.giftType == GiftSystem.GiftType.Vip){
                btn_.setVisible(true);
            }
        },this);
    },
    
    getGiftNodeBuyCount : function (giftType) {
        var giftData = GiftSystem.instance._giftData;
        var tmpGiftData = null;
        _.each(giftData, function (GD_) {
            if(GD_.giftType == giftType){
                tmpGiftData = GD_;
            }
        })
        return tmpGiftData.buy_num;
    },

    onExit: function() {

        cc.director.getScheduler().unschedule("refresh_label",this);
        notification.removeBinding(this._bindings);
        this._ui = null;
        this._super();
    },

    refreshGiftTime: function() {
        var tmpTime = GiftSystem.instance.getGiftCountTime(GiftSystem.GiftType.ZhiZun);
        var changeStr = GiftSystem.instance.changeStringToTimeStyle(tmpTime);
        this._ui.lbl_time.setString(String(changeStr));
    },

    _on_btn_1: function() {
        if(this.getGiftNodeBuyCount(GiftSystem.GiftType.Vip) > 0){
            var getPanel = new VipGetDetail();
            getPanel.pop();
            UiEffect.iconOpenEffect(getPanel.seekWidgetByName("gift_panel"));
        }
        else{
            var buy_panel = new GiftDetailVip();
            buy_panel.pop();
        }
    },

    _on_btn_2: function() {
        var buy_panel = new GiftDetailZhiZun();
        buy_panel.pop();
    },

    _on_btn_3: function() {
        var buy_panel = new GiftDetailSuit();
        buy_panel.pop();
    },

    _on_btn_4: function() {
        var buy_panel = new GiftDetailWeapon();
        buy_panel.pop();
    }
});


var GiftDetailBase = ui.GuiWindowBase.extend({
    _guiFile : null,
    _shop_id: 0,

    ctor: function(pause_game) {
        this._super();
        this._pause_game = pause_game;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            lbl_price_rmb: this.seekWidgetByName("lbl_price"),
            lbl_price_diamond: this.seekWidgetByName("lbl_price_0"),
            panel_gift: this.seekWidgetByName("gift_panel")
        };

        var channel_id = util.getChannelId();
        switch (channel_id) {
            case GameChannel.Telecom:
                this._ui.lbl_price_rmb.setVisible(false);
                this._ui.lbl_price_diamond.setVisible(false);
                this._ui.lbl_price = null;
                break;
            case GameChannel.AppStore:
                this._ui.lbl_price_rmb.setVisible(false);
                this._ui.lbl_price_diamond.setVisible(true);
                this._ui.lbl_price = this._ui.lbl_price_diamond;
                break;
            default :
                this._ui.lbl_price_rmb.setVisible(true);
                this._ui.lbl_price_diamond.setVisible(false);
                this._ui.lbl_price = this._ui.lbl_price_rmb;
                break;
        }

        if(this._ui.lbl_price && this._shop_id != undefined) {
            var config = ShopSystem.getConfig(this._shop_id);
            if(config) {
                this._ui.lbl_price.setString(this._ui.lbl_price._str_original.format(config.pay_cost));
            }
        }

        if(this._pause_game) {
            notification.emit(notification.event.GAME_PAUSE);
        }
    },

    onExit: function() {
        if(this._pause_game) {
            notification.emit(notification.event.GAME_RESUME);
        }
        this._ui = null;
        this._super();
    },

    _on_btn_close: function() {
        this.close();
    },

    _on_btn_buy : function(){
        if(UiEffect.blockShopItemWithRMB()) {
            return;
        }

        ShopSystem.instance.buyGood(this._shop_id, 1);
        this.close();
    },

    pop: function() {
        this._super();
        UiEffect.iconOpenEffect(this._ui.panel_gift);
    }
});

var GiftDetailVip = GiftDetailBase.extend({
    _guiFile : "ui/gift_vip.json",
    _shop_id: 101004
});

var GiftDetailZhiZun = GiftDetailBase.extend({
    _guiFile: "ui/gift_zhizun.json",
    _shop_id: 101003
});

var GiftDetailSuit = GiftDetailBase.extend({
    _guiFile: "ui/gift_legend_suit.json",
    _shop_id: 101001
});


var GiftDetailWeapon = GiftDetailBase.extend({
    _guiFile: "ui/gift_legend_weapon.json",
    _shop_id: 101002
});


var EndlessSelected = ui.GuiWindowBase.extend({
    _guiFile : "ui/endless_select_layer.json",
    _shop_id: 101014,

    ctor : function () {
        this._super();
    },

    onEnter : function () {
        this._super();
        
        this._lbl_round = this.seekWidgetByName("lbl_record_num");
        var num = BattleSystem.instance.endlessRound;
        LOG(" num = " + num);
        this._lbl_round.setString(String(num));

        this._btn_buy = this.seekWidgetByName("btn_buy");
        this._btn_challenge = this.seekWidgetByName("btn_challenge");
        this._panel_1 = this.seekWidgetByName("panel_1");
        this._chargetPosNode = this.seekWidgetByName("charge_node");
        this._lbl_desc = this.seekWidgetByName("lbl_desc");
        //if(this._btn_buy){
        //    this._btn_buy.setVisible(false);
        //}

        if(util.getChannelId() != GameChannel.CmccMm){
            this._panel_1.setVisible(true);

            this._btn_challenge.setPosition(this._chargetPosNode.getPosition());
        }
        else{
            this._panel_1.setVisible(false);
        }

        this._bindings = [
            notification.createBinding(notification.event.BATTLE_ENDLESS_BUY_FINISH, function (event,obj) {
                this.close();
                ui.pushScene(new BattleEndlessScene(true) );

            },this)
        ];

        if(this._shop_id) {
            var config = ShopSystem.getConfig(this._shop_id);
            if(config) {
                this._lbl_desc.setString(this._lbl_desc._str_original.format(
                    config.pay_cost,
                    ShopSystem.getPayTypeString(config.pay_type)
                ));
            }
        }
    },

    onExit : function () {
        notification.removeBinding(this._bindings);
        this._super();
    },

    _on_btn_buy : function(){
        if(UiEffect.blockShopItemWithRMB()){
            return;
        }
        //ui.pushScene(new BattleEndlessScene(true) );

        ShopSystem.instance.buyGood(this._shop_id);
        //this.close();
    },

    _on_btn_close : function () {

        this.close();
    },
    
    _on_btn_challenge : function () {
        this.close();


       ui.pushScene(new BattleEndlessScene() );

        //var sel_map_id = BattleSystem.instance.cur_battle_map;
        //var loadingPanel = new LoadingBattleLayer(sel_map_id);
        //loadingPanel.pop();
        //
        //loadingPanel.setLoadDoneFunc(function() {
        //    (function () {
        //        var scene = new BattleEndlessScene();
        //        scene._LoadingNode = loadingPanel;
        //        ui.pushSceneExtend(scene,loadingPanel);
        //    } ());
        //}, this)
    }

});

var BuySkillDetail = ui.GuiWindowBase.extend({
    _guiFile : "ui/buy_skill_layer.json",
    _shop_id: 101011,

    ctor : function (func_,target_) {
        this._super();


        this._callfunc = func_;
        this._target = target_;
    },

    onEnter : function () {
        this._super();
        this._ui = {
            lbl_price_rmb: this.seekWidgetByName("lbl_price"),
            lbl_price_diamond: this.seekWidgetByName("lbl_price_0")
        };

        var channel_id = util.getChannelId();
        switch (channel_id) {
            case GameChannel.Telecom:
                this._ui.lbl_price_rmb.setVisible(false);
                this._ui.lbl_price_diamond.setVisible(false);
                this._ui.lbl_price = null;
                break;
            case GameChannel.AppStore:
                this._ui.lbl_price_rmb.setVisible(false);
                this._ui.lbl_price_diamond.setVisible(true);
                this._ui.lbl_price = this._ui.lbl_price_diamond;
                break;
            default :
                this._ui.lbl_price_rmb.setVisible(true);
                this._ui.lbl_price_diamond.setVisible(false);
                this._ui.lbl_price = this._ui.lbl_price_rmb;
                break;
        }

        if(this._ui.lbl_price && this._shop_id) {
            var config = ShopSystem.getConfig(this._shop_id);
            if(config != undefined) {
                this._ui.lbl_price.setString(this._ui.lbl_price._str_original.format(config.pay_cost));
            }
        }
    },

    onExit : function () {
        this._ui = null;
        this._super();
    },

    _on_btn_buy : function(){

        this._callfunc.apply(this._target);
        this.close();
        if(UiEffect.blockShopItemWithRMB()){
            return
        }

       // BattleSystem.instance.buySuperSkill();

        notification.emit(notification.event.BATTLE_STOP_STATE);
        ShopSystem.instance.buyGood(this._shop_id);
    },

    _on_btn_close : function () {
        this._callfunc.apply(this._target);
        this.close();
    }
});

var VipGetDetail = ui.GuiWindowBase.extend({
    _guiFile : "ui/vip_lingqu_layer.json",

    ctor : function (func_,target_) {
        this._super();


        this._callfunc = func_;
        this._target = target_;
    },

    onEnter : function () {
        this._super();
        this._get_btn = this.seekWidgetByName("btn_get");

        if(RewardSystem.instance._isGetVipDone){
           // this._get_btn.setEnable(false);
            this._get_btn.setBright(false);
        }
        else{
           // this._get_btn.setEnable(true);
            this._get_btn.setBright(true);
        }

        this._bindings = [
            notification.createBinding(notification.event.GET_VIP_REWARD, function () {
                if(RewardSystem.instance._isGetVipDone){
                    // this._get_btn.setEnable(false);
                    this._get_btn.setBright(false);
                }
                else{
                    // this._get_btn.setEnable(true);
                    this._get_btn.setBright(true);
                }
                this.close();
            },this)
        ]
    },

    onExit : function () {
        notification.removeBinding(this._bindings);
        this._get_btn = null;
        this._super();
    },

    _on_btn_get : function(){
        net_protocol_handlers.SEND_CMD_CS_GET_VIP_REWARD({
            player_id : 101
        })
    },

    _on_btn_close : function () {
        this.close();
    }

});
