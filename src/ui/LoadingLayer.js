/*
* shilei@163.com
* 2015/03/23
* */
var LoadingBattleLayer = ui.GuiWindowBase.extend({
    _guiFile: "res/ui/LoadingLayer.json",

    ctor: function(mapId_) {
        this._super();
        this._mapId = mapId_;
    },

    _judgeResAmount : function (mapid_) {
        this.stage = BattleNorScene.initStageInfo(mapid_);
        this.BSection = BattleNorScene.initBattleSection(mapid_);
        this.chatData = BattleNorScene.initChatInfo(mapid_);

        if(this.stage){
            var battleSceneFile = this.stage.scene_file;
            var endString = (battleSceneFile.split(".lhplist"))[0] + ".png";

            cc.loader.loadImg(endString);

            var bgMusic = this.stage.bgm_file;
            cc.audioEngine.preloadMusic(bgMusic);

            var battleWeatherFile = this.stage.weather_file;
            //cc.spriteFrameCache.addSpriteFrames(battleWeatherFile);
        }
        if(this.BSection){
            _.each(this.BSection, function (sectionData) {
                if(sectionData && sectionData.monsters){
                    var monsterData = sectionData.monsters;
                    _.each(monsterData, function (data) {
                        var roleConfig = configdb.role[data.roleId];
                        var modelConfig = configdb.model[roleConfig.model_id];

                        if(modelConfig){
                            dragonBones.DragonBonesHelper.addDragonBones(modelConfig.armature);
                        }
                    });
                }
            });
        }
        if(this.chatData){
        }
    },

    onEnter: function() {
        this._super();

        this.loadLabel = this.seekWidgetByName("lbl_load");
        this.loadIcon = this.seekWidgetByName("load_icon");
        this.avatarNode = this.seekWidgetByName("avatar_node");

        //rotate icon
        if(this.loadIcon){
            this.loadIcon.runAction(cc.RepeatForever.create(
                cc.RotateBy.create(1.0,360)
            ));
        }

        //ramdon avatar
        if(this.avatarNode){
            var avatar = new ShowRole(1101);
             avatar.setScale(0.7);
            this.avatarNode.addChild(avatar);
        }

       // this._judgeResAmount(this._mapId);

        var that = this;
        this.runAction(cc.Sequence.create(cc.DelayTime.create(1.0),
                cc.CallFunc.create(function(){
                    if(that._loadDoneTarget && that._loadDoneFunc){
                        that._loadDoneFunc.apply(that._loadDoneTarget);
                    }
                }))
        );
    },

    onExit: function() {
        this.loadLabel = null;
        this.loadIcon = null;
        this.avatarNode = null;

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
