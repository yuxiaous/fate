/**
 * Created by yuxiao on 15/3/17.
 */


var SkullMan = RoleBase.extend({
    ctor: function() {
        this._super("guai03", RoleBase.Direction.Left);
        this.comboNumber = 1;
        this.speed = 200;


        this.addRoleAction(RoleAction.Type.STAND, "daiji");
        this.addRoleAction(RoleAction.Type.WALK, "xingzou");
        this.addRoleAction(RoleAction.Type.INJURE, "shouji");
        this.addRoleAction(RoleAction.Type.FLOATING_UP, ["fukong1", "fukong2"]);
        this.addRoleAction(RoleAction.Type.FLOATING_GROUND, "luodi");
        this.addRoleAction(RoleAction.Type.STAND_UP, "qishen");
        this.addRoleAction(RoleAction.Type.DIE, ["fukong1", "fukong2", "luodi"]);


        this.addRoleAction(RoleAction.Type.ATTACK1, "gongji");

        this.setBloodBar();
    }
});

