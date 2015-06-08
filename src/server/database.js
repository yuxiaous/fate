/**
 * Created by yuxiao on 15/5/12.
 */


var database = {
    //JSON.stringify(obj); -> json
    //JSON.parse(json) -> obj

    checkout: function(key, default_obj) {
        var json = cc.sys.localStorage.getItem(key);
        if(json && json.length > 0) {
            return JSON.parse(json);
        }
        return default_obj;
    },

    commit: function(key, obj) {
        if(key && obj) {
            var json = JSON.stringify(obj);
            cc.sys.localStorage.setItem(key, json);
        }
    }
};
