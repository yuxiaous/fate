/**
 * Created by yuxiao on 15/3/13.
 */


var DialogPanel = ui.GuiWindowBase.extend({
    _guiFile: "res/ui/DialogPanel.json",

    ctor: function(logs) {
        this._super();

        this.logs = [];
        if(logs != undefined) {
            _.each(logs, function(log) {
                this.logs.push(log);
            }, this);
        }
    },

    onEnter: function() {
        this._super();
        this._node_left = this.seekWidgetByName("node_left");
        this._img_head_left = this.seekWidgetByName("img_head_left");
        this._lbl_name_left = this.seekWidgetByName("lbl_leftname");
        this._lbl_chat_left = this.seekWidgetByName("lbl_leftttalk");
        this._node_right = this.seekWidgetByName("node_right");
        this._img_head_right = this.seekWidgetByName("img_head_right");
        this._lbl_name_right = this.seekWidgetByName("lbl_rightname");
        this._lbl_chat_right = this.seekWidgetByName("lbl_righttalk");

       //cc.registerTargetedDelegate(1, true, this);

        this._dialog_panel = this.seekWidgetByName("dialog_panel");
        if(this._dialog_panel){
            this._dialog_panel.addTouchEventListener(function (touch_,event_) {
                if(event_ == ccui.Widget.TOUCH_ENDED){
                    if(this.playNext() == false) {
                        this._endingCallback();
                    }
                }
            },this)
        }

        this.playNext();
    },

    onExit: function() {
        this._node_left = null;
        this._img_head_left = null;
        this._lbl_name_left = null;
        this._lbl_chat_left = null;
        this._node_right = null;
        this._img_head_right = null;
        this._lbl_name_right = null;
        this._lbl_chat_right = null;

        //cc.unregisterTouchDelegate(this);

        this._super();
    },

    addChatLog: function(text, name, side, image) {
        this.logs.push({
            text: text,
            name: name,
            side: side,
            image: image
        });
    },

    playNext: function() {
        var log = this.logs.shift();
        if(log == undefined) {
            return false;
        }

        if(log.side == DialogPanel.Side.Left) {
            this._node_left.setVisible(true);
            this._node_right.setVisible(false);
            this._img_head_left.loadTexture(log.image);
            this._lbl_name_left.setString(log.name);
            this._lbl_chat_left.setString(log.text);
        }
        else if(log.side == DialogPanel.Side.Right) {
            this._node_right.setVisible(true);
            this._node_left.setVisible(false);
            this._img_head_right.loadTexture(log.image);
            this._lbl_name_right.setString(log.name);
            this._lbl_chat_right.setString(log.text);
        }

        return true;
    },

    onTouchBegan: function(touch ,event) {

        return true;
    },

    onTouchMoved: function(touch, event) {
    },

    onTouchEnded: function(touch, event) {
        //if(this.playNext() == false) {
        //    this._endingCallback();
        //}
    },

    onTouchCancelled: function(touch, event) {
    },

    setEndingCallback: function(cb) {
        this._endingCallback = cb;
    }
});

DialogPanel.Side = {
    Left: 1,
    Right: 2
};

