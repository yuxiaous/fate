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
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_SHOP_BUY_RESULT = null;
        net_protocol_handlers.ON_CMD_SC_SHOP_ORDER_RESULT = null;
    },

    buyGood: function(id, num) {
        var config = configdb.shop[id];
        if(config == undefined) {
            return;
        }

        if(config.pay_type == ShopSystem.PayType.RMB) {
            net_protocol_handlers.SEND_CMD_CS_SHOP_ORDER({
                good_id: id
            });
        }
        else {
            net_protocol_handlers.SEND_CMD_CS_SHOP_BUY_GOODS({
                good_id: id,
                count: num
            });
        }
    },

    onBuyGoodResult: function(obj) {
        MessageBoxOk.show("购买成功");
        notification.emit(notification.event.SHOP_BUY_RESULT);
    },

    onOrderResult: function(obj) {
        var config = configdb.shop[obj.good_id];
        if(config == undefined) {
            return;
        }

        jsb.SdkManager.buy(JSON.stringify({
            order: obj.order,
            platform_good_id: "101"
        }));
    }
});

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
    Diamond: 6
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
