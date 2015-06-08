/**
 * Created by yuxiao on 15/1/25.
 */


var RoleHealthBar = ui.GuiWidgetBase.extend({
    _guiFile: "res/ui/RoleHealthBar.json",

    ctor: function(roleData) {
        this._super();
        this._roleData = roleData;
    },

    onEnter: function() {
        this._super();
        this._progress = this.seekWidgetByName("progress_hp");
        this._lbl_hp = this.seekWidgetByName("lbl_hp");
        this._lbl_name = this.seekWidgetByName("lbl_name");

        var data = this._roleData;
        if(data == null) {
            return;
        }

        this._lbl_name.setString(data.name);

        this.updateProgressBar();
    },

    onExit: function() {
        this._progress = null;
        this._lbl_hp = null;
        this._lbl_name = null;
        this._super();
    },

    //setCurrentHp: function(hp) {
    //    this._curHp = hp;
    //    this.updateProgressBar();
    //},
    //
    updateProgressBar: function() {
        var data = this._roleData;
        this._progress.setPercent(100.0 * data.curHp / data.maxHp);
        this._lbl_hp.setString(this._lbl_hp._str_original.format(data.curHp, data.maxHp));
    },

    //changeHp: function(val) {
    //    this._curHp += val;
    //    this.updateProgressBar();
    //}
});

