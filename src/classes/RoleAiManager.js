/**
 * Created by yuxiao on 15/4/16.
 */


var RoleAiManager = cc.Class.extend({
    ctor: function(role) {
        this.role = role;

        this.ai = null;
    },

    advanceTime: function(dt) {
        if(this.ai) {
            this.ai.advanceTime(dt);
        }
    },

    setAi: function(ai) {
        if(ai) {
            ai.manager = this;
        }
        this.ai = ai;
    },

    testRole : function () {
        LOG("TEST ROLE");
    }
});

var RoleAi = cc.Class.extend({
    ctor: function() {
        this.manager = null;
    },

    advanceTime: function(dt) {

    },

    onMove: function(offset, dt) {
        if(offset.x == 0 && offset.y == 0)
            return;

        var role = this.manager.role;
        var speed = role.speed;

        if(offset.x * offset.x + offset.y * offset.y > speed * dt * speed * dt) {
            cc.pNormalizeIn(offset);
            cc.pMultIn(offset, speed * dt);
        }

        role.move(offset);
        role.turn(offset.x);
    },

    onAttack: function() {
        var role = this.manager.role;
        role.attack();
    },

    onSKill: function(id) {
        var role = this.manager.role;
        role.skill(id);
    },

    onTurn: function(dir) {
        var role = this.manager.role;
        role.turn(dir);
    },

    turnToTarget: function(target) {
        var role = this.manager.role;
        if(role && target) {
            var rolePos = role.getPosition();
            var targetPos = target.getPosition();
            this.onTurn(targetPos.x - rolePos.x);
        }
    }
});

RoleAi.Type = {
    None: 0,
    Stake: 1,
    Manual: 2,
    Auto: 3,
    XiaoGuai : 4,
    Show: 5
};

var StakeAi = RoleAi.extend({
    ctor: function() {
        this._super();

        this.target = null;

        //this.clock = 0;
    },

    advanceTime: function(dt) {
        this._super();

        this.turnToTarget(this.target);
    }
});

var ShowAi = RoleAi.extend({
    ctor: function() {
        this._super();
    },

    advanceTime: function(dt) {
        this._super();

        this.onTurn(1);

        //this.clock += dt;
        //if(this.clock > 2) {
        //    this.clock = 0;
        //    this.onAttack();
        //}
    }
});

var ManualAi = RoleAi.extend({
    ctor: function() {
        this._super();

        this.joystick = null;
        this.attackButton = null;
        this.skillButton1 = null;
        this.skillButton2 = null;
        this.skillButton3 = null;
        this.skillButton4 = null;
        this.skillButton5 = null;

        this.btnCDTime1 = 0;
        this.btnCDTime2 = 0;
        this.btnCDTime3 = 0;
        this.btnCDTime4 = 0;
        this.btnCDTime5 = 0;

    },

    advanceTime: function(dt) {
        this._super();
        var velocity;
        var value;

        if(this.joystick) {
            velocity = this.joystick.getVelocity();
            cc.pMultIn(velocity, 1000);
            this.onMove(velocity, dt);
        }

        if(this.attackButton) {
            value = this.attackButton.getValue();
            if(value) {
                this.onAttack();
            }
        }

        _.each([
            [this.skillButton1, 1],
            [this.skillButton2, 2],
            [this.skillButton3, 3],
            [this.skillButton4, 4],
            [this.skillButton5, 5]
        ], function(arr) {
            var button = arr[0];
            var index = arr[1];

            if(button) {
                value = button.getValue();
                if(value) {
                    //var tmpBtnCDv = "btnCDTime"+index;
                    //var scene = cc.director.getRunningScene();
                    //scene._operator.setBtnTimingEnable(index,this[tmpBtnCDv]);

                    this.onSKill(index);
                }
            }
        }, this);
    }
});

