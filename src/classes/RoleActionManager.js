/**
 * Created by yuxiao on 15/4/16.
 */


var RoleActionManager = cc.Class.extend({
    ctor: function(role) {
        this.role = role;

        this.comboCount = 0;
        this.comboClock = 0;
        this.injureClock = 0;

        this.attackStatus = false;
        this.skillStatus = false;
        this.injureStatus = false;
        this.floatingStatus = false;
        this.groundStatus = false;
        this.deathStatus = false;

        this.strongStatus = false;

        this.actions = {};
        this.runningAction = null;
    },

    decideStopAllAction : function () {
        this.attackStatus = false;
        this.skillStatus = false;
        this.injureStatus = false;
        this.floatingStatus = false;
        this.groundStatus = false;
        this.deathStatus = false;
        var action = this.runningAction;
        if(action) {
            action.onActionEnd();
            this.runningAction = null;
        }
    },

    advanceTime: function(dt) {
        this.comboClock += dt;
        this.injureClock += dt;

        if(this.decideDeath()) {
            return;
        }
        if(this.decideFloating()) {
            return;
        }
        if(this.decideGround()) {
            return;
        }
        if(this.decideSkilling()) {
            return;
        }
        if(this.decideInjuring()) {
            return;
        }
        if(this.decideAttacking()) {
            return;
        }
        this.decideMoving();
    },

    addAction: function(type, action) {
        if(action) {
            action.manager = this;
            this.actions[type] = action;
        }
    },

    canMove: function() {
        var action = this.runningAction;
        if(action) {
            var type = action.type;
            return type == RoleAction.Type.STAND || type == RoleAction.Type.WALK;
        }
        return !this.injureStatus && !this.attackStatus && !this.deathStatus;
    },

    onActionComplete: function() {
        var action = this.runningAction;
        if(action) {
            // play next action
            if(action.playNextAction()) {
                return;
            }

            action.onActionEnd();
            this.runningAction = null;
        }
    },

    playAction: function(type, replay) {
        if(!this.actions[type]){
            return;
        }

        var action = this.runningAction;
        if(!replay && action && action.type == type) {
            return;
        }

        if(action) {
            action.onActionEnd();
        }

        action =  this.actions[type];
        if(action && action.playAction()) {
            action.onActionStart();
            this.runningAction = action;
        }

    },

    decideMoving: function() {
        if(this.role.movingValue) {
            this.playAction(RoleAction.Type.WALK);
        }
        else {
            this.playAction(RoleAction.Type.STAND);
        }
        return false;
    },

    decideAttacking: function() {
        if(this.attackStatus) {
            return true;
        }

        if(this.role.attackValue) {
            if(this.comboClock > this.role.comboTime || this.comboCount >= this.role.comboNumber) {
                this.comboCount = 0;
            }

            switch(++this.comboCount) {
                case 1: this.playAction(RoleAction.Type.ATTACK1); break;
                case 2: this.playAction(RoleAction.Type.ATTACK2); break;
                case 3: this.playAction(RoleAction.Type.ATTACK3); break;
                case 4: this.playAction(RoleAction.Type.ATTACK4); break;
                case 5: this.playAction(RoleAction.Type.ATTACK5); break;
            }
            return true;
        }
        return false;
    },

    decideSkilling: function() {
        if(this.skillStatus) {
            return true;
        }
        var skillId = this.role.skillValue;
        var tmpSkillType = 0;
        if(skillId != 0) {
            switch(skillId) {
                case 1:
                    tmpSkillType = RoleAction.Type.SKILL1;
                    this.playAction(RoleAction.Type.SKILL1);
                    break;
                case 2:
                    tmpSkillType = RoleAction.Type.SKILL2;
                    this.playAction(RoleAction.Type.SKILL2);
                    break;
                case 3:
                    tmpSkillType = RoleAction.Type.SKILL3;
                    this.playAction(RoleAction.Type.SKILL3);
                    break;
                case 4:
                    tmpSkillType = RoleAction.Type.SKILL4;
                    this.playAction(RoleAction.Type.SKILL4);
                    break;
                case 5:
                    tmpSkillType = RoleAction.Type.SKILL5;
                    this.playAction(RoleAction.Type.SKILL5);
                    break;
            }

            if(this.role.roleType == RoleBase.RoleType.Hero && tmpSkillType != 0){
                var actionData = this.actions[tmpSkillType];
                if(actionData){
                    //下次修改成COMBO模式
                    var scene = cc.director.getRunningScene();
                    scene._operator.setBtnTimingEnable(skillId,actionData.cdTime);

                    //refresh mp
                    this.role.roleDataManager.mp -= actionData.mpCost;
                }
            }
            return true;
        }
        return false;
    },

    decideInjuring: function() {
        if(!this.strongStatus && this.role.injureValue) {
            this.injureClock = 0;
            this.injureStatus = true;

            this.playAction(RoleAction.Type.INJURE, true);
            return true;
        }

        if(this.injureStatus == true && this.injureClock > this.role.injureTime) {
            this.injureStatus = false;
        }

        //function bodyBeAtkChangeColor(node_,beAtk_){
        //    if(beAtk_){
        //        var redColor = cc.color(150,10,10);
        //        node_.setColor(redColor);
        //    }
        //    else{
        //        var whiteColor = cc.color(255,255,255);
        //        node_.setColor(whiteColor);
        //    }
        //}
        //bodyBeAtkChangeColor(this.role.armatureNode,this.injureStatus);

        return this.injureStatus;
    },

    decideFloating: function() {
        if(this.role.floatingValue) {
            if(this.role.injureValue && !this.floatingStatus) {
                this.playAction(RoleAction.Type.FLOATING_UP);
                return true;
            }
        }
        else if(this.floatingStatus) {
            this.playAction(RoleAction.Type.FLOATING_GROUND);
        }

        return this.floatingStatus;
    },

    decideGround: function() {
        if(this.groundStatus) {
            this.playAction(RoleAction.Type.STAND_UP);
            return true;
        }
        return false;
    },

    decideDeath: function() {
        if(this.deathStatus) {
            return true;
        }

        if(this.role.deathValue) {
            // add effect sound
            //this.role
            this.playAction(RoleAction.Type.DIE);
            return true;
        }
        return false;
    }
});

