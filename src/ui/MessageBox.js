/**
 * Created by yuxiao on 15/5/11.
 */


var MessageBoxOk = ui.GuiWindowBase.extend({
    _guiFile: "ui/message_box_ok.json",

    ctor: function(content, ok_str) {
        this._super();
        this._content = content;
        this._ok_str = ok_str;
    },

    onEnter: function() {
        this._super();
        this._lbl_content = this.seekWidgetByName("lbl_content");
        this._btn_ok = this.seekWidgetByName("btn_ok");

        if(this._content) {
            this._lbl_content.setString(this._content);
        }

        if(this._ok_str) {
            this._btn_ok.setTitleText(this._ok_str);
        }
    },

    onExit: function() {
        this._lbl_content = null;
        this._btn_ok = null;
        this._super();
    },

    _on_btn_ok: function() {
        if (this._okCallback) {
            this._okCallback();
            this._okCallback = null;
        }
        this.close();
    },

    setOkCallback: function(selector, target) {
        if(target === undefined)
            this._okCallback = selector;
        else
            this._okCallback = selector.bind(target);
    }
});

MessageBoxOk.show = function(content) {
    var win = new MessageBoxOk(content);
    win.pop();
    return win;
};


var MessageBoxOkCancel = MessageBoxOk.extend({
    _guiFile: "ui/message_box_ok_cancel.json",

    ctor: function(content, ok_str, cancel_str) {
        this._super(content, ok_str);
        this._cancel_str = cancel_str;
    },

    onEnter: function() {
        this._super();
        this._btn_cancel = this.seekWidgetByName("btn_cancel");

        if(this._cancel_str) {
            this._btn_cancel.setTitleText(this._cancel_str);
        }
    },

    onExit: function() {
        this._btn_cancel = null;
        this._super();
    },

    _on_btn_cancel: function() {
        if (this._cancelCallback) {
            this._cancelCallback();
            this._cancelCallback = null;
        }
        this.close();
    },

    setCancelCallback: function(selector, target) {
        if(target === undefined)
            this._cancelCallback = selector;
        else
            this._cancelCallback = selector.bind(target);
    }
});

MessageBoxOkCancel.show = function(content) {
    var win = new MessageBoxOkCancel(content);
    win.pop();
    return win;
};