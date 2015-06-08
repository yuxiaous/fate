/**
 * Created by yuxiao on 14/12/30.
 */


var BossWolf = RoleBase.extend({
    _armatureName: "boss_wolf",
    _effectName: "boss_wolf_effect",
    _comboCount: 2,

    ctor: function() {
        this._super();
    },

    configureArmature: function(armature, effect) {
        this._super(armature, effect);
        this._armature = armature;
        this._effect = effect;
    },

    onEnter: function() {
        this._super();
    },

    onExit: function() {
        this._super();
    },

    stand: function() {
        this._super();
        if(this._armature) this._armature.animation.gotoAndPlay("daiji");
        if(this._effect) this._effect.animation.gotoAndPlay("daiji");
    },

    walk: function() {
        this._super();
        if(this._armature) this._armature.animation.gotoAndPlay("pao");
    },

    attack: function(combo) {
        this._super(combo);
        if(this._armature) this._armature.animation.gotoAndPlay("kan" + (combo+1));
        if(this._effect) this._effect.animation.gotoAndPlay("kan" + (combo+1));
    }
});