var RoleAction = cc.Class.extend({
    ctor: function() {
        this.manager = null;
        this.type = RoleAction.Type.UNKNOWN;
        this.animations = [];
    },

    setAnimation: function(animation) {
        var animations = animation instanceof Array ? animation : [animation];
        _.each(animations, function(anima) {
            this.animations.push(anima);
        }, this);
    },

    playAction: function() {
        this._animationIndex = 0;
        return this.playNextAction();
    },

    playNextAction: function() {
        if(this.animations.length > this._animationIndex) {
            var animation = this.animations[this._animationIndex++];
            var role = this.manager.role;
            return role.playAnimation(animation);
        }
        return false;
    },


    onThrowWeapon : function () {
        var role = this.manager.role;
        if( this.type == RoleAction.Type.ATTACK1 ||
            this.type == RoleAction.Type.ATTACK2 ||
            this.type == RoleAction.Type.ATTACK3 ||
            this.type == RoleAction.Type.ATTACK4 ||
            this.type == RoleAction.Type.ATTACK5 ){
            var tmpID = role.throwModelId
        }
        else if(this.type == RoleAction.Type.SKILL1 ||
                this.type == RoleAction.Type.SKILL2 ||
                this.type == RoleAction.Type.SKILL3 ||
                this.type == RoleAction.Type.SKILL4 ||
                this.type == RoleAction.Type.SKILL5 ){
            tmpID = this.attack.throwModelId;
        }

       // var tmpID = this.throwModelId;
        var modelConf = configdb.model[tmpID];

        if(modelConf){
            var tmpThrow = null;
            if(modelConf.remoteAtkType == ThrowBase.ThrowType.singleArrow){
                tmpThrow = ThrowArrow;
            }
            else if(modelConf.remoteAtkType == ThrowBase.ThrowType.singleFireBall){

            }
            else if(modelConf.remoteAtkType == ThrowBase.ThrowType.singleRaiden){
                tmpThrow = ThrowRaiden;
            }
            else if(modelConf.remoteAtkType == ThrowBase.ThrowType.multipleFireBall){
                tmpThrow = ThrowFireBall;
            }

            if(tmpThrow){
                (new tmpThrow(role,tmpID)).throwStart();
            }
        }
    },

    onActionStart: function() {

    },

    onActionEnd: function() {

    }
});

