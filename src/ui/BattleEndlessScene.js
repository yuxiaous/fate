var BattleEndlessScene = SceneEndlessBase.extend({
    status: {
        hero: Saber,
        BSection : []
    },

    ctor: function() {
        this.tmpStageInfo = configdb.stage[10];
        this._super(this.tmpStageInfo.scene_file);

        this.initBattleData();
    },

    onEnter: function() {
        this._super();
        MusicManager.getInstance().playBackgroundMusic(this.tmpStageInfo.bgm_file);
        this.play(this.status);
    },

    initBattleData : function () {
        //this.status.stage = BattleEndlessScene.initStageInfo();
        this.status.stage = this.tmpStageInfo;
        this.status.BSection = BattleEndlessScene.initBattleSection();
        //this.status.chatData = BattleNorScene.initChatInfo(map_id_);
    },

    onExit: function() {
        this._super();
        MusicManager.getInstance().stopBackgroundMusic();
    }
});

//BattleEndlessScene.initChatInfo = function (map_id_) {
//    var chatData = {}
//    var mapConfig = configdb.map[map_id_];
//    chatData.beforeFight =[];
//    chatData.beforeBossFight =[];
//    chatData.afterFight =[];
//    var beforeF =[];
//    var beforeBF =[];
//    var afterF =[];
//    var preTalk = "talk_id_";
//    for(var i = 1; i<=12; i++){
//        if(mapConfig[preTalk+i]){
//            if(i <= 4){
//                beforeF.push(mapConfig[preTalk+i]);
//            }
//            else if(i > 4 && i <= 8){
//                beforeBF.push(mapConfig[preTalk+i]);
//            }
//            else if(i > 8){
//                afterF.push(mapConfig[preTalk+i]);
//            }
//        }
//    }
//
//    _.each(beforeF, function (idx) {
//        var talkConfig = configdb.talks[idx];
//        if(talkConfig) {
//            chatData.beforeFight.push({
//                name: talkConfig.name,
//                text: talkConfig.content,
//                side: talkConfig.pos,
//                image: talkConfig.head
//            });
//        }
//    },this);
//
//    _.each(beforeBF, function (idx) {
//        var talkConfig = configdb.talks[idx];
//        if(talkConfig) {
//            chatData.beforeBossFight.push({
//                name: talkConfig.name,
//                text: talkConfig.content,
//                side: talkConfig.pos,
//                image: talkConfig.head
//            });
//        }
//    },this);
//
//    _.each(afterF, function (idx) {
//        var talkConfig = configdb.talks[idx];
//        if(talkConfig){
//            chatData.afterFight.push({
//                name : talkConfig.name,
//                text : talkConfig.content,
//                side : talkConfig.pos,
//                image: talkConfig.head
//            });
//        }
//    },this);
//
//    return chatData;
//};

BattleEndlessScene.initBattleSection = function () {
    var BSection = [];
    function randomRoleId(monsterConter_){
        var conCount = monsterConter_.length;
        if(conCount > 0){
            var ranIdx = _.random(0,conCount-1);
            return monsterConter_[ranIdx];
        }
        else{
            LOG("wrong endlessround monster config");
        }
    }
    var endlessData = configdb.endlessround;
    _.each(configdb.endlessround, function (roundData_) {
        var curRoundNum = _.random(roundData_.num_min,roundData_.num_max);

        var monsterContainer = [];
        _.each(["monster_1",
                "monster_2",
                "monster_3",
                "monster_4",
                "monster_5",
                "monster_6",
                "monster_7",
                "monster_8",
                "monster_9"],function (str_) {
            if(roundData_[str_]){
                monsterContainer.push(roundData_[str_]);
            }
        })

        var tmpMonster = [];
        for(var i = 0; i < curRoundNum; i++){
            var aiConfi = configdb.ai[roundData_.aiType];
            var atkV             = _.random(roundData_.atk_min,roundData_.atk_max);
            var hpV              = _.random(roundData_.hp_min,roundData_.hp_max);
            var crit_probability = roundData_.crit_probability;
            var crit             = roundData_.crit;

            tmpMonster.push({
                roleId      : randomRoleId(monsterContainer),
                atkValue    : atkV,
                hpValue     : hpV,
                crit_pro    : crit_probability,
                crit        : crit,
                ai : {
                    atkPer    : aiConfi.atk_probably,
                    restPer   : aiConfi.rest_probably,
                    rangeActW : aiConfi.range_act_width,
                    rangeActH : aiConfi.range_act_height,
                    followAtk : aiConfi.follow_atk
                }
            });
        }

        BSection.push({
            area : cc.rect(0,0,3000,640),
            street: cc.rect(0,0,3000,220),
            heroPos : cc.p(300,110),
            monsters :tmpMonster
        });
    },this);

    return BSection;
};

BattleEndlessScene.initStageInfo = function () {
    //var mapConfig = configdb.map[map_id_];
    //var stageConfig = configdb.stage[mapConfig.stage_id];
    //
    //if(stageConfig){
    //    return stageConfig;
    //}
    //else{
    //    LOG("NOT FIND STAGE INFO");
    //    return null;
    //}
};

