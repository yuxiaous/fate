/**
 * Created by yuxiao on 15/5/14.
 */


var LoginSystem = SystemBase.extend({
    ctor: function () {

    },

    onInit: function () {
        net_protocol_handlers.ON_CMD_SC_INIT_BEGIN = this.onPlayerInitBegin.bind(this);
        net_protocol_handlers.ON_CMD_SC_INIT_END = this.onPlayerInitEnd.bind(this);

    },

    onFinalize: function () {
        net_protocol_handlers.ON_CMD_SC_INIT_BEGIN = null;
        net_protocol_handlers.ON_CMD_SC_INIT_END = null;
    },

    login: function() {

    },

    logout: function() {
        SystemManager.end();
    },

    authorize: function(token) {
        net_protocol_handlers.SEND_CMD_CS_AUTH({
            token: token
        });
    },

    onPlayerInitBegin: function() {
        LOG("onPlayerInitBegin")
        SystemManager.start();
        notification.emit(notification.event.INIT_BEGIN);
    },

    onPlayerInitEnd: function() {
        LOG("onPlayerInitEnd")
        notification.emit(notification.event.INIT_END);
    }
});

LoginSystem.instance = new LoginSystem();
LoginSystem.instance.onInit();

