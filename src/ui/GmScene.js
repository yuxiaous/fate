/**
 * Created by yuxiao on 15/5/14.
 */


var GmScene = ui.GuiSceneBase.extend({
    _guiFile: "ui/gm_scene.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        this._tf_cmd = this.seekWidgetByName("tf_cmd");
        this._list_history = this.seekWidgetByName("list_history");

        this._bindings = [
            notification.createBinding(notification.event.GM_CMD, this.refreshHistory, this)
        ];

        this.refreshHistory();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._tf_cmd = null;
        this._list_history = null;
        this._super();
    },

    refreshHistory: function(event, cmd) {
        if(event != undefined) {
            this._list_history.insertCustomItem(new ccui.Text(cmd, "", 24), 0);
        }
        else {
            var system = GmSystem.instance;

            this._list_history.removeAllItems();
            _.each(system.history, function(cmd) {
                this._list_history.insertCustomItem(new ccui.Text(cmd, "", 24), 0);
            }, this);
        }
    },

    _on_btn_send: function() {
        var cmd = this._tf_cmd.getString();
        if(cmd.length > 0) {
            GmSystem.instance.sendCommand(cmd);
            this._tf_cmd.setString("");
        }
    },

    _on_btn_back: function() {
        this.popScene();
    }
});

