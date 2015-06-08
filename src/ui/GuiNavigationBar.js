/**
 * Created by yuxiao on 14-11-19.
 */

var ui = ui || {};

ui.GuiNavigationBar = ui.GuiViewBase.extend({
    _guiFile: null,

    ctor: function() {
        this._super();
        this._binds = [];
    },

    onEnter: function() {
        this._super();
    },

    onExit: function() {
        this.clearAllBinds();
        this._super();
    },

    clearAllBinds: function() {
        _.each(this._binds, function(bind) {
            var binding = bind.binding;
            if(binding) notification.removeBinding(binding);
        });
    },

    bindButton: function(view, button) {
        this._binds.push({
            view: view,
            button: button
        });

        if(button) {
            button.addTouchEventListener(function (target, event) {
                if(event == ccui.Widget.TOUCH_ENDED) {
                    this.to(view);
                }
            }, this);
        }
    },

    bindSignal: function(view, signal) {
        var binding = notification.createBinding(signal, function() {
            this.to(view);
        }, this);

        this._binds.push({
            view: view,
            binding: binding
        });
    },

    to: function(view) {
        var associate = _.findWhere(this._binds, {view: view});
        if(associate) {
            if(this._runningView) {
                this._runningView.removeFromParent();
            }

            this._runningView = new associate.view();
            this.addChild(this._runningView);

            _.each(this._binds, function(asso) {
                var button = asso.button;
                if(button) {
                    var enable = (asso != associate);
                    button.setBright(enable);
                    button.setTouchEnabled(enable);
                }
            }, this);
        }
    }
});
