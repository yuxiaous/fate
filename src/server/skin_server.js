/**
 * Created by yuxiao on 15/6/16.
 */


var skin_server = {
    start: function() {
        this.skin_info = database.checkout("skin_info", {
            use_skin: 0,
            skins: [
                //{skin_id: 0}
            ]
        });
    },

    end: function() {

    },

    flush: function() {
        database.commit("skin_info", this.skill_info);
    },

    addSkin: function(skin_id) {
        var find = _.find(this.skin_info.skins, function(skin) {
            return skin.skin_id == skin_id;
        });
        if(find) {
            return;
        }

        var new_skin = {
            skin_id: skin_id
        };
        this.skin_info.skins.push(new_skin);

        server.send(net_protocol_handlers.CMD_SC_SKIN_INFO, {
            skins: [new_skin]
        });
    }
};

server.registerCallback(net_protocol_handlers.CMD_CS_SKIN_CHANGE, function(obj) {
    LOG("CMD_CS_SKIN_CHANGE");
    var skin_id = obj.skin_id;

    if(skin_id != 0) {
        var find = _.find(this.skin_info.skins, function(skin) {
            return skin.skin_id == skin_id;
        });
        if(find == undefined) {
            server.sendError(net_error_code.ERR_SKIN_NOT_EXIT);
            return;
        }
    }

    skin_server.skin_info.use_skin = skin_id;
    server.send(net_protocol_handlers.CMD_CS_SKIN_CHANGE_RESULT, {
        result: 0,
        skin_id: skin_server.skin_info.use_skin
    });
});

