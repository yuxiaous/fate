/**
 * Created by yuxiao on 15/4/23.
 */


var MapStage = ui.GuiController.extend({
    ctor: function(map_id) {
        this._super();
        this.mapId = map_id;
    },

    onEnter: function() {
        this._super();
        this._img_bg = this.seekWidgetByName("img_bg");
        this._lbl_name = this.seekWidgetByName("lbl_name");
        this._lbl_level = this.seekWidgetByName("lbl_level");
        this._lbl_score = this.seekWidgetByName("lbl_score");

        var config = configdb.map[this.mapId];
        if(config == undefined) {
            return;
        }

        // background
        //this._img_bg.loadTexture(config.icon);
        this.setOpened(true);

        // name
        this._lbl_name.setString(config.name);

        // level
        this._lbl_level.setString(this._lbl_level._str_original.format(config.req_lv));

        // score
        this._lbl_score.setString(this._lbl_score._str_original.format(config.score));
    },

    onExit: function() {
        this._img_bg = null;
        this._lbl_name = null;
        this._lbl_level = null;
        this._lbl_score = null;
        this._super();
    },

    setVisible: function(visible) {
        var widget = this.getWidget();
        if(widget) {
            widget.setVisible(visible);
        }
    },

    _on_btn_enter: function() {
        var win = new MapStageInfo(this.mapId, this.isOpen);
        win.pop();
    },

    setOpened: function(val) {
        this.isOpen = val;

        var config = configdb.map[this.mapId];
        if(config == undefined) {
            return;
        }

        this._img_bg.loadTexture(val ? config.icon : config.icon_gray);
    }
});

