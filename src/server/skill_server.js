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
    },

    end: function() {

    },

    flush: function() {
        database.commit("skill_info", this.skill_info);
    }
};


server.registerCallback(net_protocol_handlers.CMD_CS_SKILL_UP, function(obj) {
    LOG("CMD_CS_SKILL_UP");
    var info = _.findWhere(skill_server.skill_info, {skill_id: obj.skill_id});
    if(info == undefined) {
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    if(info.level >= player_server.player_info.level) {
        server.sendError(net_error_code.ERR_SKILL_LEVEL_LIMIT);
        return;
    }

    // skill config
    var config = configdb.skill[info.skill_id];
    if(config == undefined) {
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    // skill up config
    config = configdb.skillup[config.skillup_id + info.level - 1];
    if(config == undefined || config.skill_id != info.skill_id) {
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    // pay out money
    if(!player_server.changeGold(-config.cost)) {
        return;
    }

    // update skill info
    info.level += 1;
    server.send(net_protocol_handlers.CMD_SC_SKILL_INFO, {
        skills: [info]
    });

    // send result
    server.send(net_protocol_handlers.CMD_SC_SKILL_UP_RESULT, {
        result: 0
    });
});