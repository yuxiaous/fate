/**
 * Created by yuxiao on 15/5/21.
 */


var bag_server = {
    start: function() {
        this.bag_info = database.checkout("bag_info", [
            //{ uid: 1, id: 20006, num: 1, type: 1 }
        ]);

        _.each(this.bag_info, function(info, i) {
            info.uid = i + 1;
        });
        this.max_uid = this.bag_info.length;

        this.update = [];
    },

    end: function() {

    },

    flush: function() {
    },

    sync: function() {
        if(this.update.length > 0) {
            LOG("bag_server.sync");

            database.commit("bag_info", this.bag_info);
            server.send(net_protocol_handlers.CMD_SC_ITEM_INFO, {
                items: this.update
            });
            this.update = [];
        }
    },

    addItem: function(id, num) {
        var config = BagSystem.getConfig(id);
        if(config == undefined) {
            return false;
        }
        var stack = config.stack || 1;

        // update exist item
        _.each(this.bag_info, function(info) {
            if(info.id != id) {
                return;
            }

            var remain = stack - info.num;
            if(remain == 0) {
                return;
            }

            if(remain >= num) {
                info.num += num;
                num = 0;
            }
            else {
                info.num += remain;
                num -= remain;
            }

            this.update.push(info);
        }, this);

        // add new item
        while(num > 0) {
            var info = {
                uid: ++this.max_uid,
                id: id,
                num: 0
            };

            if(stack >= num) {
                info.num = num;
                num = 0;
            }
            else {
                info.num = stack;
                num -= stack;
            }

            this.bag_info.push(info);
            this.update.push(info);
        }
        return true;
    },

    reduceItem: function(uid, num) {
        var index = _.findIndex(this.bag_info, function(info) {
            return info.uid == uid
        });
        if(index < 0) {
            LOG("reduceItem error 1");
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        var info = bag_server.bag_info[index];
        if(info == undefined) {
            LOG("reduceItem error 2");
            server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
            return false;
        }

        if(info.num < num) {
            LOG("reduceItem error 3");
            server.sendError(net_error_code.ERR_LESS_ITEM);
            return false;
        }

        info.num -= num;
        this.update.push(info);
        if(info.num == 0) {
            bag_server.bag_info.splice(index, 1);
        }
        return true;
    }
};

server.registerCallback(net_protocol_handlers.CMD_CS_ITEM_SELL, function(obj) {
    LOG("CMD_CS_ITEM_SELL");
    var info = _.findWhere(bag_server.bag_info, { uid: obj.uid });
    if(info == undefined) {
        LOG("CMD_CS_ITEM_SELL error 1");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    var config = BagSystem.getConfig(info.id);
    if(config == undefined) {
        LOG("CMD_CS_ITEM_SELL error 2");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    if(config.price == undefined || config.price == 0) {
        LOG("CMD_CS_ITEM_SELL error 3");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    if(bag_server.reduceItem(obj.uid, obj.num) == false) {
        return;
    }

    var earn = config.price * obj.num;
    player_server.changeGold(earn);
});

