/**
 * Created by yuxiao on 15/4/16.
 */


var RoleBase = PhysicalNode.extend({
    ctor: function(armatureName, designDirection) {
        // setter
        this.roleSize = null;
        this.roleType = RoleBase.RoleType.Unknown;
        this.designDirection = designDirection;
        this.speed = 300;
        this.comboNumber = 1;
        this.comboTime = 0.4;
        this.injureTime = 0.5;
        this.invincibleTime = 1;
        this.roleType = 0;
        this.viewLength = 200;
        this.throwModelId = null;
        this.independent = false;

        // status
        this.direction = 0;
        this.attackValue = false;
        this.movingValue = false;
        this.skillValue = 0;
        this.injureValue = false;
        this.floatingValue = false;
        this.deathValue = false;
        this.invincibleValue = false;

        this.invincibleClock = 0;

        //投掷物品容器  items : throwBase
        this.throwWeaponContain = [];

        // armature
        this.armatureName = armatureName;
        this.armatureNode = null;

        // manager
        this.roleAiManager = new RoleAiManager(this);
        this.roleActionManager = new RoleActionManager(this);
        this.roleDataManager = new RoleDataManager(this);

        //this.init();
        this._super();
    },

    addThrowWeaponItem : function (throwItem_) {
        this.throwWeaponContain.push(throwItem_);
    },

    init: function() {
        var armatureNode = dragonBones.DragonBonesHelper.buildArmatureNode(this.armatureName, this.independent);
        this.addChild(armatureNode);

        //if(this.roleType == RoleBase.RoleType.Boss){
        //    var underFootE = dragonBones.DragonBonesHelper.buildArmatureNode("guanghuan");
        //    underFootE.gotoAndPlay("guanghuan");
        //    this.addChild(underFootE,-1);
        //}
        //else{
        //    this.setShadow(200);
        //}

        this.armatureNode = armatureNode;
        this.roleSize = this.getBoneBox("body");
    },

    dispose: function() {
        this._super();
    },

    injuredToRed : function(){
        var that = this;
        that.armatureNode.setColor(cc.color(150,0,0));
        function changeColor(){
            var redV = that.armatureNode.getColor().r + 25;
            if(redV >= 255){
                redV = 255;
            }
            that.armatureNode.setColor(cc.color(redV,0,0));
            callChange();
        }
        function revertColor(){
            that.armatureNode.setColor(cc.color(255,255,255));
        }

        function callChange(){
            if(that.armatureNode.getColor().r != 255){
                that.armatureNode.runAction(cc.Sequence.create(cc.DelayTime.create(0.05),
                    cc.CallFunc.create(changeColor)));
            }
            else{
                that.armatureNode.runAction(cc.Sequence.create(cc.DelayTime.create(0.2),
                    cc.CallFunc.create(revertColor)));
            }
        }
        callChange();
    },

    onEnter: function() {
        this._super();

        if(this.roleType == RoleBase.RoleType.Boss){
            //var underFootE = dragonBones.DragonBonesHelper.buildArmatureNode("guanghuan");
            //underFootE.gotoAndPlay("guanghuan");
            //this.addChild(underFootE,-1);
            this.setGuanghuan();
        }
        else{
            this.setShadow(200);
        }

        this._bindings = [
            notification.createBinding(notification.event.ROLE_ATTACK, this.onAttackJudgement, this),
            notification.createBinding(notification.event.HERO_REVIVE_ATTACK,this.onAllInjure,this),
            notification.createBinding(notification.event.THROW_UPDATE, function () {
               // LOG("THROW UPDATE =" + this.throwWeaponContain.length);

            },this)
        ];

        if(this.armatureNode) {
            var roleActionManager = this.roleActionManager;
            var attacker = this;
            var armatureNode = this.armatureNode;

            armatureNode.registerFrameEventHandler(function(node, frameLabel) {
                //LOG("registerFrameEventHandler, label: {0}".format(frameLabel));
                var action;
                switch (frameLabel) {
                    case "emitAttack":
                    case "emitweapon":
                        notification.emit(notification.event.ROLE_ATTACK, attacker);
                        break;
                    case "emitthrow":
                        action = roleActionManager.runningAction;
                        if(action && action.onThrowWeapon){
                            action.onThrowWeapon();
                        }
                        break;
                    case "emitSound":
                        action = roleActionManager.runningAction;
                        if(action && action.onAttackSound) {
                            action.onAttackSound();
                        }
                        break;
                    case "emitMove":
                    case "attackmovement":
                        action = roleActionManager.runningAction;
                        if(action && action.onAttackMove) {
                            action.onAttackMove();
                        }
                        break;
                }
            });
            armatureNode.registerMovementEventHandler(function(node, type) {
                //LOG("registerMovementEventHandler, type: {0}".format(type));
                switch(type) {
                    case "complete":
                        if(roleActionManager) {
                            roleActionManager.onActionComplete();
                        }
                        break;
                    case "fadeInComplete":
                        armatureNode.setVisible(true);
                        break;
                }
            });
            armatureNode.setVisible(false);
        }
    },

    onExit: function() {
        this._super();

        notification.removeBinding(this._bindings);

        if(this.armatureNode) {
            this.armatureNode.unregisterFrameEventHandler();
            this.armatureNode.unregisterMovementEventHandler();
        }
    },

    advanceTime: function(dt) {
        this._super();

        // floating
        this.floatingValue = this.altitude > 0;

        // invincible
        if(this.invincibleClock > 0) {
            this.invincibleClock -= dt;
            this.invincibleValue = true;
        }
        else {
            this.invincibleValue = false;
        }

        if(this.roleAiManager) {
            this.roleAiManager.advanceTime(dt);
        }
        if(this.roleActionManager) {
            this.roleActionManager.advanceTime(dt);
        }

        this.movingValue = false;
        this.attackValue = false;
        this.injureValue = false;
        this.skillValue = 0;
    },

    turn: function(dir) {
        if(this.roleActionManager && !this.roleActionManager.canMove()) {
            return;
        }

        var direction = dir < 0 ? RoleBase.Direction.Left : RoleBase.Direction.Right;
        if(this.direction == direction)
            return;

        this.direction = direction;
        switch (direction) {
            case RoleBase.Direction.Left:
                this.armatureNode.setScaleX(-this.designDirection);
                break;

            case RoleBase.Direction.Right:
                this.armatureNode.setScaleX(this.designDirection);
                break;
        }
    },

    move: function(offset) {
        this.movingValue = true;

        if(this.roleActionManager && this.roleActionManager.canMove()) {
            var pos = this.getSpacePosition();
            this.setSpacePosition(pos.x + offset.x, pos.y + offset.y, pos.z);
        }
    },

    attack: function() {
        this.attackValue = true;
    },

    skill: function(id) {
        this.skillValue = id;
    },

    injure: function(attacker) {
        this.injureValue = true;
        //damage
        var damageData = BattleSystem.getAtkActualValue(attacker,this);

        var damageValue = damageData.damageValue;
        if( damageValue <= 0){
            damageValue = 1;
        }

        var hp = this.roleDataManager.hp - damageValue;
        this.roleDataManager.hp = hp < 0 ? 0 : hp;

        DamageWorld.createDamage(damageValue,this,this.roleSize, damageData.isCrit);

        this.updateBloodBar();

        // this.injuredToRed();
        if(hp <= 0){
            this.die();
        }
    },

    hit: function(defender) {
        var action = this.roleActionManager.runningAction;
        if(action && action.onHitTarget) {
            action.onHitTarget(defender);
        }
    },

    die: function() {

        //if(this.roleType == RoleBase.RoleType.Boss){
        //var curScenePhyWorld = cc.director.getRunningScene()._physicalWorld;
        //    _.each(curScenePhyWorld.physicalNodes, function (roleItem_) {
        //        if(roleItem_.roleType != RoleBase.RoleType.Hero){
        //            roleItem_.roleDataManager.hp = 0;
        //            roleItem_.updateBloodBar();
        //            roleItem_.deathValue = true;
        //        }
        //    });
        //}

        this.deathValue = true;
    },

    disappear: function() {
        //var disappear = cc.sequence(
        //    cc.delayTime(2),
        //    cc.callFunc(function() {
        //        this.onDisappear();
        //    }, this)
        //);
        //var duration = disappear.getDuration();
        //var blink = cc.blink(duration, duration / 0.25);
        //this.armatureNode.runAction(cc.spawn(disappear, blink));

        var effectName = "guai_siwang/daiji".split('/');
        var effectNode = dragonBones.DragonBonesHelper.buildArmatureNode(effectName[0]);
        if(effectNode) {
            effectNode.registerFrameEventHandler(function(node, frameLabel) {
                if(frameLabel == "emitDisappear") {
                    this.armatureNode.setVisible(false);
                }
            }.bind(this));
            effectNode.registerMovementEventHandler(function(node, type) {
                if(type == "complete") {
                    effectNode.removeFromParent();
                    this.onDisappear();
                }
            }.bind(this));
            if(effectNode.gotoAndPlay(effectName[1])) {
                this.addChild(effectNode, 999);
                MusicManager.getInstance().playEffectMusic("res/sounds/roleSound/guai_xiaoshi.mp3");
            }
        }
    },

    invincible: function() {
        this.invincibleClock = this.invincibleTime;
        if(this.roleType == RoleBase.RoleType.Hero){
            var wudiEffect = dragonBones.DragonBonesHelper.buildArmatureNode("wudi");
            wudiEffect.gotoAndPlay("wudi");
            this.armatureNode.addChild(wudiEffect);
            wudiEffect.registerMovementEventHandler(function(node, type) {
                switch(type) {
                    case "complete":
                        node.removeFromParent();
                        break;
                    default :
                        break;
                }
            });
        }
        else{
            var duration = this.invincibleTime;
            var blink = cc.blink(duration, duration / 0.2);
            this.armatureNode.runAction(blink);
        }
    },

    reviveEffect : function (func_,target_) {
        var reviveEffect = dragonBones.DragonBonesHelper.buildArmatureNode("fuhuo");
        reviveEffect.gotoAndPlay("fuhuo");
        this.addChild(reviveEffect,-1);
        this.invincibleClock = 1000;
        reviveEffect.registerMovementEventHandler(function(node, type) {
            switch(type) {
                case "complete":
                    this.invincibleClock = 0;
                    node.removeFromParent();
                    func_.apply(target_);
                    break;
                default :
                    break;
            }
        });
    },

    playAnimation: function(name) {
        return this.armatureNode.gotoAndPlay(name);
    },

    onAttackJudgement: function(event, attacker,attackBox_,throwWeapon_) {
        if(this.deathValue) {
            return;
        }
        attackBox_ = (attackBox_ == undefined ? attacker.getAttackBox() : attackBox_);
        if( attacker == null ||
            attacker == this ||
            this.invincibleValue ||
            !this.JudgeIsEnemy(attacker.roleType)||
            !cc.rectIntersectsRect(attackBox_, this.getBodyBox()))
            return;

        //NOTIFICATION HERO COMBO
        if(attacker.roleType == RoleBase.RoleType.Hero){
            notification.emit(notification.event.ROLE_HIT)
        }

        //当前武器命中目标
        if(throwWeapon_ != undefined){
            throwWeapon_.weaponHitTheTarget();
        }

        // hit feedback
        attacker.hit(this);

        // injure
        this.injure(attacker);
    },

    onAllInjure : function (event,attacker) {
        if(this.deathValue){
            return;
        }

        if(attacker == this){
            return;
        }

        // hit feedback
        attacker.hit(this);

        // injure
        this.injure(attacker);
    },

    onFloatingUp: function() {

    },

    onTouchGround: function() {

    },
    onTouchGroundEnd: function() {
        this.invincible();
    },

    onStandUp: function() {

    },

    onAttackEnd: function() {

    },

    onSkillEnd: function() {

    },

    onDie: function() {
        notification.emit(notification.event.ROLE_DIE, this);
    },

    onDisappear: function() {
        notification.emit(notification.event.ROLE_DISAPPEAR, this);

        this.setVisible(false);
    },

    getBoneBox: function(name) {
        var box = this.armatureNode.getBoundingBox(name);

        var flip = (this.direction * this.designDirection) < 0;
        if(flip) {
            box.x = -box.x - box.width;
        }

        var sc = this.getScale();
        if(sc != 1) {
            box.x *= sc;
            box.y *= sc;
            box.width *= sc;
            box.height *= sc;
        }

        return cc.rect(box.x, box.y, box.width, box.height);
    },

    getBodyBox: function() {
        var box = this.getBoneBox("body");
        var pos = this.getSpacePosition();
        return cc.rect(pos.x + box.x, pos.y, box.width, 0);
    },

    getAttackBox: function() {
        var box = this.getBoneBox("attack");
        var pos = this.getSpacePosition();
        return cc.rect(pos.x + box.x, pos.y + box.y, box.width, box.height);
    },

    getBestAtackRange : function () {
        var box = this.getBoneBox("lock");
        var pos = this.getSpacePosition();
        return cc.rect( box.x, box.y, box.width, box.height);
    },

    getBestThrowPos : function () {
       var box = this.getBoneBox("throw");

        return cc.p(box.x,box.y);
    },

    setRoleAi: function(type, attr) {
        var ai = null;
        switch (type) {
            case RoleAi.Type.Stake:  ai = new StakeAi(); break;
            case RoleAi.Type.Manual: ai = new ManualAi(); break;
            case RoleAi.Type.Auto:   ai = new AutoAi(); break;
            case RoleAi.Type.XiaoGuai: ai = new XiaoGuaiAi();break;
            case RoleAi.Type.Show: ai = new ShowAi(); break;
        }

        if(ai && attr) {
            _.extend(ai, attr);
        }

        if(this.roleAiManager) {
            this.roleAiManager.setAi(ai);
        }
    },

    getRoleAi : function () {
        return this.roleAiManager.ai;
    },

    setBloodBar : function (isTitle_,titleName_) {
        if(isTitle_ != undefined && isTitle_){
            if(!this._roleTitle){
                this._roleTitle = new cc.LabelTTF(""+titleName_);
                this._roleTitle.setFontSize(30);
                this._roleTitle.setColor(cc.color(255,241,0));
                this._roleTitle.setPosition(cc.p(0,this.roleSize.height));
                this.addChild(this._roleTitle);
            }
        }
        else{
            if(!this._bloodBar){
                this._bloodBar = new RoleBloodBar(this.roleDataManager.maxHp,this.roleDataManager.hp);
                this._bloodBar.setPosition(cc.p(0,this.roleSize.height));
                this.addChild(this._bloodBar);
            }
        }
    },

    updateBloodBar : function () {
      if(this._bloodBar){
          this._bloodBar.refreshBloodBarPer(this.roleDataManager.maxHp, this.roleDataManager.hp);
      }
    },

    addRoleAction: function(type, animation, attr) {
        var action = null;
        switch (type) {
            case RoleAction.Type.WALK:
                action = new RoleActionWalk();
                break;

            case RoleAction.Type.INJURE:
                action = new RoleActionInjure();
                break;

            case RoleAction.Type.ATTACK1:
            case RoleAction.Type.ATTACK2:
            case RoleAction.Type.ATTACK3:
            case RoleAction.Type.ATTACK4:
            case RoleAction.Type.ATTACK5:
                action = new RoleActionAttack();
                break;

            case RoleAction.Type.SKILL1:
            case RoleAction.Type.SKILL2:
            case RoleAction.Type.SKILL3:
            case RoleAction.Type.SKILL4:
            case RoleAction.Type.SKILL5:
                action = new RoleActionSkill();
                break;

            case RoleAction.Type.FLOATING_UP:
                action = new RoleActionFloating();
                break;

            case RoleAction.Type.FLOATING_GROUND:
                action = new RoleActionGround();
                break;

            case RoleAction.Type.STAND_UP:
                action = new RoleActionStandUp();
                break;

            case RoleAction.Type.DIE:
                action = new RoleActionDie();
                break;
            case RoleAction.Type.REVIVE:
                action = new RoleActionRevive();
                break;
            default:
                action = new RoleAction();
                break;
        }

        if(action) {
            action.type = type;
            action.setAnimation(animation);

            if(attr) {
                _.extend(action, attr);
            }
        }

        if(this.roleActionManager) {
            this.roleActionManager.addAction(type, action);
        }
    },

    setRoleData: function(data) {
        this.roleDataManager.setData(data);
    }
});

RoleBase.Direction = {
    Unknown: 0,
    Left: -1,
    Right: 1
};

RoleBase.RoleType = {
    Unknown: 0,
    Hero: 1,
    Friend: 2,
    Monster: 3,
    Boss: 4,
    Item: 5
};

RoleBase.prototype.JudgeIsEnemy = function (atkRoleType_) {
    if(this.roleType == RoleBase.RoleType.Hero){
        if(atkRoleType_ != RoleBase.RoleType.Hero){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(atkRoleType_ == RoleBase.RoleType.Hero){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
};
