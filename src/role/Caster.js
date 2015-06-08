/**
 * Created by yuxiao on 15/3/17.
 */


var Caster = RoleBase.extend({
    ctor: function() {
        this._super("caster", RoleBase.Direction.Left);
        this.comboNumber = 1;
        this.speed = 200;


        this.addRoleAction(RoleAction.Type.STAND, "daiji");
        this.addRoleAction(RoleAction.Type.WALK, "xingzou");
        this.addRoleAction(RoleAction.Type.INJURE, "shouji");
        this.addRoleAction(RoleAction.Type.FLOATING_UP, ["fukong1", "fukong2"]);
        this.addRoleAction(RoleAction.Type.FLOATING_GROUND, "luodi");
        this.addRoleAction(RoleAction.Type.STAND_UP, "qishen");
        this.addRoleAction(RoleAction.Type.DIE, ["fukong1", "luodi"]);


        this.addRoleAction(RoleAction.Type.ATTACK1, ["gongji1"],{
            attack: {
                animation: undefined,
                sound: "",
                movement: 10
            },
            hit: {
                animation: "sabar_effect/jineng1",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(0, 0),
                    onFloating: cc.p(90, 300)
                },
                quake: {
                    intensity: 5,
                    time: 0.05
                },
                pause: {
                    time: 0.06
                }
            }
        });

        this.setBloodBar();
    }
});