/**
 * Created by yuxiao on 15/5/19.
 */


var equip_server = {
    start: function() {
        this.equip_info = database.checkout("equip_info", [
            { slot: 1, level: 1, id: configdb.property[102].value }, // 部位，等级，装备
            { slot: 2, level: 1, id: configdb.property[105].value },
            { slot: 3, level: 1, id: configdb.property[103].value },
            { slot: 4, level: 1, id: configdb.property[106].value },
            { slot: 5, level: 1, id: configdb.property[104].value },
            { slot: 6, level: 1, id: configdb.property[107].value }
        ]);

        this.update = [];
    },

    end: function() {

    },

    sync: function() {
        if(this.update.length > 0) {
            LOG("equip_server.sync");

            database.commit("equip_info", this.equip_info);
            server.send(net_protocol_handlers.CMD_SC_EQUIP_SLOT_INFO, {
                slots: this.update
            });
            this.update = [];
        }
    },

    upgradeSlot: function(slot) {
        var info = _.findWhere(this.equip_info, {slot: slot});
        if(info == undefined) {
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        if(info.level >= player_server.player_info.level) {
            server.sendError(net_error_code.ERR_EQUiP_SLOT_LEVEL_LIMIT);
            return false;
        }

        var upgrade_id = EquipSystem.getEquipSlotUpgradeId(slot, info.level);
        var config = configdb.duanzao[upgrade_id];
        if(config == undefined) {
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        if(config.next == undefined) {
            server.sendError(net_error_code.ERR_TOP_LEVEL);
            return false;
        }

        // pay out money
        if(player_server.changeGold(-config.cost) == false) {
            return false;
        }

        // update info
        info.level += 1;
        this.update.push(info);
        return true;
    },

    upgradeSlotToMax: function (duanzao_id) {
        var config = configdb.duanzao[duanzao_id];
        if(config == undefined) {
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        var info = _.findWhere(this.equip_info, {slot: config.slot_type});
        if(info == undefined) {
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        // update info
        info.level = config.level;
        this.update.push(info);
        return true;
    },

    equip: function(uid) {
        var bag_info = _.findWhere(bag_server.bag_info, { uid: uid });
        if(bag_info == undefined) {
            LOG("CMD_CS_ITEM_EQUIP error 1");
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        var equip_config = configdb.equip[bag_info.id];
        if(equip_config == undefined) {
            LOG("CMD_CS_ITEM_EQUIP error 2");
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        var equip_info = _.findWhere(this.equip_info, {slot: equip_config.slot});
        if(equip_info == undefined) {
            LOG("CMD_CS_ITEM_EQUIP error 3");
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        // take off equip
        if(equip_info.id != 0) {
            if(bag_server.addItem(equip_info.id, 1) == false) {
                return false;
            }
            equip_info.id = 0;
        }

        // pick equip from bag
        if(bag_server.reduceItem(uid, 1) == false) {
            return false;
        }

        equip_info.id = bag_info.id;
        this.update.push(equip_info);
        return true;
    },

    changeEquip: function(id) {
        var config = configdb.equip[id];
        if(config == undefined) {
            LOG("changeEquip error 1");
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        var info = _.findWhere(this.equip_info, {slot: config.slot});
        if(info == undefined) {
            LOG("changeEquip error 2");
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        info.id = id;
        this.update.push(info);
        return true;
    }
};

server.registerCallback(net_protocol_handlers.CMD_CS_EQUIP_SLOT_UPGRADE, function(obj) {
    LOG("CMD_CS_EQUIP_SLOT_UPGRADE");
    if(equip_server.upgradeSlot(obj.slot_type) == false) {
        return;
    }

    mission_server.count(mission_server.Type.EquipSlotUpgrade);

    // send result
    server.send(net_protocol_handlers.CMD_SC_EQUIP_SLOT_UPGRADE_RESULT, {
        result: 0
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_EQUIP_SLOT_UPGRADE_TOP, function (obj) {

});

server.registerCallback(net_protocol_handlers.CMD_CS_EQUIP_ITEM, function(obj) {
    LOG("CMD_CS_ITEM_EQUIP");
    if(equip_server.equip(obj.uid) == false) {
        return;
    }

    // result
    server.send(net_protocol_handlers.CMD_CS_EQUIP_ITEM_RESULT, {
        result: 0
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_UNEQUIP_ITEM, function(obj) {
    LOG("CMD_CS_UNEQUIP_ITEM");
});

