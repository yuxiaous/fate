/**
 * Created by yuxiao on 15/6/16.
 */


var skin_server = {
    start: function() {
        this.skin_info = database.checkout("skin_info", {
            use_skin: 101,
            skins: [
                {skin_id: 101}
            ]
        });

        this.update = [];
        this.update_use_skin = 0;
    },

    end: function() {

    },

    sync: function() {
        if(this.update.length > 0 || this.update_use_skin != 0) {
            LOG("skin_server.sync");

            database.commit("skin_info", this.skin_info);
            server.send(net_protocol_handlers.CMD_SC_SKIN_INFO, {
                skins: this.update,
                use_skin: this.skin_info.use_skin
            });
            this.update = [];
            this.update_use_skin = 0;
        }
    },

    addSkin: function(skin_id) {
        var find = _.findWhere(this.skin_info.skins, {skin_id: skin_id});
        if(find != undefined) {
            return false;
        }

        var new_skin = {
            skin_id: skin_id
        };
        this.skin_info.skins.push(new_skin);
        this.update.push(new_skin);
        return true;
    },

    changeSkin: function(skin_id) {
        if(skin_id != 0) {
            var find = _.find(skin_server.skin_info.skins, function(skin) {
                return skin.skin_id == skin_id;
            });
            if(find == undefined) {
                server.sendError(net_error_code.ERR_SKIN_NOT_EXIT);
                return false;
            }
        }

        this.skin_info.use_skin = skin_id;
        this.update_use_skin = skin_id;
        return true;
    }
};

server.registerCallback(net_protocol_handlers.CMD_CS_SKIN_CHANGE, function(obj) {
    LOG("CMD_CS_SKIN_CHANGE");
    if(skin_server.changeSkin(obj.skin_id) == false) {
        return;
    }

    server.send(net_protocol_handlers.CMD_SC_SKIN_CHANGE_RESULT, {
        result: 0
    });
});

