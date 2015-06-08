/**
 * Created by yuxiao on 15/3/17.
 */


var YingLiu = RoleBase.extend({
    ctor: function() {
        this._super("yingliu", RoleBase.Direction.Right);
        this.comboNumber = 1;
        this.speed = 200;


        this.addRoleAction(RoleAction.Type.STAND, "daiji2");
        this.addRoleAction(RoleAction.Type.WALK, "pao");
        this.addRoleAction(RoleAction.Type.INJURE, "shouji");
        this.addRoleAction(RoleAction.Type.FLOATING_UP, ["float1", "float2"]);
        this.addRoleAction(RoleAction.Type.FLOATING_GROUND, "touchground");
        this.addRoleAction(RoleAction.Type.STAND_UP, "qishen");
        this.addRoleAction(RoleAction.Type.DIE, ["float1", "touchground"]);


        this.addRoleAction(RoleAction.Type.ATTACK1, ["kan1","kan2"],{
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