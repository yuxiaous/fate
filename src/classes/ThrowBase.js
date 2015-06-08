
var ThrowBase = PhysicalNode.extend({
    ctor : function (hostRole_,throwModelId_) {
        this._super();

        this._hostRole = hostRole_;
        this._throwMID = throwModelId_;

        this._atkEvent = false;
        this._completeEvent = false;

        //this._isMineActivite = false;
        this._isDone = false;
    },

    dispose : function () {
        this._super();
    },

    onEnter : function(){
        this._super();

    },

    judgeThrowEvent : function (throwNode_) {
        if(throwNode_) {
            var that = this;
            throwNode_.registerFrameEventHandler(function(node, frameLabel) {
                var action;
                switch (frameLabel) {
                    case "emitAttack":
                        that._atkEvent = true;
                        break;
                    default :
                        break;
                }
            });

            throwNode_.registerMovementEventHandler(function(node, type) {
                switch(type) {
                    case "complete":
                        //LOG("COMPLETE");
                        that._completeEvent = true;
                        break;
                    default :
                        break;
                }
            });
        }
    },

    onExit : function(){
        this._super();

    },
    
    advanceTime : function (dt) {
        this._super();

    },

    //judgeNodeIsOverlaping : function (initiationNode_,targetNode_) {
    //    var area_1 = this.getBodyAttackRange(initiationNode_);
    //    var area_2 = this.getBodyRange(targetNode_);
    //    if(cc.rectIntersectsRect(area_1,area_2)){
    //        return true;
    //    }
    //    return false;
    //},

    getBoneBox: function(dbNode_,name) {
        var box = dbNode_.getBoundingBox(name);
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

    getBodyAttackRange: function(phyNode_) {
        var box = this.getBoneBox(phyNode_._throwNode,"attack");
        var pos = phyNode_.getSpacePosition();
        return cc.rect(pos.x + box.x, pos.y + box.y, box.width, box.height);
    },

    getBodyRange : function (phyNode_) {
        var box =  this.getBoneBox(phyNode_.armatureNode,"body");
        var pos = phyNode_.getSpacePosition();
        return cc.rect(pos.x + box.x,pos.y + box.y,box.width,0);
    },
    
    refreshIsMineActive : function () {
        //if(this._isMineActivite){
        //    this._isMineActivite = false;
        //
        //}
    },

    weaponHitTheTarget : function () {
        //this._isDone = true;
        //this.removeThrowNode();
    },

    removeThrowNode : function(){


        //if(this._isDone && this._completeEvent){
        //    this._hostRole.physicalWorld.removePhysicalNode(this);
        //    delete  this;
        //    return;
        //}

        if(this._completeEvent){
            this._hostRole.physicalWorld.removePhysicalNode(this);
            delete  this;
            return;
        }

        if(this._hostRole.physicalWorld){
            var size = this._hostRole.physicalWorld.getContentSize();
            if(this.getSpacePosition().x >= size.width || this.getSpacePosition().x <= 0){
                this._hostRole.physicalWorld.removePhysicalNode(this);
            }
        }
    }
});

ThrowBase.ThrowType ={
    singleArrow      : 1,
    singleFireBall   : 2,
    singleRaiden     : 3,
    multipleFireBall : 4
}

var ThrowArrow = ThrowBase.extend({
    ctor : function (hostRole_,throwModelId_) {
        this._super(hostRole_,throwModelId_);

        this.drag = - 200;
        this.gravity = 0;

        this.velocity = {x: 0, y: 0, z: 0};

        this._throwModelId = throwModelId_;
        this._hostRole = hostRole_;
    },

    onEnter : function () {
        this._super();


    },

    onExit : function () {
        this._super();
    },

    advanceTime : function () {
        this._super();
        //throw weapon 超出物理世界范围
        this.removeThrowNode();

        if(this._atkEvent){
            this._atkEvent = false;
            var area_1 = this.getBodyAttackRange(this);
            var targetRole = this._hostRole.roleAiManager.ai.target;
            targetRole.onAttackJudgement(notification.event.ROLE_ATTACK,this._hostRole,area_1,this);
        }

        //var isAtkSome = false;
        //var tmpAllNode = this._hostRole.physicalWorld.physicalNodes;
        //tmpAllNode.forEach(function (physicalNode_) {
        //    if(physicalNode_ == this || physicalNode_ == this._hostR){
        //
        //    }
        //    else{
        //        if(this._hostR.JudgeIsEnemy(physicalNode_.roleType)){
        //            var isHitSomeBody = this.judgeNodeIsOverlaping(this,physicalNode_);
        //            if(isHitSomeBody){
        //                physicalNode_.injure(this);
        //                this._hostRole.physicalWorld.removePhysicalNode(this);
        //                isAtkSome = true;
        //                return;
        //            }
        //        }
        //    }
        //},this);
        //
        //if(!isAtkSome){

        //}
    },



    throwStart : function () {
        var throwConf = configdb.model[this._throwModelId]
        if(!throwConf){
            return;
        }

        this.addThrowWeapon();

        var bestThrowP = this._hostRole.getBestThrowPos();
        var pos = {
            x:this._hostRole.getSpacePosition().x + bestThrowP.x,
            y:this._hostRole.getSpacePosition().y ,
            z:this._hostRole.getSpacePosition().z + bestThrowP.y
        }
        this.velocity = {x: this._hostRole.direction * 1000, y: 0, z: -150};
        this.setSpacePosition(pos);
        this._hostRole.physicalWorld.addPhysicalNode(this);
    },

    addThrowWeapon : function () {
        var throwConf = configdb.model[this._throwModelId];

        this._throwNode = dragonBones.DragonBonesHelper.buildArmatureNode(throwConf.armature);
        this._throwNode.gotoAndPlay(throwConf.stand);
        this._throwNode.setScaleX(-this._hostRole.direction);
        this.addChild(this._throwNode);

        this.judgeThrowEvent(this._throwNode);

        //this._hostRole.addThrowWeaponItem(this);
    },

    //弓箭这个动画 COMPLETE 有BUG
    weaponHitTheTarget : function () {
        this._isDone = true;
        this._hostRole.physicalWorld.removePhysicalNode(this);
        delete  this;
    }
});

var ThrowRaiden = ThrowBase.extend({
    ctor : function (hostRole_,throwModelId_) {
        this._super(hostRole_,throwModelId_)

        this._throwModelId = throwModelId_;
        this._hostRole = hostRole_;

        if(this._hostRole.roleAiManager.ai.target){
            this._targetRole = this._hostRole.roleAiManager.ai.target;
        }

        this.isActive = false;
    },
    
    onEnter : function(){
        this._super();

    },
    
    onExit : function () {
      this._super();
        
    },
    
    advanceTime : function () {
        this._super();

        //throw weapon 超出物理世界范围
        this.removeThrowNode();

        if(this._atkEvent){
            this._atkEvent = false;
            var area_1 = this.getBodyAttackRange(this);
            var targetRole = this._hostRole.roleAiManager.ai.target;
            targetRole.onAttackJudgement(notification.event.ROLE_ATTACK,this._hostRole,area_1,this);
        }
    },

    throwStart : function () {
        var throwConf = configdb.model[this._throwModelId]
        if(!throwConf){
            return;
        }
        this.addThrowWeapon(this._hostRole, this._throwModelId);

        var pos = {
            x : this._targetRole.getSpacePosition().x,
            y : this._targetRole.getSpacePosition().y,
            z : this._targetRole.getSpacePosition().z
        }

        this.setSpacePosition(pos);
        this._hostRole.physicalWorld.addPhysicalNode(this);
    },

    addThrowWeapon : function () {
        var alertNode = dragonBones.DragonBonesHelper.buildArmatureNode("yujing1");
        alertNode.gotoAndPlay("yujing1");
        this.addChild(alertNode,-1);

        this.runAction(cc.Sequence.create(
                            cc.DelayTime.create(1.0),
                            cc.CallFunc.create(function () {
                                alertNode.removeFromParent();

                                var throwConf = configdb.model[this._throwModelId];
                                this._throwNode = dragonBones.DragonBonesHelper.buildArmatureNode(throwConf.armature);
                                this._throwNode.gotoAndPlay(throwConf.stand);
                                this._throwNode.setScaleX(-this._hostRole.direction);
                                this.addChild(this._throwNode);

                                this.isActive = true;

                                this.judgeThrowEvent(this._throwNode);
                            },this)
                        ));
    },

    weaponHitTheTarget : function () {
        this._isDone = true;
        this.removeThrowNode();
    }
});

var ThrowFireBall = ThrowBase.extend({
    ctor : function (hostRole_,throwModelId_) {
        this._super(hostRole_,throwModelId_);

        this._throwModelId = throwModelId_;
        this._hostRole = hostRole_;

        if(this._hostRole.roleAiManager.ai.target){
            this._targetRole = this._hostRole.roleAiManager.ai.target;
        }
    },

    onEnter : function () {
        this._super();
        
    },
    
    onExit : function () {
        this._super();
        
    },

    advanceTime : function () {
        this._super();
        //if(this.isActive){
        //    if(this._atkEvent){
        //        this._atkEvent = false;
        //        var tmpAllNode = this._hostRole.physicalWorld.physicalNodes;
        //        tmpAllNode.forEach(function (physicalNode_) {
        //            if(physicalNode_ == this || physicalNode_ == this._hostRole){
        //
        //            }
        //            else{
        //                if(this._hostR.JudgeIsEnemy(physicalNode_.roleType)){
        //                    var isHitSomeBody = this.judgeNodeIsOverlaping(this,physicalNode_);
        //                    if(isHitSomeBody){
        //                        physicalNode_.injure(this);
        //                        return;
        //                    }
        //                }
        //            }
        //        },this);
        //    }
        //}
    },
    
    throwStart : function(){
        var throwConf = configdb.model[this._throwModelId]
        if(!throwConf){
            return;
        }
        this.addThrowWeapon();

        var mapPos = MapSystem.instance.getGameMapPos();
        var pos = {
            x : - mapPos.x,
            y : 0,
            z : 0
        }

        this.setSpacePosition(pos);
        this._hostRole.physicalWorld.addPhysicalNode(this);
    },

    addThrowWeapon : function () {
        var screenSize = cc.director.getVisibleSize();
        var minX = 0 + 100;
        var maxX = screenSize.width - 100;
        var maxY = MapSystem.instance.getGameMapRect().height;

        var fireBCount = 8;
        var tmpValue = (maxX - minX) / (fireBCount -1);

        var that = this;
        var tmpIndex = 0;
        function addFireBox(){
            tmpIndex += 1;
            that.runAction(cc.Sequence.create(
                cc.DelayTime.create(cc.random0To1()),
                cc.CallFunc.create(
                    function () {
                        var throwConf = configdb.model[that._throwModelId];
                        var _tmpNode = dragonBones.DragonBonesHelper.buildArmatureNode(throwConf.armature);
                        _tmpNode.setScaleX(-that._hostRole.direction);

                        var tmpPos = cc.p(minX + tmpIndex * tmpValue, cc.random0To1() * maxY);
                        _tmpNode.setPosition(tmpPos);
                        _tmpNode.gotoAndPlay(throwConf.stand);
                        that.addChild(_tmpNode);
                        that.judgeThrowEvent(_tmpNode);
                        if(tmpIndex <= 8){
                            addFireBox();
                        }

                    }
                )
            ));
        }
        addFireBox();
        this.isActive = true;
    }
});

