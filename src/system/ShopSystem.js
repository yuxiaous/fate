/**
 * Created by yuxiao on 15/5/11.
 */


var ShopSystem = SystemBase.extend({
    ctor: function () {
        this._super();

        this._historyBuyInfo  = [];
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_SHOP_BUY_RESULT = this.onBuyGoodResult.bind(this);
        net_protocol_handlers.ON_CMD_SC_SHOP_ORDER_RESULT = this.onOrderResult.bind(this);
        net_protocol_handlers.ON_CMD_SC_BUY_SHILIAN_FINISH = this.onBuyShiLianResult.bind(this);
        net_protocol_handlers.ON_CMD_SC_SHOP_HISTORY_BUY_INFO = this.onShopHistoryInfo.bind(this);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_SHOP_BUY_RESULT = null;
        net_protocol_handlers.ON_CMD_SC_SHOP_ORDER_RESULT = null;
        net_protocol_handlers.ON_CMD_SC_BUY_SHILIAN_FINISH = null;
        net_protocol_handlers.ON_CMD_SC_SHOP_HISTORY_BUY_INFO = null;
        this._historyBuyInfo = null;
    },

    buyGood: function(id, num) {
        if(num == undefined) num = 1;
        LOG("ShopSystem.buyGood id: {0}, num: {1}".format(id, num));

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
                    item: config.buy_id,
                    number: num * config.buy_count,
                    price: config.pay_cost
                }));
        }
    },

    onBuyGoodResult: function(obj) {
        LOG("onBuyGoodResult");
        //LOG(obj);
        //MessageBoxOk.show("购买成功");
        if(obj.result != 0) {
            UiEffect.showFloatLabel("购买失败！");
            return;
        }

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
    },

    onShopHistoryInfo : function (obj) {
        LOG("---=========");
        LOG(obj);
        _.forEach(this._historyBuyInfo, function (info_) {
            LOG("item id = " + info_.item_id +", buy_num = " + info_.buy_num);
        });

        //if(obj && obj.history_buy_info){
        //    this._historyBuyInfo.concat(obj.history_buy_info);
        //
        //}

        this._historyBuyInfo = obj.history_buy_info;

        _.forEach(this._historyBuyInfo, function (info_) {
            LOG("item id = " + info_.item_id +", buy_num = " + info_.buy_num);
        });

        notification.emit(notification.event.SHOP_UPDATE_HISTORY_BUYINFO);
    },

    getHistoryBuyInfo : function (good_id) {
        var buy_num = 0;
        _.forEach(this._historyBuyInfo, function (itemInfo_) {
            if(itemInfo_ && itemInfo_.item_id == good_id){
                buy_num = itemInfo_.buy_num;
            }
        },this);

        return buy_num;
    }
});


ShopSystem.getShopPlatformId = function() {
    var channel_id = util.getChannelId();
    var sim_operator = util.getSimOperator();
    switch (channel_id) {
        case GameChannel.AppStore:
            return [2];
        case GameChannel.CmccMm:
            return [3];
        case GameChannel.CmccAnd:
        case GameChannel.XyAnzhuo:
            return [4];
        case GameChannel.Unicom:
            return [5];
        case GameChannel.Telecom:
            return [6];
        case GameChannel.Qh360:
            return [7];
        case GameChannel.TencentMidas:
            return [8];
        case GameChannel.Mix:
        case GameChannel.Pps:
        case GameChannel.SohuWan:
        case GameChannel.Youku:
        case GameChannel.Baidu91:
        case GameChannel.BaiduTieba:
        case GameChannel.BaiduShoujizhushou:
        case GameChannel.BaiduDuoku:
        case GameChannel.Ttyx:
        case GameChannel.Sevenk:
        case GameChannel.Letvs:
        case GameChannel.Youletang:
        case GameChannel.Feiliu:
        case GameChannel.Htc:
        case GameChannel.Youyoucun:
        case GameChannel.Anzhi:
        case GameChannel.Meitu:
        case GameChannel.Yingyonghui:
        case GameChannel.Dangle:
        case GameChannel.Sanxing:
        case GameChannel.Kuwo:
        case GameChannel.Mzw:
        case GameChannel.SouGou5:
        case GameChannel.SouGou6:
        case GameChannel.SouGou7:
        case GameChannel.SouGou8:
        case GameChannel.SouGou9:
        case GameChannel.SouGou11:
        case GameChannel.Meizu:
        case GameChannel.Wandoujia:
            switch (sim_operator) {
                case SimOperator.CMCC:
                    return [4];
                case SimOperator.UNICOM:
                    return [5];
                case SimOperator.TLELCOM:
                    return [6];
            }
            break;
        case GameChannel.M4399:
            switch (sim_operator) {
                case SimOperator.CMCC:
                    return [4, 11];
                case SimOperator.UNICOM:
                    return [5, 11];
                case SimOperator.TLELCOM:
                    return [6, 11];
            }
            break;
        case GameChannel.Uc:
            switch (sim_operator) {
                case SimOperator.CMCC:
                    return [4, 9];
                case SimOperator.UNICOM:
                    return [5, 9];
                case SimOperator.TLELCOM:
                    return [6, 9];
            }
            break;
        case GameChannel.Coolpad:
            switch (sim_operator) {
                case SimOperator.CMCC:
                    return [4, 10];
                case SimOperator.UNICOM:
                    return [5, 10];
                case SimOperator.TLELCOM:
                    return [6, 10];
            }
            break;
    }
    return [1];
};

ShopSystem.getConfig = function(good_id) {
    var config = configdb.shop[good_id];
    if(config != undefined) {
        _.some(ShopSystem.getShopPlatformId(), function(id) {
            var config2 = config[id];
            if(config2 != undefined) {
                config = config2;
                return true;
            }
            return false;
        });
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
ShopSystem.getPayTypeString = function(type) {
    switch (type) {
        case ShopSystem.PayType.Gold: return "金币";
        case ShopSystem.PayType.Diamond: return "钻石";
        case ShopSystem.PayType.RMB: return "元";
    }
    return "未知";
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
