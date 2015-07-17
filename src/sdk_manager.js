/**
 * Created by yuxiao on 15/7/16.
 */


var sdk_manager = {
    sendSdkCommand: function(name, cmd) {
        jsb.SdkManager.sendSdkCommand(name, cmd);
    },

    onSdkCommond: function(name, cmd) {
        LOG("onSdkCommond name: {0}, cmd: {1}".format(name, cmd));
    }
};

jsb.SdkManager.setSdkCommandCallback(sdk_manager.onSdkCommond);
