/**
 * Created by yuxiao on 15/8/18.
 */


var StrengthenSystem = SystemBase.extend({
    ctor: function () {
        this._super();
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_EQUIP_STRENGTHEN_RESULT = this.onStrengthenEquipResult.bind(this);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_EQUIP_STRENGTHEN_RESULT = null;
    },

    strengthenEquipInBag: function(uid) {
        net_protocol_handlers.SEND_CMD_CS_EQUIP_STRENGTHEN_IN_BAG({
            uid: uid
        });
    },

    strengthenEquipOnEquip: function(slot) {
        net_protocol_handlers.SEND_CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP({
            slot: slot
        });
    },

    onStrengthenEquipResult: function(obj) {
        notification.emit(notification.event.EQUIP_STRENGTHEN_RESULT, obj.equip_id);
    }
});

