/**
 * Created by yuxiao on 15/5/12.
 */


var database = {
    base64: new Base64(),
    //JSON.stringify(obj); -> json
    //JSON.parse(json) -> obj

    init: function(name) {
        cc.sys.localStorage.free();
        cc.sys.localStorage.init(name + ".data");
    },

    checkout: function(key, default_obj) {
        var code = cc.sys.localStorage.getItem(key);
        if(code && code.length > 0) {
            var json = this.base64.decode(code);
            return JSON.parse(json);
        }
        return default_obj;
    },

    commit: function(key, obj) {
        if(key && obj) {
            var json = JSON.stringify(obj);
            var code = this.base64.encode(json);
            cc.sys.localStorage.setItem(key, code);
        }
    }
};

