/**
 * Created by yuxiao on 15/5/11.
 */


var ShopSystem = SystemBase.extend({
    ctor: function () {
        this._super();
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_SHOP_BUY_RESULT = this.onBuyGoodResult.bind(this);
        net_protocol_handlers.ON_CMD_SC_SHOP_ORDER_RESULT = this.onOrderResult.bind(this);
        net_protocol_handlers.ON_CMD_SC_BUY_SHILIAN_FINISH = this.onBuyShiLianResult.bind(this);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_SHOP_BUY_RESULT = null;
        net_protocol_handlers.ON_CMD_SC_SHOP_ORDER_RESULT = null;
        net_protocol_handlers.ON_CMD_SC_BUY_SHILIAN_FINISH = null;
    },

    buyGood: function(id, num) {
        LOG("ShopSystem.buyGood id: {0}, num: {1}".format(id, num));
        if(num == undefined) num = 1;

        var config = ShopSystem.getConfig(id);
        if(config == undefined) {
            LOG("Error: ShopSystem.buyGood 1");
            return;
        }

        if(config.pay_type == ShopSystem.PayType.RMB) {
            if(config.pay_cost != 0 ){
                if(UiEffect.blockShopItemWithRMB()){
                    return;
                }
            }
            LOG("buyGood get order");
            net_protocol_handlers.SEND_CMD_CS_SHOP_ORDER({
                good_id: id
            });
        }
        else {
            LOG("buyGood purchase");
            net_protocol_handlers.SEND_CMD_CS_SHOP_BUY_GOODS({
                good_id: id,
                count: num
            });
            sdk_manager.sendSdkCommand("TalkingDataGA", "onPurchase",
                "{item},{number},{price}".format({
                    item: config.name,
                    number: num,
                    price: config.pay_cost
                }));
        }
    },

    onBuyGoodResult: function(obj) {
        //MessageBoxOk.show("购买成功");


        if(obj && obj.good_id == 101014){

        }
        else{
            UiEffect.showFloatLabel("购买成功");
        }

        if(obj.result == 0 && obj.order && obj.order.length > 0) {
            sdk_manager.sendSdkCommand("TalkingDataGA", "onChargeSuccess", obj.order);
        }

        notification.emit(notification.event.SHOP_BUY_RESULT,obj);

    },

    onBuyShiLianResult : function(){
        notification.emit(notification.event.BATTLE_ENDLESS_BUY_FINISH);
    },

    onOrderResult: function(obj) {
        LOG("onOrderResult");
        var config = ShopSystem.getConfig(obj.good_id);
        if(config == undefined) {
            return;
        }
        sdk_manager.charge(obj.order, config.platform_good_id);

        sdk_manager.sendSdkCommand("TalkingDataGA", "onChargeRequest",
            "{order},{iapId},{currencyAmount},{currencyType},{virtualCurrencyAmount},{paymentType}".format({
                order: obj.order,
                iapId: config.name,
                currencyAmount: config.pay_cost,
                currencyType: "CNY",
                virtualCurrencyAmount: 0,
                paymentType: ""
            }));
    }
});


ShopSystem.getShopPlatformId = function() {
    var channel_id = util.getChannelId();
    switch (channel_id) {
        case GameChannel.AppStore: return 2;
        case GameChannel.CmccAnd: return 4;
        case GameChannel.CmccMm: return 3;
        case GameChannel.Telecom: return 6;
        case GameChannel.Unicom: return 5;
        default : return 1;
    }
};

ShopSystem.getConfig = function(good_id) {
    var config = configdb.shop[good_id];
    if(config != undefined) {
        var platform_id = ShopSystem.getShopPlatformId();
        var config2 = config[platform_id];
        if(config2 != undefined) {
            config = config2;
        }
    }
    return config;
};

ShopSystem.ShopType = {
    Equip: 1,
    Item: 2,
    Role: 3,
    Charge: 4
};

ShopSystem.PayType = {
    Gold: 1,
    Diamond: 2,

    RMB: 101
};

ShopSystem.GoodType = {
    Equip: 1,
    Item: 2,

    Skin: 4,
    Gold: 5,
    Diamond: 6,
    Gift : 7,
    EquipSlotTopLevel: 8,
    DaZhao : 9,
    Tili : 10,
    FuHuo : 11,
    ShiLian : 12
};

//ShopSystem.GoodType = {
//    Coating: 1,
//    Item: 2,
//    weapon: 3,
//    armor: 4,
//    Diamond: 5,
//    Gold: 6
//};
//
//ShopSystem.getGoodType = function(type) {
//    switch (type) {
//        case ShopSystem.GoodType.Coating: return "时装";
//        case ShopSystem.GoodType.Item: return "道具";
//        case ShopSystem.GoodType.weapon: return "武器";
//        case ShopSystem.GoodType.armor: return "防具";
//        case ShopSystem.GoodType.Diamond: return "钻石";
//        case ShopSystem.GoodType.Gold: return "金币";
//    }
//    return "未知";
//};
