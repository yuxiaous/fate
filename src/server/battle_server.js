var battle_server = {

    start: function() {
        this.battle_info = database.checkout("battle_info", {
            endlessRound : 0
        });
        this.update = [];
    },

    end: function() {

    },

    sync: function() {
        if(this.update.length > 0) {
            database.commit("battle_info", this.battle_info);
            this.update = [];
        }
    }
};

battle_server.cur_battle_map = 0;
server.registerCallback(net_protocol_handlers.CMD_CS_BATTLE_MAP, function(obj) {
    LOG("CMD_CS_BATTLE_MAP");
    // TODO

    //player_server.player_info.action -=2;
    //player_server.update

    if(player_server.changeAction(2) == false){
        return;
    }

    battle_server.cur_battle_map = obj.map_id;
    server.send(net_protocol_handlers.CMD_SC_BATTLE_MAP_RESULT, {
        result: 0,
        map_id: battle_server.cur_battle_map
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_BATTLE_FINISH, function(obj) {
    if(obj.result != 1) {
        return;
    }

    var max_map = _.max(map_server.map_info, function(info) {
        return info.map_id;
    });

    var is_first_battle = (battle_server.cur_battle_map == max_map.map_id);

    var config = configdb.map[battle_server.cur_battle_map];
    if(config == undefined) {
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    // open map
    if(config.next_map) {
        map_server.openMap([config.next_map]);
    }

    // add resource
    player_server.changeExp(config.gain_exp);
    player_server.changeGold(config.gain_gold);
    player_server.changeDiamond(is_first_battle ? config.gain_diamond : 0);

    // add item
    if(config.gain_item_id_1) {
        bag_server.addItem(config.gain_item_id_1, 1)
    }
    if(config.gain_item_id_2) {
        bag_server.addItem(config.gain_item_id_2, 1)
    }


    // result
    var reward = {};
    reward.exp = config.gain_exp;
    reward.gold = config.gain_gold;
    reward.items = [];
    if( is_first_battle) {
        reward.diamond = config.gain_diamond;
        reward.items = [
            {
                item_id : config.gain_item_id_1 || 0,
                item_num: 1
            },
            {
                item_id : config.gain_item_id_2 || 0,
                item_num: 1
            }
        ];
    }

    // drop item
    var dropItems = BattleSystem.instance._curMapDropItems;
    _.forEach(dropItems, function (dropItem_) {
        if(dropItem_){
            var dropItemConfig = configdb.item[dropItem_.item_id];
            if(dropItemConfig){
                if(dropItemConfig.goldtype == DroppedItem.ItemType.GoldType){
                    player_server.changeGold(dropItem_.item_num);
                }
                else{
                    bag_server.addItem(dropItem_.item_id,dropItem_.item_num);

                    reward.items.push({
                        item_id : dropItem_.item_id,
                        item_num : dropItem_.item_num
                    });
                }
            }
        }
    },this);

    server.send(net_protocol_handlers.CMD_SC_BATTLE_FINISH_RESULT, {
        result : 1,
        map_id: battle_server.cur_battle_map,
        reward : reward
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_USE_BATTLE_ITEM, function (obj) {
    var info = _.findWhere(bag_server.bag_info, { uid: obj.uid });
    if(info == undefined) {
        LOG("CMD_CS_ITEM_USE error 1");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    var config = configdb.item[info.id];
    if(config == undefined) {
        LOG("CMD_CS_ITEM_USE error 2");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    if(bag_server.reduceItem(obj.uid, obj.num) == false) {
        return;
    }

    var itemResultType = 1;
    switch (config.result) {
        case item_server.ItemUseType.AddLive:
            itemResultType = 4;
            break;
        case item_server.ItemUseType.AddHpPer:
            itemResultType = 1;
            break;
        case item_server.ItemUseType.AddMpPer:
            itemResultType = 2;
            break;
        case item_server.ItemUseType.AddHpMp:
            itemResultType = 3;
            break;
    }
    server.send(net_protocol_handlers.CMD_SC_USE_BATTLE_ITEM_RESULT, {
        result: 0,
        item_type :itemResultType
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_ENDLESS_MAX_ROUND, function (obj) {
    if(obj && obj.endless_round > battle_server.battle_info.endlessRound){

        battle_server.battle_info.endlessRound = obj.endless_round
        battle_server.update.push(obj);

        server.send(net_protocol_handlers.CMD_SC_ENDLESS_MAX_ROUND,{
            endless_round : battle_server.battle_info.endlessRound
        });
    }
});
 
server.registerCallback(net_protocol_handlers.CMD_CS_ENDLESS_BATTLE_END, function (obj) {
    if(obj && obj.endless_round){
        var conf = configdb.endlessround[obj.endless_round];
        if(conf == undefined){
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return;
        }

        // add resource
        player_server.changeExp(conf.gain_exp);
        player_server.changeGold(conf.gain_gold);

        server.send(net_protocol_handlers.CMD_SC_ENDLESS_BATTLE_END,{
            endless_round : obj.endless_round
        });
    }
});

server.registerCallback(net_protocol_handlers.CMD_CS_BATTLE_REVIVE, function (obj) {
    if(obj && obj.player_id == 101){

        if(bag_server.addItem(100007, 3) == false) {
           LOG("add item error");
            return;
        }
        server.send(net_protocol_handlers.CMD_SC_BATTLE_REVIVE,{
            result : 0
        });
    }
})



