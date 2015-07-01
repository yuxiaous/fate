var gift_server = {
    start: function() {
        //this.gift_info = database.checkout("gift_info", {
        //    gift_1 : 0,
        //    gift_2 : 0,
        //    gift_3 : 0,
        //    gift_4 : 0
        //
        //});


        this.gift_info = database.checkout("gift_info", [
            { giftType: 1, buy_num: 0 },
            { giftType: 2, buy_num: 0 },
            { giftType: 3, buy_num: 0 },
            { giftType: 4, buy_num: 0 }
        ]);

        LOG("13241231234124");
        LOGOBJ(this.gift_info);

        this.update = [];
    },

    end: function() {

    },

    //flush: function() {
    //    database.commit("gift_info", this.gift_info);
    //},

    sync: function() {
        if(this.update.length > 0) {
            database.commit("gift_info", this.gift_info);
            this.update = [];
        }
    }
};

gift_server.GiftType = {
    ZhuangBei : 1,
    WuQi : 2,
    ZhiZun : 3,
    Vip : 4
}

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