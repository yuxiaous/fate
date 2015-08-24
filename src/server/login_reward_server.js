
var login_reward_server = {
    start: function() {
        this.login_reward_info = database.checkout("login_info", {
            player_id: 101,
            login_time : 0,
            login_index : 0,

            vip_time : 0,
            vip_index : 0
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
    },
    
    getCurDailyVipIsGetDone : function () {
        if(util.compareTimeWithToday(login_reward_server.login_reward_info.login_time)){
           return 0;
        }
        return 1;
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

    //更新当天是否更新了VIP功能
    server.send(net_protocol_handlers.CMD_SC_VIP_IS_GET_INFO,{
        get_done :login_reward_server.getCurDailyVipIsGetDone()
    })

    server.send(net_protocol_handlers.CMD_SC_LOGIN_REWARD_INFO,{
        player_id : login_reward_server.login_reward_info.player_id,
        login_index : login_reward_server.login_reward_info.login_index,
        vip_time : login_reward_server.login_reward_info.vip_time
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
            else if(curRewardInfo.type == 3){
                bag_server.addItem(curRewardInfo.itemid,curRewardInfo.num);
            }
        }

        login_reward_server.update.push(obj);

        server.send(net_protocol_handlers.CMD_SC_GET_REWARD_RESULT,{
            result : 0
        })
    }
})

server.registerCallback(net_protocol_handlers.CMD_CS_GET_VIP_REWARD, function (obj) {
    if(obj && obj.player_id == 101){

        var hadBuyVip = false
        _.each(gift_server.gift_info, function (giftInfo_) {
            if(giftInfo_ && giftInfo_.giftType == gift_server.GiftType.Vip && giftInfo_.buy_num > 0){
                hadBuyVip = true;
            }
        },this);

        if(!hadBuyVip){
            LOG(" did not buy vip gift");
            return;
        }

        if(login_reward_server.login_reward_info.vip_index == 0){
            login_reward_server.login_reward_info.vip_index = 1;
            login_reward_server.login_reward_info.vip_time = util.getCurrentDate();
        }
        else{
            if(util.compareTimeWithToday(login_reward_server.login_reward_info.vip_time)){
                LOG("time is done");
                login_reward_server.login_reward_info.vip_index += 1;
                login_reward_server.login_reward_info.vip_time = util.getCurrentDate();
            }
            else{
                LOG("not over one day");
                return;
            }
        }

        //if(util.getChannelId() == GameChannel.Telecom){
        //    player_server.changeGold(20000);
        //}
        //else{
        //    player_server.changeGold(30000);
        //}
        player_server.changeGold(30000);


        login_reward_server.update.push(obj);

        server.send(net_protocol_handlers.CMD_SC_GET_VIP_REWARD_RESULT,{
            result : 0
        })
    }
})