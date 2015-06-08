/**
 * Created by yuxiao on 14/12/28.
 */


var Wolf = RoleBase.extend({
    //_armatureName: "yaolangdajiang",
    //_attackName: "wolf",
    //_width: 200,
    //_height: 185,
    //_maxComboCount: 2,
    //_speed: 100,

    ctor: function() {
        this._super("yaolangdajiang", RoleBase.Direction.Left);

        this.setComboNumber(1);
        this.setRoleSize(cc.size(200, 185));
        this.setSpeed(100);
        this.setBestAttackRange(cc.rect(150, -20, 40, 40));
        this.setViewLength(500);

        this.addRoleAction(jsb.RoleActionManager.ActionType.STAND, "daiji");
        this.addRoleAction(jsb.RoleActionManager.ActionType.WALK, "pao");
        this.addRoleAction(jsb.RoleActionManager.ActionType.INJURE, "shouji1");
        this.addRoleAction(jsb.RoleActionManager.ActionType.FLOATING_UP, ["float1", "float2"]);
        this.addRoleAction(jsb.RoleActionManager.ActionType.FLOATING_GROUND, "touchground");
        this.addRoleAction(jsb.RoleActionManager.ActionType.STAND_UP, "qishen");
        this.addRoleAction(jsb.RoleActionManager.ActionType.DIE, "siwang");
        this.addRoleAction(jsb.RoleActionManager.ActionType.STRUCK_OUT, "jifei", {
            gVelocity: cc.p(400, 500),
            fVelocity: cc.p(500, 250)
        });

        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK1, "kan1", {
            range: cc.rect(100, -25, 150, 50),
            quakeIntensity: cc.p(5, 5),
            quakeTime: 0.05,
            pauseTime: 0.05,
            gVelocity: cc.p(0, 0),
            fVelocity: cc.p(90, 300),
            movement: 0,
            injureEffects: [
                {
                    armature: "hurt_effect",
                    animation: "smoke_effect"
                }
            ]
        });

        this.setData({
            hp: 10000
        });
    }
});

