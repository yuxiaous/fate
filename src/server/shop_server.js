/**
 * Created by yuxiao on 15/5/12.
 */


var shop_server = {
    start: function() {
        jsb.SdkManager.setBuyCallback(this.onBuyCallback.bind(this));

        this.orders = {
            //order_id: {
            //    order: Math.uuid(),
            //    good_id: good_id,
            //    status: 0
            //}
        };
    },

    end: function() {

    },

    onBuyCallback: function(json) {
        LOG("shop_server.onBuyCallback");
        var obj = JSON.parse(json);
        if(obj.result == 0) {
            this.handleOrder(obj.order);
        }
    },

    buyGood: function(good_id, good_num, order) {
        var config = configdb.shop[good_id];
        if(config == undefined) {
            LOG("CMD_CS_SHOP_BUY_GOODS error 1");
            server.sendError(net_error_code.ERR_SHOP_GOODS_NOT_EXIST);
            return false;
        }

        // pay
        var cost = config.pay_cost * good_num;
        switch (config.pay_type) {
            case shop_server.PayType.Gold: // gold
                if(player_server.changeGold(-cost) == false) {
                    return false;
                }
                break;

            case shop_server.PayType.Diamond: // diamond
                if(player_server.changeDiamond(-cost) == false) {
                    return false;
                }
                break;

            case shop_server.PayType.RMB:
                if(this.checkOrder(order) == false) {
                    return false;
                }
        }

        // gain
        var count = config.buy_count * good_num;
        if(config.buy_type == shop_server.GoodsType.Equip || config.buy_type == shop_server.GoodsType.Item) {
            if(bag_server.addItem(config.buy_id, count) == false) {
                return false;
            }
        }
        else if(config.buy_type == shop_server.GoodsType.Diamond) {
            if(player_server.changeDiamond(count) == false) {
                return false;
            }
        }
        else if(config.buy_type == shop_server.GoodsType.Gold) {
            if(player_server.changeGold(count) == false) {
                return false;
            }
        }
        else if(config.buy_type == shop_server.GoodsType.Skin) {
            if(skin_server.addSkin(config.buy_id) == false) {
                return false;
            }
        }

        return true;
    },

    genOrder: function(good_id) {
        var ret = {
            order: Math.uuid(15),
            good_id: good_id,
            status: 0
        };

        this.orders[ret.order] = ret;
        return ret;
    },
    handleOrder: function(o) {
        var order = this.orders[o];
        if(order) {
            order.status = 1;
            this.buyGood(order.good_id, 1, order.order);
        }
    },
    checkOrder: function(o) {
        var order = this.orders[o];
        if(order) {
            return (order.status == 1);
        }
        return false;
    }
};

shop_server.GoodsType = {
    Equip: 1,
    Item: 2,
    Skin: 4,
    Diamond: 5,
    Gold: 6
};
shop_server.PayType = {
    Gold: 1,
    Diamond: 2,
    RMB: 101
};

server.registerCallback(net_protocol_handlers.CMD_CS_SHOP_BUY_GOODS, function(obj) {
    LOG("CMD_CS_SHOP_BUY_GOODS");
    if(shop_server.buyGood(obj.good_id, obj.count) == false) {
        return;
    }

    server.send(net_protocol_handlers.CMD_SC_SHOP_BUY_RESULT, {
        result: 0,
        good_id: obj.good_id,
        remaining: 12345
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_SHOP_ORDER, function(obj) {
    LOG("CMD_CS_SHOP_ORDER");

    var order = shop_server.genOrder(obj.good_id);
    server.send(net_protocol_handlers.CMD_SC_SHOP_ORDER_RESULT, {
        order: order.order,
        good_id: obj.good_id
    });
});