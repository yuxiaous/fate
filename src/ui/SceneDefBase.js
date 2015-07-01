/*
* 守塔 模式
* */
 var SceneDefBase = SceneBase.extend({
    ctor: function(sceneName) {
        this._super(sceneName,SceneBase.Type.DefendType);

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

    playNextSection : function () {
        cc.audioEngine.stopAllEffects();
        this.clearStreet();
        this._sectionIndex += 1;
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

            if(this._sectionIndex == 1){
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

                var isBoss = false;
                if (roleConfig.type == 1) {
                    role.roleType = RoleBase.RoleType.Monster;
                }
                else if (roleConfig.type == 2) {
                    role.roleType = RoleBase.RoleType.Boss;
                    isBoss = true;
                }

                var pos = this.getMonsterPosWithHero(this._hero,tmpSections[this._sectionIndex -1].street);

                role.setSpacePosition(pos);
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
                role.aiData = data;

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

        this.onBeforeFightChatStart();
    },

    onBeforeFightChatEnd: function() {

        this._battleUiLayer.setVisible(true);
        this.refreshRoundTitle(this._sectionIndex,this._sectionAmount);

        //var countDownTime = 4;
        //var that = this;
        //function changeCountDownLabel(){
        //    countDownTime -= 1;
        //    var countDownLayer = that._frontUi.getChildByTag(1000);
        //    if(countDownLayer) {
        //        var countDownLabel = countDownLayer.getChildByTag(1000);
        //    }
        //
        //    if(countDownTime == -1){
        //        cc.director.getScheduler().unschedule("downTime",this);
        //        that.onBattleStart();
        //        that.setBossAndMonsterTarget();
        //        countDownLayer.removeAllChildren();
        //        countDownLayer.removeFromParent();
        //    }
        //    else{
        //        if(!countDownLayer){
        //            var countDownLayer = ccui.Layout.create();
        //            countDownLayer.setTag(1000);
        //            countDownLayer.setTouchEnabled(true);
        //            countDownLayer.addTouchEventListener(function(){
        //                LOG("TOUCH COUNT DOWN LAYER");
        //            },this);
        //            that._frontUi.addChild(countDownLayer,SceneDefBase.FrontUITag.countDownLayerTag);
        //
        //            countDownLabel = cc.LabelTTF.create(String(countDownTime));
        //            var size = cc.director.getWinSize();
        //            countDownLabel.setFontSize(200);
        //            countDownLabel.setTag(1000);
        //            countDownLabel.setPosition(cc.p(size.width/2,size.height/2));
        //
        //            countDownLayer.addChild(countDownLabel);
        //        }
        //        else{
        //            countDownLabel.setString(String(countDownTime));
        //        }
        //    }
        //}
        //changeCountDownLabel();
        //cc.director.getScheduler().schedule(changeCountDownLabel,this,1.0,cc.REPEAT_FOREVER,0,false,"downTime");
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

SceneDefBase.FrontUITag = {
    roleInfoPanel : 80,
    bossInfoPanel : 81,
    operatorTag : 100,
    countDownLayerTag : 110,
    dialogPanelTag : 120
}

