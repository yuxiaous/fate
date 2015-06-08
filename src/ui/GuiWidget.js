/**
 * Created by yuxiao on 14-10-16.
 */

var ui = ui || {};

ui.GuiWidgetBase = ccui.Layout.extend(ui.guiExtend).extend({
    _guiFile: null,

    ctor: function() {
        this._super();
        this.loadGui(this._guiFile);
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
