/**
 * Created by yuxiao on 15/3/17.
 */


var ComboPanel = ui.GuiViewBase.extend({
    _guiFile: "res/ui/ComboHits.json",

    _comboTime: 3,

    ctor: function() {
        this._super();
        this._combo = 0;
        this._comboCount = 0;
    },

    onEnter: function() {
        this._super();
        this._lbl_combo = this.seekWidgetByName("lbl_combo");
        this._lbl_combo_scale = this._lbl_combo.getScale();


        this._bindings = [
            notification.createBinding(notification.event.ROLE_HIT, this.combo, this)
        ];

        cc.director.getScheduler().scheduleUpdateForTarget(this);

        this.setVisible(false);
    },

    onExit: function() {
        cc.director.getScheduler().unscheduleUpdateForTarget(this);
        notification.removeBinding(this._bindings);
        this._lbl_combo = null;
        this._super();
    },

    update: function(dt) {
        this._comboCount += dt;

        if(this.isVisible() && this._comboCount > this._comboTime) {
            this.setVisible(false);
            this._combo = 0;
        }
    },

    combo: function() {
        this._lbl_combo.setString(++this._combo);

        this._comboCount = 0;
        this.setVisible(true);
        this._lbl_combo.runAction(cc.sequence(
            cc.scaleTo(0.1, this._lbl_combo_scale * 2),
            cc.scaleTo(0.1, this._lbl_combo_scale)
        ));

        MissionSystem.instance.countCombo(this._combo);
    }
});
