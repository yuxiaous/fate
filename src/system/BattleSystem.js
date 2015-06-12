/**
 * Created by yuxiao on 15/5/29.
 */


var BattleSystem = SystemBase.extend({
    ctor: function () {
        this._super();

        this.cur_battle_map = 0;
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_BATTLE_MAP_RESULT = this.battleMapResult.bind(this);
        net_protocol_handlers.ON_CMD_SC_BATTLE_FINISH_RESULT = this.battleFinishResult.bind(this);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_BATTLE_MAP_RESULT = null;
        net_protocol_handlers.ON_CMD_SC_BATTLE_FINISH_RESULT = null;
    },

    battleMap: function(map_id) {
        if(PlayerSystem.instance.action < 2){
            MessageBoxOk.show("体力不足");
            return;
        }
        if(map_id) {
            net_protocol_handlers.SEND_CMD_CS_BATTLE_MAP({
                map_id: map_id
            });
        }
    },
    battleMapResult: function(obj) {
        this.cur_battle_map = obj.map_id;
        notification.emit(notification.event.BATTLE_MAP_RESULT);
    },

    battleFinish: function(isWin) {
        net_protocol_handlers.SEND_CMD_CS_BATTLE_FINISH({
            result: isWin ? 1: 2,
            time: 0
        });
    },
    battleFinishResult: function(obj) {
        //if(obj.result == 0){
        //    notification.emit(notification.event.BATTLE_FINISH_RESULT,obj.result);
        //}
        //else if(obj.result == -1){
        //
        //}
        notification.emit(notification.event.BATTLE_FINISH_RESULT,obj);

        LOG("BATTLE FINISH RESULT");
        LOGOBJ(obj);
    }
});

BattleSystem.BattleType = {
    normalType  : 1,
    defendType  : 2,
    endlessType : 3
};


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
        damageValue = Formula.calculateSkillAttack(ATK_atkV,1.1,ATK_sunderV,DEF_defV);
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



























