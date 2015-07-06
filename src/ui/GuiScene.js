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

        //cc.eventManager.addListener({
        //    event: cc.EventListener.KEYBOARD,
        //    onKeyReleased: function(code, event){
        //        switch (code) {
        //            case cc.KEY.back:
        //                if(this._on_keyboard_back) {
        //                    this._on_keyboard_back();
        //                }
        //                break;
        //            case cc.KEY.menu:
        //                if(this._on_keyboard_menu) {
        //                    this._on_keyboard_menu();
        //                }
        //                break;
        //        }
        //    }.bind(this)
        //}, this);
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
