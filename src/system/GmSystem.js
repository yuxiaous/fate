/**
 * Created by yuxiao on 15/5/14.
 */


var GmSystem = SystemBase.extend({
    ctor: function () {
        this._super();

        this.history = [];
    },

    onInit: function () {
        this._super();
    },

    onFinalize: function () {
        this._super();
    },

    sendCommand: function(cmd) {
        if(cmd && cmd.length > 0) {
            net_protocol_handlers.SEND_CMD_CS_GM_CMD({
                cmd: cmd
            });

            this.history.push(cmd);
            notification.emit(notification.event.GM_CMD, cmd);
        }
    }
});

