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
            btn_about : this.seekWidgetByName("btn_about"),
            btn_more_game: this.seekWidgetByName("btn_more_game"),
            btn_exit: this.seekWidgetByName("btn_exit")
        };

        var channel_id = util.getChannelId();

        // 关于按钮
        this._ui.btn_about.setVisible(channel_id == GameChannel.Telecom);

        // 更多游戏按钮
        this._ui.btn_more_game.setVisible(
            channel_id == GameChannel.CmccAnd ||
            channel_id == GameChannel.Telecom);

        // 退出按钮
        this._ui.btn_exit.setVisible(cc.sys.os == cc.sys.OS_ANDROID);

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
        this._ui = null;
        this._super();
    },

    onEnterGame: function() {
        var hadEnterG = jsb.JsonStorage.GetInstance(LoginSystem.settingFile).getBoolForKey(LoginSystem.recordEnterGame);
        if(!hadEnterG){
            BattleSystem.instance.startTryBattle(Archer,true);
        }
        else{
            //sdk_manager.sendSdkCommand("TalkingDataGA", "setAccountName", "Saber");
            this.pushScene(MainScene);
        }
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
        switch (util.getChannelId()) {
            case GameChannel.CmccAnd:
                sdk_manager.sendSdkCommand("AndGame", "exit", "");
                break;
            case GameChannel.Telecom:
                sdk_manager.sendSdkCommand("Egame", "exit", "");
                break;
            case GameChannel.Baidu91:
            case GameChannel.BaiduTieba:
            case GameChannel.BaiduShoujizhushou:
            case GameChannel.BaiduDuoku:
                sdk_manager.sendSdkCommand("DKSingle", "exit", "");
                break;
            default:
                MessageBoxOkCancel.show("确定退出游戏？").setOkCallback(function() {
                    sdk_manager.sendSdkCommand("", "exit", "");
                    cc.director.end();
                });
                break;
        }
    },

    _on_btn_more_game: function() {
        switch (util.getChannelId()) {
            case GameChannel.CmccAnd:
                sdk_manager.sendSdkCommand("AndGame", "showMoreGames", "");
                break;
            case GameChannel.Telecom:
                sdk_manager.sendSdkCommand("Egame", "moreGame", "");
                break;
        }
    }
});

