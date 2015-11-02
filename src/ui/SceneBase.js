
var SceneBase = lh.LHScene.extend({
    status: {

    },

    ctor : function (sceneName,curType_) {
        if(!sceneName.startsWith("scenes")){
            sceneName = "scenes/" + sceneName + ".lhplist";
        }
        this._super(sceneName);
        LOG(sceneName);

        this._hero = null;
        this._boss = null;
        this._monsters = [];
        this._friends = [];
        this._items = [];

        this._curSceneType = curType_;

        this._enterDropUi = 0;
        this._isEnteringEquipSuit = false;
       // this._LoadingNode = null;

        BattleSystem.instance.curBattleType = this._curSceneType;
    },

    onEnter : function () {
        this._super();

        var winSize = cc.director.getWinSize();
        var gameWorld = this.getGameWorldNode();
        var backUi = this.getBackUINode();
        var frontUi = this.getUINode();

        // street
        var street = this.getChildNodeWithName("street");
        var physicalWorld = new PhysicalWorld();
        physicalWorld.shakingNode = gameWorld;
        gameWorld.addChild(physicalWorld, street.getLocalZOrder());

        var foreUI = this.getChildNodeWithName("qian");

        // camera
        var camera = this.getChildNodeWithName("UntitledCamera");
        camera.setImportantAreaUnit(cc.size(0, 0));

        // operator panel
        var operator = new OperationLayer();
        operator.setVisible(false);
        operator.setEnable(false);
        frontUi.addChild(operator);

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
        this._street = street;
        this._foreUI = foreUI;


        if(this._bgmFile) {
            cc.audioEngine.playMusic(this._bgmFile, true);
        }

        var that = this;
        this._bindings = [
            notification.createBinding(notification.event.ROLE_DIE, this.onRoleDie, this),
            notification.createBinding(notification.event.ROLE_DISAPPEAR, this.onRoleDisappear, this),
            notification.createBinding(notification.event.ITEM_DISAPPEAR, this.onItemDisappear, this),
            notification.createBinding(notification.event.BATTLE_FINISH_RESULT, this.showFinishPanel, this),
            notification.createBinding(notification.event.BATTLE_ADD_SKILL_EFFECT, function () {
                if(!that._street.skillEL){
                    var skillEL = new SkillEffectLayer(that);
                    var mapPos = MapSystem.instance.getGameMapPos();
                    var maprect = MapSystem.instance.getGameMapRect();
                    var pos = cc.p(- mapPos.x + maprect.x,0);
                    skillEL.setPosition(pos);
                    that._street.addChild(skillEL);
                    that._street.skillEL = skillEL;
                }
            },this),
            notification.createBinding(notification.event.BATTLE_DEL_SKILL_EFFECT, function () {
                if(that._street.skillEL){
                    that._street.skillEL.delSkillEffect();
                    that._street.skillEL.removeFromParent();
                    that._street.skillEL = null;
                }
            },this),
            notification.createBinding(notification.event.BATTLE_HERO_REVIVE, function () {
                this._hero.deathValue = false;
                this._hero.roleDataManager.hp = this._hero.roleDataManager.maxHp;
                this._hero.roleDataManager.mp = this._hero.roleDataManager.maxMp;
                this._hero.roleActionManager.deathStatus = false;
                //this._hero.roleActionManager.playAction(RoleAction.Type.STAND_UP);
                LOG("PLAY REVIVE ACTION");

                this._hero.roleActionManager.playAction(RoleAction.Type.REVIVE);
                this._isLostBattle = false;
                this.schedule(this.battleObserver);
                this._operator.setHide(true);

                //notification.emit(notification.event.HERO_REVIVE_ATTACK, this._hero);
                //this._hero.reviveEffect(function () {
                //    this._hero.invincible();
                //
                //},this);

            },this),
            notification.createBinding(notification.event.PLAYER_INFO, function () {
                var system = PlayerSystem.instance;
                this._operator.setBtnReleaseCount(4,system.superSkillCount);
            }, this),
            notification.createBinding(notification.event.BATTLE_RECOVER_STATE, function () {
                //cc.director.resume();
                notification.emit(notification.event.GAME_RESUME);
            },this),

            notification.createBinding(notification.event.GAME_PAUSE, function () {
                LOG("game pause game scene");
                BattleSystem.instance._isStop = true;
                MusicManager.getInstance().pauseBGM();
            },this),
            notification.createBinding(notification.event.GAME_RESUME, function () {
                LOG("game resume game scene");
                BattleSystem.instance._isStop = false;
                MusicManager.getInstance().resumeBGM();
            },this),
            notification.createBinding(notification.event.BATTLE_END, function () {
                _.each(this._items, function(item) {
                    if(item._dropType == DroppedItem.DropType.ItemType){
                        item.flyToTarget(this._hero);
                    }
                }, this);
            },this)

        ];

        //this.scheduleUpdate();

        //if( this._LoadingNode ) {
        //    this._LoadingNode.close();
        //}

    },

    //initBattleData : function (map_id_) {
    //    var skin = SkinSystem.instance.use_skin;
    //    if(skin == 101){
    //        this.status.hero = Saber;
    //    }
    //    else if(skin == 102){
    //        this.status.hero = Nero;
    //    }
    //
    //    this.status.stage = BattleNorScene.initStageInfo(map_id_);
    //    this.status.BSection = BattleNorScene.initBattleSection(map_id_);
    //    this.status.chatData = BattleNorScene.initChatInfo(map_id_);
    //},

    onExit : function () {

        this._hero = null;
        this._boss = null;
        this._camera = null;
        this._gameWorld = null;
        this._backUi = null;
        this._frontUi = null;
        this._physicalWorld = null;
        this._operator = null;
        this._battleUiLayer = null;
        this._coverView = null;
        this._street = null;

        cc.audioEngine.stopMusic();
        notification.removeBinding(this._bindings);

        this._super();
    },
    
    update : function (dt) {
        if(this._isEnteringEquipSuit == false){
            if(this._enterDropUi < 60){
                this._enterDropUi += 1;
            }
        }

        // hero pickup
        if(this._hero != null) {
            var hero = this._hero;
            _.each(this._items, function(item) {
                var heroPos = hero.getSpacePosition();
                var itemPos = item.getPosition();
                var pickRadius = cc.p(150, 150);
                if (Math.abs(heroPos.x - itemPos.x) <= pickRadius.x &&
                    Math.abs(heroPos.y - itemPos.y) <= pickRadius.y) {
                   if(item._dropType == DroppedItem.DropType.ItemType){
                        item.flyToTarget(hero);
                    }
                }

                if(GiftSystem.instance.getGiftBuyNumWith(GiftSystem.GiftType.WuQi) <= 0 && item._dropType == DroppedItem.DropType.DaBaoJianType && !this._isEnteringEquipSuit && this._enterDropUi >= 60) {
                    var enterRadius = cc.p(70, 100);
                    if (Math.abs(heroPos.x - itemPos.x) <= enterRadius.x
                        && Math.abs(heroPos.y - itemPos.y) <= enterRadius.y
                        && this._street.skillEL == null) {

                        this._isEnteringEquipSuit = true;
                        item.entranceBuyEquipSuit(hero, this);
                    }
                }
            }, this);
        }

        //set map pos
        var tmpNode_ = this.getGameWorldNode();
        MapSystem.instance.setGameMapPos(tmpNode_.getPosition());
    },
    
    setBackgroundMusic : function (musicFile) {
        this._bgmFile = musicFile;
        if(this._bgmFile) {
            cc.audioEngine.preloadMusic(this._bgmFile);
        }
    },
    
    addItem : function (item) {
        item.setLocalZOrder(-item.getPosition().y);
        this._items.push(item);
        if(this._physicalWorld){
            this._physicalWorld.addChild(item);
        }
    },
    
    removeItem : function (item) {
        this._items = _.without(this._items, item);
        if(this._physicalWorld) {
            this._physicalWorld.removeChild(item);
        }
    },
    
    removeAllItems : function(){
        _.each(this._items, function(item) {
                if(this._physicalWorld) {
                    this._physicalWorld.removeChild(item);
                }
        }, this);
        this._items = [];
    },
    
    onRoleDie : function (event,role) {
        switch (role.roleType) {
            case RoleBase.RoleType.Hero:
                //this.clearMonsterTarget();
                break;
            case RoleBase.RoleType.Friend:
                break;

            case RoleBase.RoleType.Monster:
                role.disappear();
                MissionSystem.instance.countKillMonster();
                break;

            case RoleBase.RoleType.Boss:
                MissionSystem.instance.countKillMonster();
                break;
        }
    },
    
    onRoleDisappear : function (event,role) {
        var type = role.roleType;
        if(type == RoleBase.RoleType.Monster ||
            type == RoleBase.RoleType.Boss) {
            if(GiftSystem.instance.getGiftBuyNumWith(GiftSystem.GiftType.WuQi) <= 0 && role.dropId != undefined){
                var dropId = role.dropId || 101002;
                var dropType = DroppedItem.DropType.DaBaoJianType;
                var dropItem = new DroppedItem(dropId,dropType);
                var pos = role.getSpacePosition();

                var size = MapSystem.instance.getGameMapRect();
                var tmpValue = 0;
                if(pos.x >= size.width - 300){
                    tmpValue = - 300;
                }
                else if(pos.x <= 300){
                    tmpValue = 300;
                }
                dropItem.setPosition(pos.x + tmpValue,pos.y);
                this.addItem(dropItem);
                return;
            }

            //if(this._curSceneType != SceneBase.Type.EndlessType && cc.random0To1() * 100 > 40){
            //    var itemId = 100005;
            //    var dropType = DroppedItem.ItemType.BloodType;
            //    if(cc.random0To1() * 100 > 50){
            //        itemId = 100006;
            //        dropType = DroppedItem.ItemType.MagicType;
            //    }
            //    var item = new DroppedItem(itemId,dropType);
            //    var pos = role.getSpacePosition();
            //    item.setPosition(pos.x, pos.y);
            //    this.addItem(item);
            //}

            if(this._curSceneType == SceneBase.Type.EndlessType){
                return;
            }

            if(BattleSystem.instance.curIsTryBattle()){
                return;
            }

            var dropItemInfo_ =  BattleSystem.instance.getCurDropItemData(this._sceneStatus.maxMonster,role.idx);

            //if(dropItemInfo_.item_id){
            //    for(var idx = 0 ; idx < dropItemInfo_.item_num; idx++){
            //        var dropItem = new DroppedItem(parseInt(dropItemInfo_.item_id),DroppedItem.DropType.ItemType );
            //        var pos = BattleSystem.instance.randomDropItemPos(role,dropItemInfo_.item_num);
            //        dropItem.setPosition(pos);
            //        this.addItem(dropItem);
            //    }
            //}

            if(dropItemInfo_.item_id){
                var that = this;
                function addItemFunc(itemId_,itemNum_, isLarge_,allNum_){
                    for(var idx = 0 ; idx < itemNum_; idx++){
                        var dropItem = new DroppedItem(parseInt(itemId_),DroppedItem.DropType.ItemType );
                        var pos = BattleSystem.instance.randomDropItemPos(role,allNum_);
                        dropItem.setPosition(pos);
                        if(isLarge_){
                            dropItem.setScale(1.2);
                        }
                        else{
                            dropItem.setScale(0.8);
                        }
                        that.addItem(dropItem);
                    }
                };

                 if(dropItemInfo_.largeNum > 0){
                    addItemFunc(dropItemInfo_.item_id,dropItemInfo_.largeNum,true,dropItemInfo_.allNum);
                 }

                 if(dropItemInfo_.smallNum > 0){
                     addItemFunc(dropItemInfo_.item_id,dropItemInfo_.smallNum,false,dropItemInfo_.allNum);
                 }
            }

        }
    },
    
    onItemDisappear : function (event,item) {
        this.removeItem(item);
    },
    
    clearStreet : function () {
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

    clearMonsterTarget : function () {
        _.each(this._monsters, function(monster) {
            if(monster){
                monster.setRoleAi(RoleAi.Type.Stake);
            }
        }, this);

        if(this._boss){
            this._boss.setRoleAi(RoleAi.Type.Stake);
        }
    },

    onBattleStart: function() {
        this._battleUiLayer.setVisible(true);
        this._operator.setHide(true);

        this._operator.setSkillBtnOpenEffect();

        //if(this._sectionIndex == 1){
        //    //var actionData = this._hero.roleActionManager.actions[RoleAction.Type.SKILL4];
        //    //this._operator.setBtnTimingEnable(4,actionData.cdTime);
        //    var playersys = PlayerSystem.instance;
        //    //playersys.superSkillCount += 1;
        //    this._operator.setBtnReleaseCount(4,playersys.superSkillCount);
        //}

            var playersys = PlayerSystem.instance;
            this._operator.setBtnReleaseCount(4,playersys.superSkillCount);
        
        this.schedule(this.battleObserver);

        if(MapSystem.instance.max_map_id == 101 && this._sectionIndex == 1){
            var cover_tmp = new CaoZuoJiaoXue();
            cover_tmp.pop();
        }
    },

    onBattleEnd: function() {
        this.unschedule(this.battleObserver);
        if(this._isLostBattle){
            if(BattleSystem.instance.curIsTryBattle()){
                notification.emit(notification.event.BATTLE_TRY_TYPE_END,false);
            }
            else{
                // show revive window
                var revive = new BattleRevivePanel(this._curSceneType,this._sectionIndex);
                revive.pop();
            }
        }
        else{
            this.onAfterFightChatStart();
        }
    },

    battleObserver : function () {
        var end = false;

        if(this._hero && this._hero.deathValue == true) {
            // lose
            end = true;
            this._isLostBattle = true;
            this._operator.setHide(false);
        }
        else if(this._boss){
            if(this._boss.deathValue == true){
                this._operator.setHide(false);
                _.each(this._monsters, function(monster) {
                    monster.roleDataManager.hp = 0;
                    monster.setBloodBar();
                    monster.die();
                }, this);
            }

            if(this._boss.deathValue == true && this._boss.roleActionManager.runningAction == null) {
                end = true;
                this._isLostBattle = false;
            }
        }
        else if(_.every(this._monsters, function(monster) {
                return monster.deathValue == true && monster.roleActionManager.runningAction == null;
            }, this)) {

            if(this.nextMonsterWave() == false) {
                end = true;
                this._isLostBattle = false;
            }

        }

        if(end) {
            this.onBattleEnd();
        }
    },

    battleFinish : function () {
        if(BattleSystem.instance.curIsTryBattle()){
            notification.emit(notification.event.BATTLE_TRY_TYPE_END,true);
        }
        else{
            notification.emit(notification.event.BATTLE_END);
            BattleSystem.instance.battleFinish(true);
        }
    },

    showFinishPanel : function () {
        LOG("show finish panel ");
        this._operator.setHide(false);
        var mapId = BattleSystem.instance.cur_battle_map
        var mapConf = configdb.map[mapId];
        if( mapConf && mapConf.drop_gift){
            var revive = null;
            switch (GiftSystem.instance.randomSellGiftPanel()) {
                case  GiftSystem.GiftType.Vip :
                    revive = new GiftDetailVip();
                    break;
                case GiftSystem.GiftType.ZhiZun :
                    revive = new GiftDetailZhiZun();
                    break;
                case GiftSystem.GiftType.ZhuangBei :
                    revive = new GiftDetailSuit();
                    break;
                case GiftSystem.GiftType.WuQi :
                    revive = new GiftDetailWeapon();
                    break;
                default  :
                    revive = new GiftDetailZhiZun();
                    break;
            }
            //var revive = new GiftBuyDetail(giftType,giftId);
            if(revive) {
                revive.setCloseCallback(function () {
                    var win = new BattleWinPanel();
                    win.setCloseCallback(this.onSceneFinished, this);
                    win.pop();
                },this);
                revive.pop();
                //UiEffect.iconOpenEffect(revive.seekWidgetByName("gift_panel"));
            }
        }
        else{
            var win = new BattleWinPanel();
            win.setCloseCallback(this.onSceneFinished, this);
            win.pop();
        }
    },

    onSceneFinished : function (){
        cc.audioEngine.stopMusic();
        ui.popScene();
    },

    play: function(status,startIndex_,isFirst_) {
        var that = this;
        //var sel_map_id = BattleSystem.instance.cur_battle_map;
        //that.initBattleData(sel_map_id);
        that._sceneStatus = status;
        // weather
        var tmpWeather = that._sceneStatus.stage.weather_file;
        if(tmpWeather) {
            that._weather = cc.ParticleSystem.create(tmpWeather);
            that._weather.setPositionType(cc.ParticleSystem.TYPE_RELATIVE);
            that._gameWorld.addChild(that._weather);
        }

        that._sectionIndex = startIndex_ || 0;
        that._sectionAmount = that._sceneStatus.BSection.length;
        that.playNextSection(isFirst_);
        that.scheduleUpdate();
    },

    playNextSection : function () {
        cc.audioEngine.stopAllEffects();
        this.clearStreet();
        this._sectionIndex++;
        if(this._sectionIndex > 1){
            BattleSystem.instance.refreshBattleTryTypeStatus();
        }

        var tmpSections = this._sceneStatus.BSection;
        if(this._sectionIndex <= this._sectionAmount) {
            if (this._sectionIndex == this._sectionAmount) {
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

            this._physicalWorld.setPosition(cc.p(streetRect.x, streetRect.y));
            this._physicalWorld.setContentSize(streetRect.width, streetRect.height);
            MapSystem.instance.setGameMapRect(cc.rect(streetRect.x,streetRect.y,streetRect.width,streetRect.height));


            //hero
            if (this._hero == null) {
                var hero_id = this._sceneStatus.hero;

                //if(MapSystem.instance.max_map_id == 104){
                //    hero_id = Nero;
                //}

                if(BattleSystem.instance.curIsTryBattle()){
                    hero_id = BattleSystem.instance.getTryBattleHero();
                }

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

            //monster
            this._waveIndex = 0;
            this.nextMonsterWave();
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

    nextMonsterWave: function() {
        this._waveIndex++;

        var monsterData = this._sceneStatus.BSection[this._sectionIndex-1].monsters[this._waveIndex-1];
        if(monsterData == undefined) {
            return false;
        }

        _.each(monsterData, function (data) {
            var roleConfig = configdb.role[data.roleId];
            var role = new Role(data.roleId);

            // play effect
            var effectName = "shuaguai/daiji".split('/');
            var effectNode = dragonBones.DragonBonesHelper.buildArmatureNode(effectName[0]);
            if(effectNode) {
                //effectNode.registerFrameEventHandler(function(node, frameLabel) {
                //    if(frameLabel == "emitDisappear") {
                //        this.armatureNode.setVisible(false);
                //    }
                //}.bind(this));
                effectNode.registerMovementEventHandler(function(node, type) {
                    if(type == "complete") {
                        effectNode.removeFromParent();
                    }
                }.bind(this));
                if(effectNode.gotoAndPlay(effectName[1])) {
                    role.addChild(effectNode, 999);
                }
            }

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
            role.aiData = data;
            role.dropId = data.dropId;
            role.idx = data.idx;
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

        return true;
    },

    onBeforeFightChatStart : function () {
        var tmpChatData = [];
        if(this._sceneStatus.chatData){
            if(this._sectionIndex == 1){
                tmpChatData = this._sceneStatus.chatData.beforeFight;
            }
            else if(this._sectionIndex == this._sceneStatus.BSection.length){
                tmpChatData = this._sceneStatus.chatData.beforeBossFight;
            }
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
           // that._isEnteringEquipSuit = true;
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
    }
});

SceneBase.Type = {
    NormalType : 1,
    DefendType : 2,
    EndlessType : 3,
    GuideType: 4
};


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
        notification.emit(notification.event.GAME_RESUME);
        this.close();
    },

    _on_btn_back : function () {
        notification.emit(notification.event.GAME_RESUME);
        ui.popScene();

        sdk_manager.sendSdkCommand("TalkingDataGA", "onFailed",
            "map.{missionId},{failedCause}".format({
                missionId: BattleSystem.instance.cur_battle_map,
                failedCause: "玩家暂停退出"
            }));
    },

    _on_keyboard_back: function() {
        this._on_btn_restart();
    }
});