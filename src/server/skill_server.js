/**
 * Created by yuxiao on 15/5/14.
 */


var skill_server = {
    start: function() {
        this.skill_info = database.checkout("skill_info", [
            { skill_id: 10106, level: 1 },
            { skill_id: 10107, level: 1 },
            { skill_id: 10108, level: 1 },
            { skill_id: 10109, level: 1 }
        ]);

        this.update = [];
    },

    end: function() {

    },

    sync: function() {
        if(this.update.length > 0) {
            LOG("skill_server.sync");

            database.commit("skill_info", this.skill_info);
            server.send(net_protocol_handlers.CMD_SC_SKILL_INFO, {
                skills: this.update
            });
            this.update = [];
        }
    },

    skillUp: function(skill_id) {
        var info = _.findWhere(this.skill_info, {skill_id: skill_id});
        if(info == undefined) {
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        if(info.level >= player_server.player_info.level) {
            server.sendError(net_error_code.ERR_SKILL_LEVEL_LIMIT);
            return false;
        }

        // skill config
        var config = configdb.skill[info.skill_id];
        if(config == undefined) {
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        // skill up config
        config = configdb.skillup[config.skillup_id + info.level - 1];
        if(config == undefined || config.skill_id != info.skill_id) {
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        // pay out money
        if(player_server.changeGold(-config.cost) == false) {
            return false;
        }

        // update skill info
        info.level += 1;
        this.update.push(info);
        return true;
    }
};


server.registerCallback(net_protocol_handlers.CMD_CS_SKILL_UP, function(obj) {
    LOG("CMD_CS_SKILL_UP");
    if(skill_server.skillUp(obj.skill_id) == false) {
        return;
    }

    // send result
    server.send(net_protocol_handlers.CMD_SC_SKILL_UP_RESULT, {
        result: 0
    });
});