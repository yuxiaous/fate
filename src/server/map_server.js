/**
 * Created by yuxiao on 15/5/5.
 */


var map_server = {
    start: function() {
        this.map_info = database.checkout("map_info", [
            { map_id: 101 }
        ]);

        this.update = [];
    },

    end: function() {

    },

    sync: function() {
        if(this.update.length > 0) {
            LOG("map_server.sync");

            database.commit("map_info", this.map_info);
            server.send(net_protocol_handlers.CMD_SC_MAP_INFO, {
                maps: this.update
            });
            this.update = [];
        }
    },

    openMap: function(ids) {
        _.each(ids, function(id) {
            var find = _.findWhere(this.map_info, {map_id: id});
            if(find == undefined) {
                var info = {
                    map_id: id
                };
                this.map_info.push(info);
                this.update.push(info);

                var config = configdb.map[id];
                if(config) {
                    mission_server.count(mission_server.Type.MapUnlock, config.chapter);
                }
            }
        }, this);
    }
};

