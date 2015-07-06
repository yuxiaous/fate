/**
 * Created by yuxiao on 15/5/12.
 */


var player_server = {
    servers: [],

    start: function() {
        this.player_info = database.checkout("player_info", {
            player_id: 101,
            level: 1,
            exp: 0,
            diamond: 0,
            gold: 0,
            action: 60 ,//行动力,
            superSkillCount : 1     //大技能可以释放的次数
        });

        this.update = null;
    },

    end: function() {

    },

    sync: function() {
        if(this.update != null) {
            LOG("player_server.sync");

            database.commit("player_info", this.player_info);
            server.send(net_protocol_handlers.CMD_CS_PLAYER_INFO, {
                player: this.update
            });
            this.update = null;
        }
    },

    changeGold: function(val) {
        if(val == undefined || val == 0) {
            return;
        }
        if(this.player_info.gold + val < 0) {
            LOG("changeGold error 1");
            server.sendError(net_error_code.ERR_LESS_GOLD);
            return false;
        }
        this.update = this.update || {};

        this.player_info.gold += val;
        this.update.gold = this.player_info.gold;
        return true;
    },
    changeDiamond: function(val) {
        if(val == undefined || val == 0) {
            return;
        }
        if(this.player_info.diamond + val < 0) {
            LOG("changeDiamond error 1");
            server.sendError(net_error_code.ERR_LESS_DIAMOND);
            return false;
        }
        this.update = this.update || {};

        this.player_info.diamond += val;
        this.update.diamond = this.player_info.diamond;
        return true;
    },
    changeExp: function(val) {
        if(val == undefined || val <= 0) {
            return;
        }
        this.update = this.update || {};

        this.player_info.exp += val;
        this.update.exp = this.player_info.exp;

        // check level up
        while(true) {
            var config = configdb.levelup[this.player_info.level];
            if(config) {
                if(this.player_info.exp >= config.exp) {
                    this.player_info.level += 1;
                    this.update.level = this.player_info.level;
                    continue;
                }
            }
            break;
        }
    },
    changeSuperSkillCount : function (val) {
        if(val == undefined || val == 0){
            return;
        }
        if(this.player_info.superSkillCount + val < 0){

            return false;
        }

        this.update = this.update || {};

        this.player_info.superSkillCount += val;
        this.update.superSkillCount = this.player_info.superSkillCount;
        return true;
    }
};


//server.registerCallback(net_protocol_handlers.CMD_CS_GET_PLAYER_INFO, function(obj) {
//    LOG("CMD_CS_GET_PLAYER_INFO")
//    server.send(net_protocol_handlers.CMD_CS_PLAYER_INFO, {
//        player: player_server.player_info
//    });
//});