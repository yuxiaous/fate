/**
 * Created by yuxiao on 15/4/21.
 */


var MapScene = ui.GuiSceneBase.extend({
    _guiFile: "ui/map_scene.json",

    ctor: function() {
        this._super();

        this._cur_chapter_id = 0;
        this._sel_map_id = 0;
    },

    onEnter: function() {
        this._super();
        MusicManager.getInstance().playBackgroundMusic("sounds/background.mp3");

        this._ui = {
            ctrl_action: (function() {
                var ctrl = new BagScene.Resource(BagScene.Resource.Type.Action);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_action"));
                return ctrl;
            }.bind(this) ()),
            ctrl_gold: (function() {
                var ctrl = new BagScene.Resource(BagScene.Resource.Type.Gold);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_gold"));
                return ctrl;
            }.bind(this) ()),
            ctrl_diamond: (function() {
                var ctrl = new BagScene.Resource(BagScene.Resource.Type.Diamond);
                ctrl.setWidget(this.seekWidgetByName("ProjectNode_diamond"));
                return ctrl;
            }.bind(this) ()),


            list_maps: this.seekWidgetByName("list_maps"),
            cell_maps: [],
            lbl_chapter: this.seekWidgetByName("lbl_chapter"),
            btn_pre: this.seekWidgetByName("btn_pre"),
            btn_next: this.seekWidgetByName("btn_next"),
            btn_battle: this.seekWidgetByName("btn_battle"),
            btn_raid: this.seekWidgetByName("btn_raid")
        };
        this._bindings = [
            //notification.createBinding(notification.event.MAP_MAP_INFO, this.createChapterPages, this),
            notification.createBinding(notification.event.BATTLE_MAP_RESULT, this.onBattleMapResult, this)
        ];

        this._cur_chapter_id = MapSystem.instance.max_chapter_id;
        this.createChapterPages();
    },

    onExit: function() {
        this.clearChapterPages();
        notification.removeBinding(this._bindings);
        this._ui.ctrl_action.setWidget(null);
        this._ui.ctrl_gold.setWidget(null);
        this._ui.ctrl_diamond.setWidget(null);
        this._ui = null;
        this._super();
    },

    clearChapterPages: function() {
        _.each(this._ui.cell_maps, function(cell) {
            cell.setSelectCallback(null);
        }, this);
        this._ui.cell_maps.length = 0;
        this._ui.list_maps.removeAllItems();
    },

    createChapterPages: function() {
        this.clearChapterPages();

        var config = configdb.chapter[this._cur_chapter_id];
        if(config == undefined) {
            return;
        }

        // chapter
        var system = MapSystem.instance;
        var has_pre = config.pre && config.pre > 0;
        var has_next = config.next && config.next <= system.max_chapter_id;
        this.setChapterSwitchButton(has_pre, has_next);
        this._ui.lbl_chapter.setString(config.name);

        // maps
        _.each([
            config.map1_id, config.map2_id, config.map3_id,
            config.map4_id, config.map5_id, config.map6_id,
            config.map7_id, config.map8_id, config.map9_id
        ], function(map_id) {
            if(map_id) {
                var cell = new MapScene.MapCell(map_id);
                this._ui.list_maps.pushBackCustomItem(cell);
                this._ui.cell_maps.push(cell);
                cell.setSelectCallback(this.onSelectMap, this);
            }
        }, this);

        // auto selected map
        this._sel_map_id = (this._cur_chapter_id == system.max_chapter_id) ? system.max_map_id : this._ui.cell_maps[0].id;
        this.refreshSelectedMapInfo();

        // center selected map
        this.centerSelectedMap();
    },

    setChapterSwitchButton: function(has_pre, has_next) {
        this._ui.btn_pre.setBright(has_pre);
        this._ui.btn_pre.setEnabled(has_pre);
        this._ui.btn_next.setBright(has_next);
        this._ui.btn_next.setEnabled(has_next);
    },

    onSelectMap: function(cell) {
        this._sel_map_id = cell.id;
        this.refreshSelectedMapInfo();
    },

    refreshSelectedMapInfo: function() {
        _.each(this._ui.cell_maps, function(cell) {
            cell.setSelected(cell.id == this._sel_map_id);

            if(cell.id == this._sel_map_id) {
                var is_open = cell.open;
                this._ui.btn_battle.setBright(is_open);
                this._ui.btn_battle.setEnabled(is_open);
                this._ui.btn_raid.setBright(is_open);
                this._ui.btn_raid.setEnabled(is_open);
            }
        }, this);
    },

    centerSelectedMap: function() {
        this._ui.list_maps.forceDoLayout();
        var cell = _.find(this._ui.cell_maps, function(cell) {
            return cell.id == this._sel_map_id;
        }, this);

        var list_size = this._ui.list_maps.getInnerContainerSize();
        var cell_size = cell.getContentSize();
        var cell_pos = cell.getPosition();
        this._ui.list_maps.jumpToPercentHorizontal(cell_pos.x / (list_size.width - cell_size.width) * 100);
    },

    _on_btn_back: function() {
        this.popScene();
    },

    _on_btn_pre: function() {
        var config = configdb.chapter[this._cur_chapter_id];
        if(config && config.pre) {
            if(config.pre) {
                this._cur_chapter_id = config.pre;
                this.createChapterPages();
            }
        }
    },

    _on_btn_next: function() {
        var config = configdb.chapter[this._cur_chapter_id];
        if(config && config.next) {
            this._cur_chapter_id = config.next;
            this.createChapterPages();
        }
    },

    _on_btn_battle: function() {
        BattleSystem.instance.battleMap(this._sel_map_id);
    },
    _on_btn_raid: function() {

    },
    onBattleMapResult: function() {
        LOG("onBattleMapResult");
        var costValue = 2;
        PlayerSystem.instance.action -= costValue;


        var sel_map_id = BattleSystem.instance.cur_battle_map;
        var loadingPanel = new LoadingBattleLayer(sel_map_id);
        loadingPanel.pop();

        loadingPanel.setLoadDoneFunc(function() {
            (function () {
                var mapConfig = configdb.map[sel_map_id];
                if(mapConfig ){
                    if(mapConfig.map_type == BattleSystem.BattleType.NormalType){
                        ui.pushScene(new BattleScene(sel_map_id));
                        //ui.pushScene(new BattleDefScene(this.mapId) );
                    }
                    else if(mapConfig.map_type == BattleSystem.BattleType.DefendType){
                        ui.pushScene(new BattleDefScene(sel_map_id) );
                    }
                    else if(mapConfig.map_type == BattleSystem.BattleType.EndlessType){

                    }
                }
                else{
                    LOG("MAP ID NOT FIND!");
                }
            } ());
            loadingPanel.close();
        }, this)
    }
});

