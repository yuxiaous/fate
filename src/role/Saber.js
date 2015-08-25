/**
 * Created by yuxiao on 15/3/10.
 */


var Saber = RoleBase.extend({
    ctor: function() {
        this._super("sabar", RoleBase.Direction.Left);

        var config = configdb.role[1001];
        if(config == undefined) {
            return;
        }

        this.comboNumber = 5;
        this.speed = config.speed;
        this.injureTime = config.injure_time;
        this.invincibleTime = config.invincible_time;

        // scale
        if(config.scale != undefined) {
            this.setScale(config.scale);
        }

        var score = PlayerSystem.instance.getPlayerBattleScore();


        if(BattleSystem.instance.curIsTryBattle()){
            score.hp = score.hp * configdb.property[110].value;
            score.mp = score.mp * configdb.property[111].value;
        }

        this.setRoleData({
            hp: score.hp,
            mp: score.mp,
            atk: score.atk,
            def: score.def,
            crit : score.crit,
            crit_probability: score.critPro,
            sunder: score.sunder
        });

        // action
        this.addRoleAction(RoleAction.Type.STAND, "daiji");
        this.addRoleAction(RoleAction.Type.WALK, "xingzou", {
            sound: "sounds/saber/walk.mp3"
        });
        this.addRoleAction(RoleAction.Type.INJURE, "shouji", {
            sound: "sounds/saber/injure.mp3"
        });
        this.addRoleAction(RoleAction.Type.FLOATING_UP, ["fukong1", "fukong2"]);
        this.addRoleAction(RoleAction.Type.FLOATING_GROUND, "luodi");
        this.addRoleAction(RoleAction.Type.STAND_UP, "qishen");
        this.addRoleAction(RoleAction.Type.REVIVE,"qishen",{
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk5.mp3",
                movement: 200
            },
            hit: {
                animation: "sabar_effect/jineng5",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(500, 400),
                    onFloating: cc.p(500, 400)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.DIE, ["fukong1","fukong2", "luodi"]);

        this.addRoleAction(RoleAction.Type.ATTACK1, "gongji1", {
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk1.mp3",
                movement: 10
            },
            hit: {
                animation: "sabar_effect/jineng1",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(180, 0),
                    onFloating: cc.p(90, 300)
                },
                quake: {
                    intensity: 5,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }

            //remoteAtk : {
            //    animation : "remote atk test",
            //    sound : "remote atk sound",
            //    remoteType : ThrowArrow
            //}
        });
        this.addRoleAction(RoleAction.Type.ATTACK2, "gongji2", {
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk2.mp3",
                movement: 10
            },
            hit: {
                animation: "sabar_effect/jineng2",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(180, 0),
                    onFloating: cc.p(90, 300)
                },
                quake: {
                    intensity: 5,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.ATTACK3, "gongji3", {
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk3.mp3",
                movement: 150
            },
            hit: {
                animation: "sabar_effect/jineng3",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(200, 0),
                    onFloating: cc.p(200, 300)
                },
                quake: {
                    intensity: 8,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.ATTACK4, "gongji4", {
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk4.mp3",
                movement: 10
            },
            hit: {
                animation: "sabar_effect/jineng4",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(200, 780),
                    onFloating: cc.p(200, 400)
                },
                quake: {
                    intensity: 13,
                    time: 0.09
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.ATTACK5, "gongji5", {
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk5.mp3",
                movement: 200
            },
            hit: {
                animation: "sabar_effect/jineng5",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 0),
                    onFloating: cc.p(400, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });

        this.addRoleAction(RoleAction.Type.SKILL1, "jineng1", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/saber/skill_1.mp3",
                movement: 300
            },
            hit: {
                animation: "sabar_effect/jineng6",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 780),
                    onFloating: cc.p(800, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.2
            },
            cdTime : 6,
            mpCost : 8
        });
        this.addRoleAction(RoleAction.Type.SKILL2, "jineng2", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/saber/skill_2.mp3",
                movement: 600
            },
            hit: {
                animation: "sabar_effect/jineng6",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 780),
                    onFloating: cc.p(500, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.3
            },
            cdTime: 8,
            mpCost : 10
        });
        this.addRoleAction(RoleAction.Type.SKILL3, "jineng3", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/saber/skill_3.mp3",
                movement: 300
            },
            hit: {
                animation: "sabar_effect/jineng7",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 780),
                    onFloating: cc.p(500, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.4
            },
            cdTime: 10,
            mpCost : 12
        });
        this.addRoleAction(RoleAction.Type.SKILL4, "jineng4", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/saber/skill_4.mp3",
                movement: 300
            },
            hit: {
                animation: "sabar_effect/jineng7",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 200),
                    onFloating: cc.p(500, 100)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.5
            },
            cdTime: 0,
            mpCost : 15
        });
        this.addRoleAction(RoleAction.Type.SKILL5, "jineng5", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/saber/skill_5.mp3",
                movement: 500,
                drag : -18000
            },
            hit: {
                animation: "sabar_effect/jineng7",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 200),
                    onFloating: cc.p(500, 100)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.0
            },
            cdTime: 1.0,
            mpCost : 0
        });

    }
});

