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
        this.playAnimation("background", true);
        MusicManager.getInstance().playBackgroundMusic("sounds/background.mp3");

        this._ui = {
            sp_touch: this.seekWidgetByName("Sprite_1")
        };

        this._bindings = [
            notification.createBinding(notification.event.INIT_END, this.onEnterGame, this)
        ];

        this._ui.sp_touch.runAction(cc.repeatForever(cc.sequence(
            cc.fadeOut(1),
            cc.fadeIn(1)
        )));

    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._super();
    },

    onEnterGame: function() {
        this.pushScene(MainScene);
    },

    _on_btn_enter: function() {
        LoginSystem.instance.authorize("Saber");
    }
});

