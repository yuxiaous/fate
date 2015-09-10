var LoadingScene = ui.GuiSceneBase.extend({
    //_guiFile: "",

    ctor: function () {
        this._super();

    },

    onEnter : function(){
        this._super();

        cc.director.purgeCachedData();

        var sel_map_id = BattleSystem.instance.cur_battle_map;
        var loadingPanel = new LoadingBattleLayer(sel_map_id);
        loadingPanel.pop();

        loadingPanel.setLoadDoneFunc(function() {
            (function () {
                var mapConfig = configdb.map[sel_map_id];
                if(mapConfig ){
                    if(mapConfig.map_type == BattleSystem.BattleType.NormalType){
                        var scene = new BattleNorScene(sel_map_id);
                        ui.pushScene(scene);
                    }
                    else if(mapConfig.map_type == BattleSystem.BattleType.DefendType){
                        var scene = new BattleDefScene(sel_map_id);
                        ui.pushScene(scene);
                    }
                }
                else{
                    LOG("MAP ID NOT FIND!");
                }
            } ());
            loadingPanel.close();
        }, this)


    },

    onExit : function () {
        this._super();
    }

})