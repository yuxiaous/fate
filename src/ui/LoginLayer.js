

//var LoginRewardLayer = ui.GuiWindowBase.extend({
//    _guiFile: "ui/LoginRewardLayer.json",
//
//    ctor: function (login_index_) {
//        this._super();
//
//        this._curIdx = login_index_;
//    },
//
//    onEnter : function () {
//        this._super();
//
//        this._allRewardItems = [];
//        _.each(["ProjectNode_1",
//                "ProjectNode_2",
//                "ProjectNode_3",
//                "ProjectNode_4",
//                "ProjectNode_5"], function (str_,idx_) {
//            var _rewardPanel = new LoginRewardLayer.RewardPanel(idx_+1,this._curIdx,this);
//            _rewardPanel.setWidget(this.seekWidgetByName(str_));
//            this._allRewardItems.push(_rewardPanel);
//        },this);
//     },
//
//    onExit : function () {
//        _.each(this._allRewardItems, function (item_) {
//            if(item_){
//                item_.setWidget(null);
//            }
//        });
//
//        this._allRewardItems = null;
//        this._super();
//    },
//
//    _on_btn_close : function () {
//        this.close();
//    },
//
//    _on_btn_get : function () {
//        LOG("btn get");
//        notification.emit(notification.event.GET_LOGIN_REWARD);
//    }
//});

//LoginRewardLayer.RewardPanel = ui.GuiController.extend({
//    ctor: function (idx_,curRewardIdx_,target_) {
//        this._super();
//
//        this._target = target_;
//        this._loginIdx = idx_;
//        this._curRewardIdx = curRewardIdx_;
//
//        this._getRewardAction = false;
//        _.each(configdb.loginreward, function (data_) {
//            if(data_.index == this._loginIdx){
//                this._rewardData = data_;
//            }
//        },this)
//    },
//
//    onEnter: function () {
//        this._super();
//
//        this._ui = {
//            getRewardCover : this.seekWidgetByName("reward_cover"),
//            curSelectPanel : this.seekWidgetByName("reward_selected"),
//            lblDay         : this.seekWidgetByName("lbl_reward_day"),
//            lblRewardNum   : this.seekWidgetByName("lbl_reward_num"),
//            rewardIcon     : this.seekWidgetByName("reward_icon")
//        }
//
//        this._ui.lblDay.setString(this._ui.lblDay._str_original.format(this._rewardData.index));
//        this._ui.lblRewardNum.setString(String("X "+this._rewardData.num));
//        this._ui.rewardIcon.loadTexture(this._rewardData.icon);
//
//
//
//        var curSelect = false;
//        var getReward = false;
//        if(this._curRewardIdx < this._loginIdx){
//
//        }
//        else if(this._curRewardIdx == this._loginIdx){
//            curSelect = true;
//        }
//        else{
//            getReward = true;
//        }
//
//        this._ui.curSelectPanel.setVisible(curSelect);
//        this._ui.getRewardCover.setVisible(getReward);
//
//
//
//        this._bindings = [
//            notification.createBinding(notification.event.GET_LOGIN_REWARD, this.playGetRewardEffet,this)
//        ]
//    },
//
//    onExit : function () {
//        this._ui = null;
//
//        notification.removeBinding(this._bindings);
//        this._super();
//    },
//
//    playGetRewardEffet : function () {
//        if(this._curRewardIdx == this._loginIdx && !this._getRewardAction){
//            this._getRewardAction = true;
//            this._ui.getRewardCover.setVisible(true);
//            UiEffect.iconSealEffect_Rotate(this._ui.getRewardCover, function () {
//                this._target.close();
//            },this);
//        }
//    }
//});

var LoginRewardLayer = ui.GuiWindowBase.extend({
    _guiFile: "ui/login_reward_panel.json",

    ctor: function (login_index_) {
        this._super();

        this._curIdx = login_index_;
    },

    onEnter : function () {
        this._super();

        this._curCoverIcon = null;
        _.each(["get_cover_1",
                "get_cover_2",
                "get_cover_3",
                "get_cover_4",
                "get_cover_5"], function (str_,idx_) {
                var tmpIcon = this.seekWidgetByName(str_);
                tmpIcon.setVisible(false);
                if(idx_ + 1 == this._curIdx) {
                    this._curCoverIcon = tmpIcon;
                }
        },this);

        this._login_label = this.seekWidgetByName("lbl_login_index");

        this._login_label.setString(String(this._curIdx));
    },

    onExit : function () {
        this._login_label = null;
        this._super();
    },

    _on_btn_close : function () {
        this.close();
    },

    _on_btn_get : function () {
        this._curCoverIcon.setVisible(true);
        UiEffect.iconSealEffect_Rotate(this._curCoverIcon, function () {
            this.close();
        },this);
    }
});