/**
 * Created by yuxiao on 15/5/12.
 */


var player_server = {
    servers: [],

    start: function() {
        this.player_info = database.checkout("player_info", {
            player_id: 0,
            level: 1,
            exp: 0,
            diamond: 0,
            gold: 0,
            action: 0 //行动力
        });
    },

    end: function() {

    },

    flush: function() {
        database.commit("player_info", this.player_info);
    },

    checkLevelUp: function() {
        var is_level_up = false;
        while(true) {
            var config = configdb.levelup[this.player_info.level];
            if(config) {
                if(this.player_info.exp >= config.exp) {
                    this.player_info.level += 1;
                    is_level_up = true;
                }
                else {
                    break;
                }
            }
        }
        if(is_level_up) {
            server.send(net_protocol_handlers.CMD_CS_PLAYER_INFO,{
                player:{
                    level: this.player_info.level
                }
            });
        }
    },

    changeGold: function(val) {
        if(this.player_info.gold + val < 0) {
            LOG("changeGold error 1");
            server.sendError(net_error_code.ERR_LESS_GOLD);
            return false;
        }
        server.send(net_protocol_handlers.CMD_CS_PLAYER_INFO, {
            player: {
                gold: this.player_info.gold += val
            }
        });
        return true;
    },
    changeDiamond: function(val) {
        if(this.player_info.diamond + val < 0) {
            LOG("changeDiamond error 1");
            server.sendError(net_error_code.ERR_LESS_DIAMOND);
            return false;
        }
        server.send(net_protocol_handlers.CMD_CS_PLAYER_INFO, {
            player: {
                diamond: this.player_info.diamond += val
            }
        });
        return true;
    }
};


//server.registerCallback(net_protocol_handlers.CMD_CS_GET_PLAYER_INFO, function(obj) {
//    LOG("CMD_CS_GET_PLAYER_INFO")
//    server.send(net_protocol_handlers.CMD_CS_PLAYER_INFO, {
//        player: player_server.player_info
//    });
//});