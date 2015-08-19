/**
 * Created by yuxiao on 15/8/18.
 */


var strengthen_server = {
    start: function() {

    },

    end: function() {

    },

    sync: function() {

    }
};

server.registerCallback(net_protocol_handlers.CMD_CS_EQUIP_STRENGTHEN_IN_BAG, function(obj) {
    LOG("CMD_CS_EQUIP_STRENGTHEN_IN_BAG");

    // result
    server.send(net_protocol_handlers.CMD_SC_EQUIP_STRENGTHEN_RESULT, {
        result: 0
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP, function(obj) {
    LOG("CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP");
    var slot = obj.slot;

    var info = _.findWhere(equip_server.equip_info, {slot: slot});
    if(info == undefined) {
        LOG("CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP 1");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    var config = configdb.equip[info.id];
    if(config == undefined) {
        LOG("CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP 2");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    // check next
    if(config.qh_next == undefined) {
        LOG("CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP 3");
        server.sendError(net_error_code.ERR_TOP_LEVEL);
        return;
    }

    // check gold
    if(config.qh_gold > player_server.player_info.gold) {
        LOG("CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP 4");
        server.sendError(net_error_code.ERR_LESS_GOLD);
        return;
    }

    // check request
    var enough = _.every([
        [config.qh_need_1, config.qh_num_1],
        [config.qh_need_2, config.qh_num_2],
        [config.qh_need_3, config.qh_num_3],
        [config.qh_need_4, config.qh_num_4]
    ], function(data) {
        var item_id = data[0];
        if(item_id) {
            var req = data[1];
            var num = bag_server.getItemNumber(item_id);
            return req <= num;
        }
        return true;
    }, this);
    if(enough == false) {
        LOG("CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP 5");
        server.sendError(net_error_code.ERR_LESS_ITEM);
        return;
    }

    // cost
    player_server.changeGold(-config.qh_gold);
    _.each([
        [config.qh_need_1, config.qh_num_1],
        [config.qh_need_2, config.qh_num_2],
        [config.qh_need_3, config.qh_num_3],
        [config.qh_need_4, config.qh_num_4]
    ], function(data) {
        var item_id = data[0];
        if(item_id) {
            var num = data[1];
            bag_server.reduceItem2(item_id, num);
        }
    }, this);

    // change equip
    equip_server.changeEquip(config.qh_next);

    // result
    server.send(net_protocol_handlers.CMD_SC_EQUIP_STRENGTHEN_RESULT, {
        result: 0
    });
});
