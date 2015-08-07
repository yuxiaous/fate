/*
* shilei@163.com
* 2015/03/23
* */
var LoadingBattleLayer = ui.GuiWindowBase.extend({
    _guiFile: "res/ui/LoadingLayer.json",

    ctor: function(mapId_) {
        this._super();
        this._mapId = mapId_;
        this._avater = null;
        this._addResContent = [];

        //this._curPercent = 0;
        this._loadResCount = 0;
        this._loadResMax = 0;
        this._maxWidth = 0;

        this._moveMaxTime = 1.0;
    },

    judgeResData : function (mapId_) {
        this.stage = BattleNorScene.initStageInfo(mapId_);
        this.BSection = BattleNorScene.initBattleSection(mapId_);
        this.chatData = BattleNorScene.initChatInfo(mapId_);

        LOG("judge res data");
        if(this.stage){
            var battleSceneFile = this.stage.scene_file;
            var endString = (battleSceneFile.split(".lhplist"))[0];
            endString = (endString.split("/"))[1];
            endString = "res/scenes/568/"+endString+".png";
            this.addResToContent(endString);

            //LOG("lh scene tmp----" + endString);
            ////var tmpScene = new lh.LHScene();
            ////tmpScene.initWithContentOfFile(this.stage.scene_file);
            ////tmpScene.removeFromParent();
            //LOG("--- done");
            ////tmpScene = null;
        }

        if(this.BSection){
            _.each(this.BSection, function (sectionData) {
                _.each(sectionData.monsters, function (wave) {
                    _.each(wave, function(data) {
                        var roleConfig = configdb.role[data.roleId];
                        var modelConfig = configdb.model[roleConfig.model_id];
                        if(modelConfig){
                            var armatureStr = modelConfig.armature;
                            armatureStr = "res/armatures/" + armatureStr + "/texture.png";
                            LOG("armature str = " + armatureStr);
                            this.addResToContent(armatureStr);
                        }
                    }, this);
                }, this);
            }, this);
        }

        if(this.chatData){

        }

        var skin = SkinSystem.instance.use_skin;
        var tmpHero = null;
        if(skin == 101){
            tmpHero = new Saber();
        }
        else if(skin == 102){
            tmpHero = new Nero();
        }

        if(true){
            var armStr = tmpHero.armatureName;
            var armStr = "res/armatures/" + armStr + "/texture.png";
            this.addResToContent(armStr);

            var str = "res/armatures/sabar_effect/texture.png";
            this.addResToContent(str);
        }
    },

    addResToContent : function (res_) {
        if(this._addResContent ){
            var hadAdd = false
            _.each(this._addResContent, function (str_) {
                if(str_ == res_){
                    hadAdd = true;
                }
            });

            if(!hadAdd){
                this._addResContent.push(res_);
                this._loadResMax = this._addResContent.length;
                LOG("this load res max = " + this._loadResMax);
            }
        }
    },

    loadResData : function () {
        //var that = this;
        //var size = cc.director.getWinSize();
        //var url = "res/armatures/sabar/texture.png";
        //LOG(" start = " + util.getCurrentDate());
        //cc.loader.loadImg(url, null, function(err,img){
        //    LOG("end = " + util.getCurrentDate());
        //    var logo  = new cc.Sprite(img);
        //    that.addChild(logo);
        //    logo.x = size.width / 2;
        //    logo.y = size.height / 2;
        //});

        LOG("over = " + util.getCurrentDate());
        var that = this;
        _.each(this._addResContent, function (resStr_) {
            if(resStr_){
                var url = resStr_;
                cc.loader.loadImg(url, null, function(err,img){
                    that._loadResCount += 1;
                    //LOG("end = " + util.getCurrentDate());
                    LOG("load count = " + that._loadResCount);

                    that.updateAvaterAndPercent();
                });
            }
        })
    },

    onEnter: function() {
        this._super();

        this.loadLabel = this.seekWidgetByName("lbl_load");
        //this.loadLabel.setVisible(false);
        this.loadBar = this.seekWidgetByName("loadingBarPro");

        //ramdon avatar

        if(this.loadBar){
            this._avater = new ShowRole(1101);
            this._avater.setWalkAction();
            this._avater.setScale(0.8);
            this._avater.setPosition(cc.p(0,30));
            this.loadBar.addChild(this._avater);

            this._maxWidth = this.loadBar.getContentSize().width;
        }


        this.loadBar.setPercent(0);
        this._avater.setPosition(cc.p(0,30));

        this.judgeResData(this._mapId);

        this.loadResData();
        cc.director.getScheduler().schedule(this.updateLoadPercent,this,0.1,cc.REPEAT_FOREVER,0,false,"updateAvater");
    },

    updateLoadPercent : function () {

        var posx = this._avater.getPosition().x;

        var per = posx / this._maxWidth;

        this.loadBar.setPercent(per * 100);
    },
    
    
    updateAvaterAndPercent : function () {
            var _curPercent = this._loadResCount / this._loadResMax;
            var endPosx = this._maxWidth * _curPercent;
            //LOG("end pos  = " + endPosx);
            //LOG("this maxwidth = " +this._maxWidth);
            var dur = _curPercent * this._moveMaxTime;
            var moveAct = cc.MoveTo.create(dur,cc.p(endPosx,30));
            var Callf = cc.CallFunc.create(function () {
               if(this._loadResCount == this._loadResMax){
                   if(this._loadDoneTarget && this._loadDoneFunc){
                       this._loadDoneFunc.apply(this._loadDoneTarget);
                   }
               }
            },this);

            this._avater.stopAllActions();

            this._avater.runAction(cc.Sequence.create(
                moveAct,Callf
            ));

    },

    onExit: function() {
        this.loadLabel = null;
        this._addResContent = null;

        cc.director.getScheduler().unschedule("updateAvater",this);
        this._super();
    },

    setLoadDoneFunc : function (loadDoneFunc_,target_) {
        this._loadDoneFunc = loadDoneFunc_;
        this._loadDoneTarget = target_;
    }
});
