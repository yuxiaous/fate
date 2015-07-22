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
        this.playAnimation("blink", true);
        MusicManager.getInstance().playBackgroundMusic("sounds/background.mp3");

        this._ui = {
            sp_bg: this.seekWidgetByName("sp_background"),
            sp_touch: this.seekWidgetByName("Sprite_1"),
            about_btn : this.seekWidgetByName("btn_about")
        };

        //电信渠道显示
        //this._ui.about_btn.setVisible(util.getChannelId() == GameChannel.ChinaTelecom);
        this._ui.about_btn.setVisible(true);
        this._ui.about_btn.setPressedActionEnabled(true);

        this._bindings = [
            notification.createBinding(notification.event.INIT_END, this.onEnterGame, this)
        ];

        this._ui.sp_touch.runAction(cc.repeatForever(cc.sequence(
            cc.fadeOut(1),
            cc.fadeIn(1)
        )));
        this._ui.sp_bg.runAction(cc.repeatForever(cc.sequence(
            cc.moveBy(40, -119, 0),
            cc.moveBy(40, 119, 0)
        )));
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._super();
    },

    onEnterGame: function() {
        sdk_manager.sendSdkCommand("TalkingDataGA", "setAccountName", "Saber");
        this.pushScene(MainScene);
    },

    _on_btn_enter: function() {
        LoginSystem.instance.login(LoginSystem.LoginType.Identifier, util.getUdid());
    },
    
    _on_btn_about : function () {
        var annLayer = new AnnouncementLayer();
        annLayer.pop();

        UiEffect.iconOpenEffect(annLayer);
    },
    
    _on_btn_exit : function () {
        var box = MessageBoxOkCancel.show("确定退出游戏？");
        box.setOkCallback(function() {
            cc.director.end();
        }, this);
    }
});

