/**
 * Created by yuxiao on 15/5/12.
 */


var shop_server = {
    start: function() {
        jsb.SdkManager.setChargeCallback(this.onChargeCallback.bind(this));

        this.orders = {
            //order_id: {
            //    order: Math.uuid(),
            //    good_id: good_id,
            //    status: 0
            //}
        };

        this.shop_info = database.checkout("shop_info", [
        ]);
        this.update = [];
    },

    end: function() {

    },

    sync: function() {
        if(this.update.length > 0) {
            database.commit("shop_info", this.shop_info);
            this.update = [];
        }
    },

    onChargeCallback: function(json) {
        LOG("shop_server.onChargeCallback");
        var obj = JSON.parse(json);
        this.handleOrder(obj.order, obj.result);
    },

    buyGood: function(good_id, good_num, order) {
        var config = ShopSystem.getConfig(good_id);
        if(config == undefined) {
            LOG("shop_server.buyGood error 1");
            server.sendError(net_error_code.ERR_SHOP_GOODS_NOT_EXIST);
            return false;
        }

        // check
        if(config.cond_type != undefined &&
            config.cond_type == 1 &&
            config.cond_value > player_server.player_info.level) {
            server.sendError(net_error_code.ERR_LESS_LEVEL);
            return false;
        }

        // pay
        var cost = config.pay_cost * good_num;
        switch (config.pay_type) {
            case shop_server.PayType.Gold: // gold
                if(player_server.changeGold(-cost) == false) {
                    return false;
                }
                break;

            case shop_server.PayType.Diamond: // diamond
                if(player_server.changeDiamond(-cost) == false) {
                    return false;
                }
                break;

            case shop_server.PayType.RMB:
                if(this.checkOrder(order) == false) {
                    return false;
                }
        }

        // gain
        var count = config.buy_count * good_num;

        if(config.sale_count != 0 && config.sale_count > this.getHistoryBuyInfo(good_id)){
            count = config.buy_count * (1 + config.on_sale /10) * good_num;
        }

        if(config.buy_type == shop_server.GoodsType.Equip || config.buy_type == shop_server.GoodsType.Item) {
            if(bag_server.addItem(config.buy_id, count) == false) {
                return false;
            }

            //server.send(net_protocol_handlers.CMD_SC_RECOVER_BATTLE,{
            //    result : 0
            //})
        }
        else if(config.buy_type == shop_server.GoodsType.Diamond) {
            if(player_server.changeDiamond(count) == false) {
                return false;
            }
        }
        else if(config.buy_type == shop_server.GoodsType.Gold) {
            if(player_server.changeGold(count) == false) {
                return false;
            }
        }
        else if(config.buy_type == shop_server.GoodsType.Skin) {
            if(skin_server.addSkin(config.buy_id) == false) {
                return false;
            }
            if(skin_server.changeSkin(config.buy_id) == false) {
                return false;
            }
        }
        else if(config.buy_type == shop_server.GoodsType.Gift){
            var giftConf = configdb.item[config.buy_id];
            if(giftConf){
                _.each([["gift1","gift1_val"],
                    ["gift2","gift2_val"],
                    ["gift3","gift3_val"],
                    ["gift4","gift4_val"],
                    ["gift5","gift5_val"]
                ], function (conf_) {
                    if(conf_ && giftConf[conf_[0]]){
                        var type = BagSystem.getConfigType(giftConf[conf_[0]]);
                        if(type == BagSystem.ConfigType.Equip) {
                            bag_server.addItem(giftConf[conf_[0]], giftConf[conf_[1]])
                        }
                        else {
                            //TODO shilei
                            if(giftConf[conf_[0]] == 100002){
                                player_server.changeGold(giftConf[conf_[1]]);
                            }
                            else if(giftConf[conf_[0]] == 100003){
                                player_server.changeDiamond(giftConf[conf_[1]]);
                            }
                            else if(giftConf[conf_[0]] == 100005){
                                bag_server.addItem(giftConf[conf_[0]], giftConf[conf_[1]])
                            }
                            else {
                                bag_server.addItem(giftConf[conf_[0]], giftConf[conf_[1]])
                            }
                        }
                    }
                });
               // LOG("config buy_id = " + config.buy_id);

                var gift_type = 0;
                switch (config.buy_id){
                    case 101001:
                        gift_type = gift_server.GiftType.ZhuangBei;
                        break;
                    case 101002:
                        gift_type = gift_server.GiftType.WuQi;
                        break;
                    case 101003:
                        gift_type = gift_server.GiftType.ZhiZun;
                        break;
                    case 101004:
                        gift_type = gift_server.GiftType.Vip;
                        break;
                }
                gift_server.updateGiftDate(gift_type);
            }
        }
        else if(config.buy_type == shop_server.GoodsType.EquipSlotTopLevel) {
            if(equip_server.upgradeSlotToMax(config.buy_id) == false) {
                return false;
            }
        }
        else if(config.buy_type == shop_server.GoodsType.DaZhao){
            LOG("buy dazhao");
            //if(!player_server.changeSuperSkillCount(3)){
            //    return;
            //}
            player_server.changeSuperSkillCount(3);

            //server.send(net_protocol_handlers.CMD_SC_RECOVER_BATTLE,{
            //    result : 0
            //})
        }
        else if(config.buy_type == shop_server.GoodsType.Tili){
            LOG("buy tili");
            player_server.changeAction(-60);
        }
        else if(config.buy_type == shop_server.GoodsType.FuHuo){
            LOG("buy fuhuo");

            server.send(net_protocol_handlers.CMD_SC_BATTLE_REVIVE,{
                result : 0
            });

            //server.send(net_protocol_handlers.CMD_SC_RECOVER_BATTLE,{
            //    result : 0
            //})

            var giftConf = configdb.item[config.buy_id];
            if(giftConf){
                _.each([["gift1","gift1_val"],
                    ["gift2","gift2_val"],
                    ["gift3","gift3_val"],
                    ["gift4","gift4_val"],
                    ["gift5","gift5_val"]
                ], function (conf_) {
                    if(conf_ && giftConf[conf_[0]]){
                        var type = BagSystem.getConfigType(giftConf[conf_[0]]);
                        //LOG("type = " + type);
                        if(type == BagSystem.ConfigType.Item) {
                            bag_server.addItem(giftConf[conf_[0]], giftConf[conf_[1]])
                        }
                    }
                });
            }

        }
        else if(config.buy_type == shop_server.GoodsType.ShiLian){
            server.send(net_protocol_handlers.CMD_SC_BUY_SHILIAN_FINISH,{
                result : 0
            });
        }

        return true;
    },

    genOrder: function(good_id) {
        var config = ShopSystem.getConfig(good_id);
        var ret = {
            order: Math.uuid(8) + "-" + config.platform_id,
            good_id: good_id,
            status: 0
        };

        this.orders[ret.order] = ret;
        return ret;
    },
    handleOrder: function(order, result) {
        var info = this.orders[order];
        if(info == undefined) {
            LOG("Error: handleOrder info not found.");
            return;
        }

        if(result == 0) {
            info.status = 1;
            this.buyGood(info.good_id, 1, info.order);
        }

        shop_server.updateHistoryBuyInfo(info.good_id,1);

        server.send(net_protocol_handlers.CMD_SC_SHOP_BUY_RESULT, {
            result: result,
            good_id: info.good_id,
            remaining: 0,
            order: info.order
        });
    },

    sendHistoryBuyInfo : function () {
         server.send(net_protocol_handlers.CMD_SC_SHOP_HISTORY_BUY_INFO,{
             history_buy_info : this.shop_info
         });
    },

    updateHistoryBuyInfo : function (item_id,buy_num) {
        var tmpNum = 1;
        if(buy_num != undefined){
            tmpNum = buy_num;
        }
        var hadChange = false;
        _.forEach(this.shop_info, function (itemInfo_) {
            if(itemInfo_ && itemInfo_.item_id == item_id){
                itemInfo_.buy_num += tmpNum;
            }
        },this);

        if(!hadChange){
            this.shop_info.push({
                item_id : item_id,
                buy_num : tmpNum
            });
        }
        this.update.push({
            refresh : true
        });

        this.sendHistoryBuyInfo();
    },

    getHistoryBuyInfo : function (good_id) {
        var buy_num = 0;
        _.forEach(this.shop_info, function (itemInfo_) {
            if(itemInfo_ && itemInfo_.item_id == good_id){
                buy_num = itemInfo_.buy_num;
            }
        },this);

        return buy_num;
    },
    checkOrder: function(order) {
        var info = this.orders[order];
        if(info == undefined) {
            LOG("Error: checkOrder info not found.");
            return false;
        }
        return (info.status == 1);
    }
};

shop_server.GoodsType = {
    Equip: 1,
    Item: 2,

    Skin: 4,
    Gold: 5,
    Diamond: 6,
    Gift : 7,
    EquipSlotTopLevel: 8,
    DaZhao : 9,
    Tili : 10,
    FuHuo : 11,
    ShiLian : 12
};
shop_server.PayType = {
    Gold: 1,
    Diamond: 2,
    RMB: 101
};

server.registerCallback(net_protocol_handlers.CMD_CS_SHOP_BUY_GOODS, function(obj) {
    if(shop_server.buyGood(obj.good_id, obj.count) == false) {
        return;
    }

    shop_server.updateHistoryBuyInfo(obj.good_id,obj.count);

    server.send(net_protocol_handlers.CMD_SC_SHOP_BUY_RESULT, {
        result: 0,
        good_id: obj.good_id,
        remaining: 12345,
        order: ""
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_SHOP_ORDER, function(obj) {

    var order = shop_server.genOrder(obj.good_id);
    server.send(net_protocol_handlers.CMD_SC_SHOP_ORDER_RESULT, {
        order: order.order,
        good_id: obj.good_id
    });
});