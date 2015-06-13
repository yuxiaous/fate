/**
 * Created by yuxiao on 15/4/8.
 */


var SceneBase = lh.LHScene.extend({
    ctor: function(sceneName) {
        if(!sceneName.startsWith("scenes")) {
            sceneName = "scenes/" + sceneName + ".lhplist";
        }
        this._super(sceneName);

        this._hero = null;
        this._boss = null;
        this._monsters = [];
        this._friends = [];
        this._items = [];

        this.scheduleUpdate();

    },

    onEnter: function() {
        this._super();

        var winSize = cc.director.getWinSize();
        var gameWorld = this.getGameWorldNode();
        var backUi = this.getBackUINode();
        var frontUi = this.getUINode();

        // street
        var street = this.getChildNodeWithName("street");
        var physicalWorld = new PhysicalWorld();
        //world.setContentSize(street.getContentSize());
        physicalWorld.shakingNode = gameWorld;
        gameWorld.addChild(physicalWorld, street.getLocalZOrder());

        // camera
        var camera = this.getChildNodeWithName("UntitledCamera");
        camera.setImportantAreaUnit(cc.size(0, 0));

        // operator panel
        var operator = new OperationLayer();
        operator.setVisible(false);
        operator.setEnable(false);
        frontUi.addChild(operator);

        //// role info panel
        //var rolePanel = new RoleBattlePanel();
        //rolePanel.setPosition(0, winSize.height);
        //rolePanel.setVisible(false);
        //rolePanel.setRole(this._hero);
        //frontUi.addChild(rolePanel);

        ////boss info panel
        //var bossPanel = new BossBattlePanel();
        //bossPanel.setPosition(winSize.width,winSize.height);
        //bossPanel.setVisible(false);
        //frontUi.addChild(bossPanel);

        //battle ui layer
        var battleUiLayer = new BattleUILayer();
        battleUiLayer.setPosition(cc.p(0,0));
        battleUiLayer.setAnchorPoint(cc.p(0,0));
        frontUi.addChild(battleUiLayer);

        // combo panel
        var comboPanel = new ComboPanel();
        comboPanel.setPosition(winSize.width, winSize.height);
        comboPanel.setVisible(false);
        frontUi.addChild(comboPanel);

        var coverLayer = cc.LayerColor.create(cc.color(0, 0, 0, 255),winSize.width,winSize.height);
        coverLayer.setPosition(cc.p(-winSize.width,0));
        coverLayer.setAnchorPoint(cc.p(0,0));
        frontUi.addChild(coverLayer,100);
        coverLayer.state = 0;

        ////pause battle
        //var pauseItem = new cc.MenuItemFont("PAUSE", function(){
        //    cc.director.pause();
        //    var pausePanel = new PauseLayer();
        //    frontUi.addChild(pausePanel);
        //}, this);
        //var menu = new cc.Menu(pauseItem);
        //menu.setPosition(cc.p(50,winSize.height/2));
        //frontUi.addChild(menu);

        this._camera = camera;
        this._gameWorld = gameWorld;
        this._backUi = backUi;
        this._frontUi = frontUi;
        this._physicalWorld = physicalWorld;
        this._operator = operator;
        this._battleUiLayer = battleUiLayer;
        this._rolePanel = this._battleUiLayer._rolePanel;
        this._bossPanel = this._battleUiLayer._bossPanel;

        this._coverView = coverLayer;

        if(this._bgmFile) {
            cc.audioEngine.playMusic(this._bgmFile, true);
        }

        this._bindings = [
            notification.createBinding(notification.event.ROLE_DIE, this.onRoleDie, this),
            notification.createBinding(notification.event.ROLE_DISAPPEAR, this.onRoleDisappear, this),
            notification.createBinding(notification.event.ITEM_DISAPPEAR, this.onItemDisappear, this),
            notification.createBinding(notification.event.BATTLE_FINISH_RESULT, this.showFinishPanel, this)
        ];
    },

    onExit: function() {
        //LOG("SceneBase.onExit")

        this._camera = null;
        this._gameWorld = null;
        this._backUi = null;
        this._frontUi = null;
        this._physicalWorld = null;
        this._operator = null;
        this._battleUiLayer = null;
        this._coverView = null;

        cc.audioEngine.stopMusic();
        notification.removeBinding(this._bindings);

        this._super();
    },

    update: function(dt) {
        // hero pickup
        if(this._hero != null) {
            var hero = this._hero;
            _.each(this._items, function(item) {
                var heroPos = hero.getSpacePosition();
                var itemPos = item.getPosition();
                var pickRadius = cc.p(150, 150);

                if (Math.abs(heroPos.x - itemPos.x) <= pickRadius.x &&
                    Math.abs(heroPos.y - itemPos.y) <= pickRadius.y) {
                    item.flyToTarget(hero);
                }
            }, this);
        }

        // set target
        var that = this;
        function setMonsterTarget(monster, target) {
            var ai = monster.getRoleAi();
            if(ai.target == null){
                var targetPos = target.getSpacePosition();
                //var section = that._sceneStatus.sections[that._sectionIndex-1];
                //if(section && targetPos.x > section.warningLine){
                //    ai.target = target;
                //}
                if(targetPos.x > 400){
                    ai.target = target;
                }
            }
        }
        if(this._boss) {
            setMonsterTarget(this._boss, this._hero);
        }
        _.each(this._monsters, function(monster) {
            setMonsterTarget(monster, this._hero);
        }, this);

        //set map pos
        var tmpNode_ = this.getGameWorldNode();
        MapSystem.instance.setGameMapPos(tmpNode_.getPosition());
    },

    setBackgroundMusic: function(musicFile) {
        this._bgmFile = musicFile;
        if(this._bgmFile) {
            cc.audioEngine.preloadMusic(this._bgmFile);
        }
    },

    addItem: function(item) {
        item.setLocalZOrder(-item.getPosition().y);
        this._items.push(item);
        this._physicalWorld.addChild(item);
    },

    removeItem: function(item) {
        this._items = _.without(this._items, item);
        this._physicalWorld.removeChild(item);
    },

    removeAllItems: function() {
        _.each(this._items, function(item) {
            this._physicalWorld.removeChild(item);
        }, this);
        this._items = [];
    },

    onRoleDie: function(event, role) {
        switch (role.roleType) {
            case RoleBase.RoleType.Hero:
                break;

            case RoleBase.RoleType.Friend:
                break;

            case RoleBase.RoleType.Monster:
                role.disappear();
                break;

            case RoleBase.RoleType.Boss:
                break;
        }
    },

    onRoleDisappear: function(event, role) {
        var type = role.roleType;
        if(type == RoleBase.RoleType.Monster ||
            type == RoleBase.RoleType.Boss) {

            if(cc.random0To1() * 100 > 80){
                var item = new DroppedItem(101);
                var pos = role.getSpacePosition();
                item.setPosition(pos.x, pos.y);
                this.addItem(item);
            }
        }
    },

    onItemDisappear: function(event, item) {
        this.removeItem(item);
    },

    clearStreet: function() {
        if(this._hero) {
            this._hero.roleActionManager.decideStopAllAction();
            this._hero.setSpaceVelocity(0,0,0);
        }

        if(this._boss) {
            this._physicalWorld.removePhysicalNode(this._boss);
            this._boss = null;
        }

        _.each(this._monsters, function(monster) {
            this._physicalWorld.removePhysicalNode(monster);
        }, this);
        this._monsters = [];

        _.each(this._friends, function(friend) {
            this._physicalWorld.removePhysicalNode(friend);
        }, this);
        this._friends = [];

        _.each(this._items, function(item) {
            this._physicalWorld.removeChild(item);
        }, this);
        this._items = [];
    },

    play: function(status) {
        this._sceneStatus = status;
        // weather
        var tmpWeather = this._sceneStatus.stage.weather_file;
        if(tmpWeather) {
            this._weather = cc.ParticleSystem.create(tmpWeather);
            this._weather.setPositionType(cc.ParticleSystem.TYPE_RELATIVE);
            this._gameWorld.addChild(this._weather);
        }

        this._sectionIndex = 0;
        this.playNextSection();
    },

    playNextSection : function () {
        cc.audioEngine.stopAllEffects();
        this.clearStreet();
        this._sectionIndex++;
        var tmpSections = this._sceneStatus.BSection;
        if(this._sectionIndex <= tmpSections.length) {
            if (this._sectionIndex == tmpSections.length) {
                this._isLastSection = true;
            }

            if(this._isLastSection){
                this._battleUiLayer.setBossRound(true);
            }
            else{
                this._battleUiLayer.setBossRound(false);
            }

            //area
            var sec = tmpSections[this._sectionIndex -1];
            this.setGameWorldRect(sec.area);

            //street
            var streetRect = sec.street;
            LOG("STREET RECT x= " + streetRect.x);
            LOG("STREET RECT y= " + streetRect.y);
            LOG("STREET RECT w= " + streetRect.width);
            LOG("STREET RECT h= " + streetRect.height);

            this._physicalWorld.setPosition(cc.p(streetRect.x, streetRect.y));
            this._physicalWorld.setContentSize(streetRect.width, streetRect.height);
            MapSystem.instance.setGameMapRect(cc.rect(streetRect.x,streetRect.y,streetRect.width,streetRect.height));


            //hero
            if (this._hero == null) {
                var hero_id = this._sceneStatus.hero;
                var hero = hero_id instanceof Object ? new hero_id() : new Role(hero_id);
                hero.roleType = RoleBase.RoleType.Hero;
                hero.turn(RoleBase.Direction.Right);
                hero.setRoleAi(RoleAi.Type.Manual, {
                    joystick: this._operator._joystick,
                    attackButton: this._operator._attackButton,
                    skillButton1: this._operator._skillButton1,
                    skillButton2: this._operator._skillButton2,
                    skillButton3: this._operator._skillButton3,
                    skillButton4: this._operator._skillButton4,
                    skillButton5: this._operator._skillButton5,
                    btnCDTime1: 3,
                    btnCDTime2: 4,
                    btnCDTime3: 5,
                    btnCDTime4: 8,
                    btnCDTime5: 10
                });
                this._rolePanel.setRole(hero);
                this._physicalWorld.addPhysicalNode(hero);
                this._hero = hero;
            }


            this._hero.setSpacePosition(_.defaults(sec.heroPos, {x: 0., y: 0, z: 0}));
            this._camera.followNode(this._hero);
            //var actionData = this.actions[RoleAction.Type.SKILL5];
            //this._operator.setBtnTimingEnable(5,actionData.cdTime);


            //monster
            var monsterData = this._sceneStatus.BSection[this._sectionIndex-1].monsters;

            _.each(monsterData, function (data) {

                var roleConfig = configdb.role[data.roleId];
                var role = new Role(data.roleId);

                var isBoss = false;
                if (roleConfig.type == 1) {
                    role.roleType = RoleBase.RoleType.Monster;
                }
                else if (roleConfig.type == 2) {
                    role.roleType = RoleBase.RoleType.Boss;
                    isBoss = true;
                }

                role.setSpacePosition(_.defaults(cc.p(data.posX, data.posY), {x: 0., y: 0, z: 0}));
                role.setRoleAi(RoleAi.Type.XiaoGuai,{
                    atkPer    : data.ai.atkPer,
                    restPer   : data.ai.restPer,
                    rangeActW : data.ai.rangeActW,
                    rangeActH : data.ai.rangeActH,
                    followAtk : data.ai.followAtk,
                    isRemote  : data.ai.isRemote
                });
                role.turn(data.dir);
                role.setBloodBar(isBoss,roleConfig.name);

                switch (role.roleType) {
                    case RoleBase.RoleType.Monster:
                        this._monsters.push(role);
                        break;
                    case RoleBase.RoleType.Boss:
                        this._boss = role;
                        break;
                }
                this._physicalWorld.addPhysicalNode(role);

                if(role.roleType == RoleBase.RoleType.Boss){
                    this._bossPanel.setBoss(this._boss);
                }
            }, this);
        }

        //this.onBeforeFightChatStart();
        if(this._coverView.state == 1){
            var size = cc.director.getWinSize();
            this._coverView.runAction(cc.Sequence.create(
                cc.MoveBy.create(0.5,cc.p(size.width,0)),
                cc.CallFunc.create(function () {
                    this._coverView.state = 0;
                    this.onBeforeFightChatStart();
                },this)
            ));
        }
        else{
            this.onBeforeFightChatStart();
        }
    },

    onBeforeFightChatStart : function () {
        var tmpChatData = [];
        if(this._sectionIndex == 1){
            tmpChatData = this._sceneStatus.chatData.beforeFight;
        }
        else if(this._sectionIndex == this._sceneStatus.BSection.length){
            tmpChatData = this._sceneStatus.chatData.beforeBossFight;
        }

        if(tmpChatData && tmpChatData.length > 0){
            var dialog = new DialogPanel(tmpChatData);
            this._frontUi.addChild(dialog);

            dialog.setEndingCallback(function() {
                dialog.removeFromParent();
                this.onBeforeFightChatEnd();
            }.bind(this));
        }
        else{
            this.onBeforeFightChatEnd();
        }
    },

    onBeforeFightChatEnd: function() {
        this.onBattleStart();
    },

    onBattleStart: function() {
        this._battleUiLayer.setVisible(true);
        this._operator.setHide(true);
        if(this._sectionIndex == 1){
            var actionData = this._hero.roleActionManager.actions[RoleAction.Type.SKILL4];
            this._operator.setBtnTimingEnable(4,actionData.cdTime);
        }

        this.schedule(this.battleObserver);
    },
    onBattleEnd: function() {
        this.unschedule(this.battleObserver);
        if(this._isLostBattle){
            // show lose window
            var win = new BattleLosePanel();
            win.setCloseCallback(function(w) {
                if(w.exit) {
                    cc.director.popScene();
                }
            }, this);
            win.pop();
        }
        else{
            this.onAfterFightChatStart();
        }
    },
    battleObserver: function() {
        var end = false;

        if(this._hero && this._hero.deathValue == true) {
            // lose
            end = true;
            this._isLostBattle = true;
        }
        else if(_.every(this._monsters, function(monster) {
                return monster.deathValue == true;
            }, this)) {

            if(this._boss) {
                if(this._boss.deathValue == true && this._boss.roleActionManager.runningAction == null) {
                    end = true;
                    this._isLostBattle = false;
                }
            }
            else {
                // win
                end = true;
            }
        }

        if(end) {
            this.onBattleEnd();
        }
    },

    onGoForwardStart: function() {
        if(this._goForwardPanel == null) {
            var winSize = cc.director.getWinSize();
            this._goForwardPanel = new GoForwardPanel();
            this._goForwardPanel.setPosition(winSize.width * 0.8, winSize.height);
            this._frontUi.addChild(this._goForwardPanel);
        }

        this.schedule(this.goForwardObserver);
    },
    onGoForwardEnd: function() {
        this.unschedule(this.goForwardObserver);

        var that = this;
        function goNextSection(){
            if(that._goForwardPanel) {
                that._goForwardPanel.removeFromParent();
                that._goForwardPanel = null;
            }
            //that._rolePanel.setVisible(false);
            that._operator.setHide(false);
            that.playNextSection();
        }
        if(this._coverView.state == 0){
            var size = cc.director.getVisibleSize();
            this._coverView.setPosition(cc.p(-size.width,0));
            this._coverView.runAction(cc.Sequence.create(
                cc.MoveBy.create(0.5,cc.p(size.width,0)),
                cc.DelayTime.create(0.3),
                cc.CallFunc.create(function () {
                    this._coverView.state = 1;
                    goNextSection();
                },this)
            ));
        }
        else{
            goNextSection();
        }
    },
    goForwardObserver: function() {
        if(this._hero) {
            var pos = this._hero.getSpacePosition();
            var size = this._physicalWorld.getContentSize();
            if(pos.x >= size.width - 10) {
                this.onGoForwardEnd();
            }
        }
        else {
            this.onGoForwardEnd();
        }
    },

    onAfterFightChatStart : function () {
        if(this._isLastSection) {
            if(this._sceneStatus.chatData.afterFight.length > 0){
                var dialog = new DialogPanel(this._sceneStatus.chatData.afterFight);
                this._frontUi.addChild(dialog);

                dialog.setEndingCallback(function() {
                    dialog.removeFromParent();
                    this.battleFinish();
                }.bind(this));

                this._battleUiLayer.setVisible(false);
                this._operator.setHide(false);
            }
            else{
                this.battleFinish();
            }
        }
        else {
            this.onAfterFightChatEnd();
        }
    },
    onAfterFightChatEnd : function () {
        this.onGoForwardStart();
    },

    battleFinish: function() {
        BattleSystem.instance.battleFinish(true);
    },
    showFinishPanel: function() {
        this._operator.setHide(false);

        var win = new BattleWinPanel();
        win.setCloseCallback(this.onSceneFinished, this);
        win.pop();
    },

    onSceneFinished: function() {
        cc.audioEngine.stopMusic();
        ui.popScene();
    }
});


var PauseLayer = ui.GuiWindowBase.extend({
    _guiFile: "ui/pauseBattleLayer.json",

    ctor: function () {
        this._super();
    },

    onEnter: function () {
        this._super();
    },

    onExit : function () {
        this._super();
    },

    _on_btn_restart : function () {
        cc.director.resume();
        this.removeFromParent();
    },
    
    _on_btn_back : function () {
        cc.director.resume();
        ui.popScene();
    }
})

