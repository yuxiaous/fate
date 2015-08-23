/**
 * Created by yuxiao on 15/5/29.
 */


var BattleSystem = SystemBase.extend({
    ctor: function () {
        this._super();

        this.cur_battle_map = 0;
        this.endlessRound = 1;

        this.needRestart = false;
        this.needRestartBattleType = SceneBase.Type.NormalType;

        this.curBattleType = SceneBase.Type.NormalType;

        this.isFirstTryType = false;

        this.needDropItems = [];
        this.randomDropInfo = {};

        this._curMapDropItems = [];
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_BATTLE_MAP_RESULT = this.battleMapResult.bind(this);
        net_protocol_handlers.ON_CMD_SC_BATTLE_FINISH_RESULT = this.battleFinishResult.bind(this);
        net_protocol_handlers.ON_CMD_SC_USE_BATTLE_ITEM_RESULT = this.batttleUseItemResult.bind(this);
        net_protocol_handlers.ON_CMD_SC_ENDLESS_MAX_ROUND = this.refreshEndlessRound.bind(this);
        net_protocol_handlers.ON_CMD_SC_ENDLESS_BATTLE_END = this.endlessBattleFinishResult.bind(this);

        net_protocol_handlers.ON_CMD_SC_BATTLE_REVIVE = this.reviveFinish.bind(this);
        net_protocol_handlers.ON_CMD_SC_RECOVER_BATTLE = this.recoverBattle.bind(this);

        this._bindings =[
            notification.createBinding(notification.event.BATTLE_TRY_TYPE_END, function (event_,data_) {
                LOG("data_ = " + data_);
                //if(data_){
                //
                //}
                //else{
                //
                //}

                var hadEnterG = jsb.JsonStorage.GetInstance(LoginSystem.settingFile).getBoolForKey(LoginSystem.recordEnterGame);
                if(!hadEnterG){
                    ui.popScene();
                }
                else{
                    if(this.isFirstTryType){
                        ui.pushScene(MainScene);
                    }
                    else{
                        ui.popScene();
                    }
                }
            },this)
        ]
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_BATTLE_MAP_RESULT = null;
        net_protocol_handlers.ON_CMD_SC_BATTLE_FINISH_RESULT = null;

        notification.removeBinding(this._bindings);

        this.needDropItems = null;
        this.randomDropInfo = null;
        this._curMapDropItems = null;
    },

    refreshEndlessRound : function (obj) {
        if(obj && obj.endless_round){
            this.endlessRound = obj.endless_round;
        }
    },

    recoverBattle : function (obj) {
        //notification.emit(notification.event.BATTLE_RECOVER_STATE);
    },

    battleMap: function(map_id) {
        if(PlayerSystem.instance.action < 2){
            MessageBoxOk.show("体力不足");
            return true;
        }

        if(map_id) {
            net_protocol_handlers.SEND_CMD_CS_BATTLE_MAP({
                map_id: map_id
            });
        }
        //return false;
    },
    battleMapResult: function(obj) {
        this.cur_battle_map = obj.map_id;

        this._curMapDropItems.length = 0;
        this.needDropItems = this._curLevelNeedDropData();

        //notification.emit(notification.event.BATTLE_MAP_RESULT);
        ui.pushScene(new LoadingScene());
        
        sdk_manager.sendSdkCommand("TalkingDataGA", "onBegin", "map."+String(obj.map_id));
    },

    getCurDropItemData : function (roleAllCount_,roleIDx_) {

        //function randDropInfoFunc(allDropCount_,allRoleCount_){
        //
        //
        //}
        //
        //if(this.randomDropInfo == null){
        //    var tmpCount = 0;
        //    _.forEach(this.needDropItems, function (dropItem_) {
        //        if(dropItem_){
        //            tmpCount += dropItem_.item_num;
        //        }
        //    },this);
        //    if(tmpCount != 0){
        //        this.randomDropInfo = randDropInfoFunc(tmpCount,roleAllCount_);
        //    }
        //}
        var dropItemInfo_ = {};
        var hadDropItem = false;


        _.forEach(this.needDropItems, function (dropItem_) {
            if(hadDropItem == false && roleIDx_ > roleAllCount_/ 2){
                if( dropItem_ && dropItem_.used == 0){
                    dropItem_.used = 1;
                    hadDropItem = true;
                    dropItemInfo_.item_id = dropItem_.item_id;
                    dropItemInfo_.item_num = dropItem_.item_num;
                }
            }
        },this);

        if(hadDropItem == false){
            _.forEach(this.needDropItems, function (dropItem_) {
                    if(hadDropItem == false && dropItem_ && this.judgeRandomPro(dropItem_.drop_pro)){
                        hadDropItem = true;
                        dropItemInfo_.item_id = dropItem_.item_id;
                        dropItemInfo_.item_num = dropItem_.drop_base;
                    }
            },this);
        }

        this._curMapDropItems.push(dropItemInfo_);

        return dropItemInfo_;
    },

    _curLevelNeedDropData : function () {
        var dropItems = [];
        var tmpData = this._parseLevelDropData(this.cur_battle_map);

        _.forEach(tmpData, function (dropItem) {
            if(dropItem){
                dropItems.push({
                    item_id : dropItem.drop_item_id,
                    item_num : dropItem.drop_base,
                    drop_base : dropItem.drop_pro_base,
                    drop_pro : dropItem.drop_item_pro,
                    used : 0
                });
            }
        },this);

        return dropItems;
    },

    _parseLevelDropData : function (mapId_) {
        var dropItems = [];
        var config = configdb.map[mapId_];
        if(config == undefined){
            return dropItems;
        }

        var drop_id_str_pre = "drop_item_";
        var drop_base_str_pre = "drop_base_";
        var drop_pro_base_str_pre = "drop_pro_base_";
        var drop_item_pro_str_pre = "drop_item_pro_";

        var dropNum = 4;
        for(var idx = 1; idx <= dropNum ; idx++){
            var drop_id_str = drop_id_str_pre + idx;
            if(config[drop_id_str]){
                var drop_base_str = drop_base_str_pre + idx;
                var drop_pro_base_str = drop_pro_base_str_pre + idx;
                var drop_item_pro_str = drop_item_pro_str_pre + idx;

                dropItems.push({
                    drop_item_id  : config[drop_id_str],
                    drop_base     : config[drop_base_str],
                    drop_pro_base : config[drop_pro_base_str],
                    drop_item_pro : config[drop_item_pro_str]
                })
            }
        }

        return dropItems;
    },

    battleFinish: function(isWin) {
        net_protocol_handlers.SEND_CMD_CS_BATTLE_FINISH({
            result: isWin ? 1: 2,
            time: 0
        });

        sdk_manager.sendSdkCommand("TalkingDataGA", "onCompleted", "map."+String(this.cur_battle_map));
    },

    updateEndlessBattleRound : function (round_) {
      net_protocol_handlers.SEND_CMD_CS_ENDLESS_MAX_ROUND({
          endless_round : round_
      })
    },

    endlessBattleLose : function (round_) {
      net_protocol_handlers.SEND_CMD_CS_ENDLESS_BATTLE_END({
          endless_round : round_
      })
    },

    battleFinishResult: function(obj) {
        //if(obj.result == 0){
        //    notification.emit(notification.event.BATTLE_FINISH_RESULT,obj.result);
        //}
        //else if(obj.result == -1){
        //
        //}
        this.battle_reward = obj.reward;
        notification.emit(notification.event.BATTLE_FINISH_RESULT,obj);

        LOG("BATTLE FINISH RESULT");
        //LOGOBJ(obj);
    },

    endlessBattleFinishResult : function (obj) {
        notification.emit(notification.event.BATTLE_ENDLESS_FINISH,obj);
        LOG("end less battle finsih");
    },

    sendReviveBattle : function (obj) {
        net_protocol_handlers.SEND_CMD_CS_BATTLE_REVIVE({
            player_id : 101
        })
    },

    reviveFinish : function (obj) {
      if(obj && obj.result == 0){
         LOG("");
          notification.emit(notification.event.BATTLE_HERO_REVIVE);
      }
      else{

      }
    },

    useBattleItem: function (obj) {
        var uid = 0;
        _.each(BagSystem.instance.items, function(info) {
            if(info.id == obj.itemId) {
                uid = info.uid;
            }
        }, this);

        ItemSystem.instance.useItem(uid,obj.num);
    },

    batttleUseItemResult: function (obj) {
        if(obj.result == 0){
            var target = cc.director.getRunningScene()._hero;
            if(obj.item_type == BattleSystem.UseItemType.UseHp){     //单加满血
                target.roleDataManager.hp = target.roleDataManager.maxHp;
            }
            else if(obj.item_type == BattleSystem.UseItemType.UseMp){    //单加满蓝
                target.roleDataManager.mp = target.roleDataManager.maxMp;
            }
            else if(obj.item_type == BattleSystem.UseItemType.UseHpAndMp){    //加满血和蓝
                target.roleDataManager.hp = target.roleDataManager.maxHp;
                target.roleDataManager.mp = target.roleDataManager.maxMp;
            }
            else if(obj.item_type == BattleSystem.UseItemType.UseRevive){ //复活币
                target.roleDataManager.hp = target.roleDataManager.maxHp;
                target.roleDataManager.mp = target.roleDataManager.maxMp;
            }

            notification.emit(notification.event.BATTLE_USE_ITEM_RESULT,obj.item_type);
        }
    },

    buySuperSkill : function () {
        net_protocol_handlers.SEND_CMD_CS_BUY_SUPER_SKILL_COUNT({
            player_id : 101
        });
    },
    
    useSuperSkill : function () {
        net_protocol_handlers.SEND_CMD_CS_USE_SUPER_SKILL({
            player_id : 101
        })

        PlayerSystem.instance.superSkillCount -= 1;
        notification.emit(notification.event.PLAYER_INFO);
    },

    startTryBattle : function (role_,isFirstTry_) {
        this._try_role = role_;

        if(isFirstTry_ != undefined && isFirstTry_){
            this.isFirstTryType = true;
        }
        else{
            this.isFirstTryType = false;
        }

        BattleSystem.instance.battleMap(configdb.property[108].value);

    },

    getTryBattleHero : function () {
      return this._try_role;
    },

    curIsTryBattle : function () {
        if(this.cur_battle_map == configdb.property[108].value){
            return true;
        }
        return false;
    },

    refreshBattleTryTypeStatus : function () {
        if(this.curIsTryBattle()){
            var hadEnterG = jsb.JsonStorage.GetInstance(LoginSystem.settingFile).getBoolForKey(LoginSystem.recordEnterGame);
            if(!hadEnterG){
                jsb.JsonStorage.GetInstance(LoginSystem.settingFile).setBoolForKey(LoginSystem.recordEnterGame,true);
                jsb.JsonStorage.GetInstance(LoginSystem.settingFile).flush();
            }
        }
    },
    
    randomDropItem : function (roleAllCount_,roleIdx_) {
        var dropItems = [];


        for(var idx = 1 ; idx <= 4; idx++){
            var itemId = 120001;
            dropItems.push(itemId);
        }

        return dropItems;
    },
    
    randomDropItemPos : function (role_,itemCount_) {
        var pos = cc.p(0,0);
        var rolePos = role_.getSpacePosition();

        var mapRect = MapSystem.instance.getGameMapRect();

        var randomLength = 50 + itemCount_ * 20;

        pos.x = _.random(randomLength);
        pos.y = _.random(randomLength/2);

        if(_.random(10) > 5){
            pos.x *= -1;
        }

        if(_.random(10) > 5){
            pos.y *= -1;
        }

        pos = cc.pAdd(pos,rolePos);

        if(pos.x > mapRect.width){
            var tmpValue = pos.x - mapRect.width;
            pos.x =  mapRect.width - tmpValue;
        }

        if(pos.x < 0){
            pos.x *= -1;
        }

        if(pos.y > mapRect.height){
            pos.y = mapRect.height - _.random(10);
        }

        if(pos.y < 0){
            pos.y *= -1;
        }

        return pos;
    },

    //概率 万分比
    judgeRandomPro : function (pro_value_) {
        LOG("pro _ value = " + pro_value_);
        //return true;
        var tmpRandValue = _.random(10000);
        if(pro_value_ >= tmpRandValue){
            return true;
        }
        return false;
    }
});

