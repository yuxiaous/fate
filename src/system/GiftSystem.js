
var GiftSystem = SystemBase.extend({
    ctor: function () {
        this._super();
        this._giftData = null;
    },

    onInit: function () {
        this._super();

        //net_protocol_handlers.ON_CMD_SC_BUY_GIFT_RESULT = function (obj) {
        //    LOG("update gift result");
        //    this._giftData = obj;
        //    LOG("gift info = 1 = " + this._giftData.gift1);
        //    LOG("gift info = 2 = " + this._giftData.gift2);
        //    LOG("gift info = 3 = " + this._giftData.gift3);
        //    LOG("gift info = 4 = " + this._giftData.gift4);
        //
        //    notification.emit(notification.event.REFRESH_GIFT_INFO);
        //}.bind(this);

        net_protocol_handlers.ON_CMD_SC_BUY_GIFT_RESULT = this.refreshGiftInfo.bind(this);
    },

    refreshGiftInfo : function (obj) {
        LOG("update gift result");
        this._giftData = obj.gift_type_data;
        LOG("gift info = 1 = " + this._giftData[0].buy_num);
        LOG("gift info = 2 = " + this._giftData[1].buy_num);
        LOG("gift info = 3 = " + this._giftData[2].buy_num);
        LOG("gift info = 4 = " + this._giftData[3].buy_num);
        notification.emit(notification.event.REFRESH_GIFT_INFO);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_BUY_GIFT_RESULT = null;
    },
    
    buyGiftItem : function (type_) {
        net_protocol_handlers.SEND_CMD_CS_BUY_GIFT({
            gift_type : type_
        });
    }
});

GiftSystem.GiftType = {
    ZhuangBei : 1,
    WuQi : 2,
    ZhiZun : 3,
    Vip : 4
}
