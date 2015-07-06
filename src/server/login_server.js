/**
 * Created by yuxiao on 15/5/14.
 */


var login_server = {
    start: function() {

    },

    end: function() {

    },

    flush: function() {
    },

    sync: function() {

    }
};

server.registerCallback(net_protocol_handlers.CMD_CS_AUTH, function(obj) {
    LOG("CMD_CS_AUTH");
    LOG(obj.token);

    // start player server
    server_manager.flush();
    server_manager.end();
    server_manager.start();

    server.send(net_protocol_handlers.CMD_SC_INIT_BEGIN);

    // player info
    server.send(net_protocol_handlers.CMD_CS_PLAYER_INFO, {
        player: player_server.player_info
    });

    // map info
    server.send(net_protocol_handlers.CMD_SC_MAP_INFO, {
        maps: map_server.map_info
    });

    // skill info
    server.send(net_protocol_handlers.CMD_SC_SKILL_INFO, {
        skills: skill_server.skill_info
    });

    // equip slot info
    server.send(net_protocol_handlers.CMD_SC_EQUIP_SLOT_INFO, {
        slots: equip_server.equip_info
    });

    // bag info
    server.send(net_protocol_handlers.CMD_SC_ITEM_INFO, {
        items: bag_server.bag_info
    });

    // skin info
    server.send(net_protocol_handlers.CMD_SC_SKIN_INFO, {
        skins: skin_server.skin_info.skins,
        use_skin: skin_server.skin_info.use_skin
    });

    //gift info
    server.send(net_protocol_handlers.CMD_SC_BUY_GIFT_RESULT,{
        result : 0,
        gift_type_data : gift_server.gift_info
    });

    //battle endless info
    server.send(net_protocol_handlers.CMD_SC_ENDLESS_MAX_ROUND,{
        endless_round : battle_server.battle_info.endlessRound
    });

    //guide index init
    server.send(net_protocol_handlers.CMD_SC_UPDATE_GUIDE_INFO,{
        guide_info : guide_server.guide_info
    })

    //更新当天是否更新了VIP功能
    server.send(net_protocol_handlers.CMD_SC_VIP_IS_GET_INFO,{
        get_done :login_reward_server.getCurDailyVipIsGetDone()
    })

    server.send(net_protocol_handlers.CMD_SC_INIT_END);
});