BattleSystem.BattleType = {
    NormalType  : 1,
    DefendType  : 2,
    EndlessType : 3
};

BattleSystem.UseItemType = {
    UseHp : 1,
    UseMp : 2,
    UseHpAndMp : 3,
    UseRevive : 4
}


BattleSystem.getAttackDamage = function(atk, crit_value_min, crit_value_max, crit_probability) {
    var crit = 1;
    if(cc.random0To1() <= crit_probability) {
        crit = crit_value_min + (crit_value_max - crit_value_min) * cc.random0To1()
    }

    return atk * crit;
};

BattleSystem.getAtkActualValue = function (atk_role_,def_role_) {
    if(atk_role_ == undefined || def_role_ == undefined){
        return 1;
    }
    var ATK_atkV    = atk_role_.roleDataManager.atk;
    var ATK_sunderV = atk_role_.roleDataManager.sunder;
    var ATK_crit    = atk_role_.roleDataManager.crit;
    var ATK_critPro = atk_role_.roleDataManager.critPro;
    var DEF_defV    = def_role_.roleDataManager.def;
    var  damageValue = Formula.calculateNormalAttack(ATK_atkV,ATK_sunderV,DEF_defV);

    //技能加成
    var runningACT = atk_role_.roleActionManager.runningAction;
    if(runningACT &&(
        runningACT.type == RoleAction.Type.SKILL1 ||
        runningACT.type == RoleAction.Type.SKILL2 ||
        runningACT.type == RoleAction.Type.SKILL3 ||
        runningACT.type == RoleAction.Type.SKILL4 ||
        runningACT.type == RoleAction.Type.SKILL5
        )){

        var skillUPValue = SkillSystem.instance.getSkillUPLevel(runningACT.type);
        damageValue = Formula.calculateSkillAttack(ATK_atkV,skillUPValue,ATK_sunderV,DEF_defV);
    }

    //暴击
    var isCrit = false;
    if(cc.random0To1() <= ATK_critPro){
        var critV = Formula.calculateCritFormula(ATK_crit);
        damageValue *= critV;
        isCrit = true;

    }

    //防御大于攻击数值
    if(damageValue <= 0){
        damageValue = 0;
    }

    var damageData = {
        damageValue : Math.floor(damageValue),
        isCrit : isCrit
    }

    return  damageData;
}



























