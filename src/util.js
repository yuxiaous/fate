/**
 * Created by yuxiao on 14-9-28.
 */


var util = {
    str: function(id) {
        if(textDB[id]) {
            return textDB[id].Name;
        }
        return "Error: string id: " + id;
    },

    log: function(value) {
        var text;
        switch (typeof value) {
            case 'string':
                if(arguments.length == 1) {
                    text = value;
                }
                else if(arguments.length > 1) {
                    var args = {};
                    for(var i = 1; i < arguments.length; ++i) {
                        args[i-1] = arguments[i];
                    }
                    text = value.format(args);
                }
                break;

            case 'number':
                text = String(value);
                break;

            case 'object':
                text = JSON.stringify(value, null, 4);
                break;

            case 'boolean':
                text = value ? "true" : "false";
                break;

            default:
                text = "Unknown log type: " + typeof value;
                break;
        }

        cc.log("@@@ " + text)
    },

    logObj: function (obj_) {
        var des ="";
        for(var i in obj_){
            var property = obj_[i];
            if(typeof  property == "object"){
                cc.log(i + ":");
                util.logObj(property);
            }
            else if(typeof  property == "function"){
                continue;
            }
            else{
                des += i + " = " + property + "\n";
            }
        }
        cc.log("##" + des);
    },

    sleep : function (numberMillis_) {
        var now = new Date();
        var exitTime = now.getTime() + numberMillis_;
        while(1){
            now = new Date();
            if(now.getTime() > exitTime){
                return;
            }
        }
    },

    getChannelId: function() {
        jsb.GameUtils.getChannelId();
    }
};

var GameChannel = {
    AppStore: 1,
    CmccAnd: 2,
    CmccMm: 3,
    ChinaTelecom: 4,
    ChinaUnicom: 5
};

var LOG = util.log;
var LOGOBJ = util.logObj;
var SLEEP = util.sleep;

var GET_STRING = function(value) {
    switch (typeof value) {
        case 'string':
            return value;

        case 'number':
            return util.str(value);
    }

    return util.str(value);
};

