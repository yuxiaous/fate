/**
 * Created by yuxiao on 14/12/23.
 */


var crows = crows || {};


crows.start = function() {
    jsb.fileUtils.addSearchPath("res");

    //cc.sys.localStorage.setItem("OperatyBtn","LEFT");
    cc.sys.localStorage.setItem("OperatyBtn","RIGHT");

    //MusicManager.getInstance().setBackgroundMusicIsOpen(true);
    //MusicManager.getInstance().setEffectMusicIsOpen(true);

    MusicManager.getInstance().setBackgroundVolumn(0.5);
    MusicManager.getInstance().setEffectVolume(0.5);
    
    switch (util.getChannelId()) {
        case GameChannel.AppStore:
            ui.pushScene(StartLayerScene);
            break;

        default:
            ui.pushScene(LOGScene);
            break;
    }
};

crows.quit = function() {
    // pop to login scene
    ui.popScene(1);
};

crows.pause = function() {

};

crows.resume = function() {

};


var LOGScene = cc.Scene.extend({
    init : function () {
        this._super();
    },

    onEnter : function(){
        this._super();
        var winSize = cc.director.getWinSize();

        var logString = "res/logo_03.png";
        if(winSize.width < 960){
            logString = "res/logo_01.png";
        }
        else if(winSize.width > 960 ){
            logString = "res/logo_02.png";
        }

        var logoPic = cc.Sprite.create(logString);
        logoPic.setPosition(cc.p(winSize.width,0));
        logoPic.setAnchorPoint(cc.p(0,0));

        logoPic.setRotation(-90);
        this.addChild(logoPic);

        this.runAction(cc.Sequence.create(
            cc.DelayTime.create(3.0),
            cc.CallFunc.create(function () {
                ui.pushScene(StartLayerScene);
            })
        ));

    }
});

