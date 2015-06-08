/**
 * Created by yuxiao on 15/5/29.
 */


var BattleSystem = SystemBase.extend({
    ctor: function () {
        this._super();
    },

    onInit: function () {
        this._super();
    },

    onFinalize: function () {
        this._super();
    }
});


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
    //var ATK_defV    = atk_role_.roleDataManager.def;
    //var ATK_critMin   = atk_role_.roleDataManager.critMin;
    //var ATK_critMax   = atk_role_.roleDataManager.critMax;
    //var ATK_critPro   = atk_role_.roleDataManager.critProbability;
    //var DEF_atkV    = def_role_.roleDataManager.atk;
    //var DEF_sunderV = def_role_.roleDataManager.sunder;
    var DEF_defV    = def_role_.roleDataManager.def;

    //LOG("ATK ATK   = " + ATK_atkV);
    //LOG("ATK SUNDER= " + ATK_sunderV);
    //LOG("ATK CRIT  = " + ATK_crit);
    //LOG("DEF defV  = " + DEF_defV);

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
        //var powerValue = runningACT.hit.power || 1;
        //damageValue = Math.floor( damageValue * powerValue);
    }

    //暴击
    if(cc.random0To1() > 0.2){
        var critV = Formula.calculateCritFormula(ATK_crit);
        //LOG("CRIT CRIT = " + tmpC);
        damageValue *= critV;
    }

    return Math.floor(damageValue) ;
}

























