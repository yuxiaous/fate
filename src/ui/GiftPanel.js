

var GiftPanel = ui.GuiController.extend({
    ctor: function() {
        this._super();

    },

    onEnter: function() {
        this._super();

        this._ui = {
            btn_1 : this.seekWidgetByName("btn_1"),
            btn_2 : this.seekWidgetByName("btn_2"),
            btn_3 : this.seekWidgetByName("btn_3"),
            btn_4 : this.seekWidgetByName("btn_4")
        }

        _.each([this._ui.btn_1,
                this._ui.btn_2,
                this._ui.btn_3,
                this._ui.btn_4], function (btn_,idx_) {
            var btnSelectImg = btn_.setPressedActionEnabled(true);

            btn_.addTouchEventListener(function (touch,event) {
                if(event == ccui.Widget.TOUCH_ENDED){
                    var giftType = 0;
                    var giftId = 0;

                    switch (idx_){
                        case 0 :
                            giftType = GiftSystem.GiftType.Vip;
                            giftId = 101004;
                            break;
                        case 1 :
                            giftType = GiftSystem.GiftType.ZhiZun;
                            giftId = 101003;
                            break;
                        case 2 :
                            giftType = GiftSystem.GiftType.ZhuangBei;
                            giftId = 101001;
                            break;
                        case 3 :
                            giftType = GiftSystem.GiftType.WuQi;
                            giftId = 101002;
                            break;
                    }
                    var buy_panel = new GiftBuyDetail(giftType,giftId);
                    buy_panel.pop();
                    UiEffect.iconOpenEffect(buy_panel.seekWidgetByName("gift_panel"));
                }
            },this);

            var lbl_time = this.seekWidgetByName("lbl_time");
            if(lbl_time){
                btn_.lbl_time = lbl_time;

                var tmpTime = GiftSystem.instance.getGiftCountTime(GiftSystem.GiftType.ZhiZun);
                var changeStr = GiftSystem.instance.changeStringToTimeStyle(tmpTime);
                btn_.lbl_time.setString(String(changeStr));
            }

            if(idx_ == 1){
                UiEffect.buttonBBB(btn_);
            }
            else{
                this.addBtnEffect(btn_);
            }
        },this);



        this._bindings =[
            notification.createBinding(notification.event.REFRESH_GIFT_INFO, function () {
                this.refreshGiftNodeDisplay();
            },this)
        ]

        this.refreshGiftNodeDisplay();


        GiftSystem.instance.getGiftItemTime();

        cc.director.getScheduler().schedule(function () {
            _.each([this._ui.btn_1,
                this._ui.btn_2,
                this._ui.btn_3,
                this._ui.btn_4], function (btn_,idx_) {
                if(idx_ == 1 && btn_.lbl_time){
                    var tmpTime = GiftSystem.instance.getGiftCountTime(GiftSystem.GiftType.ZhiZun);
                    var changeStr = GiftSystem.instance.changeStringToTimeStyle(tmpTime);
                    btn_.lbl_time.setString(String(changeStr));
                }
            },this);
        },this,1.0,cc.REPEAT_FOREVER,0,false,"refresh_label");
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

            if(tmpGiftData.buy_num > 0 && tmpGiftData.giftType != GiftSystem.GiftType.ZhiZun){
                btn_.setVisible(false);
            }
            else{
                btn_.setVisible(true);
            }

        },this);
    },

    onExit: function() {

        cc.director.getScheduler().unschedule("refresh_label",this);
        notification.removeBinding(this._bindings);
        this._ui = null;
        this._super();
    }
});

var GiftBuyDetail = ui.GuiWindowBase.extend({
    _guiFile : "ui/gift_detail_panel.json",

    ctor : function (type_,giftId_,gift_target_,gift_callfunc_) {
        this._super();

        this._giftType = type_;
        this._giftId = giftId_;
        this._target = gift_target_;
        this._callfunc = gift_callfunc_;
    },


    onEnter : function () {
        this._super();

        //this.setScale(0.8);

        var gift_detail_img = "";
        switch (this._giftType){
            case GiftSystem.GiftType.ZhuangBei :
                gift_detail_img = "ui_314.png";
                break;
            case  GiftSystem.GiftType.WuQi :
                gift_detail_img = "ui_313.png";
                break;
            case GiftSystem.GiftType.ZhiZun :
                gift_detail_img = "ui_312.png";
                break;
            case GiftSystem.GiftType.Vip:
                gift_detail_img = "ui_315.png";
                break;
        }

        var baseString = "images/code_ui/";
        gift_detail_img = String(baseString+gift_detail_img);
        //gift_title_img = String(baseString+gift_title_img);

        //this._title_img = this.seekWidgetByName("item_title");
        this._detail_img = this.seekWidgetByName("gift_panel");


        //this._title_img.loadTexture(gift_title_img);
        this._detail_img.loadTexture(gift_detail_img);


        this.buy_btn = this.seekWidgetByName("btn_buy");


        UiEffect.buttonBBB(this.buy_btn);

    },

    onExit : function () {
        this._super();

    },

    _on_btn_buy : function(){

        if(UiEffect.blockShopItemWithRMB()){
            return
        }

        GiftSystem.instance.buyGiftItem(this._giftType);
        ShopSystem.instance.buyGood(this._giftId,1);
        this._on_btn_close();
    },

    _on_btn_close : function () {
        if(this._target && this._callfunc){
            cc.director.resume();
            this._callfunc(this._target);
        }
        this.close();
    }
});


var EndlessSelected = ui.GuiWindowBase.extend({
    _guiFile : "ui/endless_select_layer.json",

    ctor : function () {
        this._super();


    },

    onEnter : function () {
        this._super();
        
        this._lbl_round = this.seekWidgetByName("lbl_record_num");
        var num = BattleSystem.instance.endlessRound;
        LOG(" num = " + num);
        this._lbl_round.setString(String(num));
    },

    onExit : function () {
        this._super();

    },

    _on_btn_buy : function(){
        this.close();

        if(UiEffect.blockShopItemWithRMB()){
            return;
        }
        ui.pushScene(new BattleEndlessScene(true) );
    },

    _on_btn_close : function () {

        this.close();
    },
    
    _on_btn_challenge : function () {
        this.close();
        ui.pushScene(new BattleEndlessScene() );
    }

});

var BuySkillDetail = ui.GuiWindowBase.extend({
    _guiFile : "ui/buy_skill_layer.json",

    ctor : function (func_,target_) {
        this._super();


        this._callfunc = func_;
        this._target = target_;
    },

    onEnter : function () {
        this._super();


    },

    onExit : function () {
        this._super();

    },

    _on_btn_buy : function(){

        this._callfunc.apply(this._target);
        this.close();
        if(UiEffect.blockShopItemWithRMB()){
            return
        }

        BattleSystem.instance.buySuperSkill();
    },

    _on_btn_close : function () {
        this._callfunc.apply(this._target);
        this.close();
    }
});
