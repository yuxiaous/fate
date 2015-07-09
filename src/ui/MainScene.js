/**
 * Created by yuxiao on 15/6/8.
 */


var MainScene = ui.GuiSceneBase.extend({
    _guiFile: "ui/main_scene.json",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        this.playAnimation("fadein");
        MusicManager.getInstance().playBackgroundMusic("sounds/background.mp3");

        this._ui = {
            lbl_level: this.seekWidgetByName("lbl_level"),
            lbl_score: this.seekWidgetByName("lbl_score"),
            sp_circle: this.seekWidgetByName("sp_circle"),
            sp_gear: this.seekWidgetByName("Node_gear"),
            gift_node: this.seekWidgetByName("gift_node"),
            lbl_rotate : this.seekWidgetByName("lbl_rotate"),
            rotate_panel : this.seekWidgetByName("rotate_label_panel"),

            btn_map : this.seekWidgetByName("btn_map")
        };

        GuideSystem.AddGuidePanel(this.seekWidgetByName("btn_map"),101);
        GuideSystem.AddGuidePanel(this.seekWidgetByName("btn_bag"),103);
        GuideSystem.AddGuidePanel(this.seekWidgetByName("btn_skill"),106);
        GuideSystem.AddGuidePanel(this.seekWidgetByName("btn_equip"),109);
        GuideSystem.AddGuidePanel(this.seekWidgetByName("btn_shop"),112);

        GuideSystem.AddGuidePanel(this.seekWidgetByName("btn_shop"),121);


        this._ui.lbl_rotate.setVisible(false);
        //this._ui.gift_node.setScale(0.5);

        this._ui.gift_panel = new GiftPanel();
        this._ui.gift_panel.setWidget(this.seekWidgetByName("gift_node"));

        this._ui.action = new ResourcePanel(ResourcePanel.Type.Action);
        this._ui.action.setWidget(this.seekWidgetByName("ProjectNode_1"));

        this._ui.gold = new ResourcePanel(ResourcePanel.Type.Gold);
        this._ui.gold.setWidget(this.seekWidgetByName("ProjectNode_2"));

        this._ui.diamond = new ResourcePanel(ResourcePanel.Type.Diamond);
        this._ui.diamond.setWidget(this.seekWidgetByName("ProjectNode_3"));
        //this._ui.diamond.setVisible(false);

        //appstore 显示
        this._ui.diamond.setVisible(util.getChannelId() == GameChannel.AppStore);


        this._ui.sp_circle.runAction(cc.repeatForever(cc.rotateBy(60, 360)));
        this._ui.sp_gear.runAction(cc.repeatForever(cc.rotateBy(60, -360)));

        this.refreshPlayerInfo();
        this.refreshRotateLabel();

        //// 进入游戏
        //var size = cc.director.getWinSize();
        //var enterGame = new cc.MenuItemFont("登陆奖励", function () {
        //    //var loginPanel = new LoginRewardLayer();
        //    //loginPanel.pop();
        //    RewardSystem.instance.getLoginRewardDaily();
        //});
        //enterGame.attr({
        //    x: size.width * 0.9,
        //    y: size.height * 0.8,
        //    fontSize: 30
        //});
        //var menu = new cc.Menu(enterGame);
        //menu.x = 0;
        //menu.y = 0;
        //this.addChild(menu, 1);

        this._bindings = [
            notification.createBinding(notification.event.OPEN_LOGIN_REWARD, function (event,obj) {
                var loginPanel = new LoginRewardLayer(obj.login_index);
                loginPanel.pop();
            },this)
        ];


        //var loginPanel = new LoginRewardLayer(3);
        //loginPanel.pop();

        if(GuideSystem.instance._curGuideType == 0){
            RewardSystem.instance.getLoginRewardDaily();
        }

        if(BattleSystem.instance.needRestart) {
            BattleSystem.instance.needRestart = false;
            if (BattleSystem.instance.needRestartBattleType == BattleSystem.instance.curBattleType) {
                if (BattleSystem.instance.curBattleType == SceneBase.Type.EndlessType) {
                    ui.pushScene(new BattleEndlessScene());
                }
            }
        }

    },


    onExit: function() {
        cc.director.getScheduler().unschedule("play_label",this);
        this._rotateLabelPanel.removeAllChildren();
        this._rotateLabelPanel.removeFromParent();
        this._rotateLabelPanel = null;
        this._ui = null;
        notification.removeBinding(this._bindings);
        this._super();
    },

    refreshPlayerInfo: function() {
        var system = PlayerSystem.instance;

        // level
        this._ui.lbl_level.setString(this._ui.lbl_level._str_original.format(system.level));

        // battle score
        var score = system.getPlayerBattleScore();
        this._ui.lbl_score.setString(this._ui.lbl_score._str_original.format(score.score));
    },

    refreshRotateLabel : function () {
        var label_content = [
            "残血时可以使用血瓶满血满蓝",
            "红色骑士套装，炫酷外形，所向披靡",
            "不要忘记技能和锻造升级",
            "替换装备不影响锻造提升属性",
            "金币可提升技能和锻造等级",
            "各式礼包可提升人物战力",
            "趁手的兵器，让你有更强大的攻击力",
            "请不要忘记装备上获得的更好得装备",
            "体力值为零时可通过购买回满体力值"
        ]

        var panelSize = this._ui.rotate_panel.getContentSize();
        var panelPos = this._ui.rotate_panel.getPosition();

        var scrollV = ccui.ScrollView.create();
        scrollV.setPosition(panelPos);
        scrollV.setAnchorPoint(cc.p(0,0));
        scrollV.setBackGroundColor(cc.color(230,10,10));
        scrollV.setInnerContainerSize(panelSize);
        scrollV.setContentSize(panelSize);
        scrollV.setDirection(ccui.ScrollView.DIR_VERTICAL);
        this.addChild(scrollV);
        this._rotateLabelPanel = scrollV;

        createLabel(true);
        createLabel(false);
        function createLabel(isFirst_){
            var idx = _.random(0,label_content.length-1);
            var rotateLabel = cc.LabelTTF.create(label_content[idx]);
            rotateLabel.labelIndex = idx;
            rotateLabel.setPosition(cc.p(0,-panelSize.height));
            if(isFirst_){
                rotateLabel.setPosition(cc.p(0,0));
            }
            rotateLabel.setAnchorPoint(cc.p(0,0));
            rotateLabel.setFontSize(24);
            scrollV.addChild(rotateLabel);
        }

        function updateLabel(){
            _.each(scrollV.getChildren(), function (label_) {
                if(label_.getPosition().y == panelSize.height){
                    label_.setPosition(cc.p(0,-panelSize.height));
                    do{
                        var idx = _.random(0,label_content.length-1);
                        label_.setString(label_content[idx]);
                    }while(idx == label_.labelIndex);
                    label_.labelIndex = idx;
                }
            })
        }

        function moveLabel(){
            _.each(scrollV.getChildren(), function (label_) {
                label_.runAction(cc.Sequence.create(
                    cc.MoveBy.create(1.0,cc.p(0,panelSize.height)),
                    cc.CallFunc.create(function () {
                        updateLabel();
                    },this)
                ));
            })
        }

        cc.director.getScheduler().schedule(function () {
            moveLabel();
        },this,2.0,cc.REPEAT_FOREVER,0,false,"play_label");
    },

    _on_btn_back: function() {
        LoginSystem.instance.logout();
        this.popScene();
    },

    _on_btn_map: function() {
        this.pushScene(MapScene);
        //ui.pushScene(new BattleScene(101));
    },

    _on_btn_bag: function() {

        if(!GuideSystem.instance.getCurFunctionIsOpenWithMapId(GuideSystem.Type.zhuangbei)){
            MessageBoxOk.show("通过第一章第三关开放");
            return;
        }

        //this.pushScene(BagScene);
        var win = new BagScene();
        win.pop();
    },

    _on_btn_skill: function() {
        if(!GuideSystem.instance.getCurFunctionIsOpenWithMapId(GuideSystem.Type.jineng)){
            MessageBoxOk.show("通过第一章第四关开放");
            return;
        }
        //this.pushScene(SkillScene);
        var win = new SkillScene();
        win.pop();
    },

    _on_btn_map_endless: function() {
        if(!GuideSystem.instance.getCurFunctionIsOpenWithMapId(GuideSystem.Type.shilian)){
            MessageBoxOk.show("通过第二章第六关开放");
            return;
        }

        //ui.pushScene(new BattleEndlessScene() );
        var endless_select = new EndlessSelected();
        endless_select.pop();
        UiEffect.iconOpenEffect(endless_select.seekWidgetByName("gift_panel"));
    },

    _on_btn_equip: function() {
        if(!GuideSystem.instance.getCurFunctionIsOpenWithMapId(GuideSystem.Type.duanzao)){
            MessageBoxOk.show("通过第一章第五关开放");
            return;
        }
        //this.pushScene(EquipScene);
        var win = new EquipScene();
        win.pop();
    },

    _on_btn_shop: function() {
        if(!GuideSystem.instance.getCurFunctionIsOpenWithMapId(GuideSystem.Type.shangdian)){
            MessageBoxOk.show("通过第一章第三关开放");
            return;
        }
        this.pushScene(ShopScene);
        //var win = new ShopScene();
        //win.pop();
    }
});

