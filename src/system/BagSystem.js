/**
 * Created by yuxiao on 15/5/21.
 */


var BagSystem = SystemBase.extend({
    ctor: function () {
        this._super();

        this.items = {};
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_ITEM_INFO = this.onItemsInfo.bind(this);
        net_protocol_handlers.ON_CMD_SC_ITEM_SELL_RESULT = this.onSellResult.bind(this);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_ITEM_INFO = null;
        net_protocol_handlers.ON_CMD_SC_ITEM_SELL_RESULT = null;
    },

    onItemsInfo: function(obj) {
        // update items
        _.each(obj.items, function(info) {
            this.items[info.uid] = info;
        }, this);

        // remove empty items
        _.each(this.items, function(info) {
            if(info.num <= 0) {
                delete this.items[info.uid];
            }
        }, this);

        notification.emit(notification.event.ITEM_INFO);
    },

    getItemNums : function (itemId_) {
        var magicBottleNum = 0;
        _.reduce(BagSystem.instance.items, function(sum, item) {

            if(item.id == itemId_) {
                magicBottleNum += item.num || 0;
            }
        }, 0, this)

        return magicBottleNum;
    },

    sell: function(uid, num) {
        net_protocol_handlers.SEND_CMD_CS_ITEM_SELL({
            uid: uid,
            num: num
        });
    },

    onSellResult: function(obj) {

    }
});


BagSystem.ConfigType = {
    Item: 1,
    Equip: 2
};

BagSystem.getConfigType = function(id) {
    if(id == undefined) id = 0;
    return Math.floor(id/100000);
};

BagSystem.getConfig = function(id) {
    var type = BagSystem.getConfigType(id);
    if(type == BagSystem.ConfigType.Equip) {
        return configdb.equip[id];
    }
    else {
        return configdb.item[id];
    }
};

BagSystem.getItemUseMethodName = function(id) {
    var type = BagSystem.getConfigType(id);
    if(type == BagSystem.ConfigType.Equip) {
        return "装备"
    }

    var config = configdb.item[id];
    if(config) {
        switch (config.type) {
            case ItemSystem.ItemType.Item: return "使用";
            case ItemSystem.ItemType.Equip: return "装备";
            case ItemSystem.ItemType.Gift: return "打开";
        }
    }
    return "未知"
};