var GuidePanel = ui.GuiWindowBase.extend({
    _guiFile : "ui/yin_dao.json",

    ctor : function (guideType_) {
        this._super();




    },


    onEnter : function () {
        this._super();
        this._arrow_img = this.seekWidgetByName("arrow_img");
        this._content_img = this.seekWidgetByName("content_img");

    },

    onExit : function () {

        this._arrow = null;
        this._content_img = null;

        this._super();
    },
    
    refreshArrowImage : function (rotate_,pos_,endPos_) {
        this._arrow_img.setRotation(rotate_)

        this._arrow_img.setPosition(endPos_);
    },
    
    refreshContentImage : function (pos_,endPos_,iconStr_) {
        this._content_img.setPosition(endPos_);
        if(iconStr_ != undefined){

            var spr = cc.Sprite.create(iconStr_);
            spr.retain();
            var size = spr.getContentSize();
            LOG("SIZE W = " + size.width);
            LOG("SIZE W = " + size.height);
            this._content_img.loadTexture(iconStr_);
            var orgPos = this._content_img.getPosition();
            
            this._content_img.setContentSize(cc.size(size.width,size.height))

        }
    }
});


var CaoZuoJiaoXue = ui.GuiWindowBase.extend({
    _guiFile : "ui/caozuo_jiaoxue.json",

    ctor : function () {
        this._super();

    },


    onEnter : function () {
        this._super();
        //this._arrow_img = this.seekWidgetByName("arrow_img");
        this._cover_bg = this.seekWidgetByName("cover_layer");


        this._cover_bg.addTouchEventListener(function (touch,event) {
            if(event == ccui.Widget.TOUCH_ENDED){
                this.removeFromParent();
            }
        },this)
    },

    onExit : function () {



        this._super();
    }
});

