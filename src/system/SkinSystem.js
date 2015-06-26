/**
 * Created by yuxiao on 15/6/16.
 */


var SkinSystem = SystemBase.extend({
    ctor: function () {
        this._super();
        this.skins = {};
        this.use_skin = 0;
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_SKIN_INFO = this.onSkinInfo.bind(this);
        net_protocol_handlers.ON_CMD_SC_SKIN_CHANGE_RESULT = this.onChangeSkinResult.bind(this);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_SKIN_INFO = null;
        net_protocol_handlers.ON_CMD_SC_SKIN_CHANGE_RESULT = null;
    },

    onSkinInfo: function(obj) {
        _.each(obj.skins, function(skin) {
            this.skins[skin.skin_id] = skin;
        }, this);
        this.use_skin = obj.use_skin;
        notification.emit(notification.event.SKIN_INFO);
    },

    changeSkin: function(skin_id) {
        net_protocol_handlers.SEND_CMD_CS_SKIN_CHANGE({
            skin_id: skin_id
        });
    },

    onChangeSkinResult: function(obj) {
        notification.emit(notification.event.SKIN_CHANGE_RESULT);
    }
});

