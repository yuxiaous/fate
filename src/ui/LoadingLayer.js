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

        var that = this;
        if(this.BSection){
            _.each(this.BSection, function (sectionData) {
                if(sectionData && sectionData.monsters){
                    var monsterData = sectionData.monsters;
                    _.each(monsterData, function (data) {
                        var roleConfig = configdb.role[data.roleId];
                        var modelConfig = configdb.model[roleConfig.model_id];
                        if(modelConfig){
                            var armatureStr = modelConfig.armature;
                            armatureStr = "res/armatures/" + armatureStr + "/texture.png";
                            that.addResToContent(armatureStr);
                        }
                    });
                }
            });
        }

        if(this.chatData){

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
                //LOG("this load res max = " + this._loadResMax);
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
            LOG("end pos  = " + endPosx);
            LOG("this maxwidth = " +this._maxWidth);

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

/*
*
*  //统计加载资源的数量
 var judgeResAmount = function(resCon){
 var resAmount = 0;
 if(resCon.dragonBonesRes){
 _.each(resCon.dragonBonesRes, function (res_) {
 resAmount += 1;
 })
 }

 if(resCon.weather){

 }

 if(resCon.music){
 if(resCon.music.background) {
 //resAmount += 1;
 }
 if(resCon.music.effect) {
 _.each(resCon.music.effect, function(effect) {
 //resAmount += 1;
 });
 }
 }

 if(resCon.openingChat){
 _.each(resCon.openingChat, function (chatInfo_) {
 if(chatInfo_.image){
 resAmount += 1;
 }
 })
 }

 if(resCon.enemies){

 }
 return resAmount;
 }
 //加载资源，每加载完成单个资源会刷新PROGRESSBAR
 //var that = this;
 jsb.fileUtils.addSearchPath("res");
 var preStart = function (resCon) {
 var loadCount = 0;
 if(resCon.dragonBonesRes){
 _.each(resCon.dragonBonesRes, function(res_) {
 if(dragonBones.DragonBonesHelper.addDragonBones(res_)){
 loadDone();
 }
 //SLEEP(1000);
 });
 }
 if(resCon.weather){
 if(resCon.weather.res){

 }
 }
 if(resCon.music){
 if(resCon.music.background) {
 //cc.audioEngine.preloadMusic(resCon.music.background);
 }
 if(resCon.music.effect) {
 _.each(resCon.music.effect, function(effect) {
 //cc.audioEngine.preloadEffect(effect);
 });
 }
 }
 if(resCon.openingChat){
 _.each(resCon.openingChat, function (chatInfo_) {
 cc.loader.loadImg(chatInfo_.image, function (err,data) {
 if(err){
 cc.log("loader openningChat img err");
 }
 else{
 loadDone();
 }
 })
 })
 }
 if(resCon.enemies){
 }
 function loadDone(){
 loadCount += 1;
 var curPercent = loadCount / judgeResAmount(that._resContainer);
 cc.log("load res count =" + loadCount);
 cc.log("load percent ="+curPercent);
 cc.log("all res amount = "+ judgeResAmount(that._resContainer));
 //that.progressBar.setPercent(curPercent * 100);
 if(loadCount == judgeResAmount(that._resContainer)){
 that.close();
 }
 }
 };

 this.runAction(cc.Sequence.create(cc.DelayTime.create(1.0),
 cc.CallFunc.create(function(){
 preStart(that._resContainer);
 }))
 );
* */
