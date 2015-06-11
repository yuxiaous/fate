/**
 * Created by yuxiao on 15/4/16.
 */


var RoleDataManager = cc.Class.extend({
    ctor: function(role) {
        this.role = role;

        this._curHp = 300;
        this._maxHp = 300;
        this._roleLV = 1;

        this.level = 0;
        this.hp = 0;
        this.maxHp = 0;
        this.mp = 0;
        this.maxMp = 0;
        this.atk = 0;
        this.def = 0;
        this.crit = 1;
        this.critPro = 0;
        this.sunder = 0;
    },

    setData: function(data) {
        if(data.level != undefined) {
            this.level = data.level;
        }
        if(data.hp != undefined) {
            this.hp = data.hp;
            this.maxHp = data.hp;
        }
        if(data.mp != undefined) {
            this.mp = data.mp;
            this.maxMp = data.mp;
        }
        if(data.atk != undefined) {
            this.atk = data.atk;
        }
        if(data.def != undefined) {
            this.def = data.def;
        }
        if(data.crit != undefined) {
            this.crit = data.crit;
        }
        if(data.crit_probability != undefined){
            this.critPro = data.crit_probability;
        }
        if(data.sunder != undefined) {
            this.sunder = data.sunder;
        }
    }
});

