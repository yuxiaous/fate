/**
 * Created by yuxiao on 15/3/10.
 */


var Fangyan = RoleBase.extend({
    ctor: function() {
        this._super("fangyan", RoleBase.Direction.Left);

        this.setComboNumber(5);
        this.setRoleSize(cc.size(200, 185));
        this.setSpeed(500);
        this.setBestAttackRange(cc.rect(150, -20, 40, 40));
        this.setBestAttackLength(150);
        this.setViewLength(500);

        this.addRoleAction(jsb.RoleActionManager.ActionType.STAND, "daiji");
        this.addRoleAction(jsb.RoleActionManager.ActionType.WALK, "xingzou");
        this.addRoleAction(jsb.RoleActionManager.ActionType.INJURE, "shouji");
        //this.addRoleAction(jsb.RoleActionManager.ActionType.FLOATING_UP, ["float1", "float2"]);
        //this.addRoleAction(jsb.RoleActionManager.ActionType.FLOATING_GROUND, "touchground");
        //this.addRoleAction(jsb.RoleActionManager.ActionType.STAND_UP, "qishen");
        //this.addRoleAction(jsb.RoleActionManager.ActionType.DIE, "siwang");
        //this.addRoleAction(jsb.RoleActionManager.ActionType.STRUCK_OUT, "jifei", {
        //    gVelocity: cc.p(400, 500),
        //    fVelocity: cc.p(500, 250)
        //});

        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK1, "gongji1", {
            range: cc.rect(0, -50, 150, 100),
            quake: {
                intensity: cc.p(5, 5),
                time: 0.05
            },
            pause: {
                time: 0.05
            },
            velocity: {
                onGround: cc.p(180, 0),
                onFloating: cc.p(90, 300)
            },
            movement: cc.p(10, 0),
            effect: {
                attack: [
                ],
                injure: [
                    {
                        armature: "fangyan_effect",
                        animation: "jineng01",
                        sound: "hit1.mp3",
                        position: cc.p(0, 180),
                        rotation: 0,
                        scale: 1.5
                    }
                ]
            }
        });
        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK2, "gongji2", {
            range: cc.rect(0, -50, 150, 100),
            quake: {
                intensity: cc.p(5, 5),
                time: 0.05
            },
            pause: {
                time: 0.05
            },
            velocity: {
                onGround: cc.p(180, 0),
                onFloating: cc.p(90, 300)
            },
            movement: cc.p(10, 0),
            effect: {
                attack: [
                ],
                injure: [
                    {
                        armature: "fangyan_effect",
                        animation: "jineng02",
                        sound: "hit2.mp3",
                        position: cc.p(0, 180),
                        rotation: 0,
                        scale: 1.5
                    }
                ]
            }
        });
        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK3, "gongji3", {
            range: cc.rect(0, -50, 150, 100),
            quake: {
                intensity: cc.p(8, 8),
                time: 0.05
            },
            pause: {
                time: 0.05
            },
            velocity: {
                onGround: cc.p(200, 780),
                onFloating: cc.p(200, 300)
            },
            movement: cc.p(150, 0),
            effect: {
                attack: [
                ],
                injure: [
                    {
                        armature: "fangyan_effect",
                        animation: "jineng03",
                        sound: "hit3.mp3",
                        position: cc.p(0, 180),
                        rotation: 0,
                        scale: 1.5
                    }
                ]
            }
        });
        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK4, "gongji4", {
            range: cc.rect(0, -50, 200, 100),
            quake: {
                intensity: cc.p(8, 8),
                time: 0.05
            },
            pause: {
                time: 0.05
            },
            velocity: {
                onGround: cc.p(300, 0),
                onFloating: cc.p(300, 400)
            },
            movement: cc.p(100, 0),
            effect: {
                attack: [
                ],
                injure: [
                    {
                        armature: "fangyan_effect",
                        animation: "jineng04",
                        sound: "hit3.mp3",
                        position: cc.p(0, 180),
                        rotation: 0,
                        scale: 1.5
                    }
                ]
            }
        });
        this.addRoleAction(jsb.RoleActionManager.ActionType.ATTACK5, "gongji5", {
            range: cc.rect(0, -50, 200, 100),
            quake: {
                intensity: cc.p(15, 15),
                time: 0.05
            },
            pause: {
                time: 0.05
            },
            velocity: {
                onGround: cc.p(500, 0),
                onFloating: cc.p(600, 250)
            },
            movement: cc.p(5, 0),
            effect: {
                attack: [
                    {
                        sound: "attack1.mp3"
                    }
                ],
                injure: [
                    {
                        armature: "fangyan_effect",
                        animation: "jineng05",
                        sound: "hit2.mp3",
                        position: cc.p(0, 180),
                        rotation: 0,
                        scale: 1.5
                    }
                ]
            }
        });

        this.addRoleAction(jsb.RoleActionManager.ActionType.SKILL1, "jineng01", {
            range: cc.rect(0, -50, 100, 100),
            quake: {
                intensity: cc.p(15, 15),
                time: 0.05
            },
            pause: {
                time: 0.05
            },
            velocity: {
                onGround: cc.p(800, 300),
                onFloating: cc.p(800, 250)
            },
            movement: cc.p(600, 0),
            effect: {
                attack: [
                ],
                injure: [
                    {
                        armature: "fangyan_effect",
                        animation: "jineng06",
                        sound: "hit3.mp3",
                        position: cc.p(0, 180),
                        rotation: 0,
                        scale: 1.5
                    }
                ]
            }
        });

        this.setData({
            hp: 10000,
            level: 12
        });
    }
});