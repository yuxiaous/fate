/**
 * Created by yuxiao on 15/5/12.
 */


var database = {
    encrypt: true,
    base64: new Base64(),
    //JSON.stringify(obj); -> json
    //JSON.parse(json) -> obj

    init: function(name) {
        cc.sys.localStorage.free();
        cc.sys.localStorage.init(jsb.fileUtils.getWritablePath() + name + ".data");
    },

    checkout: function(key, default_obj) {
        var skey = this.encrypt ? this.base64.encode(key) : key;
        var code = cc.sys.localStorage.getItem(skey);
        if(code && code.length > 0) {
            var json = this.encrypt ? this.base64.decode(code) : code;
            return JSON.parse(json);
        }
        return default_obj;
    },

    commit: function(key, obj) {
        if(key && obj) {
            var json = JSON.stringify(obj);
            var code = this.encrypt ? this.base64.encode(json) : json;
            var skey = this.encrypt ? this.base64.encode(key) : key;
            cc.sys.localStorage.setItem(skey, code);
        }
    },

    verify: function(code) {
        var verify_code = this.checkout("verify_code");
        if(verify_code == undefined) {
            this.commit("verify_code", {
                code: code
            });
        }
        else if(verify_code.code != code) {
            cc.sys.localStorage.clear();
            this.commit("verify_code", {
                code: code
            });
        }
    }
};