RoleAction.Type = {
    UNKNOWN: 0,
    STAND: 1,
    WALK: 2,
    ATTACK1: 31,
    ATTACK2: 32,
    ATTACK3: 33,
    ATTACK4: 34,
    ATTACK5: 35,
    SKILL1: 41,
    SKILL2: 42,
    SKILL3: 43,
    SKILL4: 44,
    SKILL5: 45,
    INJURE: 5,
    FLOATING: 60,
    FLOATING_UP: 6,
    FLOATING_AIR: 7,
    FLOATING_GROUND: 8,
    STAND_UP: 9,
    DIE: 10,
    STRUCK_OUT: 11
};

var RoleActionWalk = RoleAction.extend({
    ctor: function() {
        this._super();

        this.sound = null;
    },

    onActionStart: function() {
        this._super();

        if(this.sound) {
            this._soundId = cc.audioEngine.playEffect(this.sound, true);
        }
    },

    onActionEnd: function() {
        this._super();

        if(this._soundId) {
            cc.audioEngine.stopEffect(this._soundId);
        }
    }
});

var RoleActionInjure = RoleAction.extend({
    ctor: function() {
        this._super();

        this.sound = null;
    },

    onActionStart: function() {
        this._super();

        if(this.sound) {
            cc.audioEngine.playEffect(this.sound);
        }
    }
});

var RoleActionAttack = RoleAction.extend({
    onActionStart: function() {
        this._super();

        this.manager.attackStatus = true;

        //set strong status
        if(this.attack.strong){
            this.manager.strongStatus = true;
        }

        //this.onAttackSound();
    },

    onActionEnd: function() {
        this._super();

        this.manager.strongStatus = false;
        this.manager.comboClock = 0;
        this.manager.attackStatus = false;
        this.manager.role.onAttackEnd();

    },

    onAttackMove: function() {
        var attr = this.attack;
        if(attr && attr.movement) {
            var role = this.manager.role;
            var movement = attr.movement;
            var drag = PhysicalWorld.drag;
            var vx = Math.sqrt(2 * movement * -drag) * role.direction;

            role.setSpaceVelocity(vx, 0, 0);
        }
    },

    onAttackSound: function() {
        //if(this.effect){
        //    var attr = this.effect.attack;
        //    if(attr && attr.sound) {
        //        cc.audioEngine.playEffect(attr.sound);
        //    }
        //}
        var attr = this.attack;
        if(attr && attr.sound) {
            cc.audioEngine.playEffect(attr.sound);
        }
    },
    //
    //onThrowWeapon : function (attacker_) {
    //    var role = this.manager.role;
    //    var modelConf = configdb.model[role.throwModelId];
    //    if(modelConf){
    //        var tmpThrow = null;
    //        if(modelConf.remoteAtkType == ThrowBase.ThrowType.singleArrow){
    //            tmpThrow = ThrowArrow;
    //        }
    //        else if(modelConf.remoteAtkType == ThrowBase.ThrowType.singleFireBall){
    //
    //        }
    //        else if(modelConf.remoteAtkType == ThrowBase.ThrowType.singleRaiden){
    //            tmpThrow = ThrowRaiden;
    //        }
    //        else if(modelConf.remoteAtkType == ThrowBase.ThrowType.multipleFireBall){
    //            tmpThrow = ThrowFireBall;
    //        }
    //
    //        if(tmpThrow){
    //            (new tmpThrow(role,role.throwModelId)).throwStart();
    //        }
    //    }
    //},

    onHitTarget: function(target) {
        var attr = this.hit;
        if(attr) {
            var direction = this.manager.role.direction;

            // pause
            if(attr.pause) {
                notification.emit(notification.event.PHYSICAL_PAUSE, attr.pause);
            }

            // quake
            if(attr.quake) {
                notification.emit(notification.event.PHYSICAL_QUAKE, attr.quake);
            }

            // velocity
            if(attr.velocity) {
                var velocity = target.floatingValue ? attr.velocity.onFloating : attr.velocity.onGround;
                target.setSpaceVelocity(velocity.x * direction, 0, velocity.y);
            }

            // sound
            if(attr.sound) {
                cc.audioEngine.playEffect(attr.sound);
            }

            // effect
            if(attr.animation) {
                var effectName = attr.animation.split('/');
                var effectNode = dragonBones.DragonBonesHelper.buildArmatureNode(effectName[0]);
                if(effectNode) {
                    effectNode.setScaleX(-direction);
                    effectNode.setPosition(0, target.roleSize.height/2);
                    effectNode.registerMovementEventHandler(function(node, type) {
                        if(type == "complete") {
                            effectNode.removeFromParent();
                        }
                    });

                    if(effectNode.gotoAndPlay(effectName[1])) {
                        target.addChild(effectNode, 999);
                    }
                }
            }
        }
    }
});

