/**
 * Created by yuxiao on 15/5/14.
 */


var SkillSystem = SystemBase.extend({
    ctor: function () {
        this._super();
        this.skills = {};
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_SKILL_INFO = this.onSkillInfo.bind(this);
        net_protocol_handlers.ON_CMD_SC_SKILL_UP_RESULT = this.onSkillLevelUp.bind(this);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_SKILL_INFO = null;
        net_protocol_handlers.ON_CMD_SC_SKILL_UP_RESULT = null;
    },

    onSkillInfo: function(obj) {
        _.each(obj.skills, function(skill) {
            this.skills[skill.skill_id] = skill;
        }, this);

        notification.emit(notification.event.SKILL_INFO);
    },

    requestSkillLevelUp: function(id) {
        net_protocol_handlers.SEND_CMD_CS_SKILL_UP({
            skill_id: id
        });
    },

    onSkillLevelUp: function() {

    },

    canUpgradeSkill: function() {
        var ret = false;

        _.some(this.skills, function(skill) {
            var config = configdb.skill[skill.skill_id];
            if(config == undefined) {
                return false;
            }

            config = configdb.skillup[config.skillup_id + skill.level - 1];
            if(config == undefined) {
                return false;
            }

            if(config.skill_id != skill.skill_id) {
                return false;
            }

            if(config.cost <= PlayerSystem.instance.gold) {
                ret = true;
            }
            return ret
        }, this);

        return ret;
    },

    getSkillUPLevel : function(skill_type_){
        var conf = this.getSkillUpConfig(skill_type_);
        if(conf){
            return conf.skill_up;
        }
        return 1;
    },

    getSkillUpMpcost : function(skill_type_){
        var conf = this.getSkillUpConfig(skill_type_);
        if(conf){
            return conf.cost_mp;;
        }
        return 0;
    },

    getSkillUpConfig : function (skill_type_) {
        var skillId = 0;
        switch (skill_type_){
            case  RoleAction.Type.SKILL1 :
                skillId = 10106;
                break;
            case  RoleAction.Type.SKILL2 :
                skillId = 10107;
                break;
            case  RoleAction.Type.SKILL3 :
                skillId = 10108;
                break;
            case  RoleAction.Type.SKILL4 :
                skillId = 10109;
                break;
        }
        var level = 1;
        _.each(this.skills, function (skill) {
            if( skill && skill.skill_id == skillId){
                level = skill.level;
            }
        });

        var tmpSkillInfo = null;
        _.each(configdb.skillup, function (skillInfo_) {
            if(skillInfo_.skill_id == skillId && skillInfo_.level == level){
                tmpSkillInfo = skillInfo_;
            }
        });

        return tmpSkillInfo;
    }


});

