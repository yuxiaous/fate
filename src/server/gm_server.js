/**
 * Created by yuxiao on 15/5/13.
 */


var gm_server = {
    start: function() {
    },

    end: function() {
    },

    flush: function() {
    },

    // ar [id] [qty] 加资源(1金币 2钻石 3行动力 4经验值)
    // ai [id] [qty] 添加物品
    // ae [id] [qty] 添加装备
    // om [id]
    parse: function(cmd) {
        var list = cmd.split(' ');
        switch (list[0]) {
            case "ar": this.parseAddResource(list); break;
            case "ai": this.parseAddItem(list); break;
            case "ae": this.parseAddEquip(list); break;
            case "om": this.parseOpenMap(list); break;
        }
    },

    parseAddResource: function(list) {
        var player = null;
        var id = Number(list[1]);
        var qty = Number(list[2]) || 1;
        if(qty <= 0) {
            return;
        }

        switch (id) {
            case 1:
                player = {
                    gold: player_server.player_info.gold += qty
                };
                break;

            case 2:
                player = {
                    diamond: player_server.player_info.diamond += qty
                };
                break;

            case 3:
                player = {
                    action: player_server.player_info.action += qty
                };
                break;
        }
        if(player) {
            server.send(net_protocol_handlers.CMD_CS_PLAYER_INFO, {
                player: player
            });
        }
    },

    parseAddItem: function(list) {
        var id = Number(list[1]);
        var qty = Number(list[2]) || 1;
        var type = Math.floor(id/100000);

        if(type == 1) {
            bag_server.addItem(id, qty);
        }
    },

    parseAddEquip: function(list) {
        var id = Number(list[1]);
        var qty = Number(list[2]) || 1;
        var type = Math.floor(id/100000);

        if(type == 2) {
            bag_server.addItem(id, qty);
        }
    },

    parseOpenMap: function(list) {
        var id = Number(list[1]);

        var open = [];
        _.each(configdb.map, function(config) {
            if(config.key <= id) {
                open.push(config.key);
            }
        }, this);

        map_server.openMap(open);
    }
};


server.registerCallback(net_protocol_handlers.CMD_CS_GM_CMD, function(obj) {
    LOG("CMD_CS_GM_CMD");
    gm_server.parse(obj.cmd);
});