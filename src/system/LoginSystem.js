/**
 * Created by yuxiao on 15/5/14.
 */


var LoginSystem = SystemBase.extend({
    ctor: function () {
        this.account = "";
    },

    onInit: function () {
        net_protocol_handlers.ON_CMD_SC_INIT_BEGIN = this.onPlayerInitBegin.bind(this);
        net_protocol_handlers.ON_CMD_SC_INIT_END = this.onPlayerInitEnd.bind(this);
        net_protocol_handlers.ON_CMD_SC_LOGIN_RESULT = this.onLoginResult.bind(this);
    },

    onFinalize: function () {
        net_protocol_handlers.ON_CMD_SC_INIT_BEGIN = null;
        net_protocol_handlers.ON_CMD_SC_INIT_END = null;
        net_protocol_handlers.ON_CMD_SC_LOGIN_RESULT = null;
    },

    login: function(type, user, pass) {
        if(type == LoginSystem.LoginType.UserPass) {
            net_protocol_handlers.SEND_CMD_CS_LOGIN_WITH_USER_PASS({
                username: user,
                password: pass
            });
        }
        else if(type == LoginSystem.LoginType.Identifier) {
            net_protocol_handlers.SEND_CMD_CS_LOGIN_WITH_IDENTIFIER({
                identifier: user
            });
        }
    },

    onLoginResult: function(obj) {
        if(obj.result == 0) {
            this.account = obj.account;
            sdk_manager.sendSdkCommand("TalkingDataGA", "setAccount", this.account);

            this.authorize(obj.token);
        }
        else {
            this.account = "";
        }
        notification.emit(notification.event.LOGIN_RESULT);
    },

    logout: function() {
        SystemManager.end();
        server_manager.end();
    },

    authorize: function(token) {
        net_protocol_handlers.SEND_CMD_CS_AUTH({
            token: token
        });
    },

    onPlayerInitBegin: function() {
        LOG("onPlayerInitBegin");
        SystemManager.start();
        notification.emit(notification.event.INIT_BEGIN);
    },

    onPlayerInitEnd: function() {
        LOG("onPlayerInitEnd");
        notification.emit(notification.event.INIT_END);
    }
});

LoginSystem.instance = new LoginSystem();
LoginSystem.instance.onInit();


LoginSystem.LoginType = {
    UserPass: 1,
    Identifier: 2
};

