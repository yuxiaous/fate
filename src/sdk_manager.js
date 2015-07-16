/**
 * Created by yuxiao on 15/7/16.
 */


var sdk_manager = {
    sendSdkCommand: function(cmd) {
        jsb.SdkManager.sendSdkCommand(cmd);
    },

    onSdkCommond: function(cmd) {
        LOG("onSdkCommond cmd: "+cmd);
    }
};

jsb.SdkManager.setSdkCommandCallback(sdk_manager.onSdkCommond);