MapScene.MapCell = ui.GuiWidgetBase.extend({
    _guiFile: "ui/map_cell.json",

    ctor: function(id) {
        this._super();
        this.id = id;
        this.open = false;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_name: this.seekWidgetByName("lbl_name"),
            lbl_level: this.seekWidgetByName("lbl_level"),
            lbl_score: this.seekWidgetByName("lbl_score"),

            img_sel: this.seekWidgetByName("img_sel"),
            btn_touch: this.seekWidgetByName("btn_touch"),
            sp_indicator: this.seekWidgetByName("sp_indicator")
        };
        this._bindings = [
            notification.createBinding(notification.event.CMD_SC_MAP_INFO, this.refreshMapInfo, this)
        ];

        this.refreshMapInfo();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._ui = null;
        this._super();
    },

    refreshMapInfo: function() {
        var config = configdb.map[this.id];
        if(config == undefined) {
            return;
        }

        // name
        this._ui.lbl_name.setString(config.name);

        // level
        this._ui.lbl_level.setString(this._ui.lbl_level._str_original.format(config.req_lv));

        // score
        this._ui.lbl_score.setString(this._ui.lbl_score._str_original.format(config.score));

        // indicator
        if(this.id == MapSystem.instance.max_map_id) {
            this._ui.sp_indicator.setVisible(true);
            this.playAnimation("indicator", true);
        }
        else {
            this._ui.sp_indicator.setVisible(false);
            this.stopAnimation();
        }

        // open
        this.setOpened(this.id <= MapSystem.instance.max_map_id);
    },

    setOpened: function(val) {
        this.open = val;

        var config = configdb.map[this.id];
        if(config == undefined) {
            return;
        }

        this._ui.sp_icon.setTexture(val ? config.icon : config.icon_gray);
    },

    setSelected: function(val) {
        this._ui.img_sel.setVisible(val);
        this._ui.btn_touch.setEnabled(!val);
    },

    setSelectCallback: function (selector, target) {
        if(target === undefined)
            this._selectCallback = selector;
        else
            this._selectCallback = selector.bind(target);
    },

    _on_btn_touch: function() {
        if (this._selectCallback) {
            this._selectCallback(this);
        }
    }
});
