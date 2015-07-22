/**
 * Created by yuxiao on 15/5/26.
 */


var ItemSystem = SystemBase.extend({
    ctor: function () {
        this._super();
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_ITEM_USE_RESULT = this.onUseResult.bind(this);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_ITEM_USE_RESULT = null;
    },

    useItem: function(uid, num) {
        net_protocol_handlers.SEND_CMD_CS_ITEM_USE({
            uid: uid,
            num: num
        });

        var info = BagSystem.instance.items[uid];
        if(info != undefined) {
            var config = BagSystem.getConfig(info.id);
            if(config != undefined) {
                sdk_manager.sendSdkCommand("TalkingDataGA", "onUse",
                    "{item},{number}".format({
                        item: config.name,
                        number: num
                    }));
            }
        }
    },

    onUseResult: function(obj) {
        if(obj.result == 0){
            var target = cc.director.getRunningScene()._hero;
            if(obj.item_type == ItemSystem.ItemUseType.AddHpMp){    //加满血和蓝
                target.roleDataManager.hp = target.roleDataManager.maxHp;
                target.roleDataManager.mp = target.roleDataManager.maxMp;
            }
            //else if(obj.item_type == BattleSystem.UseItemType.UseRevive){ //复活币
            //    target.roleDataManager.hp = target.roleDataManager.maxHp;
            //    target.roleDataManager.mp = target.roleDataManager.maxMp;
            //}
            notification.emit(notification.event.BATTLE_USE_ITEM_RESULT,obj.item_type);
        }
    }
});


ItemSystem.ItemType = {
    Item: 1,
    Equip: 2,
    Gift: 3,
    BattleItem: 4,
    Exp: 5,
    GameCoin: 6,
    Skin: 7
};

ItemSystem.ItemUseType = {
    AddEXP :    1,  //增加经验
    AddGold:    2,  //增加金币
    AddDiamond: 3,  //增加钻石
    AddAction : 4,  //增加行动力
    AddHpPer :  5,  //增加HP
    AddMpPer :  6,  //增加MP
    AddHpMp :   7,  //增加HP 和 MP
    AddSkin:    8,  //角色套装
    AddLive :   9,   //战斗复活 复活币

    EntranceDaBaoJian : 10,  //大保健礼包购买入口
    SuperSkillCount : 11,   //大招次数
    BattleRevive : 12       //战斗复活
};

ItemSystem.getItemTypeName = function(type) {
    switch (type) {
        case ItemSystem.ItemType.Equip: return "装备";
        case ItemSystem.ItemType.Item: return "道具";
        case ItemSystem.ItemType.Gift: return "礼包";
    }
};

