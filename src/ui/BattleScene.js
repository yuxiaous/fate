/**
 * Created by yuxiao on 15/4/27.
 */


var BattleScene = SceneBase.extend({
    status: {
        hero: Saber,
        BSection : []
    },

    ctor: function(map_id) {
        this.map_id = map_id;
        var config = configdb.map[this.map_id];
        this.stage_config = configdb.stage[config.stage_id];
        if(!this.stage_config) {
            return;
        }

        this._super(this.stage_config.scene_file);
        MusicManager.getInstance().playBackgroundMusic(this.stage_config.bgm_file);
        this.initBattleData(this.map_id);
    },

    onEnter: function() {
        this._super();

        this.play(this.status);
    },

    initBattleData : function (map_id_) {
        this.status.stage = BattleScene.initStageInfo(map_id_);
        this.status.BSection = BattleScene.initBattleSection(map_id_);
        this.status.chatData = BattleScene.initChatInfo(map_id_);
        //var mapConfig = configdb.map[map_id_];
        //
        //this.status.stage ={}
        //var stageConfig = configdb.stage[mapConfig.stage_id];
        //this.status.stage = stageConfig;
        //this.status.BSection =[];
        //var prePZ_id ="peizhi_id_";
        //var preScenePos = "scene_pos_";
        //var preSceneLen = "scene_len_";
        //for(var i = 1; i<=4; i++){
        //    var peizhi_id = mapConfig[prePZ_id+i];
        //    ////test role
        //    //if(0 && i == 1){
        //    //    peizhi_id = 1001;
        //    //}
        //    if(peizhi_id){
        //        var peizhiConf = configdb.peizhi[peizhi_id];
        //        var tmpMonster =[];
        //        var preRoleId = "role_id_";
        //        var preRolePosx = "posx_";
        //        var preRolePosy = "posy_";
        //        var preRoleDir = "dir_";
        //        var preRoleAi = "aiType_";
        //        for(var idx = 1; idx <= 6; idx++){
        //            if(peizhiConf[preRoleId + idx]){
        //                var aiConfi = configdb.ai[peizhiConf[preRoleAi+idx]];
        //                tmpMonster.push({
        //                    roleId : peizhiConf[preRoleId + idx],
        //                    posX   : peizhiConf[preRolePosx+idx],
        //                    posY   : peizhiConf[preRolePosy+idx],
        //                    dir    : peizhiConf[preRoleDir+idx],
        //                    ai : {
        //                        atkPer    : aiConfi.atk_probably,
        //                        restPer   : aiConfi.rest_probably,
        //                        rangeActW : aiConfi.range_act_width,
        //                        rangeActH : aiConfi.range_act_height,
        //                        followAtk : aiConfi.follow_atk,
        //                        isRemote  : aiConfi.isRemote
        //                    }
        //                })
        //            }
        //        }
        //
        //        this.status.BSection.push({
        //            area : cc.rect(mapConfig[preScenePos+i],0,mapConfig[preSceneLen+i],640),
        //            street: cc.rect(mapConfig[preScenePos+i],0,mapConfig[preSceneLen+i],220),
        //            heroPos : cc.p(300,110),
        //            warningLine : 400,
        //            monsters :tmpMonster
        //        });
        //    }
        //}
        // chatinfo
        //this.status.chatData = {};
        //this.status.chatData.beforeFight =[];
        //this.status.chatData.beforeBossFight =[];
        //this.status.chatData.afterFight =[];
        //var beforeF =[];
        //var beforeBF =[];
        //var afterF =[];
        //var preTalk = "talk_id_";
        //for(var i = 1; i<=12; i++){
        //    if(mapConfig[preTalk+i]){
        //        if(i <= 4){
        //            beforeF.push(mapConfig[preTalk+i]);
        //        }
        //        else if(i > 4 && i <= 8){
        //            beforeBF.push(mapConfig[preTalk+i]);
        //        }
        //        else if(i > 8){
        //            afterF.push(mapConfig[preTalk+i]);
        //        }
        //    }
        //}
        //
        //_.each(beforeF, function (idx) {
        //    var talkConfig = configdb.talks[idx];
        //    this.status.chatData.beforeFight.push({
        //        name : talkConfig.name,
        //        text : talkConfig.content,
        //        side : talkConfig.pos,
        //        image: talkConfig.head
        //    });
        //},this);
        //
        //_.each(beforeBF, function (idx) {
        //    var talkConfig = configdb.talks[idx];
        //    this.status.chatData.beforeBossFight.push({
        //        name : talkConfig.name,
        //        text : talkConfig.content,
        //        side : talkConfig.pos,
        //        image: talkConfig.head
        //    });
        //},this);
        //
        //_.each(afterF, function (idx) {
        //    var talkConfig = configdb.talks[idx];
        //    this.status.chatData.afterFight.push({
        //        name : talkConfig.name,
        //        text : talkConfig.content,
        //        side : talkConfig.pos,
        //        image: talkConfig.head
        //    });
        //},this);
    },

    onExit: function() {
        this._super();
    }
});

