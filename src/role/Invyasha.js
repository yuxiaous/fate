/**
 * Created by yuxiao on 15/1/15.
 */


var Invyasha = RoleBase.extend({
    //_armatureName: "QYCCC",
    //_effectName: "qyc_effect",
    //_attackName: "invyasha",
    //_width: 150,
    //_height: 225,
    //_maxComboCount: 5,
    //_speed: 300,

    ctor: function() {
        this._super("QYCCC", RoleBase.Direction.Left);

        this.setComboNumber(5);
        this.setRoleSize(cc.size(150, 225));

        this.addRoleAction(jsb.RoleActionManager.ActionType.STAND, "daiji");
        this.addRoleAction(jsb.RoleActionManager.ActionType.WALK, "pao");
        this.addRoleAction(jsb.RoleActionManager.ActionType.INJURE, "shouji1");

        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK1, "kan1", {
            range: cc.rect(100, -25, 150, 50),
            quakeIntensity: cc.p(5, 5),
            quakeTime: 0.05,
            pauseTime: 0.05,
            gVelocity: cc.p(200, 0),
            fVelocity: cc.p(90, 300),
            movement: 5,
            attackEffects: [
                {
                    armature: "qyc_effect",
                    animation: "kan1"
                }
            ],
            injureEffects: [
                {
                    armature: "hurt_effect",
                    animation: "smoke_effect"
                },
                {
                    armature: "hurt_effect",
                    animation: "light_effect"
                }
            ]
        });
        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK2, "kan2", {
            range: cc.rect(100, -25, 200, 50),
            quakeIntensity: cc.p(6, 6),
            quakeTime: 0.05,
            pauseTime: 0.05,
            gVelocity: cc.p(200, 0),
            fVelocity: cc.p(90, 300),
            movement: 15,
            attackEffects: [
                {
                    armature: "qyc_effect",
                    animation: "kan2"
                }
            ],
            injureEffects: [
                {
                    armature: "hurt_effect",
                    animation: "smoke_effect"
                },
                {
                    armature: "hurt_effect",
                    animation: "light_effect"
                }
            ]
        });
        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK3, "kan3", {
            range: cc.rect(100, -25, 150, 50),
            quakeIntensity: cc.p(8, 8),
            quakeTime: 0.05,
            pauseTime: 0.05,
            gVelocity: cc.p(200, 0),
            fVelocity: cc.p(90, 300),
            movement: 15,
            attackEffects: [
                {
                    armature: "qyc_effect",
                    animation: "kan3"
                }
            ],
            injureEffects: [
                {
                    armature: "hurt_effect",
                    animation: "smoke_effect"
                },
                {
                    armature: "hurt_effect",
                    animation: "light_effect"
                }
            ]
        });
        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK4, "kan4", {
            range: cc.rect(0, -25, 300, 50),
            quakeIntensity: cc.p(10, 10),
            quakeTime: 0.15,
            pauseTime: 0.15,
            gVelocity: cc.p(90, 900),
            fVelocity: cc.p(90, 700),
            movement: 200,
            attackEffects: [
                {
                    armature: "qyc_effect",
                    animation: "kan4"
                }
            ],
            injureEffects: [
                {
                    armature: "hurt_effect",
                    animation: "smoke_effect"
                },
                {
                    armature: "hurt_effect",
                    animation: "light_effect"
                }
            ]
        });
        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK5, "kan5", {
            range: cc.rect(-350, -25, 625, 50),
            quakeIntensity: cc.p(5, 5),
            quakeTime: 0.05,
            pauseTime: 0.05,
            gVelocity: cc.p(200, 0),
            fVelocity: cc.p(90, 300),
            movement: 130,
            attackEffects: [
                {
                    armature: "qyc_effect",
                    animation: "kan5"
                }
            ],
            injureEffects: [
                {
                    armature: "hurt_effect",
                    animation: "smoke_effect"
                },
                {
                    armature: "hurt_effect",
                    animation: "light_effect"
                }
            ]
        });

        this.setData({
            hp: 100,
            level: 13
        });
    }
});

