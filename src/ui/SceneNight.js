/**
 * Created by yuxiao on 15/3/10.
 */


var SceneNight = ui.GuiLevelHelperScene.extend({
    _guiFile: "scenes/senlin.lhplist",

    status: {
        weather: {
            res: "particles/rain.plist"
        },

        music: {
            background: "sounds/background1.mp3"
            //effect: []
        },
        dragonBonesRes: [
        ],

        openingChat: [
            {
                text: "我靠，又要跟我比武！！",
                name: "Archer",
                side: DialogPanel.Side.Left,
                image: "res/images/1.png"
            },
            {
                text: "Archer，你别跑！！",
                name: "Saber",
                side: DialogPanel.Side.Right,
                image: "res/images/2.png"
            },
            {
                text: "整天打打杀杀，不如当老师泡校花。",
                name: "Archer",
                side: DialogPanel.Side.Left,
                image: "res/images/1.png"
            },
            {
                text: "朱雀学园我来了～～",
                name: "Archer",
                side: DialogPanel.Side.Left,
                image: "res/images/1.png"
            }
        ],

        enemies: [
            {
                roleType: StoneGhost,
                roleTitle : RoleBase.RoleType.Monster,
                pos: {x:1000, y:0}
            },
            {
                roleType: SkullMan,
                roleTitle : RoleBase.RoleType.Monster,
                pos: {x: 1000, y: 100}
            },

            {
                roleType: StoneGhost,
                roleTitle : RoleBase.RoleType.Monster,
                pos: {x: 2000, y: 0}
            },
            {
                roleType: SkullMan,
                roleTitle : RoleBase.RoleType.Monster,
                pos: {x: 2000, y: 50}
            },
            {
                roleType: StoneGhost,
                roleTitle : RoleBase.RoleType.Monster,
                pos: {x: 2000, y: 100}
            },

            {
                roleType: StoneGhost,
                roleTitle : RoleBase.RoleType.Monster,
                pos: {x: 3500, y: 25}
            },
            {
                roleType: SkullMan,
                roleTitle : RoleBase.RoleType.Monster,
                pos: {x: 3500, y: 75}
            },
            {
                roleType: StoneGhost,
                roleTitle : RoleBase.RoleType.Monster,
                pos: {x: 3500, y: 0}
            },
            {
                roleType: SkullMan,
                roleTitle : RoleBase.RoleType.Monster,
                pos: {x: 3800, y: 50}
            },
            {
                roleType: YingLiu,
                roleTitle : RoleBase.RoleType.Boss,
                pos: {x: 3700, y: 100}
            }
        ]


    },

    ctor: function() {
        this._super();
        battleSceneManager.setScene(this);
    },

    onEnter: function() {
        this._super();
        this._gameWorldNode = this.getGameWorldNode();
        this._backUiNode = this.getBackUINode();
        this._uiNode = this.getUINode();

        // music
        if(this.status.music.background) {
            cc.audioEngine.preloadMusic(this.status.music.background);
            cc.audioEngine.playMusic(this.status.music.background, true);
        }
        if(this.status.music.effect) {
            _.each(this.status.music.effect, function(effect) {
                cc.audioEngine.preloadEffect(effect);
            });
        }

        // weather
        var rain = cc.ParticleSystem.create(this.status.weather.res);
        rain.setPositionType(cc.ParticleSystem.TYPE_RELATIVE);
        this._gameWorldNode.addChild(rain);

        // dragon bones res
        _.each(this.status.dragonBonesRes, function(res) {
            dragonBones.DragonBonesHelper.addDragonBones(res);
        }, this);


        // main role
        var role1 = new Saber();
        //role1.setRoleType(RoleBase.RoleType.Hero);
        role1.setSpacePosition({x:200, y:200, z:0});
        //role1.setRoleAi(jsb.RoleAiManager.AiType.STAKE);
        battleSceneManager.setMainRole(role1);
        this._mainRole = role1;

        // enemies
        _.each(this.status.enemies, function(e) {
            var enemy = new e.roleType();
            enemy.setRoleType(e.roleTitle);
            enemy.setSpacePosition(_.defaults(e.pos, {x:0., y:0, z:0}));
            enemy.setRoleAi(jsb.RoleAiManager.AiType.AUTO);
            enemy.turn(-1);
            battleSceneManager.addOpponent(enemy);
        }, this);


        this.startOpeningChat();
    },

    onExit: function() {
        this._super();

        cc.audioEngine.stopMusic();
    },

    startOpeningChat: function() {
        var dialog = new DialogPanel(this.status.openingChat);
        dialog.setEndingCallback(function() {
            dialog.removeFromParent();
            this.startFighting();
        }.bind(this));
        this._uiNode.addChild(dialog);
    },

    startFighting: function() {
        var winSize = cc.director.getWinSize();

        // operator
        var operator = new OperationLayer();
        this._mainRole.setRoleAi(jsb.RoleAiManager.AiType.MANUAL, {
            joystick: operator._joystick,
            attackButton: operator._attackButton,
            skillButton1: operator._skillButton1
        });
        this._uiNode.addChild(operator);

        // role info panel
        var rolePanel = new RoleBattlePanel();
        rolePanel.setPosition(0, winSize.height);
        rolePanel.setRole(this._mainRole);
        this._uiNode.addChild(rolePanel);

        // combo panel
        var comboPanel = new ComboPanel();
        comboPanel.setPosition(winSize.width, winSize.height);
        this._uiNode.addChild(comboPanel);
    }
});

