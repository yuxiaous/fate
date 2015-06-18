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
        this.initBattleData(this.map_id);
    },

    onEnter: function() {
        this._super();
        MusicManager.getInstance().playBackgroundMusic(this.stage_config.bgm_file);
        this.play(this.status);
    },

    initBattleData : function (map_id_) {
        this.status.stage = BattleScene.initStageInfo(map_id_);
        this.status.BSection = BattleScene.initBattleSection(map_id_);
        this.status.chatData = BattleScene.initChatInfo(map_id_);
    },

    onExit: function() {
        this._super();
        MusicManager.getInstance().stopBackgroundMusic();
    }
});

