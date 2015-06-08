/**
 * Created by yuxiao on 15/5/4.
 */


var Session = cc.Class.extend({
    ctor: function(pipe_in, pipe_out) {
        this.pipe_in = pipe_in;
        this.pipe_out = pipe_out;

        this.recvQueue = [];
        this.sendQueue = [];
        this.callbacks = {};
    },

    beginUpdateTick: function() {
        cc.director.getScheduler().scheduleCallbackForTarget(this, this.updateTick);
    },

    endUpdateTick: function() {
        cc.director.getScheduler().unscheduleCallbackForTarget(this, this.updateTick);
    },

    updateTick: function(dt) {
        this.onRecv();
        this.onHandle();
        this.onSend();
    },

    onRecv: function() {
        _.each(this.pipe_in, function(data) {
            this.recvQueue.push(data);
        }, this);
        this.pipe_in.length = 0;
    },

    onHandle: function() {
        _.each(this.recvQueue, function(data) {
            var code = data[0];
            var callback = this.callbacks[code];
            if (callback != null) {
                callback(data[1]);
            }
        }, this);
        this.recvQueue.length = 0;
    },

    onSend: function() {
        _.each(this.sendQueue, function(data) {
            this.pipe_out.push(data);
        }, this);
        this.sendQueue.length = 0;
    },

    registerCallback: function (code, callback) {
        if(code != 0) {
            this.callbacks[code] = callback;
        }
    },

    send: function(code, packet) {
        this.sendQueue.push([code, packet]);
    }
});

