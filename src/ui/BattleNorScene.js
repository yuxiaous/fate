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
    var prePZ_id ="peizhi_id_";
    var preScenePos = "scene_pos_";
    var preSceneLen = "scene_len_";
    for(var i = 1; i<=4; i++){
        var peizhi_id = mapConfig[prePZ_id+i];
        ////test role
        //if(1 && i == 1){
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
            var preRoleDrop = "drop_id_";
            for(var idx = 1; idx <= 6; idx++){
                if(peizhiConf[preRoleId + idx]){
                    var aiConfi = configdb.ai[peizhiConf[preRoleAi+idx]];
                    LOG("-----drop id = " + peizhiConf[preRoleDrop+idx]);
                    tmpMonster.push({
                        roleId : peizhiConf[preRoleId + idx],
                        posX   : peizhiConf[preRolePosx+idx],
                        posY   : peizhiConf[preRolePosy+idx],
                        dir    : peizhiConf[preRoleDir+idx],
                        dropId : peizhiConf[preRoleDrop+idx],
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

BattleNorScene.initStageInfo = function (map_id_) {
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


