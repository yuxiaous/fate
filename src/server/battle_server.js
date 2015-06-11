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
    var map_id = obj.map_id;

    battle_server.cur_battle_map = map_id;
    server.send(net_protocol_handlers.CMD_SC_BATTLE_MAP_RESULT, {
        result: 0,
        map_id: map_id
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_BATTLE_FINISH, function(obj) {
    LOG("CMD_CS_BATTLE_FINISH");
    if(obj.result == 1) {
        var config = configdb.map[battle_server.cur_battle_map];
        if(config && config.next_map) {
            map_server.openMap([config.next_map]);
        }
    }

    server.send(net_protocol_handlers.CMD_SC_BATTLE_FINISH_RESULT, {
        result: 0
    });
});
