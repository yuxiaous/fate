var BattleDefScene = SceneDefBase.extend({
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
        LOG("start -- = " + util.getCurrentDate()) ;
        this.initBattleData(this.map_id);
        LOG("end -- = " + util.getCurrentDate()) ;
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

