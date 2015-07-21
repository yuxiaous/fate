/**
 * Created by yuxiao on 15/7/16.
 */


var sdk_manager = {
    sendSdkCommand: function(name, cmd) {
        jsb.SdkManager.sendSdkCommand(name, cmd);
    },

    onSdkCommond: function(name, cmd) {
        LOG("onSdkCommond name: {0}, cmd: {1}".format(name, cmd));

        if(name == "Ktplay") {
            ktplay_helper.onSdkCommond(cmd);
        }
    }
};

jsb.SdkManager.setSdkCommandCallback(sdk_manager.onSdkCommond);



var ktplay_helper = {
    onSdkCommond: function(cmd) {
        var cmds = cmd.split(";");
        if(cmds[0] == "Rewards") {
            var rewards = [];
            _.each(cmds, function(cmd, i) {
                if(i == 0) return;

                var reward = cmd.split("=");
                rewards.push({
                    typeId: reward[0],
                    value: Number(reward[1])
                });
            });
            this.dispatchRewards(rewards);
        }
    },

    dispatchRewards: function(rewards) {
        LOG("dispatchRewards");
        _.each(rewards, function(reward) {
            var types = reward.typeId.split(".");
            var config = configdb[types[0]][types[1]];
            if(config == undefined) {
                return;
            }



        });
    }
};