var AutoAi = RoleAi.extend({
    ctor: function() {
        this._super();
        this.target = null;

        this._waitingClock = 0;
        this._attackClock = 0;
        this._walkingPoint = cc.p(0,0);

        this._doing = null;
    },

    advanceTime: function(dt) {
        this._super();
        if(this.target == null){
            return;
        }

        this.attack(dt);
        if(this._doing && !this._doing(dt)){
            this._doing = null;
        }
        else{
            this.randomThing();
        }
    },

    randomThing : function () {
        if(this._doing == null && !this.isInWalkArea()){
            this._doing = this.walk;
        }

        if(this._doing == null && cc.random0To1() * 100 < 30){
            this._doing = this.wait;
        }

        if(this._doing == null){
            this._doing = this.walk;
        }
    },

    wait : function (dt) {
      this._waitingClock += dt;

        if(this._waitingClock < 1){
            return true;
        }

        this._waitingClock = 0;
        return false;
    },

    walk : function (dt) {
        var targetPos = this.target.getPosition();
        var selfPos = this.manager.role.getPosition();

        if(!cc.pointEqualToPoint(this._walkingPoint,cc.p(0,0))){
            var delta = cc.pSub(this._walkingPoint , targetPos);
            if(delta.x < -300 || delta.x > 300 || delta.y < -200 || delta.y > 200){
                this._walkingPoint = cc.p(0,0);
            }
        }

        if(cc.pointEqualToPoint(this._walkingPoint,cc.p(0,0))){
            var worldSize = this.manager.role.physicalWorld.getContentSize();
            var minX = Math.max(targetPos.x - 300, 0);
            var maxX = Math.min(targetPos.x + 300, worldSize.width);
            var minY = Math.max(targetPos.y - 200, 0);
            var maxY = Math.min(targetPos.y + 200, worldSize.height);

            var tmpx = cc.random0To1() * (maxX - minX) + minX;
            var tmpy = cc.random0To1() * (maxY - minY) + minY;

            this._walkingPoint = cc.p(tmpx,tmpy);
        }

        var delta_1 = cc.pSub(this._walkingPoint,selfPos);
        if(cc.pLength(delta_1) > 1){
            this.onMove(delta_1,dt);
            this.onTurn(delta_1.x);
            return true;
        }

        this.onTurn(targetPos.x - selfPos.x);
        this._walkingPoint = cc.p(0,0);

        return false;
    },

    attack : function (dt) {
        this._attackClock += dt;
        if(this._attackClock > 3 && this.isInAttackArea() && cc.random0To1() * 100 < 90){
            this.turnToTarget(this.target);
            this.onAttack();
            this._attackClock = 0;
        }
        return false;
    },

    isInViewField : function(target_){
        if(target_){
            var targetPos = target_.getPosition();
            var selfPos = this.manager.role.getPosition();
            if(Math.abs(targetPos.x - selfPos.x) <= this.manager.role.viewLength){
                return true;
            }
        }
        return false;
    },

    isInWalkArea : function(){
        var targetPos = this.target.getPosition();
        var selfPos = this.manager.role.getPosition();
        var delta = cc.pSub(targetPos,selfPos);

        if(delta.x >= -300 || delta.x <= 300 || delta.y >= -200 || delta.y <= 200){
            return true;
        }
        return false;
    },

    isInAttackArea : function(){
        if(this.hadTAS()){
            var area = this.manager.role.getBestAtackRange();
            if(this.manager.role.direction < 0){
                area.x = -(area.x + area.width);
            }
            area.x += this.manager.role.getPosition().x;
            area.y += this.manager.role.getPosition().y;
            var isCon = cc.rectContainsPoint(area,this.target.getPosition());
            return isCon;
        }
        return false;
    },

    // had target node and self node
    hadTAS : function () {
        if(this.target && this.manager.role){
            return true;
        }
        return false;
    }
});

