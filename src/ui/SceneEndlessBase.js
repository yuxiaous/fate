/*
 * 无尽 模式
 * */
var SceneEndlessBase = SceneBase.extend({
    ctor: function(sceneName) {
        this._super(sceneName,SceneBase.Type.EndlessType);

        this._sectionIndex = 0;
        this._sectionAmount = 0;
    },

    onEnter: function() {
        this._super();
        var winSize = cc.director.getWinSize();

        this._defBindings = [
            notification.createBinding(notification.event.BATTLE_DEL_SKILL_EFFECT, function () {
                this.setBossAndMonsterTarget();
            },this)
        ]
    },

    onExit: function() {

        notification.removeBinding(this._defBindings);
        this._super();
    },

    setBossAndMonsterTarget : function () {
        // set target
        var that = this
        function setMonsterTarget(monster, target) {
            var ai = monster.getRoleAi();
            if(ai.target == null){
                var targetPos = target.getSpacePosition();
                ai.target = target;
            }
        }
        if(this._boss) {
            setMonsterTarget(this._boss, this._hero);
        }
        _.each(this._monsters, function(monster) {
            setMonsterTarget(monster, this._hero);
        }, this);
    },

    clearStreet: function() {
        //if(this._hero) {
        //    this._hero.roleActionManager.decideStopAllAction();
        //    this._hero.setSpaceVelocity(0,0,0);
        //}

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

    playNextSection : function (isFirst_) {
        cc.audioEngine.stopAllEffects();
        this.clearStreet();

           if(!isFirst_) {
               this._sectionIndex += 1;
               BattleSystem.instance.updateEndlessBattleRound(this._sectionIndex);
           }


        var tmpSections = this._sceneStatus.BSection;

        if(this._sectionIndex <= this._sectionAmount) {
            if (this._sectionIndex == this._sectionAmount) {
                this._isLastSection = true;
            }

            this._battleUiLayer.setBossRound(false);

            if(this._sectionIndex == 1 || isFirst_){
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
            }

            //monster
            var monsterData = this._sceneStatus.BSection[this._sectionIndex-1].monsters;

            _.each(monsterData, function (data) {
                var roleConfig = configdb.role[data.roleId];
                var role = new Role(data.roleId);
                role.setRoleData({
                    hp:                data.hpValue,
                    atk:               data.atkValue,
                    crit_probability : data.crit_pro,
                    crit :             data.crit
                });

               // if (roleConfig.type == 1) {
                    role.roleType = RoleBase.RoleType.Monster;
               // }

                var pos = this.getMonsterPosWithHero(this._hero,tmpSections[this._sectionIndex -1].street);
                var isRemote = 0;
                if(roleConfig.throw_model_id != undefined){
                    isRemote = 1;
                }
                role.setSpacePosition(pos);
                role.setRoleAi(RoleAi.Type.XiaoGuai,{
                    atkPer    : data.ai.atkPer,
                    restPer   : data.ai.restPer,
                    rangeActW : data.ai.rangeActW,
                    rangeActH : data.ai.rangeActH,
                    followAtk : data.ai.followAtk,
                    isRemote  : isRemote
                });
                role.setBloodBar();
                role.aiData = data;
                this._monsters.push(role);
                this._physicalWorld.addPhysicalNode(role);
            }, this);
        }


        this.onBeforeFightChatStart();
    },

    onBeforeFightChatEnd: function() {

        this._battleUiLayer.setVisible(true);
        this.refreshRoundTitle(this._sectionIndex,this._sectionAmount);
    },

    onAfterFightChatEnd : function () {
        //this._battleUiLayer.setVisible(true);
        this._operator.setHide(false);
        this.playNextSection();
    },

    refreshRoundTitle : function (curRound_,maxRound_) {
        this._battleUiLayer.startActionRoundLabel(curRound_, function () {
            this.onBattleStart();
            this.setBossAndMonsterTarget();
        },this);
    },

    getMonsterPosWithHero : function (hero_, worldRect_) {
        var heroPos = hero_.getSpacePosition();
        var retPos = {x:0,y:0,z:0};
        var conValue = 300;
        var hadRandPos = false;
        if(heroPos.x > worldRect_.width/2){
            retPos.x = _.random(0,conValue);
            hadRandPos = true;
        }

        if(!hadRandPos || _.random(0,10) > 5){
            if(heroPos.x < worldRect_.width/2){
                retPos.x = _.random(worldRect_.width - conValue , worldRect_.width);
            }
        }

        retPos.y = _.random(0,worldRect_.height);
        return retPos;
    }
});