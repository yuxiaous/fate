/**
 * Created by yuxiao on 15/4/23.
 */

var ui = ui || {};

ui.GuiController = cc.Class.extend(ui.guiExtend).extend({
    ctor: function() {
        this.__gui__ = null;
    },

    onEnter: function() {

    },

    onExit: function() {

    },

    setWidget: function(oWidget) {
        if(this.__gui__ == oWidget) {
            return;
        }

        if(this.__gui__ && oWidget == null) {
            this.__gui__.setOnEnterCallback(null);
            this.__gui__.setOnExitCallback(null);

            if(this.__gui__.isRunning()) {
                this.onExit();
            }
        }

        this.__gui__ = oWidget;

        if(oWidget) {
            ui.preprocessGui(oWidget, this);

            var self = this;
            oWidget.setOnEnterCallback(function() { self.onEnter(); });
            oWidget.setOnExitCallback(function() { self.onExit(); });

            if(oWidget.isRunning()) {
                this.onEnter();
            }
        }
    },

    getWidget: function() {
        return this.__gui__;
    },

    setVisible: function(val) {
        if(this.__gui__) {
            this.__gui__.setVisible(val);
        }
    }
});

ui.GuiController.prototype.loadGui = null;
ui.GuiController.prototype.unloadGui = null;

//var TestController = ui.GuiController.extend({
//    ctor: function(oWidget) {
//        this._super(oWidget);
//    },
//
//    onEnter: function() {
//        this._super();
//        LOG("TestController.onEnter");
//
//        this._widget.runAction(cc.moveBy(5, cc.p(100, 100)))
//    },
//
//    onExit: function() {
//        this._super();
//        LOG("TestController.onExit")
//    }
//});

