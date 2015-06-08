/**
 * Created by yuxiao on 15/3/16.
 */


var HatchetMen = RoleBase.extend({
    ctor: function() {
        this._super("guai01", RoleBase.Direction.Left);

        this.setComboNumber(1);
        this.setRoleSize(cc.size(200, 200));
        this.setSpeed(200);
        this.setBestAttackRange(cc.rect(150, -20, 40, 40));
        this.setBestAttackLength(150);
        this.setViewLength(500);

        this.addRoleAction(jsb.RoleActionManager.ActionType.STAND, "daiji");
        this.addRoleAction(jsb.RoleActionManager.ActionType.WALK, "xingzou");
        this.addRoleAction(jsb.RoleActionManager.ActionType.INJURE, "shouji");
        this.addRoleAction(jsb.RoleActionManager.ActionType.FLOATING_UP, ["fukong01", "fukong02"]);
        this.addRoleAction(jsb.RoleActionManager.ActionType.FLOATING_GROUND, "luodi");
        this.addRoleAction(jsb.RoleActionManager.ActionType.STAND_UP, "qishen");
        this.addRoleAction(jsb.RoleActionManager.ActionType.DIE, ["fukong01", "fukong02", "luodi"]);

        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK1, "gongji01", {
            range: cc.rect(0, -25, 150, 50),
            quake: {
                intensity: cc.p(5, 5),
                time: 0.05
            },
            pause: {
                time: 0.05
            },
            velocity: {
                onGround: cc.p(0, 0),
                onFloating: cc.p(90, 300)
            },
            movement: cc.p(0, 0),
            effect: {
                attack: [
                ],
                injure: [
                    {
                        sound: "hit1.mp3"
                    }
                ]
            }
        });

        this.setData({
            hp: 100
        });
    }

});