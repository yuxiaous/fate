/*
 * shilei@163.com
 * 2015/04/20
 * */

var StartLayerScene = ui.GuiSceneBase.extend({
    _guiFile: "ui/begin.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        MusicManager.getInstance().playBackgroundMusic("sounds/background.mp3");

        this._bindings = [
            notification.createBinding(notification.event.INIT_END, this.onEnterGame, this)
        ];
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._super();
    },

    onEnterGame: function() {
       this.pushScene(MapScene);
    },

    _on_btn_juqing: function() {
        LoginSystem.instance.authorize("Saber");
    }
});

