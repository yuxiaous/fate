
var GuideSystem = SystemBase.extend({
    ctor: function () {
        this._super();
        this._curGuideInfo = [];

        this._GuidePanel = null;
        this._curGuideType = 0;
        this._curGuideId = 0;
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_UPDATE_GUIDE_INFO = this.refreshGuideInfo.bind(this);

    },

    refreshGuideInfo : function (obj) {
        LOG("refres guide info");
        LOG(obj);

        if(obj && obj.guide_info != undefined){
            this._curGuideInfo = obj.guide_info;
            this._curGuideId = obj.guide_id;

            _.each(this._curGuideInfo, function (info_) {
                LOG(" GUIDE TYPE = " + info_.guideType);
                LOG("  GUIDE STATE = " + info_.guideState);
            })

            LOG("cur guide id = " + obj.guide_id);
        }
    },

    onFinalize: function () {
        this._super();
        this._curGuideInfo = [];

        //this._GuidePanel.removeFromParent();
        //this._GuidePanel = null;

        net_protocol_handlers.ON_CMD_SC_BUY_GIFT_RESULT = null;
    },

    sendGuideTypeIsDone : function (guide_type_) {
        net_protocol_handlers.SEND_CMD_CS_CURRENT_GUIDE_DONE({
            guideType : guide_type_
        });
    },

    sendGuideId : function (id_) {
        this._curGuideId = id_;
        LOG("----- send guide id = " + this._curGuideId);

        net_protocol_handlers.SEND_CMD_CS_CURRENT_GUIDE_ID({
            guide_id : this._curGuideId
        });
    },

    getCurGuideTypeIsDone : function (guide_type_) {
        var isDone = false;

        _.each(this._curGuideInfo, function (info_) {
            if(info_.guideType == guide_type_ && info_.guideState != 0){
                isDone = true;
            }
        })
        return isDone;
    },

    getCurGuideIsOpenWithMapId : function(guide_type_){

        var isOpen = false;
        var curMapId = MapSystem.instance.max_map_id;
        switch (guide_type_){
            case  GuideSystem.Type.enterGameGuide :
                isOpen = true;
                break;
            case  GuideSystem.Type.zhuangbei :
                if(curMapId == 104){
                    isOpen = true;
                }
                break;
            case  GuideSystem.Type.jineng :
                if(curMapId == 105){
                    isOpen = true;
                }
                break;
            case  GuideSystem.Type.duanzao :
                if(curMapId == 106){
                    isOpen = true;
                }
                break;
            case  GuideSystem.Type.shangdian :
                if(curMapId == 201){
                    isOpen = true;
                }
                break;
            case GuideSystem.Type.xueping:
                if(curMapId == 103){
                    isOpen = true;
                }
                break;
        }
        return isOpen;
    },

    getCurFunctionIsOpenWithMapId : function(guide_type_){

        var isOpen = false;
        var curMapId = MapSystem.instance.max_map_id;
        switch (guide_type_){
            case  GuideSystem.Type.enterGameGuide :
                isOpen = true;
                break;
            case  GuideSystem.Type.zhuangbei :
                if(curMapId >= 104){
                    isOpen = true;
                }
                break;
            case  GuideSystem.Type.jineng :
                if(curMapId >= 105){
                    isOpen = true;
                }
                break;
            case  GuideSystem.Type.duanzao :
                if(curMapId >= 106){
                    isOpen = true;
                }
                break;
            case  GuideSystem.Type.shangdian :
                if(curMapId >= 103){
                    isOpen = true;
                }
                break;
            case GuideSystem.Type.shilian :
                if(curMapId >= 301){
                    isOpen = true;
                }
                break;
        }
        return isOpen;
    },

    //判断当前是否有引导
    getCurrentHadGuide : function () {
        if(this._curGuideType != 0){
            return true;
        }
        else{
            return false;
        }
    },

    getSkillIsNotGuided : function (skill_id) {
        var idx = 0;
        switch (skill_id){
            case RoleAction.Type.SKILL1 :
                idx = 0;
                break;
            case  RoleAction.Type.SKILL2 :
                idx = 1;
                break;
            case  RoleAction.Type.SKILL3 :
                idx = 2;
                break;
            case  RoleAction.Type.SKILL4 :
                idx = 3;
                break;
            case  RoleAction.Type.SKILL5 :
                idx = 4;
                break;
        }
        LOG("Guide  des = " + GuideSystem.SkillDes[idx]);
        var isGuided = jsb.JsonStorage.GetInstance(LoginSystem.settingFile).getBoolForKey(GuideSystem.SkillDes[idx]);
        if(!isGuided){
            jsb.JsonStorage.GetInstance(LoginSystem.settingFile).setBoolForKey(GuideSystem.SkillDes[idx],true);
            jsb.JsonStorage.GetInstance(LoginSystem.settingFile).flush();
            return true;
        }
        return false;
    }
});

