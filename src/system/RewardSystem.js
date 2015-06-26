
var RewardSystem = SystemBase.extend({
    ctor: function () {
        this._super();

        this._isReward = false;
        this._rewardData = null;
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_LOGIN_REWARD_INFO = function (obj) {
            this._isReward = true;
            this._rewardData = obj;
            notification.emit(notification.event.OPEN_LOGIN_REWARD,obj);
        }.bind(this);

    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_LOGIN_REWARD_INFO = null;
    },
    
    getLoginRewardDaily : function () {
        if(!this._isReward){
            net_protocol_handlers.SEND_CMD_CS_LOGIN_REWARD_INFO({
                player_id : 101
            })
        }
    }
});

RewardSystem.instance = new RewardSystem();
RewardSystem.instance.onInit();

