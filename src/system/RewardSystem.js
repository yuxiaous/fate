
var RewardSystem = SystemBase.extend({
    ctor: function () {
        this._super();

        //this._isReward = false;
        this._rewardData = null;

        this._isGetVipDone = false;
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_LOGIN_REWARD_INFO = function (obj) {
            //this._isReward = true;
            this._rewardData = obj;
            notification.emit(notification.event.OPEN_LOGIN_REWARD,obj);
        }.bind(this);

        net_protocol_handlers.ON_CMD_SC_GET_REWARD_RESULT = function (obj) {

            notification.emit(notification.event.GET_LOGIN_RESULT);
        }.bind(this);

        net_protocol_handlers.ON_CMD_SC_GET_VIP_REWARD_RESULT = function (obj) {
            LOG("get rewsult vip");
            notification.emit(notification.event.GET_VIP_REWARD);
        }.bind(this);

        net_protocol_handlers.ON_CMD_SC_VIP_IS_GET_INFO = function (obj) {
            LOG("obj get done = " + obj.get_done);
            if(obj && obj.get_done == 0){
                this._isGetVipDone = false;
            }
            else{
                this._isGetVipDone = true;
            }
        }.bind(this);

    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_LOGIN_REWARD_INFO = null;
        net_protocol_handlers.ON_CMD_SC_GET_REWARD_RESULT = null;
        net_protocol_handlers.CMD_SC_GET_VIP_REWARD_RESULT = null;
    },
    
    getLoginRewardDaily : function () {
        //if(!this._isReward){
            net_protocol_handlers.SEND_CMD_CS_LOGIN_REWARD_INFO({
                player_id : 101
            })
       // }
    },

    getCurDayReward : function () {
        net_protocol_handlers.SEND_CMD_CS_GET_REWARD({
            player_id : 101
        })
    },

    getVipIsGetDone : function () {
        if(this._rewardData ){

        }
        return true;
    }


});

RewardSystem.instance = new RewardSystem();
RewardSystem.instance.onInit();

