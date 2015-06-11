/**
 * Created by yuxiao on 15/4/14.
 */


var Role = RoleBase.extend({
    ctor: function(id) {
        //LOG("ROLE CTOR");
        //LOG("ROLE BASE ID = "+ id);
        var roleConfig = configdb.role[id];
        if(roleConfig == undefined) {
            LOG("Error: role id {0} is not exist!!!".format(id));
            return;
        }

        var modelConfig = configdb.model[roleConfig.model_id];
        if(modelConfig == undefined) {
            LOG("Error: model id {0} is not exist!!!".format(roleConfig.model_id));
            LOG("role id {0}".format(id));
            return;
        }
        // super
        var designDirection = modelConfig.direction == 1 ? RoleBase.Direction.Left : RoleBase.Direction.Right;
        this._super(modelConfig.armature, designDirection);

        if(roleConfig.throw_model_id != undefined){
            this.throwModelId = roleConfig.throw_model_id;
        }

        // scale
        if(roleConfig.scale != undefined) {
            this.setScale(roleConfig.scale);
        }

        ///////////////////////////////////
        //  DATA
        ////////////////////////////////////

        // speed
        if(roleConfig.speed != undefined) {
            this.speed = roleConfig.speed;
        }

        // combo
        var combo = _.countBy([
            roleConfig.atk1, roleConfig.atk2, roleConfig.atk3, roleConfig.atk4, roleConfig.atk5
        ], function(atk) {
            return atk != undefined;
        });
        this.comboNumber = combo.true || 0;

        // injure time
        if(roleConfig.injure_time != undefined) {
            this.injureTime = roleConfig.injure_time;
        }

        // invincible time
        if(roleConfig.invincible_time != undefined) {
            this.invincibleTime = roleConfig.invincible_time;
        }

        //role icon name
        if(roleConfig.head_icon != undefined){
            this.iconName = roleConfig.head_icon;
        }

        this.setRoleData({
            hp: roleConfig.hp_value,
            mp: roleConfig.mp_value,
            atk: roleConfig.atk_value,
            def: roleConfig.def_value,
            crit : roleConfig.crit,
            crit_probability : roleConfig.crit_probability,
            sunder: roleConfig.sunder_value
        });

        ///////////////////////////////////
        //  ACTION
        ////////////////////////////////////

        // action stand
        if(modelConfig.stand) {
            this.addRoleAction(RoleAction.Type.STAND, modelConfig.stand);
        }

        // action walk
        if(modelConfig.walk) {
            this.addRoleAction(RoleAction.Type.WALK, modelConfig.walk, {
                effect: {
                    walk: {
                        sound: modelConfig.walk_sound
                    }
                }
            });
        }

        // action injure
        if(modelConfig.injure) {
            this.addRoleAction(RoleAction.Type.INJURE, modelConfig.injure, {
                effect: {
                    injure: {
                        sound: modelConfig.injure_sound
                    }
                }
            });
        }

        // action floating
        if(modelConfig.floating_up && modelConfig.floating_air) {
            this.addRoleAction(RoleAction.Type.FLOATING_UP, [
                modelConfig.floating_up,
                modelConfig.floating_air
            ]);
        }

        // action touch ground
        if(modelConfig.touch_ground) {
            this.addRoleAction(RoleAction.Type.FLOATING_GROUND, modelConfig.touch_ground);
        }

        // action stand up
        if(modelConfig.stand_up) {
            this.addRoleAction(RoleAction.Type.STAND_UP, modelConfig.stand_up);
        }

        // action die
        if(modelConfig.floating_up && modelConfig.touch_ground) {
            var dieAttr = {};
            if(modelConfig.die_sound){
                dieAttr.effect = {
                    sound: modelConfig.die_sound
                };
            }
            this.addRoleAction(RoleAction.Type.DIE, [
                modelConfig.floating_up,
                modelConfig.floating_air,
                modelConfig.touch_ground
            ],dieAttr);
        }


        //////////////////////////
        // ATTACK
        ///////////////////////////

        function getSkillAttr(skill_id, index) {
            var ret = {
                attack: {
                    animation: undefined,
                    sound: undefined, //"sounds/saber/atk1.mp3"
                    movement: undefined, //10,
                    strong: undefined, //1 or 0
                    throwModelId: undefined // 123
                },
                hit: {
                    animation: undefined, //"sabar_effect/jineng1"
                    sound: undefined, //"sounds/saber/hit.mp3"
                    velocity: {
                        onGround: undefined, //cc.p(180, 0)
                        onFloating: undefined //cc.p(90, 300)
                    },
                    quake: {
                        intensity: undefined, //5
                        time: undefined //0.05
                    },
                    pause: {
                        time: undefined //0.06
                    }
                }
            };

            var skillConfig = configdb.skill[skill_id];
            if(skillConfig != undefined) {
                ret.attack.animation = modelConfig["atk{0}_effect".format(index)];
                ret.attack.sound = modelConfig["atk{0}_sound".format(index)];
                ret.attack.movement = skillConfig.movement;
                ret.attack.strong = skillConfig.strongStatus;
                ret.attack.throwModelId = skillConfig.throw_model_id;

                ret.hit.animation = modelConfig["hit{0}_effect".format(index)];
                ret.hit.sound = modelConfig["hit{0}_sound".format(index)];
                ret.hit.velocity.onGround = cc.p(skillConfig.velocity_ground_x, skillConfig.velocity_ground_y);
                ret.hit.velocity.onFloating = cc.p(skillConfig.velocity_floating_x, skillConfig.velocity_floating_y);
                ret.hit.quake.intensity = skillConfig.quake_intensity;
                ret.hit.quake.time = skillConfig.quake_time;
                ret.hit.pause.time = skillConfig.pause_time;
            }
            return ret;
        }


        var attr;
        if(modelConfig.atk1 != undefined && roleConfig.atk1 != undefined) {
            attr = getSkillAttr(roleConfig.atk1, 1);
            this.addRoleAction(RoleAction.Type.ATTACK1, modelConfig.atk1, attr);
        }

        if(modelConfig.atk2 != undefined && roleConfig.atk2 != undefined) {
            attr = getSkillAttr(roleConfig.atk2, 2);
            this.addRoleAction(RoleAction.Type.ATTACK2, modelConfig.atk2, attr);
        }

        if(modelConfig.atk3 != undefined && roleConfig.atk3 != undefined) {
            attr = getSkillAttr(roleConfig.atk3, 3);
            this.addRoleAction(RoleAction.Type.ATTACK3, modelConfig.atk3, attr);
        }

        if(modelConfig.atk4 != undefined && roleConfig.atk4 != undefined) {
            attr = getSkillAttr(roleConfig.atk4, 4);
            this.addRoleAction(RoleAction.Type.ATTACK4, modelConfig.atk4, attr);
        }

        if(modelConfig.atk5 != undefined && roleConfig.atk5 != undefined) {
            attr = getSkillAttr(roleConfig.atk5, 5);
            this.addRoleAction(RoleAction.Type.ATTACK5, modelConfig.atk5, attr);
        }

        //////////////////////////
        // SKILL
        ///////////////////////////

        if(modelConfig.atk6 != undefined && roleConfig.skl1 != undefined) {
            attr = getSkillAttr(roleConfig.skl1, 6);
            this.addRoleAction(RoleAction.Type.SKILL1, modelConfig.atk6, attr);
        }

        if(modelConfig.atk7 != undefined && roleConfig.skl2 != undefined) {
            attr = getSkillAttr(roleConfig.skl2, 7);
            this.addRoleAction(RoleAction.Type.SKILL2, modelConfig.atk7, attr);
        }

        if(modelConfig.atk8 != undefined && roleConfig.skl3 != undefined) {
            attr = getSkillAttr(roleConfig.skl3, 8);
            this.addRoleAction(RoleAction.Type.SKILL3, modelConfig.atk8, attr);
        }

        if(modelConfig.atk9 != undefined && roleConfig.skl4 != undefined) {
            attr = getSkillAttr(roleConfig.skl4, 9);
            this.addRoleAction(RoleAction.Type.SKILL4, modelConfig.atk9, attr);
        }

        if(modelConfig.atk10 != undefined && roleConfig.skl5 != undefined) {
            attr = getSkillAttr(roleConfig.skl5, 10);
            this.addRoleAction(RoleAction.Type.SKILL5, modelConfig.atk10, attr);
        }
    }
});