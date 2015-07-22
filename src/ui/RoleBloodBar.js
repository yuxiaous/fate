/**
 * Created by shilei on 15/4/09.
 */


var RoleBloodBar = ui.GuiWidgetBase.extend({
    _guiFile: "res/ui/BloodBar.json",

    ctor: function(maxValue_,curValue_) {
        this._super();
        this._maxValue = maxValue_;
        this._curValue = curValue_;
    },

    onEnter: function() {
        this._super();
        this._bloodBarPro = this.seekWidgetByName("bloodBarPro");
        this._bloodBarPro.setPercent(100);

        this.refreshBloodBarPer(this._maxValue, this._curValue);
    },

    updateBloodBar : function () {
    },

    onExit: function() {
        this._bloodBarPro = null;
        this._super();
    },

    refreshBloodBarPer : function(maxValue_,curValue_){
        this._maxValue = maxValue_;
        this._curValue = curValue_;

        var tmpPercent = this._curValue / this._maxValue * 100;
        RoleBloodBar.setPercentChangeTo(Math.floor(tmpPercent),this._bloodBarPro,5);
    }
});

RoleBloodBar.setPercentChangeTo = function(finalValue_,loadNode_,changeValue_){
    finalValue_ = Math.floor(finalValue_);

    var everyChangeValue = 0.5;
    if(changeValue_){
        everyChangeValue = changeValue_;
    }
    var curValue_ = loadNode_.getPercent();
    var isIncreace = false;
    if(finalValue_ > curValue_){
        isIncreace = true;
    }
    else if(finalValue_ == curValue_){
        return;
    }

    function updateBloodBar(){
        var curIsDone = false;

        if(isIncreace && loadNode_.getPercent() >= finalValue_){
            curIsDone = true;
        }
        if(!isIncreace && loadNode_.getPercent() <= finalValue_){
            curIsDone = true;
        }

        if(curIsDone){
            loadNode_.unschedule(updateBloodBar);
            return;
        }

        var curPer = loadNode_.getPercent();
        var nextPer = 0;
        if(isIncreace){
            nextPer = curPer + everyChangeValue;
        }
        else{
            nextPer = curPer - everyChangeValue;
        }
        loadNode_.setPercent(nextPer);
    }
    loadNode_.schedule(updateBloodBar,1/15);
}

