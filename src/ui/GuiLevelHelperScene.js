/**
 * Created by yuxiao on 15/1/14.
 */

var ui = ui || {};

ui.GuiLevelHelperScene = lh.LHScene.extend({
    _guiFile: null,

    ctor: function() {
        this._super(this._guiFile);
    },

    onEnter: function() {
        this._super();
    },

    onExit: function() {
        this._super();
    }
});

