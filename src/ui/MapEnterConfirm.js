/**
 * Created by yuxiao on 15/4/29.
 */


var MapStageInfo = ui.GuiWindowBase.extend({
    _guiFile: "ui/map_info_title.json",

    ctor: function(map_id, is_open) {
        this._super();
        this.mapId = map_id;
        this.isOpen = is_open;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            lbl_title: this.seekWidgetByName("lbl_name"),
            lbl_reward_1: this.seekWidgetByName("lbl_reward_1"),
            lbl_reward_2: this.seekWidgetByName("lbl_reward_2"),
            lbl_reward_3: this.seekWidgetByName("lbl_reward_3"),
            btn_enter: this.seekWidgetByName("btn_enter"),
            btn_raid: this.seekWidgetByName("btn_raid"),
            node_avatar: this.seekWidgetByName("Panel_avatar")
        };

        var config = configdb.map[this.mapId];
        if(config == undefined) {
            return;
        }

        // title
        this._ui.lbl_title.setString(config.name);

        // monster avatar
        this.createMonsterAvatar(config.avatar_id);

        // reward
        this._ui.lbl_reward_1.setString(String(config.first_award));
        this._ui.lbl_reward_2.setString(String(config.gain_gold));
        this._ui.lbl_reward_3.setString(String(config.gain_exp));

        this._ui.btn_enter.setEnabled(this.isOpen);
        this._ui.btn_enter.setBright(this.isOpen);
        this._ui.btn_raid.setEnabled(this.isOpen);
        this._ui.btn_raid.setBright(this.isOpen);
    },

    onExit: function() {
        this.clearMonsterAvatar();
        this._ui = null;
        this._super();
    },

    clearMonsterAvatar: function() {
        this._ui.node_avatar.removeAllChildren();
    },

    createMonsterAvatar: function(role_id) {
        this.clearMonsterAvatar();

        if(role_id) {

            var avatar = new ShowRole(role_id);
            this._ui.node_avatar.addChild(avatar);

            var size = this._ui.node_avatar.getContentSize();
            avatar.setPosition(size.width/2, 0);

            var box = avatar.getBoneBox("body");
            if(box.height > size.height) {
                avatar.setScale(size.height/box.height);
            }
        }
    },

    _on_btn_close: function() {
        this.close();
    },

    _on_btn_raid: function() {

    },

    _on_btn_enter: function() {
        var costValue = 2;
        if(PlayerSystem.instance.action < costValue){
            MessageBoxOk.show("体力不足");
            return;
        }

        PlayerSystem.instance.action -= costValue;

        var loadingPanel = new LoadingBattleLayer(this.mapId);
        loadingPanel.pop();

        loadingPanel.setLoadDoneFunc(function() {
            this.loadResourceDone();
            loadingPanel.close();
        }, this)
    },

    loadResourceDone : function () {

        var mapConfig = configdb.map[this.mapId];
        if(mapConfig ){
            if(mapConfig.map_type == BattleSystem.BattleType.NormalType){
                ui.pushScene(new BattleScene(this.mapId));
                //ui.pushScene(new BattleDefScene(this.mapId) );
            }
            else if(mapConfig.map_type == BattleSystem.BattleType.DefendType){
                ui.pushScene(new BattleDefScene(this.mapId) );
            }
            else if(mapConfig.map_type == BattleSystem.BattleType.EndlessType){

            }
            BattleSystem.instance.battleMap(this.mapId);
            this.close();
        }
        else{
            LOG("MAP ID NOT FIND!");
        }
    }


});

