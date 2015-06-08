/**
 * Created by yuxiao on 15/4/21.
 */


var MapScene = ui.GuiSceneBase.extend({
    _guiFile: "ui/map_scene.json",

    ctor: function() {
        this._super();

        this._cur_chapter_id = 1;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            scroll: this.seekWidgetByName("scroll_map"),
            lbl_chapter: this.seekWidgetByName("lbl_chapter"),
            btn_pre: this.seekWidgetByName("btn_pre"),
            btn_next: this.seekWidgetByName("btn_next"),
            red_point_bag: this.seekWidgetByName("Sprite_red_role"),
            red_point_forge: this.seekWidgetByName("Sprite_red_streng"),
            red_point_skill: this.seekWidgetByName("Sprite_red_skill"),
            red_point_shop: this.seekWidgetByName("Sprite_red_shop")
        };

        this._ui.header = new MapScene.Header();
        this._ui.header.setWidget(this.seekWidgetByName("ProjectNode_header"));

        this._ui.action = new MapScene.Resource(MapScene.Resource.Type.Action);
        this._ui.action.setWidget(this.seekWidgetByName("ProjectNode_action"));
        this._ui.action.setAddCallback(function() {
            LOG("add action")
            GmSystem.instance.sendCommand("ar 3 10");
        });

        this._ui.gold = new MapScene.Resource(MapScene.Resource.Type.Gold);
        this._ui.gold.setWidget(this.seekWidgetByName("ProjectNode_gold"));
        this._ui.gold.setAddCallback(function() {
            LOG("add gold")
            GmSystem.instance.sendCommand("ar 1 100");
        });

        this._ui.diamond = new MapScene.Resource(MapScene.Resource.Type.Diamond);
        this._ui.diamond.setWidget(this.seekWidgetByName("ProjectNode_diamond"));
        this._ui.diamond.setAddCallback(function() {
            LOG("add diamond")
            GmSystem.instance.sendCommand("ar 2 100");
        });

        this._bindings = [
            notification.createBinding(notification.event.MAP_MAP_INFO, this.createChapterPages, this)
        ];

        this.createChapterPages();
        this.refreshRedPoint();

        MapSystem.instance.requestMapInfo();
        this.setChapterSwitchButton(false, false);

        MusicManager.getInstance().playBackgroundMusic("sounds/background.mp3");
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this.clearChapterPages();
        this._ui.header.setWidget(null);
        this._ui.action.setWidget(null);
        this._ui.action.setAddCallback(null);
        this._ui.gold.setWidget(null);
        this._ui.gold.setAddCallback(null);
        this._ui.diamond.setWidget(null);
        this._ui.diamond.setAddCallback(null);
        this._ui = null;
        this._super();
    },

    clearChapterPages: function() {
        this._ui.scroll.removeAllChildren();
    },

    createChapterPages: function() {
        this.clearChapterPages();

        // button status
        var system = MapSystem.instance;
        var config = configdb.chapter[this._cur_chapter_id];
        if(config) {
            var has_pre = config.pre && config.pre > 0;
            var has_next = config.next && config.next <= system.max_chapter_id;
            this.setChapterSwitchButton(has_pre, has_next);
        }

        if(this._cur_chapter_id > 0) {
            // scroll
            var chapter_page = new MapChapter(this._cur_chapter_id);
            this._ui.scroll.addChild(chapter_page);
            this._ui.scroll.setInnerContainerSize(chapter_page.getContentSize());

            if(chapter_page.getCurMapStagePosX() > cc.director.getVisibleSize().width/2){
                var tmpCount = this._ui.scroll.getInnerContainerSize().width;
                var tmpPer = chapter_page.getCurMapStagePosX() / tmpCount;
                this._ui.scroll.jumpToPercentHorizontal(tmpPer * 100);
            }

            //this._ui.scroll.jumpToLeft();

            // name
            this._ui.lbl_chapter.setString(chapter_page.chapterName);
        }
    },

    setChapterSwitchButton: function(has_pre, has_next) {
        this._ui.btn_pre.setBright(has_pre);
        this._ui.btn_pre.setEnabled(has_pre);
        this._ui.btn_next.setBright(has_next);
        this._ui.btn_next.setEnabled(has_next);
    },

    _on_btn_back: function() {
        LoginSystem.instance.logout();
        this.popScene();
    },

    _on_btn_pre: function() {
        var config = configdb.chapter[this._cur_chapter_id];
        if(config && config.pre) {
            if(config.pre) {
                this._cur_chapter_id = config.pre;
                this.createChapterPages();
                this._ui.scroll.jumpToLeft();
            }
        }
    },

    _on_btn_next: function() {
        var config = configdb.chapter[this._cur_chapter_id];
        if(config && config.next) {
            this._cur_chapter_id = config.next;
            this.createChapterPages();
            this._ui.scroll.jumpToLeft();
        }
    },

    _on_btn_func_role: function() {
        this.pushScene(BagScene);
    },

    _on_btn_func_strengthen: function() {
        this.pushScene(EquipScene);
    },

    _on_btn_func_skill: function() {
        this.pushScene(SkillScene);
    },

    _on_btn_func_shop: function() {
        this.pushScene(ShopScene);
    },

    _on_btn_setting: function() {
        this.pushScene(GmScene);
    },

    refreshRedPoint: function() {
        this._ui.red_point_bag.setVisible(EquipSystem.instance.hasBetterEquip());
        this._ui.red_point_forge.setVisible(EquipSystem.instance.canUpgradeEquipSlot());
        this._ui.red_point_skill.setVisible(SkillSystem.instance.canUpgradeSkill());
        this._ui.red_point_shop.setVisible(false);
    }
});


