
var login_reward_server = {
    start: function() {
        this.login_reward_info = database.checkout("login_info", {
            player_id: 101,
            login_index : 0
        });
    },

    end: function() {

    },

    flush: function() {
        database.commit("login_info", this.login_reward_info);
    }
};

server.registerCallback(net_protocol_handlers.CMD_CS_LOGIN_REWARD_INFO, function (obj) {
    //login reward
    if(login_reward_server.login_reward_info.login_index != 0){
        return;
    }

    var tmpData = 1;
    login_reward_server.login_reward_info.login_index = tmpData;

    var curRewardInfo = null;
    _.each(configdb.loginreward, function (reward_) {
        if(reward_.index == tmpData){
            curRewardInfo = reward_;
        }
    });

    if(curRewardInfo == null){
        return;
    }
    else{
        if(curRewardInfo.type == 1){
            player_server.changeGold(curRewardInfo.num);
        }
        else if(curRewardInfo.type == 2){
            player_server.changeDiamond(curRewardInfo.num);
        }
    }

    server.send(net_protocol_handlers.CMD_SC_LOGIN_REWARD_INFO,{
        player_id : login_reward_server.login_reward_info.player_id,
        login_index : login_reward_server.login_reward_info.login_index
    });
});