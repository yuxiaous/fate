/**
 * Created by yuxiao on 15/5/23.
 */


var Formula = {
    calculateBattleScore: function(hp, mp, atk, def, crit, sunder) {
        if(hp == undefined) hp = 0;
        if(mp == undefined) mp = 0;
        if(atk == undefined) atk = 0;
        if(def == undefined) def = 0;
        if(crit == undefined) crit = 0;
        if(sunder == undefined) sunder = 0;

        var config = configdb.formula[101];
        if(config) {
            return config.a0
            + config.a1 * hp
            + config.a2 * mp
            + config.a3 * atk
            + config.a4 * def
            + config.a5 * crit
            + config.a6 * sunder;
        }
        return 0;
    },

    //普通攻击
    calculateNormalAttack : function (atk,sunder,def) {
        if(atk == undefined ) atk = 0;
        if(sunder == undefined ) sunder = 0;
        if(def == undefined ) def = 0;

        var config = configdb.formula[104];
        if(config){
            return ( config.a0
            + config.a1 * atk
            + config.a2 * sunder
            - config.a3 * def ) * (_.random(1- config.a4,1 + config.a4))
        }
        return 0;
    },

    //技能攻击
    calculateSkillAttack : function (atk,skillAdd,sunder,def) {
        if(atk == undefined) atk = 0;
        if(skillAdd == undefined) skillAdd = 0;
        if(sunder == undefined) sunder = 0;
        if(def == undefined) def = 0;

        var config = configdb.formula[105];
        if(config){
            return (config.a0
            + config.a1 * atk
            + config.a2 * skillAdd
            + config.a3 * sunder
            - config.a4 * def) * (_.random(1-config.a5, 1+config.a5))
        }
        return 0;
    },

    //伤害公式
    calculateAtkFormula : function (atk , def) {
        if(atk == undefined) atk = 0;
        if(def == undefined) def = 0;

        var config = configdb.formula[102];
        if(config){
            return config.a0
            + config.a1 * atk
            - config.a2 *def
        }
        return 0;
     },

    //爆伤公式
    calculateCritFormula : function (crit) {
        if(crit == undefined) crit = 0;

        var config = configdb.formula[103];
        if(config){
            return config.a0
            + crit/config.a1
        }
        return 0;
    }
};

