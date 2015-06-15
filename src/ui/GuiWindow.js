/**
 * Created by yuxiao on 14-10-8.
 */

var ui = ui || {};

ui.GuiWindowBase = ui.GuiViewBase.extend({
    _claimed: true,
    _guiFile: null,

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();

        // set swallowing touches
        if(this._claimed) {
            cc.eventManager.addListener({
                event : cc.EventListener.TOUCH_ONE_BY_ONE,
                swallowTouches: true,
                onTouchBegan : function() { return true },
                onTouchMoved : function() {},
                onTouchEnded : function() {}
            }, this)
        }
    },

    onExit: function() {
        if(this._claimed) {
            cc.eventManager.removeListeners(this);
        }
        this._super();
    },

    pop: function() {
        return ui.popWindow(this);
    },

    close: function() {
        this.onClose();
        ui.closeWindow(this);
    },

    onClose: function() {
        if (this._closeCallback) {
            this._closeCallback(this);
            this._closeCallback = null;
        }
    },

    setCloseCallback: function (selector, target) {
        if(target === undefined)
            this._closeCallback = selector;
        else
            this._closeCallback = selector.bind(target);
    }
});