var RoleActionSkill = RoleAction.extend({
    onActionStart: function() {
        this._super();
        this.manager.skillStatus = true;
        if(this.attack && this.attack.drag){
            this.manager.role.drag = this.attack.drag;
        }
    },

    onActionEnd: function() {
        this._super();
        this.manager.skillStatus = false;
        this.manager.role.onSkillEnd();

        this.manager.role.drag = undefined;
    },

    //onAttackMove: RoleActionAttack.prototype.onAttackMove,

    onAttackMove: function() {
        var attr = this.attack;
        if(attr && attr.movement) {
            var role = this.manager.role;
            var movement = attr.movement;
            var drag = PhysicalWorld.drag;
            if(attr.drag){
                drag = attr.drag;
            }
            var vx = Math.sqrt(2 * movement * -drag) * role.direction;

            role.setSpaceVelocity(vx, 0, 0);
        }
    },

    onAttackSound: RoleActionAttack.prototype.onAttackSound,
    onHitTarget: RoleActionAttack.prototype.onHitTarget
});

var RoleActionFloating = RoleAction.extend({
    onActionStart: function() {
        this._super();
        this.manager.floatingStatus = true;
    },

    onActionEnd: function() {
        this._super();
    }
});

var RoleActionGround = RoleAction.extend({
    onActionStart: function() {
        this._super();
        this.manager.role.onTouchGround();
    },

    onActionEnd: function() {
        this._super();
        this.manager.floatingStatus = false;
        this.manager.groundStatus = true;
        this.manager.role.onTouchGroundEnd();
    }
});

var RoleActionStandUp = RoleAction.extend({
    onActionEnd: function() {
        this._super();
        this.manager.groundStatus = false;
        this.manager.role.onStandUp();
    }
});

var RoleActionDie = RoleAction.extend({
    onActionStart: function() {
        this._super();

        if(this.manager.role.roleType == RoleBase.RoleType.Boss){
            var battleScene = cc.director.getRunningScene();
            battleScene._camera.zoomToValueInSeconds(1.3,2000);
            battleScene._camera.lookAtNodeInSeconds(battleScene._boss,2000);
            this.manager.role.physicalWorld.setSlowPlay(3);
        }

        this.manager.deathStatus = true;

        var velocity = this.manager.role.velocity;
        var direction = RoleBase.Direction.Unknown;
        if(velocity.x < 0) {
            direction = RoleBase.Direction.Left;
        }
        else if(velocity.x > 0) {
            direction = RoleBase.Direction.Right;
        }
        this.manager.role.setSpaceVelocity(500 * direction, 0, 400);

        this.onDieSound();
    },

    onDieSound: function() {
        var attr = this.effect;
        if(attr && attr.sound) {
            cc.audioEngine.playEffect(attr.sound);
        }
    },

    onActionEnd: function() {
        this._super();
        if(this.manager.role.roleType == RoleBase.RoleType.Boss){
            var battleScene = cc.director.getRunningScene();
            battleScene._camera.zoomToValueInSeconds(1.0,2000);
            //battleScene._camera.resetLookAtInSeconds(2000);
            battleScene._camera.resetLookAt();
            battleScene._camera.lookAtNodeInSeconds(battleScene._hero,2000);
            this.manager.role.physicalWorld.setSlowPlay(1);
        }
        this.manager.role.onDie();
    }
});

