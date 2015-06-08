/**
 * Created by shilei on 15/4/09.
 */


var RoleBloodBar = ui.GuiWidgetBase.extend({
    _guiFile: "res/ui/BloodBar.json",

    ctor: function(maxValue_,curValue_) {
        this._super();
        this._maxValue = maxValue_;
        this._curValue = curValue_;
        cc.log("max = " + this._maxValue);
        cc.log("cur = " + this._curValue);
    },

    onEnter: function() {
        this._super();
        this._bloodBarPro = this.seekWidgetByName("bloodBarPro");

        this.refreshBloodBarPer(this._maxValue, this._curValue);
    },

    onExit: function() {
        this._bloodBarPro = null;
        this._super();
    },

    refreshBloodBarPer : function(maxValue_,curValue_){
        this._maxValue = maxValue_;
        this._curValue = curValue_;
        //cc.log("max = " + this._maxValue);
        //cc.log("cur = " + this._curValue);

        var tmpPercent = this._curValue / this._maxValue * 100;
        //cc.log("tmp PERCENT = " + tmpPercent);
        this._bloodBarPro.setPercent(tmpPercent);
    }
});