var XiaoGuaiAi = RoleAi.extend({
    stateType : {
        noneState : 0,
        walk : 1,
        attack : 2,
        wait : 3
    },

    ctor: function() {
        this._super();

        this.target = null;

        this._curState = this.stateType.noneState;

        this._skillAttack = false;

        //this._walkRect = {
        //    minX : -300,
        //    maxX : 300,
        //    minY : -200,
        //    maxY : 200
        //}

        // 观望状态 ＋ 攻击状态 = 100
        // 观望状态之中 有概率的待机
        //this._walkState = 30;
        //this._attackPercent = 55;

        //等待的前提是不在攻击状态下才会考虑的情况
        //this._waitPercent = 30;

        //随机到攻击类型，会一直跟着攻击，除非在这个 跟随攻击权值时间 到之前避开了
        //this._atkWeightInit = 10;


        //休息时间倒计时
        this._waitWeightInit = 2;
        this._waitWeight = this._waitWeightInit;

        //休息权值，每个怪物会在这个时间走完需要休息
        this._restWeightInit = 2;
        this._restWeight = this._restWeightInit;

        this._doing = null;
        this._walkingPoint = cc.p(0,0);

        this._isRemoteAtk = 0;

        //远程攻击站位差值
        this._remoteDiffV = 50;
    },

    refreshData : function () {
        if(this._attackPercent){
             return;
        }
        else{
            this._attackPercent = this.atkPer;
            this._waitPercent   = this.restPer;
            this._atkWeightInit = this.followAtk;
            this._walkRange = {
                width : this.rangeActW,
                height : this.rangeActH
            }
            this._atkWeight = this._atkWeightInit;
            this._isRemoteAtk = this.isRemote;
        }
    },

    randomSomeThing : function () {
        var tmpRan = cc.random0To1() * 100;
        if(tmpRan < this._attackPercent){
            this._curState = this.stateType.attack;
            this._atkWeight = this._atkWeightInit;

            //TODO 之后需要完善成根据BOSS CD 来决定是否释放技能
            if(this.manager.role.roleType == RoleBase.RoleType.Boss &&  cc.random0To1() > 0.4 ){
                this._skillAttack = true;
            }
            else{
                this._skillAttack = false;
            }
        }
        else{
            if(cc.random0To1() * 100 < this._waitPercent){
                this._curState = this.stateType.wait;
                this._waitWeight = this._waitWeightInit;
            }
            else{
                this._curState = this.stateType.walk;
                this._restWeight = this._restWeightInit;
                this._doing = this.walk;
            }
        }
    },

    advanceTime: function(dt) {
        this._super();
        this.refreshData();
        if(this.target == null){
            return;
        }

        if(this._curState == this.stateType.noneState){
            this.randomSomeThing();
        }
        else{
            this.refreshRoleBehaviour(dt);
        }
    },

    //跟随攻击权值倒计时
    countDownAtkWeight : function (dt) {
        this._atkWeight -= dt;
        if(this._atkWeight <= 0){
            this._curState = this.stateType.noneState;
        }
    },

    countDownWaitWeight : function (dt) {
        this._waitWeight -= dt;
        if(this._waitWeight <= 0){
            this._curState = this.stateType.noneState;
        }
    },


    refreshRoleBehaviour : function (dt) {
        switch (this._curState){
            case  this.stateType.attack:
                if(this._skillAttack){
                    this.turnToTarget(this.target);
                    this.onSKill(1);
                    this._curState = this.stateType.noneState;
                }
                else{
                    this.countDownAtkWeight(dt);
                    if(this.isInAttackArea()){
                        this.turnToTarget(this.target);
                        this.onAttack();
                        this._curState = this.stateType.noneState;
                    }
                    else{
                        this.moveToAttackArea(dt);
                    }
                }
                break;
            case  this.stateType.walk:
                if(this._doing && !this._doing(dt)){
                    this._curState = this.stateType.noneState;
                    this._doing = null;
                }
                break;
            case  this.stateType.wait:
                this.countDownWaitWeight(dt);
                break;
            default :
                break;
        }
    },

    walk : function (dt) {
        var targetPos = this.target.getPosition();
        var selfPos = this.manager.role.getPosition();

        if(!cc.pointEqualToPoint(this._walkingPoint,cc.p(0,0)) && this.isInSuitableRange(this._walkingPoint) ){
            this._walkingPoint = cc.p(0,0);
        }

        if(cc.pointEqualToPoint(this._walkingPoint,cc.p(0,0))){
            this._walkingPoint = this.getWalkRandomPos();
        }

        var delta_1 = cc.pSub(this._walkingPoint,selfPos);
        if(cc.pLength(delta_1) > 1){
            this.onMove(delta_1,dt);
            this.onTurn(delta_1.x);
            return true;
        }

        this.onTurn(targetPos.x - selfPos.x);
        this._walkingPoint = cc.p(0,0);

        return false;
    },


    isInAttackArea : function(){
        if(this.hadTAS()){
            var area = this.manager.role.getBestAtackRange();
            area.x += this.manager.role.getPosition().x;
            area.y += this.manager.role.getPosition().y;
            var isCon = cc.rectContainsPoint(area,this.target.getPosition());
            return isCon;
        }
        return false;
    },

    moveToAttackArea : function (dt_) {
        var delta = cc.p(-1000,-1000);
        var tmpRole = this.manager.role;
        var worldSize = tmpRole.physicalWorld.getContentSize();
        if(this._isRemoteAtk){
            if(this.hadTAS()){
                var area = this.manager.role.getBestAtackRange();
                var atkRange = Math.abs(area.x) + area.width;
                var tmpV = 1;
                //role is left side
                if(tmpRole.getPosition().x < this.target.getPosition.x){
                    if(this.target.getPosition().x - atkRange > 0){
                        tmpV = -1;
                    }
                    else{
                    }
                }
                //role is right side
                else{
                    if(this.target.getPosition().x + atkRange < worldSize.width){
                    }
                    else{
                        tmpV = -1;
                    }
                }
                var destinationPos = cc.p(this.target.getPosition().x + (atkRange * tmpV) ,this.target.getPosition().y);
                delta = cc.pSub(destinationPos,tmpRole.getPosition());
            }
        }
        else{
            delta = cc.pSub(this.target.getPosition(),tmpRole.getPosition());
        }

        if(!cc.pointEqualToPoint(delta, cc.p(-1000,-1000))){
            if(tmpRole.getPosition().x >= worldSize.width || tmpRole.getPosition().x <= 0){
               this._curState = this.stateType.walk;
               this._doing = this.walk;
            }
            else{
                this.onMove(delta,dt_);
                this.onTurn(delta.x);
            }
        }
    },

    isInSuitableRange : function (walkPos_) {
        var targetPos = this.target.getPosition();
        var delta = cc.pSub(walkPos_ , targetPos);
        if(this._isRemoteAtk){
            var tmpLen = cc.pLength(delta);
            if(tmpLen < this._walkRange.width || tmpLen > this._walkRange.width + this._remoteDiffV){
                //return true;
            }
        }
        else{
            if(delta.x < -this._walkRange.width || delta.x > this._walkRange.width || delta.y < -this._walkRange.height || delta.y > this._walkRange.height){
                return true;
            }
        }
        return false;
    },

    getWalkRandomPos : function () {
        var targetPos = this.target.getPosition();
        var selfPos = this.manager.role.getPosition();

        var worldSize = this.manager.role.physicalWorld.getContentSize();
        var tmpx = 0;
        var tmpy = 0;
        var minX = 0;
        var maxX = 0;
        var minY = 0;
        var maxY = 0;
        if(this._isRemoteAtk){
            var that = this;
            function getRightOrLeftPos(){
                // target right side
                if(targetPos.x + that._walkRange.width <= worldSize.width){
                    if(cc.random0To1() > 0.5){
                        minX = targetPos.x + that._walkRange.width
                        maxX = worldSize.width;
                        tmpx = cc.random0To1() * (maxX - minX) + minX;
                    }
                }
                //target left side
                if(tmpx == 0 && targetPos.x - that._walkRange.width > 0){
                    maxX = targetPos.x - that._walkRange.width;
                    minX = 0;
                    tmpx = cc.random0To1() * (maxX - minX) + minX;
                }
            }
            do{
                getRightOrLeftPos();
            }while(tmpx == 0);

            minY = Math.max(targetPos.y - this._walkRange.height, 0);
            maxY = Math.min(targetPos.y + this._walkRange.height, worldSize.height);

            tmpy = cc.random0To1() * (maxY - minY) + minY;
        }
        else{
            minX = Math.max(targetPos.x - this._walkRange.width, 0);
            maxX = Math.min(targetPos.x + this._walkRange.width, worldSize.width);
            minY = Math.max(targetPos.y - this._walkRange.height, 0);
            maxY = Math.min(targetPos.y + this._walkRange.height, worldSize.height);

            tmpx = cc.random0To1() * (maxX - minX) + minX;
            tmpy = cc.random0To1() * (maxY - minY) + minY;
        }
        return cc.p(tmpx,tmpy);
    },

    hadTAS : function () {
        if(this.target && this.manager.role){
            return true;
        }
        return false;
    }
});

