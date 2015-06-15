/**
 * Created by yuxiao on 15/5/14.
 */


var login_server = {

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

    server.send(net_protocol_handlers.CMD_SC_INIT_END);
});
