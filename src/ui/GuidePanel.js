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
            this._content_img.setVisible(true);

            var spr = cc.Sprite.create(iconStr_);
            spr.retain();
            var size = spr.getContentSize();
            this._content_img.loadTexture(iconStr_);
            var orgPos = this._content_img.getPosition();
            this._content_img.setContentSize(cc.size(size.width,size.height))
        }
        else{
            this._content_img.setVisible(false);
        }
    },
    
    //updateBtn : function (btn_) {
    //    var cpBtn = btn_.clone();
    //
    //    this.addChild(cpBtn);
    //    cpBtn.setAnchorPoint(btn_.getAnchorPoint());
    //    cpBtn.setPosition(btn_.convertToWorldSpace());
    //    cpBtn.setVisible(true);
    //
    //    return cpBtn;
    //},
    
    
    startRefreshBtn : function (btn_) {
        this._oriBtn = btn_;
        this._oriBtn.setVisible(false);

        if(this._cpBtn){
            this._cpBtn.removeFromParent();
            this._cpBtn = null;
        }

        this._cpBtn = this._oriBtn.clone();

        this.addChild(this._cpBtn);
        this._cpBtn.setVisible(true);

        UiEffect.buttonBBB(this._cpBtn);

        this.schedule(this.scheduleUpdateCpBtn);
        return this._cpBtn;
    },
    
    endRefreshBtn : function () {
        this.unschedule(this.scheduleUpdateCpBtn);

        this._oriBtn.setVisible(true);
        this._cpBtn.removeFromParent();
        this._cpBtn = null;
    },

    scheduleUpdateCpBtn : function () {
        var pos = this._oriBtn.convertToWorldSpaceAR();
        var anc = this._oriBtn.getAnchorPoint();
        this._cpBtn.setPosition(pos);
        this._cpBtn.setAnchorPoint(anc);
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

var SkillGuidePanel = ui.GuiWindowBase.extend({
    _guiFile : "ui/skill_guide.json",

    ctor : function (skill_type_,selector, target) {
        this._super();

        this._skill_idx = skill_type_;

        this._touchCallback = selector;
        this._target = target;

    },

    onEnter : function () {
        this._super();

        this._arrow_img = this.seekWidgetByName("skill_des");
        this.bgPanel = this.seekWidgetByName("bg_panel");


        var idxStr = "images/code_ui/ui_390.png";
        switch (this._skill_idx){
            case RoleAction.Type.SKILL1 :
                idxStr = "images/code_ui/ui_391.png";
                break;
            case  RoleAction.Type.SKILL2 :
                idxStr = "images/code_ui/ui_392.png";
                break;
            case  RoleAction.Type.SKILL3 :
                idxStr = "images/code_ui/ui_393.png";
                break;
            case  RoleAction.Type.SKILL4 :
                idxStr = "images/code_ui/ui_390.png";
                break;
            case  RoleAction.Type.SKILL5 :
                idxStr = "images/code_ui/ui_398.png";
                break;
        }

        this._arrow_img.loadTexture(idxStr);

        this.bgPanel.addTouchEventListener(function (touch,event) {
            if(event == ccui.Widget.TOUCH_ENDED){
                LOG("touch end");
                this._touchCallback.apply(this._target);
            }
        },this);

    },

    onExit : function () {
        this._content_img = null;
        this.bgPanel = null;


        this._super();
    }
});
