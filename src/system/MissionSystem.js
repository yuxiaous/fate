/**
 * Created by yuxiao on 15/10/26.
 */


var MissionSystem = SystemBase.extend({
    ctor: function () {
        this._super();
    },

    onInit: function () {
        this._super();
    },

    onFinalize: function () {
        this._super();
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

