/**
 * Created by yuxiao on 15/5/4.
 */


var socketPipe = socketPipe || {};
socketPipe.sc = socketPipe.sc || [];
socketPipe.cs = socketPipe.cs || [];

var server = {
    start: function() {
        this.session = new Session(socketPipe.cs, socketPipe.sc);
        this.session.beginUpdateTick();
    },

    end: function () {
        this.session.endUpdateTick();
        this.session = null;
    },

    send: net.send,
    registerCallback: net.registerCallback,

    sendError: function(code) {
        this.send(net_protocol_handlers.CMD_SC_ERROR_CODE, {
            code: code
        });
    }
};

server.start();