var Nero = RoleBase.extend({
    ctor: function() {
        this._super("nero", RoleBase.Direction.Left);

        var config = configdb.role[1001];
        if(config == undefined) {
            return;
        }

        this.comboNumber = 5;
        this.speed = config.speed;
        this.injureTime = config.injure_time;
        this.invincibleTime = config.invincible_time;

        // scale
        if(config.scale != undefined) {
            this.setScale(config.scale);
        }

        var score = PlayerSystem.instance.getPlayerBattleScore();

        if(BattleSystem.instance.curIsTryBattle()){
            LOG("cur is try battle");
            score.hp = score.hp * configdb.property[110].value;
            score.mp = score.mp * configdb.property[111].value;
        }

        this.setRoleData({
            hp: score.hp,
            mp: score.mp,
            atk: score.atk,
            def: score.def,
            crit : score.crit,
            crit_probability: score.critPro,
            sunder: score.sunder
        });

        // action
        this.addRoleAction(RoleAction.Type.STAND, "daiji");
        this.addRoleAction(RoleAction.Type.WALK, "xingzou", {
            sound: "sounds/saber/walk.mp3"
        });
        this.addRoleAction(RoleAction.Type.INJURE, "shouji", {
            sound: "sounds/saber/injure.mp3"
        });
        this.addRoleAction(RoleAction.Type.FLOATING_UP, ["fukong1", "fukong2"]);
        this.addRoleAction(RoleAction.Type.FLOATING_GROUND, "luodi");
        this.addRoleAction(RoleAction.Type.STAND_UP, "qishen");
        this.addRoleAction(RoleAction.Type.REVIVE,"qishen",{
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk5.mp3",
                movement: 200
            },
            hit: {
                animation: "sabar_effect/jineng5",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(500, 400),
                    onFloating: cc.p(500, 400)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.DIE, ["fukong1","fukong2", "luodi"]);

        this.addRoleAction(RoleAction.Type.ATTACK1, "gongji1", {
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk1.mp3",
                movement: 10
            },
            hit: {
                animation: "sabar_effect/jineng1",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(180, 0),
                    onFloating: cc.p(90, 300)
                },
                quake: {
                    intensity: 5,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }

            //remoteAtk : {
            //    animation : "remote atk test",
            //    sound : "remote atk sound",
            //    remoteType : ThrowArrow
            //}
        });
        this.addRoleAction(RoleAction.Type.ATTACK2, "gongji2", {
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk2.mp3",
                movement: 10
            },
            hit: {
                animation: "sabar_effect/jineng2",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(180, 0),
                    onFloating: cc.p(90, 300)
                },
                quake: {
                    intensity: 5,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.ATTACK3, "gongji3", {
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk3.mp3",
                movement: 150
            },
            hit: {
                animation: "sabar_effect/jineng3",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(200, 0),
                    onFloating: cc.p(200, 300)
                },
                quake: {
                    intensity: 8,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.ATTACK4, "gongji4", {
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk4.mp3",
                movement: 10
            },
            hit: {
                animation: "sabar_effect/jineng4",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(200, 780),
                    onFloating: cc.p(200, 400)
                },
                quake: {
                    intensity: 13,
                    time: 0.09
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.ATTACK5, "gongji5", {
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk5.mp3",
                movement: 200
            },
            hit: {
                animation: "sabar_effect/jineng5",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 0),
                    onFloating: cc.p(400, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });

        this.addRoleAction(RoleAction.Type.SKILL1, "jineng1", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/saber/skill_1.mp3",
                movement: 311
            },
            hit: {
                animation: "sabar_effect/jineng6",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 780),
                    onFloating: cc.p(800, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.2
            },
            cdTime : 6,
            mpCost : 8
        });
        this.addRoleAction(RoleAction.Type.SKILL2, "jineng2", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/saber/skill_2.mp3",
                movement: 600
            },
            hit: {
                animation: "sabar_effect/jineng6",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 780),
                    onFloating: cc.p(500, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.3
            },
            cdTime: 8,
            mpCost : 10
        });
        this.addRoleAction(RoleAction.Type.SKILL3, "jineng3", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/saber/skill_3.mp3",
                movement: 300
            },
            hit: {
                animation: "sabar_effect/jineng7",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 780),
                    onFloating: cc.p(500, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.4
            },
            cdTime: 10,
            mpCost : 12
        });
        this.addRoleAction(RoleAction.Type.SKILL4, "jineng4", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/saber/skill_4.mp3",
                movement: 300
            },
            hit: {
                animation: "sabar_effect/jineng7",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 200),
                    onFloating: cc.p(500, 100)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.5
            },
            cdTime: 0,
            mpCost : 15
        });
        this.addRoleAction(RoleAction.Type.SKILL5, "jineng5", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/saber/skill_5.mp3",
                movement: 500,
                drag : -18000
            },
            hit: {
                animation: "sabar_effect/jineng7",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 200),
                    onFloating: cc.p(500, 100)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.0
            },
            cdTime: 1.0,
            mpCost : 0
        });

    }
});

