/**
 * Created by yuxiao on 15/6/8.
 */


var MainScene = ui.GuiSceneBase.extend({
    _guiFile: "ui/main_scene.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        this.playAnimation("fadein");
        MusicManager.getInstance().playBackgroundMusic("sounds/background.mp3");

        this._ui = {
            lbl_level: this.seekWidgetByName("lbl_level"),
            lbl_score: this.seekWidgetByName("lbl_score"),
            sp_circle: this.seekWidgetByName("sp_circle"),
            sp_gear: this.seekWidgetByName("Node_gear"),
            gift_node: this.seekWidgetByName("gift_node")
        };

        //this._ui.gift_node.setScale(0.5);

        this._ui.gift_panel = new Gift_Panel();
        this._ui.gift_panel.setWidget(this.seekWidgetByName("gift_node"));

        this._ui.action = new MainScene.Resource(MainScene.Resource.Type.Action);
        this._ui.action.setWidget(this.seekWidgetByName("ProjectNode_1"));

        this._ui.gold = new MainScene.Resource(MainScene.Resource.Type.Gold);
        this._ui.gold.setWidget(this.seekWidgetByName("ProjectNode_2"));

        this._ui.diamond = new MainScene.Resource(MainScene.Resource.Type.Diamond);
        this._ui.diamond.setWidget(this.seekWidgetByName("ProjectNode_3"));

        this._ui.sp_circle.runAction(cc.repeatForever(cc.rotateBy(60, 360)));
        this._ui.sp_gear.runAction(cc.repeatForever(cc.rotateBy(60, -360)));

        this.refreshPlayerInfo();

        //// 进入游戏
        //var size = cc.director.getWinSize();
        //var enterGame = new cc.MenuItemFont("登陆奖励", function () {
        //    //var loginPanel = new LoginRewardLayer();
        //    //loginPanel.pop();
        //    RewardSystem.instance.getLoginRewardDaily();
        //});
        //enterGame.attr({
        //    x: size.width * 0.9,
        //    y: size.height * 0.8,
        //    fontSize: 30
        //});
        //var menu = new cc.Menu(enterGame);
        //menu.x = 0;
        //menu.y = 0;
        //this.addChild(menu, 1);

        this._bindings = [
            notification.createBinding(notification.event.OPEN_LOGIN_REWARD, function (event,obj) {
                var loginPanel = new LoginRewardLayer(obj.login_index);
                loginPanel.pop();
            },this)
        ]

        RewardSystem.instance.getLoginRewardDaily();
    },


    onExit: function() {
        notification.removeBinding(this._bindings);
        this._super();
    },

    refreshPlayerInfo: function() {
        var system = PlayerSystem.instance;

        // level
        this._ui.lbl_level.setString(this._ui.lbl_level._str_original.format(system.level));

        // battle score
        var score = system.getPlayerBattleScore();
        this._ui.lbl_score.setString(this._ui.lbl_score._str_original.format(score.score));
    },

    _on_btn_back: function() {
        LoginSystem.instance.logout();
        this.popScene();
    },

    _on_btn_map: function() {
        this.pushScene(MapScene);
        //ui.pushScene(new BattleScene(101));
    },

    _on_btn_bag: function() {
        //this.pushScene(BagScene);
        var win = new BagScene();
        win.pop();
    },

    _on_btn_skill: function() {
        //this.pushScene(SkillScene);
        var win = new SkillScene();
        win.pop();
    },

    _on_btn_map_endless: function() {
        //ui.pushScene(new BattleEndlessScene() );
        var endless_select = new EndlessSelected();
        endless_select.pop();
        UiEffect.iconOpenEffect(endless_select.seekWidgetByName("gift_panel"));
    },

    _on_btn_equip: function() {
        //this.pushScene(EquipScene);
        var win = new EquipScene();
        win.pop();
    },

    _on_btn_shop: function() {
        this.pushScene(ShopScene);
        //var win = new ShopScene();
        //win.pop();
    }
});

MainScene.Resource = ui.GuiController.extend({
    ctor: function(type) {
        this._super();
        this.type = type;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_value: this.seekWidgetByName("lbl_value")
        };
        this._bindings = [
            notification.createBinding(notification.event.PLAYER_INFO, this.refreshValue, this)
        ];

        this.refreshValue();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._ui = null;
        this._super();
    },

    refreshValue: function() {
        var system = PlayerSystem.instance;

        var value = 0;
        switch (this.type) {
            case MainScene.Resource.Type.Action:
                value = system.action;
                break;
            case MainScene.Resource.Type.Gold:
                value = system.gold;
                break;
            case MainScene.Resource.Type.Diamond:
                value = system.diamond;
                break;
        }
        this._ui.lbl_value.setString(String(value));
    },

    _on_btn_add: function() {
        switch (this.type) {
            case MainScene.Resource.Type.Action:
                LOG("add action");
                GmSystem.instance.sendCommand("ar 3 10");
                break;
            case MainScene.Resource.Type.Gold:
                LOG("add gold");
                GmSystem.instance.sendCommand("ar 1 10000");
                break;
            case MainScene.Resource.Type.Diamond:
                LOG("add diamond");
                GmSystem.instance.sendCommand("ar 2 100");
                break;
        }
    }
});

MainScene.Resource.Type = {
    Action: 1,
    Gold: 2,
    Diamond: 3
};

