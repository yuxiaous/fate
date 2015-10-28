/**
 * Created by yuxiao on 15/10/26.
 */


var mission_server = {
    start: function() {
        this.mission_info = database.checkout("mission_info", {
            time: 0,
            daily: [
                //{mission_id: 0, reward: 0}
            ],
            achievement: [
                //{mission_id: 0, reward: 0}
            ],
            count: [
                //{type: 1, total: 0, daily: 0}
            ]
        });

        this.mission_list = [
            //{mission_id: 0, count: 0, reward: 0}
        ];

        this.initDailyMission();
        this.flush();
    },

    end: function() {

    },

    flush: function() {
        //database.commit("mission_info", this.mission_info);
    },

    sync: function() {

    },

    initDailyMission: function() {
        if(util.compareTimeWithToday(this.mission_info.time)) {
            this.mission_info.time = util.getCurrentDate();
            this.mission_info.daily.length = 0;

            _.each(this.mission_info.count, function(count) {
                count.daily = 0;
            });

            _.each(mission_server.Type, function(type) {
                var filter = _.where(configdb.renwu, {class: mission_server.Class.Daily, type: type});
                _.some(filter, function(config) {
                    if(config.next) {
                        var next_config = configdb.renwu[config.next];
                        if(player_server.player_info.level < next_config.level) {
                            this.mission_info.daily.push({mission_id: config.key, reward: 0});
                            return true;
                        }
                    }
                    else {
                        this.mission_info.daily.push({mission_id: config.key, reward: 0});
                        return true;
                    }
                    return false;
                }, this)
            }, this);
        }
    },

    getMissionList: function() {
        var list = [];

        _.each(this.mission_info.daily, function(daily) {
            var config = configdb.renwu[daily.mission_id];
            if(config) {
                var count = _.findWhere(this.mission_info.count, {type: config.type});
                list.push({mission_id: config.key, count: count ? count.daily : 0, reward: daily.reward});
            }
        }, this);

        _.each(mission_server.Type, function(type) {
            var filter = _.where(configdb.renwu, {class: mission_server.Class.Achievement, type: type});
            _.some(filter, function(config) {
                var count = _.findWhere(this.mission_info.count, {type: config.type});
                if(count == undefined) {
                    count = {type: config.type, total: 0, daily: 0};
                }
                var reward = _.findWhere(this.mission_info.achievement, {mission_id: config.key});
                if(reward == undefined) {
                    reward = {mission_id: config.key, reward: 0}
                }

                if(config.next == undefined || count.total < config.need_num || reward.reward == 0) {
                    list.push({mission_id: config.key, count: count.total, reward: reward.reward});
                    return true;
                }

                return false;
            }, this);
        }, this);

        return list;
    },

    count: function(type, num) {
        var info = _.findWhere(this.mission_info.count, {type: type});
        if(info == undefined) {
            info = {type: type, total: 0, daily: 0};
            this.mission_info.count.push(info);
        }
        info.total += num;
        info.daily += num;

        this.flush();
    }
};

mission_server.Class = {
    Daily: 1,
    Achievement: 2
};

mission_server.Type = {
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

server.registerCallback(net_protocol_handlers.CMD_CS_MISSION_COMPLETE, function(obj) {
    LOG("CMD_CS_MISSION_COMPLETE");

    // send result
    server.send(net_protocol_handlers.CMD_SC_MISSION_COMPLETE_RESULT, {
        result: 0
    });
});

server.registerCallback(net_protocol_handlers.CMD_CS_MISSION_GET_REWARD, function(obj) {
    LOG("CMD_CS_MISSION_GET_REWARD");

    var info = _.findWhere(mission_server.mission_info, {mission_id: obj.mission_id});
    if(info == undefined) {
        LOG("CMD_CS_MISSION_GET_REWARD 1");
        server.sendError(error.ERR_CONFIG_NOT_EXIST);
        return;
    }

    if(info.reward == 1) {
        LOG("CMD_CS_MISSION_GET_REWARD 2");
        server.sendError(error.ERR_MISSION_HAVE_REWARD);
        return;
    }

    info.reward = 1;

    server.send(net_protocol_handlers.CMD_SC_MISSION_INFO, [
        info
    ]);

    // send result
    server.send(net_protocol_handlers.CMD_SC_MISSION_GET_REWARD_RESULT, {
        result: 0
    });
});

