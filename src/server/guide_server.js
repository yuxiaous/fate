var guide_server = {
    start: function() {
        //this.guide_info = database.checkout("guide_info",[
        //{ guideType: guide_server.Type.enterGameGuide,  guideState : 0},
        //{ guideType: guide_server.Type.zhuangbei,       guideState : 0},
        //{ guideType: guide_server.Type.jineng,          guideState : 0},
        //{ guideType: guide_server.Type.duanzao,         guideState : 0},
        //{ guideType: guide_server.Type.shangdian,       guideState : 0},
        //{ guideType: guide_server.Type.xueping,         guideState : 0},
        //]);
        //
        //this.curGuideId = 0;


        this.guideData = database.checkout("guide_info",{
            curGuideId : 0,
            guide_info : [{ guideType: guide_server.Type.enterGameGuide,  guideState : 0},
                            { guideType: guide_server.Type.zhuangbei,       guideState : 0},
                            { guideType: guide_server.Type.jineng,          guideState : 0},
                            { guideType: guide_server.Type.duanzao,         guideState : 0},
                            { guideType: guide_server.Type.shangdian,       guideState : 0},
                            { guideType: guide_server.Type.xueping,         guideState : 0},]
        });

        this.update = [];
    },

    end: function() {

    },

    sync: function() {
        //if(this.update.length > 0) {
        //    database.commit("guide_info", this.guide_info);
        //    this.update = [];
        //}

        if(this.update.length > 0) {
            database.commit("guide_info", this.guideData);
            this.update = [];
        }
    }
};

guide_server.Type = {
    //enterGameGuide : 1,
    //zhuangbei : 2,
    //jineng : 3,
    //duanzao : 4,
    //shangdian : 5,
    //xueping : 6

    enterGameGuide : 1,
    zhuangbei : 2,
    jineng : 3,
    duanzao : 4,
    shangdian : 5,
    shilian : 6,
    xueping : 7
}


server.registerCallback(net_protocol_handlers.CMD_CS_CURRENT_GUIDE_DONE, function (obj) {
    if(obj && obj.guideType != undefined){
        var guideInfo = guide_server.guideData.guide_info;
        _.each(guideInfo, function (guideInfo_) {
            if(guideInfo_ && guideInfo_.guideType == obj.guideType){
                guideInfo_.guideState = 1;
            }
        });
        guide_server.update.push(obj);
    }
    else{
        return;
    }

    server.send(net_protocol_handlers.CMD_SC_UPDATE_GUIDE_INFO,{
        guide_id : guide_server.guideData.curGuideId,
        guide_info : guide_server.guideData.guide_info
    })
});

server.registerCallback(net_protocol_handlers.CMD_CS_CURRENT_GUIDE_ID, function (obj) {
    if(obj && obj.guide_id){
        guide_server.guideData.curGuideId = obj.guide_id;

        guide_server.update.push(obj);
    }
});