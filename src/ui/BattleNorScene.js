/**
 * Created by yuxiao on 15/4/27.
 */
var BattleNorScene = SceneNormalBase.extend({
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

        this.initBattleData(this.map_id);
    },

    onEnter: function() {
        this._super();
        MusicManager.getInstance().playBackgroundMusic(this.stage_config.bgm_file);
        this.play(this.status);
    },

    initBattleData : function (map_id_) {
        var skin = SkinSystem.instance.use_skin;
        if(skin == 101){
            this.status.hero = Saber;
        }
        else if(skin == 102){
            this.status.hero = Nero;
        }

        if(BattleSystem.instance.curIsTryBattle()){
            this.status.hero = BattleSystem.instance.getTryBattleHero();
        }

        this.status.stage = BattleNorScene.initStageInfo(map_id_);
        this.status.BSection = BattleNorScene.initBattleSection(map_id_);
        this.status.chatData = BattleNorScene.initChatInfo(map_id_);
    },

    onExit: function() {
        this._super();
        MusicManager.getInstance().stopBackgroundMusic();
    }
});

BattleNorScene.initChatInfo = function (map_id_) {
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
        if(talkConfig) {
            chatData.beforeFight.push({
                name: talkConfig.name,
                text: talkConfig.content,
                side: talkConfig.pos,
                image: talkConfig.head
            });
        }
    },this);

    _.each(beforeBF, function (idx) {
        var talkConfig = configdb.talks[idx];
        if(talkConfig) {
            chatData.beforeBossFight.push({
                name: talkConfig.name,
                text: talkConfig.content,
                side: talkConfig.pos,
                image: talkConfig.head
            });
        }
    },this);

    _.each(afterF, function (idx) {
        var talkConfig = configdb.talks[idx];
        if(talkConfig){
            chatData.afterFight.push({
                name : talkConfig.name,
                text : talkConfig.content,
                side : talkConfig.pos,
                image: talkConfig.head
            });
        }
    },this);

    return chatData;
};

BattleNorScene.initBattleSection = function (map_id_) {
    var BSection = [];
    var mapConfig = configdb.map[map_id_];
    var preScenePos = "scene_pos_";
    var preSceneLen = "scene_len_";

    for(var i = 1; i <= 3; ++i){
        var sessions =[];

        for(var j = 1; j <= 4; ++j) {
            var peizhi_id = mapConfig["peizhi_id_" + i + j];
            if(peizhi_id == undefined) {
                continue;
            }

            var peizhiConf = configdb.peizhi[peizhi_id];
            if(peizhiConf == undefined) {
                continue
            }

            var waves =[];
            var preRoleId = "role_id_";
            var preRolePosx = "posx_";
            var preRolePosy = "posy_";
            var preRoleDir = "dir_";
            var preRoleAi = "aiType_";
            var preRoleDrop = "drop_id_";

            for(var k = 1; k <= 6; ++k){
                if(peizhiConf[preRoleId + k]){
                    var aiConfi = configdb.ai[peizhiConf[preRoleAi+k]];
                    //LOG("-----drop id = " + peizhiConf[preRoleDrop+k]);
                    waves.push({
                        roleId : peizhiConf[preRoleId + k],
                        posX   : peizhiConf[preRolePosx+k],
                        posY   : peizhiConf[preRolePosy+k],
                        dir    : peizhiConf[preRoleDir+k],
                        dropId : peizhiConf[preRoleDrop+k],
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

            sessions.push(waves);
        }

        if(sessions.length > 0) {
            BSection.push({
                area : cc.rect(mapConfig[preScenePos+i],0,mapConfig[preSceneLen+i],640),
                street: cc.rect(mapConfig[preScenePos+i],0,mapConfig[preSceneLen+i],220),
                heroPos : cc.p(300,110),
                warningLine : 400,
                monsters :sessions
            });
        }
    }


    // sessions 场次
    // waves 波次
    // 每关3场次，没场次4波次，每波次6怪
    return BSection;
};

BattleNorScene.initStageInfo = function (map_id_) {
    var mapConfig = configdb.map[map_id_];
    var stageConfig = configdb.stage[mapConfig.stage_id];

    if(stageConfig){
        return stageConfig;
    }
    else{
        return null;
    }
};


