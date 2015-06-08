/**
 * Created by yuxiao on 15/4/22.
 */


var MapChapter = ui.GuiWidgetBase.extend({
    _guiFile: "ui/map_widget.json",

    ctor: function(chapter_id) {
        this._super();

        var config = configdb.chapter[chapter_id];
        this.chapterId = chapter_id;
        this.chapterName = config.name;
    },

    onEnter: function() {
        this._super();

        // maps
        this._maps = [];
        var chapter_config = configdb.chapter[this.chapterId];
        _.each([
            [chapter_config.map1_id, "ProjectNode_1"],
            [chapter_config.map2_id, "ProjectNode_2"],
            [chapter_config.map3_id, "ProjectNode_3"],
            [chapter_config.map4_id, "ProjectNode_4"],
            [chapter_config.map5_id, "ProjectNode_5"],
            [chapter_config.map6_id, "ProjectNode_6"]
        ], function(data) {
            var map_id = data[0];
            var map_node = this.seekWidgetByName(data[1]);
            if(map_id && map_node) {
                var ctrl = new MapStage(map_id);
                ctrl.setWidget(map_node);
                this._maps.push(ctrl);
            }
        }, this);

        this.updateMapStatus();

        this.setCurMapStagePoint();
    },

    onExit: function() {
        _.each(this._maps, function(ctrl) {
            ctrl.setWidget(null);
        }, this);
        this._maps = null;
        this._super();
    },

    updateMapStatus: function() {
        var system = MapSystem.instance;
        var maps_info = system.maps_info;

        this._cur_StageIdx = 0;
        _.each(this._maps, function(map) {
            var info = maps_info[map.mapId];
            if(info) {
                map.setOpened(true);
                if(this._cur_StageIdx < map.mapId){
                    this._cur_StageIdx = map.mapId;
                }
            }
            else {
                map.setOpened(false);
            }
        }, this);
    },

    getCurMapStageIndex : function () {
        return this._cur_StageIdx;
    },
    
    getCurMapStagePosX : function () {
        var tmpMap = null
        _.each(this._maps,function(map){
            if(map && map.mapId == this._cur_StageIdx){
                tmpMap = map;
            }
        },this);

        if(tmpMap){
            var tmpNode = tmpMap.getWidget()
            return tmpNode.getPosition().x + tmpNode.getContentSize().width;
        }
    },
    
    setCurMapStagePoint : function () {
        _.each(this._maps,function(map){
            if(map && map.mapId == this._cur_StageIdx){
                var tmpNode = map.getWidget();

                var tmpSize = tmpNode.getContentSize();
                var pointer = cc.Sprite.create("res/images/ui/ui_43.png");
                pointer.setPosition(cc.p(tmpSize.width * 0.5,tmpSize.height));
                pointer.setAnchorPoint(cc.p(0.5,0));
                if(tmpNode){
                    tmpNode.addChild(pointer);
                    pointer.runAction(cc.RepeatForever.create(
                        cc.JumpBy.create(1, cc.p(0, 0), tmpSize.height * 0.3, 1)
                    ));
                }
            }
        },this);
    }
    
});

