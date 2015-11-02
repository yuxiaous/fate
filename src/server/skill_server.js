/**
 * Created by yuxiao on 15/5/14.
 */


var skill_server = {
    start: function() {
        this.skill_info = database.checkout("skill_info", [
            { index: 0, skill_id: 10106, level: 1 },
            { index: 1, skill_id: 10107, level: 1 },
            { index: 2, skill_id: 10108, level: 1 },
            { index: 3, skill_id: 10109, level: 1 }
        ]);
        _.each(this.skill_info, function(info, i) {
            info.index = i;
        });


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

    skillUp: function(index) {
        var info = _.findWhere(this.skill_info, {index: index});
        if(info == undefined) {
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
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

        if(config.next == undefined) {
            server.sendError(net_error_code.ERR_TOP_LEVEL);
            return false;
        }
        var next_config = configdb.skillup[config.next];
        if(next_config == undefined || next_config.skill_id != info.skill_id) {
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }


        if(next_config.req_level > player_server.player_info.level) {
            server.sendError(net_error_code.ERR_LESS_LEVEL);
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
    },

    changeSkills: function(idx, skill_id) {
        var info = this.skill_info[idx];
        if(info != undefined) {
            info.skill_id = skill_id;
            this.update.push(info);
        }
    },

    changeToSaber: function() {
        this.changeSkills(0, 10106);
        this.changeSkills(1, 10107);
        this.changeSkills(2, 10108);
        this.changeSkills(3, 10109);
    },

    changeToArcher: function() {
        this.changeSkills(0, 10201);
        this.changeSkills(1, 10202);
        this.changeSkills(2, 10203);
        this.changeSkills(3, 10204);
    }
};


server.registerCallback(net_protocol_handlers.CMD_CS_SKILL_UP, function(obj) {
    LOG("CMD_CS_SKILL_UP");
    if(skill_server.skillUp(obj.skill_idx) == false) {
        return;
    }

    mission_server.count(mission_server.Type.SkillUpgrage);

    // send result
    server.send(net_protocol_handlers.CMD_SC_SKILL_UP_RESULT, {
        result: 0
    });
});