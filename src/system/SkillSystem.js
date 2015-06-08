/**
 * Created by yuxiao on 15/5/14.
 */


var SkillSystem = SystemBase.extend({
    ctor: function () {
        this._super();
        this.skills = [];
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
            var idx = _.findIndex(this.skills, function(skl) {
                return skl.skill_id == skill.skill_id;
            });
            if(idx >= 0) {
                this.skills[idx] = skill;
            }
            else {
                this.skills.push(skill);
            }
        }, this);

        notification.emit(notification.event.SKILL_INFO);
    },

    requestSkillLevelUp: function(id) {
        net_protocol_handlers.SEND_CMD_CS_SKILL_UP({
            skill_id: id
        });
    },

    onSkillLevelUp: function() {
        MessageBoxOk.show("技能升级成功");
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
    }
});

