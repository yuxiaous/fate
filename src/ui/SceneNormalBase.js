/**
 * Created by yuxiao on 15/4/8.
 */


var SceneNormalBase = SceneBase.extend({
    ctor: function(sceneName) {
        this._super(sceneName,SceneBase.Type.NormalType);
    },

    onEnter: function() {
        this._super();
        cc.director.getScheduler().schedule(this.refreshGuaiTarget,this,1/60,cc.REPEAT_FOREVER,0,false,"refreshTarget");
    },

    onExit: function() {
        cc.director.getScheduler().unschedule(this,"refreshTarget");

        this._super();
    },

    refreshGuaiTarget : function (dt) {
        // set target
        var that = this;
        function setMonsterTarget(monster, target) {
            var ai = monster.getRoleAi();
            if(ai.target == null){
                var targetPos = target.getSpacePosition();
                if(targetPos.x > 400){
                    ai.target = target;
                }
            }
        }
        if(this._boss && this._hero) {
            setMonsterTarget(this._boss, this._hero);
        }
        if(this._monsters && this._hero){
            _.each(this._monsters, function(monster) {
                setMonsterTarget(monster, this._hero);
            }, this);
        }
    }
});