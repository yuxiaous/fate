/**
 * Created by yuxiao on 15/5/12.
 */


var shop_server = {

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
        case 1: // gold
            if(player_server.changeGold(-cost) == false) {
                return;
            }
            break;

        case 2: // diamond
            if(player_server.changeDiamond(-cost) == false) {
                return;
            }
            break;
    }

    var count = obj.count * config.buy_count;
    if(bag_server.addItem(config.buy_id, count) == false) {
        LOG("CMD_CS_SHOP_BUY_GOODS error 3");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    server.send(net_protocol_handlers.CMD_SC_SHOP_BUY_RESULT, {
        result: 0,
        good_id: obj.good_id,
        remaining: 12345
    });
});

