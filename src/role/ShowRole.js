/**
 * Created by yuxiao on 15/5/27.
 */


var ShowRole = Role.extend({
    ctor: function(id) {
        this._super(id);

        this.setRoleAi(RoleAi.Type.Show);

        this.schedule(this.advanceTime);
    },

    advanceTime: function(dt) {
        this._super();
        dragonBones.DragonBonesHelper.advanceWorldClock(dt);
    }
});