GuideSystem.AddGuidePanel = function (btn_,guideId_,topDisplay_) {
    var sys = GuideSystem.instance;

    var guideConf = GuideSystem.content[guideId_];
    if(!guideConf){
        return false;
    }

    LOG("guideid = " + guideId_);
    LOG("cur guide id = " + sys._curGuideId);

    if(sys._curGuideId == -1 || sys._curGuideId == 0){

    }
    else{
        if(guideId_ != sys._curGuideId){
            LOG("xxxx");
            return;
        }
    }

    //if(sys._curGuideId != -1 && sys._curGuideId != 0 && guideId_ != sys._curGuideId){
    //    LOG("xxxx");
    //
    //    return;
    //}

    if(guideConf.guideType != undefined){
        //判断引导是否已经执行过
        if(sys.getCurGuideTypeIsDone(guideConf.guideType)){
            return false;
        }
        //判断引导是否可以执行
        if(!sys.getCurGuideIsOpenWithMapId(guideConf.guideType)){
            return false;
        }

        if( sys._curGuideType != 0 && sys._curGuideType != guideConf.guideType){
            return false;
        }
        else{
            sys._curGuideType = guideConf.guideType;
        }
    }

    if(!sys.getCurGuideIsOpenWithMapId(sys._curGuideType)){
       return false;
    }
    if(sys._GuidePanel == null){
        sys._GuidePanel = new GuidePanel();
        var curScene = cc.director.getRunningScene();
        curScene.addChild(sys._GuidePanel,100000,100000);
    }
    sys._GuidePanel.setVisible(true);

    sys._GuidePanel.refreshArrowImage(guideConf.rotate,cc.p(0,0),guideConf.arr_pos);
    sys._GuidePanel.refreshContentImage(0,guideConf.cont_pos,guideConf.contIcon);

    if(btn_){
        var cpBtn = sys._GuidePanel.startRefreshBtn(btn_);
        cpBtn.addTouchEventListener(function (touch,event) {
            if(event == ccui.Widget.TOUCH_ENDED){
                sys._GuidePanel.endRefreshBtn();
                if(guideConf.next_id != 0){
                    sys.sendGuideId(sys._curGuideId);

                    sys._GuidePanel.removeFromParent();
                    if(guideConf.next_id == -1){
                        sys.sendGuideTypeIsDone(sys._curGuideType);
                        sys._curGuideType = 0;
                    }

                    sys._GuidePanel = null;

                    //TODO 临时使用，发完版本得重新修改
                    if(guideConf.cur_id == 207){
                        notification.emit(notification.event.GUIDE_UPDATE);
                    }
                }
            }
        })
    }

    return true;
}

GuideSystem.SkillDes = [
     "skill_des_1",
     "skill_des_2",
     "skill_des_3",
     "skill_des_4",
     "skill_des_5"
];

GuideSystem.SkillOpen = {
    SKILL_2 : "skill_open_2",
    SKILL_3 :"skill_open_3"
};

GuideSystem.Type = {
    enterGameGuide : 1,
    zhuangbei : 2,
    jineng : 3,
    duanzao : 4,
    shangdian : 5,
    shilian : 6,
    xueping : 7

};