MapScene.Header = ui.GuiController.extend({
    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        this._ui = {
            lbl_level: this.seekWidgetByName("lbl_level"),
            lbl_score: this.seekWidgetByName("lbl_score"),
            loading_exp: this.seekWidgetByName("loading_exp")
        };

        this.refreshHeaderInfo();
    },

    onExit: function() {
        this._ui = null;
        this._super();
    },

    refreshHeaderInfo: function() {
        var system = PlayerSystem.instance;

        this._ui.lbl_level.setString(String(system.level));

        var score = system.getPlayerBattleScore();
        this._ui.lbl_score.setString(String(score.score));

        var exp = system.getPlayerExperience();
        this._ui.loading_exp.setPercent(100 * exp.exp / exp.need);
    }
});

MapScene.Resource = ui.GuiController.extend({
    ctor: function(type) {
        this._super();
        this.type = type;
    },

    onEnter: function() {
        this._super();
        this._ui = {
            sp_icon: this.seekWidgetByName("sp_icon"),
            lbl_value: this.seekWidgetByName("lbl_value")
        };
        this._bindings = [
            notification.createBinding(notification.event.PLAYER_INFO, this.refreshValue, this)
        ];

        this.setType(this.type);
        this.refreshValue();
    },

    onExit: function() {
        notification.removeBinding(this._bindings);
        this._ui = null;
        this._super();
    },

    setType: function(type) {
        this.type = type;

        var file;
        switch (this.type) {
            case MapScene.Resource.Type.Action:
                file = "images/icon/icon_01.png";
                break;
            case MapScene.Resource.Type.Gold:
                file = "images/icon/icon_02.png";
                break;
            case MapScene.Resource.Type.Diamond:
                file = "images/icon/icon_03.png";
                break;
        }
        if(file) {
            this._ui.sp_icon.setTexture(file);
        }
    },

    refreshValue: function() {
        var system = PlayerSystem.instance;

        var value = 0;
        switch (this.type) {
            case MapScene.Resource.Type.Action:
                value = system.action;
                break;
            case MapScene.Resource.Type.Gold:
                value = system.gold;
                break;
            case MapScene.Resource.Type.Diamond:
                value = system.diamond;
                break;
        }
        this._ui.lbl_value.setString(String(value));
    },

    _on_btn_add: function() {
        if (this._addCallback) {
            this._addCallback();
        }
    },

    setAddCallback: function (selector, target) {
        if(target === undefined)
            this._addCallback = selector;
        else
            this._addCallback = selector.bind(target);
    }
});
MapScene.Resource.Type = {
    Action: 1,
    Gold: 2,
    Diamond: 3
};

