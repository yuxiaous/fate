//
// net manager
//


var socketPipe = socketPipe || {};
socketPipe.sc = socketPipe.sc || [];
socketPipe.cs = socketPipe.cs || [];


var net = {
    //_ConnectCallbackStru: null,
    //_DisConnectCallbackStru: null,

    start: function () {
        this.session = new Session(socketPipe.sc, socketPipe.cs);
        this.session.beginUpdateTick();
    },

    end: function () {
        this.session.endUpdateTick();
        this.session = null;
    },

    //IsActive : function(){
    //    return this.gameSession.IsActive()
    //},

    //ConnectSock: function (strip, wport, callback, target, disconnect_callback_, disconnect_target_) {
    //    this.setConnnectCallback(callback, target);
    //
    //    // 检查是否已经连接
    //    if(this._ip == strip && this._port == wport && this.gameSession.IsActive())
    //    {
    //        this.OnConnectCallback(0)
    //        return
    //    }
    //
    //    this._ip = strip;
    //    this._port = wport;
    //
    //    this.gameSession.ConnectNewSock(strip, wport);
    //
    //    this.SetDisconnectCallback(disconnect_callback_, disconnect_target_);
    //},

    //断开游戏服务器
    //ReleaseSock: function () {
    //    this._DisConnectCallbackStru = null;
    //    this.gameSession.ReleaseGameSock();
    //    //this._ClearSlotListener()
    //},

    //setConnnectCallback: function (callback, target) {
    //    if (callback == null) {
    //        this._ConnectCallbackStru = null;
    //    } else {
    //        this._ConnectCallbackStru = {};
    //        this._ConnectCallbackStru._callback = callback;
    //        this._ConnectCallbackStru._target = target;
    //    }
    //},

    //SetDisconnectCallback: function (callback, target) {
    //    if (callback == null || target == null) {
    //        this._DisConnectCallbackStru = null;
    //    }
    //    else {
    //        this._DisConnectCallbackStru = {};
    //        this._DisConnectCallbackStru._callback = callback;
    //        this._DisConnectCallbackStru._target = target;
    //    }
    //},

    // 网络连接回调
    //OnConnectCallback: function (parm) {
    //    afk.log("Net OnConnectCallback  =====" + this._ConnectCallbackStru);
    //    if (this._ConnectCallbackStru != null) {
    //        if (parm == 0) {      //连接网络成功  开启发包机制
    //        }
    //        var _callback = this._ConnectCallbackStru._callback;
    //        var _target = this._ConnectCallbackStru._target;
    //        _callback.call(_target, parm);
    //        this._ConnectCallbackStru = null;
    //    }
    //},

    //DisConnectCallback: function (parm, _bool) {
    //    afk.log("Net DisConnectCallback  =====" + this._DisConnectCallbackStru);
    //
    //    if (this._DisConnectCallbackStru != null) {
    //        var _callback = this._DisConnectCallbackStru._callback;
    //        var _target = this._DisConnectCallbackStru._target;
    //        _callback.call(_target, parm);
    //        this._DisConnectCallbackStru = null;
    //    }
    //},

    send: function (code, obj) {
        // debug, print packet content
        //LOG("Net Send, code: " + code);
        if(code != 0) {
            // serialize
            var data = obj;
            // send package
            this.session.send(code, data);
        }
    },

    registerCallback: function (code, callback, target) {
        if(code != 0 && this.session) {
            if(callback == null) {
                this.session.registerCallback(code, null);
            }
            else {
                this.session.registerCallback(code, function(data) {
                    //LOG("Net Recv, code: " + code);
                    // deserialize
                    var obj = data;

                    if(target == null) {
                        callback(obj);
                    }
                    else {
                        callback.call(target, obj);
                    }
                })
            }
        }
    }
};

// ErrorCode for Disconnect
net.EN_NEC_SUCC = 0;           //  网络连接成功
net.EN_NEC_DIS_TIMEOUT = 1;	//	连接超时
net.EN_NEC_DIS_UNABLE = 2;	    //	无法连接到服务器
net.EN_NEC_DIS_SYSERR = 3;	    //	系统异常
net.EN_NEC_DIS_NONET = 4;      //  没网


net.EN_NEC_DIS_ACTIVE = 10;	    //	主动断开连接
net.EN_NEC_DIS_BREAK = 11;	    //	网络连接中断
net.EN_NEC_DIS_SERVER = 12;	    //	服务器主动断开连接
net.EN_NEC_DIS_TIMEOUT_1 = 13;       //  掉线


// init net
net.start();



//// net 解包回调函数
//var OnNetPacketHandle = function (code, packet) {
//    net.onRecv(code, packet);
//};
//
//// 网络连接成功回调
//var OnNetConnectCallback = function (parm) {
//    net.OnConnectCallback(parm);
//};
//
//// 断开网络连接回调
//var OnNetDisconnectCallback = function (parm) {
//    net.DisConnectCallback(parm);
//};

