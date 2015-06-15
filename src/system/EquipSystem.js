/**
 * Created by yuxiao on 15/5/18.
 */


var EquipSystem = SystemBase.extend({
    ctor: function () {
        this._super();

        this.slots = {};
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_EQUIP_SLOT_INFO = this.onEquipSlotInfo.bind(this);
        net_protocol_handlers.ON_CMD_SC_EQUIP_SLOT_UPGRADE_RESULT = this.onEquipSlotUpgradeResult.bind(this);
        net_protocol_handlers.ON_CMD_CS_EQUIP_ITEM_RESULT = this.onEquipItemResult.bind(this);
        net_protocol_handlers.ON_CMD_CS_UNEQUIP_ITEM_RESULT = this.onUnequipItemResult.bind(this);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_EQUIP_SLOT_INFO = null;
        net_protocol_handlers.ON_CMD_SC_EQUIP_SLOT_UPGRADE_RESULT = null;
        net_protocol_handlers.ON_CMD_CS_EQUIP_ITEM_RESULT = null;
        net_protocol_handlers.ON_CMD_CS_UNEQUIP_ITEM_RESULT = null;
    },

    onEquipSlotInfo: function(obj) {
        _.each(obj.slots, function(slot) {
            this.slots[slot.slot] = slot;
        }, this);

        notification.emit(notification.event.EQUIP_SLOT_INFO);
        notification.emit(notification.event.EQUIP_PROPERTY_CHANGE);
    },

    upgradeEquipSlot: function(type) {
        net_protocol_handlers.SEND_CMD_CS_EQUIP_SLOT_UPGRADE({
            slot_type: type
        });
    },

    onEquipSlotUpgradeResult: function(obj) {
        notification.emit(notification.event.EQUIP_SLOT_UPGRADE_RESULT);
    },

    equipItem: function(uid) {
        net_protocol_handlers.SEND_CMD_CS_EQUIP_ITEM({
            uid: uid
        });
    },

    onEquipItemResult: function(obj) {
        notification.emit(notification.event.EQUIP_EQUIP_ITEM,{
            isRefresh : true
        });
    },

    unequipItem: function(slot) {
        net_protocol_handlers.SEND_CMD_CS_UNEQUIP_ITEM({
            slot: slot
        });
    },
    onUnequipItemResult: function(obj) {
        notification.emit(notification.event.EQUIP_UNEQUIP_ITEM,{
            isRefresh : true
        });
    },

    hasBetterEquip: function() {
        var ret = false;
        var items = BagSystem.instance.items;

        _.some(this.slots, function(slot) {
            var score = 0;

            var config = configdb.equip[slot.id];
            if(config) {
                score = Formula.calculateBattleScore(config.hp, config.mp,
                    config.atk, config.def,
                    config.crit, config.sunder);
            }

            _.some(items, function(item) {
                config = configdb.equip[item.id];
                if(config == undefined) {
                    return false;
                }

                if(config.slot != slot.slot) {
                    return false;
                }

                if(score < Formula.calculateBattleScore(config.hp, config.mp,
                        config.atk, config.def,
                        config.crit, config.sunder)) {
                    ret = true;
                }
                return ret;
            }, this);

            return ret;
        }, this);

        return ret;
    },

    canUpgradeEquipSlot: function() {
        var ret = false;

        _.some(this.slots, function(slot) {
            var id = EquipSystem.getEquipSlotUpgradeId(slot.slot, slot.level);
            var config = configdb.duanzao[id];
            if(config == undefined) {
                return false;
            }

            if(config.cost <= PlayerSystem.instance.gold) {
                ret = true;
            }
            return ret
        }, this);

        return ret;
    },

    getAllEquipBattleScore: function() {
        var ret = {hp: 0, mp: 0, atk: 0, def: 0, crit: 0, sunder: 0, score: 0};

        _.each(this.slots, function(slot) {
            var config = configdb.equip[slot.id];
            if(config) {
                ret.hp += config.hp || 0;
                ret.mp += config.mp || 0;
                ret.atk += config.atk || 0;
                ret.def += config.def || 0;
                ret.crit += config.crit || 0;
                ret.sunder += config.sunder || 0;
            }
        }, this);

        ret.score = Formula.calculateBattleScore(ret.hp, ret.mp, ret.atk, ret.def, ret.crit, ret.sunder);
        return ret;
    },

    getAllSlotBattleScore: function() {
        var ret = {hp: 0, mp: 0, atk: 0, def: 0, crit: 0, sunder: 0, score: 0};

        _.each(this.slots, function(slot) {
            var id = EquipSystem.getEquipSlotUpgradeId(slot.slot, slot.level);
            var config = configdb.duanzao[id];
            if(config) {
                switch (config.prop_type) {
                    case EquipSystem.EquipPropertyType.Hp:
                        ret.hp += config.prop_value || 0;
                        break;
                    case EquipSystem.EquipPropertyType.Mp:
                        ret.mp += config.prop_value || 0;
                        break;
                    case EquipSystem.EquipPropertyType.Atk:
                        ret.atk += config.prop_value || 0;
                        break;
                    case EquipSystem.EquipPropertyType.Def:
                        ret.def += config.prop_value || 0;
                        break;
                    case EquipSystem.EquipPropertyType.Crit:
                        ret.crit += config.prop_value || 0;
                        break;
                    case EquipSystem.EquipPropertyType.Sunder:
                        ret.sunder += config.prop_value || 0;
                        break;
                }
            }
        }, this);

        ret.score = Formula.calculateBattleScore(ret.hp, ret.mp, ret.atk, ret.def, ret.crit, ret.sunder);
        return ret;
    }
});


