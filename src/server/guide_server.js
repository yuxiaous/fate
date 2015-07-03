var guide_server = {
    start: function() {
        this.guide_info = database.checkout("guide_info",[
        { guideType: guide_server.Type.enterGameGuide,  guideState : 0},
        { guideType: guide_server.Type.zhuangbei,       guideState : 0},
        { guideType: guide_server.Type.jineng,          guideState : 0},
        { guideType: guide_server.Type.duanzao,         guideState : 0},
        { guideType: guide_server.Type.shangdian,       guideState : 0},
        ]);
        this.update = [];
    },

    end: function() {

    },

    sync: function() {
        if(this.update.length > 0) {
            database.commit("guide_info", this.guide_info);
            this.update = [];
        }
    }
};

guide_server.Type = {
    enterGameGuide : 1,
    zhuangbei : 2,
    jineng : 3,
    duanzao : 4,
    shangdian : 5
}


server.registerCallback(net_protocol_handlers.CMD_CS_CURRENT_GUIDE_DONE, function (obj) {
    LOG("GUIDE DONE = " + obj.guideType);
    if(obj && obj.guideType != undefined){
        _.each(guide_server.guide_info, function (guideInfo_) {
            LOG("guide info type ==== " + guideInfo_.guideType);
            if(guideInfo_ && guideInfo_.guideType == obj.guideType){
                LOG("-----");
                guideInfo_.guideState = 1;
            }
        });
        guide_server.update.push(obj);
    }
    else{
        return;
    }

    server.send(net_protocol_handlers.CMD_SC_UPDATE_GUIDE_INFO,{
        guide_info : guide_server.guide_info
    })
});