var operator_server = {
    start: function() {

    },

    end: function() {

    }
};
server.registerCallback(net_protocol_handlers.CMD_CS_BUY_SUPER_SKILL_COUNT, function(obj) {
    if(!player_server.changeSuperSkillCount(3)){
        return;
    }

    //server.send(net_protocol_handlers.CMD_SC_BUY_SUPER_SKILL_COUNT_RESULT, {
    //    player_id : player_server.player_info.player_id,
    //    count : player_server.player_info.superSkillCount,
    //    result: 0
    //});
});

server.registerCallback(net_protocol_handlers.CMD_CS_USE_SUPER_SKILL, function (obj) {
    if(obj.player_id  != 101){
        return;
    }

    if(player_server.player_info.superSkillCount > 0){
        player_server.player_info.superSkillCount -= 1;
    }
    else{
        player_server.player_info.superSkillCount = 0;
    }
})
