/**
 * Created by yuxiao on 15/4/9.
 */


var GoForwardPanel = ui.GuiWidgetBase.extend({
    _guiFile: "ui/GoGoGoPanel.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        //this._img_go = oWidget.seekWidgetByName("img_go");
        this._img_go = this.seekWidgetByName("img_go");

        this._img_go.runAction(cc.repeatForever(cc.sequence(
            cc.fadeOut(0.5),
            cc.fadeIn(0.5)
        )));
    },

    onExit: function() {
        this._img_go = null;
        this._super();
    }
});