var Archer = RoleBase.extend({
    ctor: function() {
        this._super("archer", RoleBase.Direction.Left);

        var config = configdb.role[1201];
        if(config == undefined) {
            return;
        }

        this.comboNumber = 5;
        this.speed = config.speed;
        this.injureTime = config.injure_time;
        this.invincibleTime = config.invincible_time;

        // scale
        if(config.scale != undefined) {
            this.setScale(config.scale);
        }

        var score = PlayerSystem.instance.getPlayerBattleScore();


        if(BattleSystem.instance.curIsTryBattle()){
            score.hp = score.hp * configdb.property[110].value;
            score.mp = score.mp * configdb.property[111].value;
        }

        this.setRoleData({
            hp: score.hp,
            mp: score.mp,
            atk: score.atk,
            def: score.def,
            crit : score.crit,
            crit_probability: score.critPro,
            sunder: score.sunder
        });

        // action
        this.addRoleAction(RoleAction.Type.STAND, "daiji");
        this.addRoleAction(RoleAction.Type.WALK, "xingzou", {
            sound: "sounds/saber/walk.mp3"
        });
        this.addRoleAction(RoleAction.Type.INJURE, "shouji", {
            sound: "sounds/archer/injure.mp3"
        });
        this.addRoleAction(RoleAction.Type.FLOATING_UP, ["fukong1", "fukong2"]);
        this.addRoleAction(RoleAction.Type.FLOATING_GROUND, "luodi");
        this.addRoleAction(RoleAction.Type.STAND_UP, "qishen");
        this.addRoleAction(RoleAction.Type.REVIVE,"qishen",{
            attack: {
                animation: undefined,
                sound: "sounds/saber/atk5.mp3",
                movement: 200
            },
            hit: {
                animation: "sabar_effect/jineng5",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(500, 400),
                    onFloating: cc.p(500, 400)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.DIE, ["fukong1","fukong2", "luodi"]);

        this.addRoleAction(RoleAction.Type.ATTACK1, "gongji1", {
            attack: {
                animation: undefined,
                sound: "sounds/archer/atk1.mp3",
                movement: 50
            },
            hit: {
                animation: "sabar_effect/jineng1",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(180, 0),
                    onFloating: cc.p(90, 300)
                },
                quake: {
                    intensity: 5,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }

            //remoteAtk : {
            //    animation : "remote atk test",
            //    sound : "remote atk sound",
            //    remoteType : ThrowArrow
            //}
        });
        this.addRoleAction(RoleAction.Type.ATTACK2, "gongji2", {
            attack: {
                animation: undefined,
                sound: "sounds/archer/atk2.mp3",
                movement: 20
            },
            hit: {
                animation: "sabar_effect/jineng2",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(180, 0),
                    onFloating: cc.p(90, 300)
                },
                quake: {
                    intensity: 5,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.ATTACK3, "gongji3", {
            attack: {
                animation: undefined,
                sound: "sounds/archer/atk3.mp3",
                movement: 150
            },
            hit: {
                animation: "sabar_effect/jineng3",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(200, 0),
                    onFloating: cc.p(200, 300)
                },
                quake: {
                    intensity: 8,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.ATTACK4, "gongji4", {
            attack: {
                animation: undefined,
                sound: "sounds/archer/atk4.mp3",
                movement: 50
            },
            hit: {
                animation: "sabar_effect/jineng4",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(200, 780),
                    onFloating: cc.p(200, 400)
                },
                quake: {
                    intensity: 13,
                    time: 0.09
                },
                pause: {
                    time: 0
                }
            }
        });
        this.addRoleAction(RoleAction.Type.ATTACK5, "gongji5", {
            attack: {
                animation: undefined,
                sound: "sounds/archer/atk5.mp3",
                movement: 200
            },
            hit: {
                animation: "sabar_effect/jineng5",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 0),
                    onFloating: cc.p(400, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                }
            }
        });

        this.addRoleAction(RoleAction.Type.SKILL1, "jineng1", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/archer/skill_1.mp3",
                movement: 300
            },
            hit: {
                animation: "sabar_effect/jineng6",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 780),
                    onFloating: cc.p(800, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.2
            },
            cdTime : 6,
            mpCost : 8
        });
        this.addRoleAction(RoleAction.Type.SKILL2, "jineng2", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/archer/skill_2.mp3",
                movement: 750
            },
            hit: {
                animation: "sabar_effect/jineng6",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 780),
                    onFloating: cc.p(500, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.3
            },
            cdTime: 8,
            mpCost : 10
        });
        this.addRoleAction(RoleAction.Type.SKILL3, "jineng3", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/archer/skill_3.mp3",
                movement: 300
            },
            hit: {
                animation: "sabar_effect/jineng7",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 780),
                    onFloating: cc.p(500, 250)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.4
            },
            cdTime: 10,
            mpCost : 12
        });
        this.addRoleAction(RoleAction.Type.SKILL4, "jineng4", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/archer/skill_4.mp3",
                movement: 300
            },
            hit: {
                animation: "sabar_effect/jineng7",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 200),
                    onFloating: cc.p(500, 100)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.5
            },
            cdTime: 0,
            mpCost : 15
        });
        this.addRoleAction(RoleAction.Type.SKILL5, "jineng5", {
            attack: {
                //animation: undefined,
                skill_sound: "sounds/saber/skill_5.mp3",
                movement: 500,
                drag : -18000
            },
            hit: {
                animation: "sabar_effect/jineng7",
                sound: "sounds/saber/hit.mp3",
                velocity: {
                    onGround: cc.p(300, 200),
                    onFloating: cc.p(500, 100)
                },
                quake: {
                    intensity: 15,
                    time: 0.05
                },
                pause: {
                    time: 0
                },
                power : 1.0
            },
            cdTime: 1.0,
            mpCost : 0
        });

    }
});