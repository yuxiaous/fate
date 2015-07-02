
var GiftSystem = SystemBase.extend({
    ctor: function () {
        this._super();
        this._giftData = null;

    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_BUY_GIFT_RESULT = this.refreshGiftInfo.bind(this);

        cc.director.getScheduler().schedule(this.updateTime,this,1.0,cc.REPEAT_FOREVER,0,false,"refresTime");
    },

    refreshGiftInfo : function (obj) {
       // LOG("update gift result");
        this._giftData = obj.gift_type_data;
        //LOG("gift info = 1 = " + this._giftData[0].buy_num);
        //LOG("gift info = 2 = " + this._giftData[1].buy_num);
        //LOG("gift info = 3 = " + this._giftData[2].buy_num);
        //LOG("gift info = 4 = " + this._giftData[3].buy_num);
        notification.emit(notification.event.REFRESH_GIFT_INFO);
    },

    updateTime : function () {
        _.each(this._giftData, function (giftInfo_) {
            if(giftInfo_ && giftInfo_.count_down > 0){
                giftInfo_.count_down -= 1;
            }
            else{

            }
        },this)
    },

    onFinalize: function () {
        this._super();

        LOG(" ON FINALIZE");
        this.sendGiftCountDown();
        net_protocol_handlers.ON_CMD_SC_BUY_GIFT_RESULT = null;
        cc.director.getScheduler().unschedule("refresTime",this);
    },
    
    buyGiftItem : function (type_) {
        net_protocol_handlers.SEND_CMD_CS_BUY_GIFT({
            gift_type : type_
        });
    },

    sendGiftCountDown : function () {
        LOG("SEND GIFT COUNT DOWN");
        var sendData = [];
        _.each(this._giftData, function (giftInfo_) {
            sendData.push({
                giftType : giftInfo_.giftType,
                count_down : giftInfo_.count_down
            });
        },this)

        net_protocol_handlers.SEND_CMD_CS_UPDATE_GIFT_TIME({
            gift_type_data : sendData
        });
    },

    randomSellGiftPanel : function () {
        var giftData = GiftSystem.instance._giftData;

        var tmpGiftData = null;
        do{
            var idx = _.random(1,4);
            _.each(giftData, function (GD_) {
                if(GD_.giftType == idx){
                    tmpGiftData = GD_;
                }
            },this)
        }while(tmpGiftData.buy_num > 0 || tmpGiftData.giftType != GiftSystem.GiftType.ZhiZun);

        return tmpGiftData.giftType;
    },

    getGiftCountTime : function (giftType_) {
        var time = 0;
        _.each(this._giftData, function (giftInfo_) {
            if(giftInfo_.giftType == giftType_){
                time = giftInfo_.count_down;
            }
        },this)
        return time;
    },

    changeStringToTimeStyle : function (countTime_) {
        function changeStr(str_){
            if(str_ < 10){
                str_ += "0"
            }
            return str_;
        }

        var endStr = "00 : 00";
        if(countTime_ < 60){
            countTime_ = Math.floor(countTime_);
            endStr = "00 : " + changeStr(countTime_);
        }
        else if(countTime_ > 60 && countTime_ < 3600){
            var secondTime = countTime_ % 60;
            var minuteTime = countTime_ / 60;
            secondTime = Math.floor(secondTime);
            minuteTime = Math.floor(minuteTime);

            endStr = "" + changeStr(minuteTime) + " : " + changeStr(secondTime);
        }
        else{
            var hourTime   = countTime_ / 3600;
            var minuteTime = (countTime_ % 3600) / 60;
            var secondTime = (countTime_ % 3600) % 60

            secondTime = Math.floor(secondTime);
            minuteTime = Math.floor(minuteTime);
            hourTime = Math.floor(hourTime);

            endStr = "" + changeStr(hourTime) + " : " + changeStr(minuteTime) + " : " + changeStr(secondTime);
        }
        return endStr;
    }
});

GiftSystem.GiftType = {
    ZhuangBei : 1,
    WuQi : 2,
    ZhiZun : 3,
    Vip : 4,

    DaBaoJian : 5
}
