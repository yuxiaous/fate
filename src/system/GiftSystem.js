
var GiftSystem = SystemBase.extend({
    ctor: function () {
        this._super();
        this._giftData = null;

    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_BUY_GIFT_RESULT = this.refreshGiftInfo.bind(this);
        //cc.director.getScheduler().schedule(this.updateTime_1,this,2.0,cc.REPEAT_FOREVER,0,false,"refresTime");
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

    //updateTime_1 : function () {
    //    LOG("GIFT INFO TYPE ==== f");
    //    _.each(this._giftData, function (giftInfo_) {
    //        //LOG("GIFT INFO TYPE = " + giftInfo_.giftType);
    //        if(giftInfo_ && giftInfo_.count_down > 0){
    //            LOG("GIFT INFO TYPE = " + giftInfo_.giftType);
    //            giftInfo_.count_down = giftInfo_.count_down - 1.0;
    //            //LOG("gift info type = " + giftInfo_.count_down);
    //        }
    //        else{
    //
    //        }
    //    },this)
    //},

    onFinalize: function () {
        this._super();

        LOG(" ON FINALIZE");
        this.sendGiftCountDown();
        net_protocol_handlers.ON_CMD_SC_BUY_GIFT_RESULT = null;
        cc.director.getScheduler().unschedule("refresTime",this);
    },
    
    buyGiftItem : function (type_) {
        //net_protocol_handlers.SEND_CMD_CS_BUY_GIFT({
        //    gift_type : type_
        //});
    },

    getGiftItemTime : function () {
        net_protocol_handlers.SEND_CMD_CS_GET_GIFT_TIME({
            play_id : 101
        })
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
        var needReRandom = true;
        do{
            needReRandom = true;
            var idx = _.random(1,4);
            _.each(giftData, function (GD_) {
                if(GD_.giftType == idx){
                    tmpGiftData = GD_;
                }
            },this)
            if(tmpGiftData.giftType == GiftSystem.GiftType.ZhiZun){
                needReRandom = false;
            }
            else{
                if(tmpGiftData.buy_num <= 0){
                    needReRandom = false;
                }
            }
        }while(needReRandom);
        return tmpGiftData.giftType;
    },

    getGiftCountTime : function (giftType_) {
        var time = 0;
        _.each(this._giftData, function (giftInfo_) {
            if(giftInfo_.giftType == giftType_){
                time = giftInfo_.count_down -1;
            }
        },this)
        return time;
    },

    getGiftBuyNumWith : function (giftType_) {
        var num = 0;
        _.each(this._giftData, function (giftInfo_) {
            if(giftInfo_.giftType == giftType_){
                num = giftInfo_.buy_num;
            }
        },this)

        return num;
    },

    changeStringToTimeStyle : function (countTime_) {
        function changeStr(str_){
            if(str_ < 10){
                str_ = "0" + str_;
            }
            return str_;
        }

        var endStr = "00:00";
        if(countTime_ < 60){
            countTime_ = Math.floor(countTime_);
            endStr = "00:" + changeStr(countTime_);
        }
        else if(countTime_ > 60 && countTime_ < 3600){
            var secondTime = countTime_ % 60;
            var minuteTime = countTime_ / 60;
            secondTime = Math.floor(secondTime);
            minuteTime = Math.floor(minuteTime);

            endStr = "" + changeStr(minuteTime) + ":" + changeStr(secondTime);
        }
        else{
            var hourTime   = countTime_ / 3600;
            var minuteTime = (countTime_ % 3600) / 60;
            var secondTime = (countTime_ % 3600) % 60

            secondTime = Math.floor(secondTime);
            minuteTime = Math.floor(minuteTime);
            hourTime = Math.floor(hourTime);

            endStr = "" + changeStr(hourTime) + ":" + changeStr(minuteTime) + ":" + changeStr(secondTime);
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
