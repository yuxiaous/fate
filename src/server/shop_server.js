/**
 * Created by yuxiao on 15/5/12.
 */


var shop_server = {

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

    var config = configdb.shop[obj.good_id];
    if(config == undefined) {
        LOG("CMD_CS_SHOP_BUY_GOODS error 1");
        server.sendError(net_error_code.ERR_SHOP_GOODS_NOT_EXIST);
        return;
    }

    if(BagSystem.getConfig(config.buy_id) == undefined) {
        LOG("CMD_CS_SHOP_BUY_GOODS error 2");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    var cost = config.pay_cost * obj.count;
    switch (config.pay_type) {
        case shop_server.PayType.Gold: // gold
            if(player_server.changeGold(-cost) == false) {
                return;
            }
            break;

        case shop_server.PayType.Diamond: // diamond
            if(player_server.changeDiamond(-cost) == false) {
                return;
            }
            break;
    }

    var count = config.buy_count * obj.count;
    if(config.buy_type == shop_server.GoodsType.Equip ||
        config.buy_type == shop_server.GoodsType.Item) {
        if(bag_server.addItem(config.buy_id, count) == false) {
            LOG("CMD_CS_SHOP_BUY_GOODS error 3");
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return;
        }
    }
    else if(config.buy_type == shop_server.GoodsType.Diamond) {
        player_server.changeDiamond(count)
    }
    else if(config.buy_type == shop_server.GoodsType.Gold) {
        player_server.changeGold(count);
    }
    else if(config.buy_type == shop_server.GoodsType.Skin) {

    }

    server.send(net_protocol_handlers.CMD_SC_SHOP_BUY_RESULT, {
        result: 0,
        good_id: obj.good_id,
        remaining: 12345
    });
});