EquipSystem.EquipSlotType = {
    Weapon: 1,
    Coat: 2,
    Head: 3,
    Glove: 4, //护手
    Shield: 5, //盾牌
    Amulet: 6
};

EquipSystem.EquipPropertyType = {
    Hp: 1,
    Mp: 2,
    Atk: 3,
    Def: 4,
    Crit: 5,
    Sunder: 6
};

EquipSystem.getEquipSlotName = function(type) {
    switch (type) {
        case EquipSystem.EquipSlotType.Weapon: return "武器";
        case EquipSystem.EquipSlotType.Coat: return "衣服";
        case EquipSystem.EquipSlotType.Head: return "头部";
        case EquipSystem.EquipSlotType.Glove: return "护手";
        case EquipSystem.EquipSlotType.Shield: return "盾牌";
        case EquipSystem.EquipSlotType.Amulet: return "戒指";
    }
    return "位置部位";
};

EquipSystem.getEquipProperty = function(type) {
    switch (type) {
        case EquipSystem.EquipPropertyType.Hp: return "生命值";
        case EquipSystem.EquipPropertyType.Mp: return "法力值";
        case EquipSystem.EquipPropertyType.Atk: return "攻击值";
        case EquipSystem.EquipPropertyType.Def: return "防御值";
        case EquipSystem.EquipPropertyType.Crit: return "暴击值";
        case EquipSystem.EquipPropertyType.Sunder: return "破甲值";
    }
    return "未知属性";
};

EquipSystem.getEquipSlotUpgradeId = function(type, level) {
    if(level == undefined) level = 1;

    var start_id = 0;
    switch (type) {
        case EquipSystem.EquipSlotType.Weapon: start_id = 1001; break;
        case EquipSystem.EquipSlotType.Coat: start_id = 2001; break;
        case EquipSystem.EquipSlotType.Head: start_id = 3001; break;
        case EquipSystem.EquipSlotType.Glove: start_id = 4001; break;
        case EquipSystem.EquipSlotType.Shield: start_id = 5001; break;
        case EquipSystem.EquipSlotType.Amulet: start_id = 6001; break;
    }
    if(start_id > 0) {
        return start_id + level - 1;
    }

    return 0;
};