BattleScene.initChatInfo = function (map_id_) {
    var chatData = {}
    var mapConfig = configdb.map[map_id_];
    chatData.beforeFight =[];
    chatData.beforeBossFight =[];
    chatData.afterFight =[];
    var beforeF =[];
    var beforeBF =[];
    var afterF =[];
    var preTalk = "talk_id_";
    for(var i = 1; i<=12; i++){
        if(mapConfig[preTalk+i]){
            if(i <= 4){
                beforeF.push(mapConfig[preTalk+i]);
            }
            else if(i > 4 && i <= 8){
                beforeBF.push(mapConfig[preTalk+i]);
            }
            else if(i > 8){
                afterF.push(mapConfig[preTalk+i]);
            }
        }
    }

    _.each(beforeF, function (idx) {
        var talkConfig = configdb.talks[idx];
        chatData.beforeFight.push({
            name : talkConfig.name,
            text : talkConfig.content,
            side : talkConfig.pos,
            image: talkConfig.head
        });
    },this);

    _.each(beforeBF, function (idx) {
        var talkConfig = configdb.talks[idx];
        chatData.beforeBossFight.push({
            name : talkConfig.name,
            text : talkConfig.content,
            side : talkConfig.pos,
            image: talkConfig.head
        });
    },this);

    _.each(afterF, function (idx) {
        var talkConfig = configdb.talks[idx];
        chatData.afterFight.push({
            name : talkConfig.name,
            text : talkConfig.content,
            side : talkConfig.pos,
            image: talkConfig.head
        });
    },this);

    return chatData;
};

BattleScene.initBattleSection = function (map_id_) {
    var BSection = [];
    var mapConfig = configdb.map[map_id_];
    var prePZ_id ="peizhi_id_";
    var preScenePos = "scene_pos_";
    var preSceneLen = "scene_len_";
    for(var i = 1; i<=4; i++){
        var peizhi_id = mapConfig[prePZ_id+i];
        ////test role
        //if(0 && i == 1){
        //    peizhi_id = 1001;
        //}
        if(peizhi_id){
            var peizhiConf = configdb.peizhi[peizhi_id];
            var tmpMonster =[];
            var preRoleId = "role_id_";
            var preRolePosx = "posx_";
            var preRolePosy = "posy_";
            var preRoleDir = "dir_";
            var preRoleAi = "aiType_";
            for(var idx = 1; idx <= 6; idx++){
                if(peizhiConf[preRoleId + idx]){
                    var aiConfi = configdb.ai[peizhiConf[preRoleAi+idx]];
                    tmpMonster.push({
                        roleId : peizhiConf[preRoleId + idx],
                        posX   : peizhiConf[preRolePosx+idx],
                        posY   : peizhiConf[preRolePosy+idx],
                        dir    : peizhiConf[preRoleDir+idx],
                        ai : {
                            atkPer    : aiConfi.atk_probably,
                            restPer   : aiConfi.rest_probably,
                            rangeActW : aiConfi.range_act_width,
                            rangeActH : aiConfi.range_act_height,
                            followAtk : aiConfi.follow_atk,
                            isRemote  : aiConfi.isRemote
                        }
                    })
                }
            }

            BSection.push({
                area : cc.rect(mapConfig[preScenePos+i],0,mapConfig[preSceneLen+i],640),
                street: cc.rect(mapConfig[preScenePos+i],0,mapConfig[preSceneLen+i],220),
                heroPos : cc.p(300,110),
                warningLine : 400,
                monsters :tmpMonster
            });
        }
    }

    return BSection;
};

BattleScene.initStageInfo = function (map_id_) {
    var mapConfig = configdb.map[map_id_];
    var stageConfig = configdb.stage[mapConfig.stage_id];

    if(stageConfig){
        return stageConfig;
    }
    else{
        LOG("NOT FIND STAGE INFO");
        return null;
    }
};


