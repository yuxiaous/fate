/**
 * Created by yuxiao on 15/7/16.
 */


var sdk_manager = {
    charge: function(order, id) {
        if(id == undefined) id = "";
        
        LOG("sdk_manager.charge, order: {0}, id: {1}".format(order, id));
        if(order == undefined || order.length == 0) {
            MessageBoxOk.show("购买订单");
            return;
        }
        jsb.SdkManager.charge(order, id);
    },

    sendSdkCommand: function(calzz, method, param) {
        if(param == undefined) param = "";
        jsb.SdkManager.sendSdkCommand(calzz, method, param);
    },

    onSdkCommond: function(calzz, method, param) {
        LOG("onSdkCommond calss: {0}, method: {1}, param: {2}".format(calzz, method, param));

        if(calzz == "Ktplay") {
            if(method == "dispatchRewards") {
                ktplay_helper.dispatchRewards(param);
            }

        }
    }
};

jsb.SdkManager.setSdkCommandCallback(sdk_manager.onSdkCommond);



var ktplay_helper = {
    dispatchRewards: function(param) {
        LOG("dispatchRewards");
        var config_type;
        var config_id;
        var value;

        _.each(param.split(","), function(reward, i) {
            if(i % 2 == 0) {
                var config_param = reward.split(".");
                config_type = config_param[0];
                config_id = config_param[1];
                return;
            }
            else {
                value = Number(reward);
            }

            switch (config_type) {
                case "item":
                    config = configdb.item[config_id];
                    if(config) {
                        if(config.result == 2) {
                            player_server.changeGold(value);
                        }
                        else if(config.result == 3) {
                            player_server.changeDiamond(value);
                        }
                        else {
                            bag_server.addItem(config_id, value);
                        }
                    }
                    break;

                case "equip":
                    bag_server.addItem(config_id, value);
                    break;

                case "skin":
                    skin_server.addSkin(config_id);
                    break;
            }
        });
    }
};



