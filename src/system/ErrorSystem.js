/**
 * Created by yuxiao on 15/5/12.
 */


var ErrorSystem = SystemBase.extend({
    ctor: function () {
        this._super();
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_ERROR_CODE = this.onErrorMessage.bind(this);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_ERROR_CODE = null;
    },

    onErrorMessage: function(obj) {
        var error = net_error_code[obj.code];
        if(error) {
            //MessageBoxOk.show(error.desc);
            var mesWin = new MessageBoxOkCancel(error.desc,"购买");
            mesWin.setOkCallback(function () {
                var rechargeGold = new RechargePanel();
                rechargeGold.pop();
            },this);
            mesWin.pop();
        }
    }
});

ErrorSystem.instance = new ErrorSystem();
ErrorSystem.instance.onInit();
