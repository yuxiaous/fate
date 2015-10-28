/**
 * Created by yuxiao on 15/10/26.
 */


var MissionSystem = SystemBase.extend({
    ctor: function () {
        this._super();

        this.mission_list = {};
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_MISSION_INFO = this.onMissionInfo.bind(this);
        net_protocol_handlers.ON_CMD_SC_MISSION_COMPLETE_RESULT = this.onCompleteMissionResult.bind(this);
        net_protocol_handlers.ON_CMD_SC_MISSION_GET_REWARD_RESULT = this.onGetMissionRewardResult.bind(this);
    },

    onFinalize: function () {
        net_protocol_handlers.ON_CMD_SC_MISSION_INFO = null;
        net_protocol_handlers.ON_CMD_SC_MISSION_COMPLETE_RESULT = null;
        net_protocol_handlers.ON_CMD_SC_MISSION_GET_REWARD_RESULT = null;
        this._super();
    },

    onMissionInfo: function(obj) {
        LOG("onMissionInfo")
        LOG(obj)

        _.each(obj.missions, function(info) {
            this.mission_list[info.mission_id] = info;
        }, this);

        notification.emit(notification.event.MISSION_INFO);
    },

    completeMission: function(id, num) {
        net_protocol_handlers.SEND_CMD_CS_MISSION_COMPLETE({
            mission_id: id,
            complete_num: num
        });
    },
    onCompleteMissionResult: function(obj) {

    },

    getMissionReward: function(id) {
        net_protocol_handlers.SEND_CMD_CS_MISSION_GET_REWARD({
            mission_id: id
        });
    },
    onGetMissionRewardResult: function(obj) {

    },

    next: function(mission_id) {

    }
});

MissionSystem.Class = {
    Daily: 1,
    Achievement: 2
};

MissionSystem.Type = {
    KillMonster: 1,
    Fuben: 2,
    Combo: 3,
    Shilian: 4,
    Strengthen: 5,
    SkillUpgrage: 6,
    EquipSlotUpgrade: 7,
    MapUnlock: 8,
    BattleScore: 9,
    UseBisha: 10,
    UseHpBottle: 11,
    Resurrection: 12, //复活
    Vip: 13,
    CompleteAllMissions: 14
};

