/**
 * Created by yuxiao on 15/4/20.
 */


var PlayerSystem = SystemBase.extend({
    ctor: function() {
        this._super();
        this.playerId = 0;
        this.level = 0;
        this.exp = 0;
        this.diamond = 0;
        this.gold = 0;
        this.action = 0;

        this.superSkillCount = 0;
    },

    onInit: function() {
        this._super();
        net_protocol_handlers.ON_CMD_CS_PLAYER_INFO = this.onPlayerInfo.bind(this);
    },

    onFinalize: function() {
        this._super();
        net_protocol_handlers.ON_CMD_CS_PLAYER_INFO = null;
    },

    onPlayerInfo: function(obj) {
        var player = obj.player;
        if(player.player_id != undefined) this.playerId = player.player_id;
        if(player.level != undefined) {
            var last_level = this.level;
            this.level = player.level;

            if(this.level > last_level && last_level != 0) {
                MusicManager.getInstance().playEffectMusic("sounds/levelup.mp3");
                notification.emit(notification.event.PLAYER_LEVEL_UP);

                sdk_manager.sendSdkCommand("TalkingDataGA", "setLevel", String(this.level));
            }
        }
        if(player.exp != undefined) this.exp = player.exp;
        if(player.gold != undefined) this.gold = player.gold;
        if(player.diamond != undefined) this.diamond = player.diamond;
        if(player.action != undefined) this.action = player.action;
        if(player.superSkillCount != undefined) this.superSkillCount = player.superSkillCount;

        notification.emit(notification.event.PLAYER_INFO);
    },

    getPlayerBattleScore: function(skin_id) {
        var ret = {hp: 0, mp: 0, atk: 0, def: 0, crit: 0, sunder: 0, score: 0};

        if(skin_id == undefined) {
            skin_id = SkinSystem.instance.use_skin;
        }
        var config = configdb.skin[skin_id];
        if(config == undefined) {
            return ret;
        }

        config = configdb.role[config.role_id];
        if(config == undefined) {
            return ret;
        }
        if(config) {
            ret.hp += config.ext_hp || 0;
            ret.mp += config.ext_mp || 0;
            ret.atk += config.ext_atk || 0;
            ret.def += config.ext_def || 0;
            ret.crit += config.ext_crit || 0;
            ret.sunder += config.ext_sunder || 0;
            ret.critPro += config.crit_pro || 0;
        }

        config = configdb.levelup[this.level];
        if(config) {
            ret.hp += config.hp || 0;
            ret.mp += config.mp || 0;
            ret.atk += config.atk || 0;
            ret.def += config.def || 0;
            ret.crit += config.crit || 0;
            ret.sunder += config.sunder || 0;
            ret.critPro += config.crit_pro || 0;
            ret.score = Formula.calculateBattleScore(ret.hp, ret.mp, ret.atk, ret.def, ret.crit, ret.sunder);
        }

        _.each([
            EquipSystem.instance.getAllEquipBattleScore(),
            EquipSystem.instance.getAllSlotBattleScore()
        ], function(score) {
            ret.hp += score.hp;
            ret.mp += score.mp;
            ret.atk += score.atk;
            ret.def += score.def;
            ret.crit += score.crit;
            ret.sunder += score.sunder;
            ret.score += score.score;
        });

        ret.score = Math.floor(ret.score);
        return ret;
    },

    getPlayerExperience: function() {
        var ret = {
            exp: this.exp,
            need: 0
        };

        var config = configdb.levelup[this.level];
        if(config) {
            ret.need = config.exp;
        }

        config = configdb.levelup[this.level - 1];
        if(config) {
            ret.exp -= config.exp;
            ret.need -= config.exp;
        }

        return ret;
    },

    showPlayerScoreChange: function() {
        var last = this.lastScore;
        var now = this.getPlayerBattleScore();
        if(last) {
            var change = now.score - last.score;
            if(change != 0) {
                CombatForcesEffect.createForcesEffect(change, cc.director.getRunningScene());
            }
        }
        this.lastScore = now;
    }
});

PlayerSystem.start = function() {
    PlayerSystem.instance = new PlayerSystem();
    if(PlayerSystem.instance) {
        PlayerSystem.instance.onInit();
    }
};

PlayerSystem.end = function() {
    if(PlayerSystem.instance) {
        PlayerSystem.instance.onFinalize();
        PlayerSystem.instance = null;
    }
};

