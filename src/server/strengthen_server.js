/**
 * Created by yuxiao on 15/8/18.
 */


var strengthen_server = {
    start: function() {

    },

    end: function() {

    },

    sync: function() {

    }
};

server.registerCallback(net_protocol_handlers.CMD_CS_EQUIP_STRENGTHEN_IN_BAG, function(obj) {
    LOG("CMD_CS_EQUIP_STRENGTHEN_IN_BAG");

    // result
    server.send(net_protocol_handlers.CMD_SC_EQUIP_STRENGTHEN_RESULT, {
        result: 0
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP, function(obj) {
    LOG("CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP");

    // result
    server.send(net_protocol_handlers.CMD_SC_EQUIP_STRENGTHEN_RESULT, {
        result: 0
    });
});
