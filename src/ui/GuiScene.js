/**
 * Created by yuxiao on 14-9-29.
 */

var ui = ui || {};

ui.GuiSceneBase = cc.Scene.extend(ui.guiExtend).extend({
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
    },

    pushScene: function(oClass) {
        ui.pushScene(oClass);
    },

    popScene: function() {
        ui.popScene();
    },

    replaceScene: function(oClass) {
        ui.replaceScene(oClass)
    }
});
