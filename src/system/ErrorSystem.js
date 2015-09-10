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
            if(obj.code == net_error_code.ERR_LESS_GOLD || obj.code == net_error_code.ERR_LESS_DIAMOND){
                var mesWin = new MessageBoxOkCancel(error.desc,"购买");
                mesWin.setOkCallback(function () {
                    RechargePanel.show();
                },this);
                mesWin.pop();
            }
            else{
                MessageBoxOk.show(error.desc);
            }
        }
    }
});

ErrorSystem.instance = new ErrorSystem();
ErrorSystem.instance.onInit();
