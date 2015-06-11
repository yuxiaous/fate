/**
 * Created by yuxiao on 15/5/19.
 */


var equip_server = {
    start: function() {
        this.equip_info = database.checkout("equip_info", [
            { slot: 1, level: 1, id: 200001 }, // 部位，等级，装备
            { slot: 2, level: 1, id: 200002 },
            { slot: 3, level: 1, id: 200003 },
            { slot: 4, level: 1, id: 200004 },
            { slot: 5, level: 1, id: 200005 },
            { slot: 6, level: 1, id: 200006 }
        ]);
    },

    end: function() {

    },

    flush: function() {
        database.commit("equip_info", this.equip_info);
    }
};

server.registerCallback(net_protocol_handlers.CMD_CS_EQUIP_SLOT_UPGRADE, function(obj) {
    LOG("CMD_CS_EQUIP_SLOT_UPGRADE");
    var type = obj.slot_type;

    var info = _.findWhere(equip_server.equip_info, {slot: type});
    if(info == undefined) {
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    var upgrade_id = EquipSystem.getEquipSlotUpgradeId(type, info.level);
    var config = configdb.duanzao[upgrade_id];
    if(config == undefined) {
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    if(config.next == undefined) {
        server.sendError(net_error_code.ERR_TOP_LEVEL);
        return;
    }

    // pay out money
    if(player_server.changeGold(-config.cost) == false) {
        return;
    }

    // update info
    info.level += 1;
    server.send(net_protocol_handlers.CMD_SC_EQUIP_SLOT_INFO, {
        slots: [info]
    });

    // send result
    server.send(net_protocol_handlers.CMD_SC_EQUIP_SLOT_UPGRADE_RESULT, {
        result: 0
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_EQUIP_ITEM, function(obj) {
    LOG("CMD_CS_ITEM_EQUIP");
    var uid = obj.uid;

    var bag_info = _.findWhere(bag_server.bag_info, { uid: uid });
    if(bag_info == undefined) {
        LOG("CMD_CS_ITEM_EQUIP error 1");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    var config = configdb.equip[bag_info.id];
    if(config == undefined) {
        LOG("CMD_CS_ITEM_EQUIP error 2");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    var equip_info = _.findWhere(equip_server.equip_info, {slot: config.slot});
    if(equip_info == undefined) {
        LOG("CMD_CS_ITEM_EQUIP error 3");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    // take off equip
    if(equip_info.id != 0) {
        if(bag_server.addItem(equip_info.id, 1)) {
            equip_info.id = 0;
        }
    }

    // pick equip from bag
    if(!bag_server.reduceItem(uid, 1)) {
        return;
    }

    equip_info.id = bag_info.id;
    server.send(net_protocol_handlers.CMD_SC_EQUIP_SLOT_INFO, {
        slots: [equip_info]
    });

    // result
    server.send(net_protocol_handlers.CMD_CS_EQUIP_ITEM_RESULT, {
        result: 0
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_UNEQUIP_ITEM, function(obj) {
    LOG("CMD_CS_UNEQUIP_ITEM");
});

