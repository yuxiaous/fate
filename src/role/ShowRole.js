/**
 * Created by yuxiao on 15/5/27.
 */


var ShowRole = Role.extend({
    ctor: function(id) {
        this._super(id);

        this.setRoleAi(RoleAi.Type.Show);
        this.schedule(this.advanceTime);

        this._walk_action = false;
    },

    advanceTime: function(dt) {
        this._super();

        this.movingValue = this._walk_action;
        dragonBones.DragonBonesHelper.advanceWorldClock(dt);
    },

    setWalkAction : function () {

        this.addRoleAction(RoleAction.Type.WALK,"xingzou");
        this._walk_action = true;
        this.hideShadow();
    }
});
