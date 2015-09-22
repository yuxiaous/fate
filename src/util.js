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

    getCurrentDate : function () {
        var now = new Date();
        //LOG("get current date = " + now.getTime());
        //LOG("get current date day = " + now.getDate());
        //LOG("get current date day = " + now.getFullYear());
        //LOG("get current date day = " + Number(now.getMonth() + 1));
        //LOG("get current date day = " + now.getDay());
        //LOG("get current date day = " + now.toLocaleDateString());
        //LOG("get current date day-- = " +  Date.parse(now.getTime()));
        return now.getTime();
    },

    compareTimeWithToday : function (time_) {
        var now = new Date();
        var curTime = new Date();
        curTime.setTime(time_);

        var isLargeDay = false;
        if(curTime.getFullYear() < now.getFullYear() || curTime.getMonth() < now.getMonth() || curTime.getDate() < now.getDate()){
            isLargeDay = true;
        }
        return isLargeDay;
    },

    compareTimeWithMinutes : function (time_) {
        var now = new Date();
        var curTime = new Date();
        curTime.setTime(time_);

        var overTime = now.getTime() - curTime.getTime();

        overTime = Math.floor(overTime/1000);

        var evertRecover = configdb.property[120].value;

        var ret = Math.floor( overTime / evertRecover);
        if( ret <= 0){
            return 0;
        }
        else{
            return ret;
        }
    },

    getChannelId: function() {
        return jsb.GameUtils.getChannelId();
    },

    getUdid: function() {
        return jsb.GameUtils.getUdid();
    },

    getSimOperator: function() {
        return jsb.GameUtils.getSimOperator();
    },

    isLite: function() {
        return false;
    }
};

var GameChannel = {
    AppStore: 1,
    CmccAnd: 2,
    CmccMm: 3,
    Telecom: 4,
    Unicom: 5,
    Mzw: 6,
    "4399": 7,
    Qh360: 8,
    TencentMidas: 9, //腾讯应用宝
    Mix: 10,
    Pps: 11,
    SohuWan: 12,
    Youku: 13,
    Baidu91: 14,
    BaiduTieba: 15
};

var SimOperator = {
    CMCC: 1,
    UNICOM: 2,
    TLELCOM: 3
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