GuideSystem.content = {
    //进入副本
    "101" : {
        guideType : GuideSystem.Type.enterGameGuide,
        contIcon : "images/code_ui/ui_345.png",
        isStart : true,
        cur_id :  101,
        next_id: -1,
        rotate: 90,
        arr_pos: cc.p(300, 400),
        cont_pos: cc.p(310, 465)
    },


    //引导去商城购买免费血瓶

    //引导过去装备
    "102" : {
        guideType : GuideSystem.Type.zhuangbei,
        contIcon : "images/code_ui/ui_346.png",
        isStart : true,
        cur_id: 102,
        next_id: 103,

        rotate: 100,
        arr_pos: cc.p(90, 140),
        cont_pos: cc.p(183, 235)
    },

    "103" : {
        guideType : GuideSystem.Type.zhuangbei,
        contIcon : "images/code_ui/ui_346.png",
        cur_id: 103,
        next_id: 104,

        rotate: 180,
        arr_pos: cc.p(415, 440),
        cont_pos: cc.p(645, 440)
    },

    "104" : {
        guideType : GuideSystem.Type.zhuangbei,
        contIcon : "images/code_ui/ui_395.png",
        cur_id: 104,
        next_id: 205,

        rotate: 180,
        arr_pos: cc.p(570, 280),
        cont_pos: cc.p(500, 380)
    },

    // new guide
    "205" : {
        guideType : GuideSystem.Type.zhuangbei,
        contIcon : "images/code_ui/ui_396.png",
        cur_id: 205,
        next_id: 207,

        rotate: 90,
        arr_pos: cc.p(600, 200),
        cont_pos: cc.p(300, 200)
    },
    //
    //"206" : {
    //    guideType : GuideSystem.Type.zhuangbei,
    //    contIcon : "images/code_ui/ui_396.png",
    //    cur_id: 206,
    //    next_id: 207,
    //
    //    rotate: 90,
    //    arr_pos: cc.p(845, 280),
    //    cont_pos: cc.p(845, 380)
    //},

    "207" : {
        guideType : GuideSystem.Type.zhuangbei,
        //contIcon : "images/code_ui/ui_347.png",
        cur_id: 207,
        next_id: 208,

        rotate: -90,
        arr_pos: cc.p(830, 450),
        cont_pos: cc.p(845, 380)
    },

    "208" : {
        guideType : GuideSystem.Type.zhuangbei,
        contIcon : "images/code_ui/ui_347.png",
        cur_id: 208,
        next_id: -1,

        rotate: 90,
        arr_pos: cc.p(845, 280),
        cont_pos: cc.p(845, 380)
    },

    //引导过去升级技能
    "105" : {
        guideType : GuideSystem.Type.jineng,
        contIcon : "images/code_ui/ui_348.png",
        isStart : true,
        cur_id: 105,
        next_id: 106,

        rotate: 100,
        arr_pos: cc.p(90, 140),
        cont_pos: cc.p(183, 235)
    },

    "106" : {
        guideType : GuideSystem.Type.jineng,
        contIcon : "images/code_ui/ui_348.png",
        cur_id: 106,
        next_id: 107,

        rotate: 120,
        arr_pos: cc.p(190, 425),
        cont_pos: cc.p(263, 505)
    },

    "107" : {
        guideType : GuideSystem.Type.jineng,
        contIcon : "images/code_ui/ui_349.png",
        cur_id: 107,
        next_id: -1,

        rotate: 90,
        arr_pos: cc.p(850, 185),
        cont_pos: cc.p(850, 260)
    },

    //引导过去锻造

    "108" : {
        guideType : GuideSystem.Type.duanzao,
        contIcon : "images/code_ui/ui_350.png",
        isStart : true,
        cur_id: 108,
        next_id: 109,

        rotate: 100,
        arr_pos: cc.p(90, 140),
        cont_pos: cc.p(215, 240)
    },

    "109" : {
        guideType : GuideSystem.Type.duanzao,
        contIcon : "images/code_ui/ui_350.png",
        cur_id: 109,
        next_id: 107,

        rotate: 90,
        arr_pos: cc.p(210, 270),
        cont_pos: cc.p(230, 365)
    },

    "110" : {
        guideType : GuideSystem.Type.duanzao,
        contIcon : "images/code_ui/ui_351.png",
        cur_id: 110,
        next_id: -1,

        rotate: 90,
        arr_pos: cc.p(965, 170),
        cont_pos: cc.p(945, 260)
    },

    //引导去商店购买

    //"111" : {
    //    guideType : GuideSystem.Type.shangdian,
    //    contIcon : "images/code_ui/ui_352.png",
    //    isStart : true,
    //    cur_id: 111,
    //    next_id: 112,
    //
    //    rotate: 100,
    //    arr_pos: cc.p(90, 140),
    //    cont_pos: cc.p(275, 240)
    //},
    //
    //"112" : {
    //    guideType : GuideSystem.Type.shangdian,
    //    contIcon : "images/code_ui/ui_353.png",
    //    cur_id: 112,
    //    next_id: 113,
    //
    //    rotate: 120,
    //    arr_pos: cc.p(460, 250),
    //    cont_pos: cc.p(565, 330)
    //},
    //
    //"113" : {
    //    guideType : GuideSystem.Type.shangdian,
    //    contIcon : "images/code_ui/ui_354.png",
    //    cur_id: 113,
    //    next_id: -1,
    //
    //    rotate: 0,
    //    arr_pos: cc.p(520, 440),
    //    cont_pos: cc.p(480, 355)
    //},

    //引导去商店购买

    "120" : {
        guideType : GuideSystem.Type.xueping,
        contIcon : "images/code_ui/ui_359.png",
        isStart : true,
        cur_id: 120,
        next_id: 121,

        rotate: 100,
        arr_pos: cc.p(90, 140),
        cont_pos: cc.p(275, 240)
    },

    "121" : {
        guideType : GuideSystem.Type.xueping,
        contIcon : "images/code_ui/ui_359.png",
        cur_id: 121,
        next_id: 122,

        rotate: 120,
        arr_pos: cc.p(460, 250),
        cont_pos: cc.p(565, 330)
    },

    "122" : {
        guideType : GuideSystem.Type.xueping,
        contIcon : "images/code_ui/ui_360.png",
        cur_id: 122,
        next_id: -1,

        rotate: 0,
        arr_pos: cc.p(520, 440),
        cont_pos: cc.p(480, 355)
    }

}



