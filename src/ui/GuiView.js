/**
 * Created by yuxiao on 14-10-10.
 */

var ui = ui || {};

ui.GuiViewBase = cc.Layer.extend(ui.guiExtend).extend({
    _guiFile: null,

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        this.loadGui(this._guiFile);
    },

    onExit: function() {
        this.unloadGui();
        this._super();
    }

});
