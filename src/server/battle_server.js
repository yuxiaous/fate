var battle_server = {
    start: function() {
        this.battle_info = database.checkout("battle_info", [

        ]);
    },

    end: function() {

    },

    flush: function() {
        database.commit("battle_info", this.battle_info);
    }
};

battle_server.cur_battle_map = 0;
server.registerCallback(net_protocol_handlers.CMD_CS_BATTLE_MAP, function(obj) {
    LOG("CMD_CS_BATTLE_MAP");
    // TODO


    battle_server.cur_battle_map = obj.map_id;
    server.send(net_protocol_handlers.CMD_SC_BATTLE_MAP_RESULT, {
        result: 0,
        map_id: battle_server.cur_battle_map
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_BATTLE_FINISH, function(obj) {
    LOG("CMD_CS_BATTLE_FINISH");
    if(obj.result != 1) {
        return;
    }

    var max_map = _.max(map_server.map_info, function(info) {
        return info.map_id;
    });
    var is_first_battle = (battle_server.cur_battle_map == max_map.map_id);

    var config = configdb.map[battle_server.cur_battle_map];
    if(config == undefined) {
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    // open map
    if(config.next_map) {
        map_server.openMap([config.next_map]);
    }

    // add resource
    server.send(net_protocol_handlers.CMD_CS_PLAYER_INFO,{
        player:{
            exp : player_server.player_info.exp += config.gain_exp,
            gold: player_server.player_info.gold += config.gain_gold,
            diamond: is_first_battle ? player_server.player_info.diamond += config.gain_diamond : undefined
        }
    });
    player_server.checkLevelUp();

    // add item
    if(config.gain_item_id_1) {
        bag_server.addItem(config.gain_item_id_1, 1)
    }
    if(config.gain_item_id_2) {
        bag_server.addItem(config.gain_item_id_2, 1)
    }

    // result
    var reward = {};
    reward.exp = config.gain_exp;
    reward.gold = config.gain_gold;
    if(is_first_battle) {
        reward.diamond = config.gain_diamond;
        reward.items = [
            {
                item_id : config.gain_item_id_1,
                item_num: 1
            },
            {
                item_id : config.gain_item_id_2,
                item_num: 1
            }
        ];
    }
    server.send(net_protocol_handlers.CMD_SC_BATTLE_FINISH_RESULT, {
        result : 1,
        map_id: battle_server.cur_battle_map,
        reward : reward
    });
});
