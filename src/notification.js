/**
 * Created by yuxiao on 14-9-30.
 */



var notification = {
    _signals: [],

    _findSignal: function(eEvent) {
        var i, signal;

        for(i = this._signals.length; i--;) {
            signal = this._signals[i];
            if(signal.event === eEvent) {
                return signal;
            }
        }
        return null;
    },

    /**
     * 创建一个信号与监听函数的绑定
     * @param {Number} [eEvent] 事件id（也可使用字符串）。
     * @param {Function} [fnListener] 信号处理函数.
     * @param {Object} [oTarget] 信号处理函数的对象。
     * @return {Object} 返回一个描述信号与处理函数的绑定对象，作为移除绑定的句柄使用。
     */
    createBinding: function(eEvent, fnListener, oTarget) {
        // find signal
        var signal = this._findSignal(eEvent);

        // find unused signal
        if(signal === null) {
            signal = this._findSignal(null);
        }

        // create new signal
        if(signal === null) {
            signal = new signals.Signal();
            this._signals.push(signal);
        }

        // bind listener
        if(signal) {
            signal.event = eEvent;
            return signal.add(fnListener, oTarget);
        }
    },

    /**
     * 移除信号的绑定函数
     * @param {Object|Array} [oBinding] createSignalBinding返回的对象。
     */
    removeBinding: function(oBinding) {
        var bindings = oBinding instanceof Array ? oBinding : [oBinding];

        for(var i = bindings.length; i--;) {
            var one = bindings[i],
                signal = one.getSignal();

            one.detach();

            if(signal.getNumListeners() == 0) {
                signal.event = null;
            }
        }
    },

    /**
     * 发送信号
     * @param {Number} [eEvent] 事件id。
     */
    emit: function(eEvent) {
        var signal = this._findSignal(eEvent);
        if(signal) {
            signal.dispatch.apply(this, arguments);
        }
    }
};

notification.event = {
    HEART_BEAT: 1,
    GM_CMD: 2,
    ERROR_MSG: 3,

    LOGIN: 90,
    LOGIN_RESULT: 91,
    INIT_BEGIN: 92,
    INIT_END: 93,
    INIT_PROGRESS: 94,

    PLAYER_LEVEL_UP: 98,
    PLAYER_INFO: 99,

    MAP: 100,
    MAP_MAP_INFO: 101,

    SHOP: 200,
    SHOP_BUY_RESULT: 201,

    SKILL: 300,
    SKILL_INFO: 301,

    EQUIP: 400,
    EQUIP_SLOT_INFO: 401,
    EQUIP_SLOT_UPGRADE_RESULT: 402,
    EQUIP_EQUIP_ITEM: 403,
    EQUIP_UNEQUIP_ITEM: 404,
    EQUIP_PROPERTY_CHANGE: 405,

    ITEM: 500,
    ITEM_INFO: 501,

    BATTLE: 600,
    BATTLE_MAP_RESULT: 601,
    BATTLE_FINISH_RESULT: 602,
    BATTLE_USE_ITEM_RESULT:603,
    BATTLE_ADD_SKILL_EFFECT:604,
    BATTLE_DEL_SKILL_EFFECT: 605,
    BATTLE_HERO_REVIVE : 606,
    BATTLE_ENDLESS_FINISH : 607,

    BATTLE_ENDLESS_BUY_FINISH : 608,

    SKIN: 700,
    SKIN_INFO: 701,
    SKIN_CHANGE_RESULT: 702,

    ROLE_ATTACK: 10001,
    ROLE_HIT: 10002,
    ROLE_DIE: 10003,
    ROLE_DISAPPEAR: 10004,
    ITEM_DISAPPEAR: 10005,

    PHYSICAL_PAUSE: 11001,
    PHYSICAL_QUAKE: 11002,

    THROW_UPDATE : 12001,

    GET_LOGIN_REWARD : 13001,
    OPEN_LOGIN_REWARD : 13002,
    GET_LOGIN_RESULT : 13003,
    GET_VIP_REWARD : 13004,

    REFRESH_GIFT_INFO : 13010,
    RESTART_GAME : 13020
};


