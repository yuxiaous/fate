
var login_reward_server = {
    start: function() {
        this.login_reward_info = database.checkout("login_info", {
            player_id: 101,
            login_time : 0,
            login_index : 0
        });
        this.update = [];
    },

    end: function() {

    },
    
    sync: function() {
        if(this.update.length > 0) {
            database.commit("login_info", this.login_reward_info);
            this.update = [];
        }
    }
};

server.registerCallback(net_protocol_handlers.CMD_CS_LOGIN_REWARD_INFO, function (obj) {
    //login reward
    if(login_reward_server.login_reward_info.login_index == 0){
        login_reward_server.login_reward_info.login_index = 1;
        login_reward_server.login_reward_info.login_time = util.getCurrentDate();
    }
    else{
        if(util.compareTimeWithToday(login_reward_server.login_reward_info.login_time)){
            login_reward_server.login_reward_info.login_index += 1;
            if(login_reward_server.login_reward_info.login_index > 5){
                login_reward_server.login_reward_info.login_index = 1;
            }
            login_reward_server.login_reward_info.login_time = util.getCurrentDate();
        }
        else{
            LOG("not over one day");
            return;
        }
    }

    server.send(net_protocol_handlers.CMD_SC_LOGIN_REWARD_INFO,{
        player_id : login_reward_server.login_reward_info.player_id,
        login_index : login_reward_server.login_reward_info.login_index
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_GET_REWARD, function (obj) {

    if(obj && obj.player_id == 101){
        var tmpDate = login_reward_server.login_reward_info.login_index;
        var curRewardInfo = null;
        _.each(configdb.loginreward, function (reward_) {
            if(reward_.index == tmpDate){
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

        login_reward_server.update.push(obj);

        server.send(net_protocol_handlers.CMD_SC_GET_REWARD_RESULT,{
            result : 0
        })
    }
})