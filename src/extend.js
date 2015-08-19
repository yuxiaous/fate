/**
 * Created by yuxiao on 14/12/24.
 */


String.prototype.format = function(args) {
    var result = this,
        reg;

    if (arguments.length > 0) {
        if (arguments.length == 1 && typeof (args) == "object") {
            for (var key in args) {
                if(args.hasOwnProperty(key)) {
                    reg = new RegExp("({)" + key + "(})", "g");
                    result = result.replace(reg, args[key]);
                }
            }
        }
        else {
            for (var i = 0; i < arguments.length; i++) {
                if (arguments[i] != undefined) {
                    reg= new RegExp("({)" + i + "(})", "g");
                    result = result.replace(reg, arguments[i]);
                }
            }
        }
    }
    return result;
};


Object.prototype.Clone = function(){
    var objClone;
    if (this.constructor == Object){
        objClone = new this.constructor();
    }else{
        objClone = new this.constructor(this.valueOf());
    }
    for(var key in this){
        if ( objClone[key] != this[key] ){
            if ( typeof(this[key]) == 'object' ){
                objClone[key] = this[key].Clone();
            }else{
                objClone[key] = this[key];
            }
        }
    }
    objClone.toString = this.toString;
    objClone.valueOf = this.valueOf;
    return objClone;
};