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

ItemSystem.getItemTypeName = function(type) {
    switch (type) {
        case ItemSystem.ItemType.Equip: return "装备";
        case ItemSystem.ItemType.Item: return "道具";
        case ItemSystem.ItemType.Gift: return "礼包";
    }
};

