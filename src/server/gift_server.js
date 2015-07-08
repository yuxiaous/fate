var gift_server = {
    start: function() {
        this.gift_info = database.checkout("gift_info", [
            { giftType: 1, buy_num: 0 ,count_down : 0},
            { giftType: 2, buy_num: 0 ,count_down : 0},
            { giftType: 3, buy_num: 0 ,count_down : 900},
            { giftType: 4, buy_num: 0 ,count_down : 0},
            { giftType: 5, buy_num: 0 ,count_down : 0}
        ]);
        this.update = [];

        cc.director.getScheduler().schedule(this.updateTime,this,1.0,cc.REPEAT_FOREVER,0,false,"refresTime");
    },

    updateTime : function () {
        _.each(this.gift_info, function (giftInfo_) {
            if(giftInfo_ && giftInfo_.count_down > 0){
                giftInfo_.count_down -= 1;
            }

            if(giftInfo_.giftType == 3 && giftInfo_.count_down <= 0){
                giftInfo_.count_down = 900;
            }
        },this);
    },

    end: function() {
        cc.director.getScheduler().unschedule("refresTime",this);
    },

    sync: function() {
        if(this.update.length > 0) {
            database.commit("gift_info", this.gift_info);
            this.update = [];
        }
    },

    updateGiftDate : function (gift_type) {
        //this.gift_info[obj.gift_type -1].buy_num += 1;
        switch (gift_type){
            case gift_server.GiftType.ZhuangBei:
                gift_server.gift_info[0].buy_num += 1;
                break;
            case gift_server.GiftType.WuQi:
                gift_server.gift_info[1].buy_num += 1;
                break;
            case gift_server.GiftType.ZhiZun:
                gift_server.gift_info[2].buy_num += 1;
                break;
            case gift_server.GiftType.Vip:
                gift_server.gift_info[3].buy_num += 1;
                break;
        }

        gift_server.update.push(gift_type);

        server.send(net_protocol_handlers.CMD_SC_BUY_GIFT_RESULT,{
            result : 0,
            gift_type_data : this.gift_info
        });
    }
};

gift_server.GiftType = {
    ZhuangBei : 1,
    WuQi : 2,
    ZhiZun : 3,
    Vip : 4,
    DaBaoJian : 5
};

server.registerCallback(net_protocol_handlers.CMD_CS_GET_GIFT_TIME, function (obj) {
    gift_server.update.push(obj);

    server.send(net_protocol_handlers.CMD_SC_BUY_GIFT_RESULT,{
        result : 0,
        gift_type_data : gift_server.gift_info
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_BUY_GIFT, function (obj) {
    //login reward

    //this.gift_info[obj.gift_type -1].buy_num += 1;
    switch (obj.gift_type){
        case gift_server.GiftType.ZhuangBei:
            gift_server.gift_info[0].buy_num += 1;
            break;
        case gift_server.GiftType.WuQi:
            gift_server.gift_info[1].buy_num += 1;
            break;
        case gift_server.GiftType.ZhiZun:
            gift_server.gift_info[2].buy_num += 1;
            break;
        case gift_server.GiftType.Vip:
            gift_server.gift_info[3].buy_num += 1;
            break;
    }

    gift_server.update.push(obj);

    server.send(net_protocol_handlers.CMD_SC_BUY_GIFT_RESULT,{
        result : 0,
        gift_type_data : gift_server.gift_info
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_UPDATE_GIFT_TIME, function (obj_) {
    if(obj_ && obj_.gift_type_data){
        _.each(obj_.gift_type_data, function (giftInfo_) {
            _.each(gift_server.gift_info, function (info_) {
                if(info_.giftType == giftInfo_.giftType){
                    info_.count_down = giftInfo_.count_down;
                }
            },this);
        },this);
    }
    gift_server.update.push(obj_);
})