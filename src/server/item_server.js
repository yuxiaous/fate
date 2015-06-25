/**
 * Created by yuxiao on 15/6/3.
 */


var item_server = {
    start: function () {

    },

    end: function () {

    },

    flush: function () {

    }
};

item_server.ItemUseType = {
    AddEXP :    1,  //增加经验
    AddGold:    2,  //增加金币
    AddDiamond: 3,  //增加钻石
    AddAction : 4,  //增加行动力
    AddHpPer :  5,  //增加HP
    AddMpPer :  6,  //增加MP
    AddHpMp :   7,  //增加HP 和 MP
    AddSkin:    8,  //角色套装
    AddLive :   9,   //战斗复活
    EntranceDaBaoJian : 10
};


server.registerCallback(net_protocol_handlers.CMD_CS_ITEM_USE, function(obj) {
    LOG("CMD_CS_ITEM_USE");
    var info = _.findWhere(bag_server.bag_info, { uid: obj.uid });
    if(info == undefined) {
        LOG("CMD_CS_ITEM_USE error 1");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    var config = configdb.item[info.id];
    if(config == undefined) {
        LOG("CMD_CS_ITEM_USE error 2");
        server.sendError(net_error_code.ERR_CONFIG_NOT_EXIST);
        return;
    }

    if(bag_server.reduceItem(obj.uid, obj.num) == false) {
        return;
    }

    switch (config.result) {
        case item_server.ItemUseType.AddGold:
            if(useResultAddGold(config.result_value) == false) {
                return;
            }
            break;
        case item_server.ItemUseType.AddDiamond:
            if(useResultAddDiamond(config.result_value) == false) {
                return;
            }
            break;
    }

    server.send(net_protocol_handlers.CMD_SC_ITEM_USE_RESULT, {
        result: 0
    });
});


function useResultAddGold(value) {
    return player_server.changeGold(value);
}

function useResultAddDiamond(value) {
    return player_server.changeDiamond(value);
}

