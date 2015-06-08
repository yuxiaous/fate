/**
 * Created by yuxiao on 15/5/5.
 */


var map_server = {
    start: function() {
        this.map_info = database.checkout("map_info", [
            { map_id: 101 }
        ]);
    },

    end: function() {

    },

    flush: function() {
        database.commit("map_info", this.map_info);
    },

    openMap: function(ids) {
        var update = [];

        _.each(ids, function(id) {
            var find = _.findWhere(this.map_info, {map_id: id});
            if(find == undefined) {
                var info = {
                    map_id: id
                };
                this.map_info.push(info);
                update.push(info);
            }
        }, this);

        server.send(net_protocol_handlers.CMD_SC_MAP_INFO, {
            maps: update
        });
    }
};


server.registerCallback(net_protocol_handlers.CMD_CS_GET_MAP_INFO, function(obj) {
    LOG("CMD_CS_GET_MAP_INFO")
    server.send(net_protocol_handlers.CMD_SC_MAP_INFO, {
        maps: map_server.map_info
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_SEND_BATTLE_RESULT, function(obj) {
    LOG("CMD_CS_SEND_BATTLE_RESULT")
    if(obj.result == 1) {
        var config = configdb.map[obj.map_id];
        if(config && config.next_map) {
            map_server.openMap([config.next_map]);
        }
    }
});
