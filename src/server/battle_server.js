var battle_server = {
    start: function() {
        this.battle_info = database.checkout("battle_info", [

        ]);
    },

    end: function() {

    },

    flush: function() {
        database.commit("battle_info", this.battle_info);
    }
};

battle_server.cur_battle_map = 0;
server.registerCallback(net_protocol_handlers.CMD_CS_BATTLE_MAP, function(obj) {
    LOG("CMD_CS_BATTLE_MAP");
    // TODO


    battle_server.cur_battle_map = obj.map_id;
    server.send(net_protocol_handlers.CMD_SC_BATTLE_MAP_RESULT, {
        result: 0,
        map_id: battle_server.cur_battle_map
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_BATTLE_FINISH, function(obj) {
    var curIsWin = 0;
    var gainItem = {
        items : []
    };

    if(obj.result == 1) {
        var config = configdb.map[battle_server.cur_battle_map];
        if(config && config.next_map) {
            map_server.openMap([config.next_map]);

            gainItem.gold = config.gain_gold || 0 ;
            gainItem.exp  = config.gain_exp || 0 ;
            _.each(
                ["gainItemId_1",
                 "gainItemId_2"], function (itemTitle_) {
                    if(config[itemTitle_]){
                        gainItem.items.push(
                            {
                                item_id : config[itemTitle_],
                                item_num: 1
                            }
                        )
                    }
                }
            );
                        
        }
        curIsWin = 1;
    }
    else if(obj.result == 2){
        curIsWin = 2;
    }
                        
                        
    if(curIsWin == 1){
        _.each(gainItem.items,function(item_){
           if(item_ && item_.item_id != 0){
               bag_server.addItem(item_.item_id,1);
           }
        },this);

        server.send(net_protocol_handlers.CMD_CS_PLAYER_INFO,{
            player:{
                gold: player_server.player_info.gold += gainItem.gold,
                exp : player_server.player_info.exp += gainItem.exp
            }
        });
    }

    server.send(net_protocol_handlers.CMD_SC_BATTLE_FINISH_RESULT, {
        result : curIsWin,
        map_id: battle_server.cur_battle_map,
        reward : gainItem
        //reward : {
        //    exp: 0,
        //    gold: 0,
        //    diamond: 0,
        //    items: [
        //        {
        //            item_id: 0,
        //            item_num: 0
        //        },
        //        {
        //            item_id: 0,
        //            item_num: 0
        //        }
        //    ]
        //}
    });
});
