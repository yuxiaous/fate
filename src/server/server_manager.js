/**
 * Created by yuxiao on 15/5/23.
 */


var server_manager = {
    servers: [],

    start: function() {
        var servers = this.servers;
        function addSubServer(server) {
            if(server) {
                servers.push(server);

                if(server.start) {
                    server.start();
                }
            }
        }

        addSubServer(player_server);
        addSubServer(gm_server);
        addSubServer(map_server);
        addSubServer(shop_server);
        addSubServer(skill_server);
        addSubServer(equip_server);
        addSubServer(bag_server);
        addSubServer(item_server);
        addSubServer(battle_server);

        cc.director.getScheduler().scheduleCallbackForTarget(this, this.flush, 60);
    },

    end: function() {
        cc.director.getScheduler().unscheduleCallbackForTarget(this, this.flush);

        _.each(this.servers, function(server) {
            if(server.end) {
                server.end();
            }
        });
        this.servers.length = 0;
    },

    flush: function() {
        _.each(this.servers, function(server) {
            if(server.flush) {
                server.flush();
            }
        });
    },

    sync: function() {
        _.each(this.servers, function(server) {
            if(server.sync) {
                server.sync();
            }
        });
    }
};
