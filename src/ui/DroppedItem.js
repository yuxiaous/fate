/**
 * Created by yuxiao on 15/3/26.
 */


var DroppedItem = ui.GuiWidgetBase.extend({
    _guiFile: "ui/DroppedItem.json",

    ctor: function(id,dropType) {
        this._super();
        this._id = id;

       // this._dropItemType = ItemType_;

        this._dropType = DroppedItem.DropType.ItemType;
        if(dropType != undefined){
            this._dropType = dropType;
        }

        this._ItemType = DroppedItem.ItemType.GoldType;

        var config = configdb.item[this._id];
        if(config && config.goldtype){
            LOG("drop type----");
            this._ItemType = config.goldtype;
        }
    },

    onEnter: function() {
        this._super();
        this._img_icon = this.seekWidgetByName("img_icon");
        this._img_icon.setVisible(false);

        var config = configdb.item[this._id];
        if(config == undefined) {
            return;
        }

        //// icon
        //if(config.icon){
        //    this._img_icon.loadTexture(config.icon);
        //}

        if(this._dropType == DroppedItem.DropType.DaBaoJianType){
            var dabaojian = dragonBones.DragonBonesHelper.buildArmatureNode("dabaojian");
            dabaojian.gotoAndPlay("daiji");
            this.addChild(dabaojian);
        }
        else{

            var playString = "bai";
            var drgonStr = "cailiao";

            switch (this._ItemType){
                case DroppedItem.ItemType.GoldType :
                    playString = "daiji";
                    drgonStr = "jinbi"
                    break;
                case  DroppedItem.ItemType.WhiteType :
                    playString = "bai";
                    break;

                case  DroppedItem.ItemType.GreenType :
                    playString = "lv";
                    break;
                case  DroppedItem.ItemType.PurpleType :
                    playString = "zi";
                    break;
                case  DroppedItem.ItemType.OrangeType :
                    playString = "cheng";
                    break;
            }

            this._drop_ani =  dragonBones.DragonBonesHelper.buildArmatureNode(drgonStr);
            this._drop_ani.gotoAndPlay(playString);
            this._drop_ani.setPosition(0,0);
            this._drop_ani.setAnchorPoint(0.5,0.5);
            this.addChild(this._drop_ani);

            this._iconShakeAction = this._drop_ani.runAction(cc.repeatForever(cc.sequence(
                cc.moveBy(0.5, cc.p(0, 10)),
                cc.moveBy(0.5, cc.p(0, -10))
            )));

            if(this.itemShadow){
                this.itemShadow.removeFromParent();
                this.itemShadow = null;
            }

            this.itemShadow = cc.Sprite.create("images/shadow1.png");
            var pos = cc.pSub(this._drop_ani.getPosition(),cc.p(0,10));
            this.itemShadow.setPosition(pos);
            var scaleYV =  this._drop_ani.getBoundingBox().width / this.itemShadow.getContentSize().width;
            this.itemShadow.setScaleX(scaleYV);
            this.addChild(this.itemShadow,-1,-1);

        }
    },

    onExit: function() {
        this._img_icon = null;
        this._drop_ani = null;
        this._itemFlyAction = null;
        this._dabaojianPanel = null;
        this.itemShadow = null;

        this._super();
    },

    entranceBuyEquipSuit : function (target_,curScene_) {
        this._dabaojianPanel = new GiftDetailWeapon(true);
        this._dabaojianPanel.setCloseCallback(function() {
            curScene_._isEnteringEquipSuit = false;
            curScene_._enterDropUi = 0;
        }, this);
        this._dabaojianPanel.pop();


        //cc.director.pause();
        //notification.emit(notification.event.GAME_PAUSE);
    },

    flyToTarget: function(target) {

        if(this._iconShakeAction) {
            this._img_icon.stopAction(this._iconShakeAction);
            this._iconShakeAction = null;
        }

        if(this._itemFlyAction == null) {

            var endPos = MapSystem.instance.getGameMapPos();
            var winSize = cc.director.getWinSize();
            endPos = cc.p(- endPos.x + 90,winSize.height - 90);

            this._itemFlyAction = this.runAction(cc.sequence(
                cc.callFunc(function () {
                    if(this.itemShadow){
                        this.itemShadow.removeFromParent();
                        this.itemShadow = null;
                    }
                },this),
                cc.moveTo(0.3, endPos),
                cc.callFunc(function() {
                    //var config = configdb.item[this._id];
                    //if(config && config.result_value != undefined){
                    //    if(this._dropType == DroppedItem.ItemType.BloodType){
                    //        var addValue = target.roleDataManager.maxHp * config.result_value;
                    //        addValue = Math.floor(addValue);
                    //        target.roleDataManager.hp += addValue;
                    //        if(target.roleDataManager.hp > target.roleDataManager.maxHp){
                    //            target.roleDataManager.hp = target.roleDataManager.maxHp;
                    //        }
                    //        UiEffect.addMpOrHpParticle(target,true);
                    //    }
                    //    else if(this._dropType == DroppedItem.ItemType.MagicType){
                    //        var addValue = target.roleDataManager.maxMp * config.result_value;
                    //        addValue = Math.floor(addValue);
                    //        target.roleDataManager.mp += addValue;
                    //        addValue = Math.floor(addValue);
                    //        if(target.roleDataManager.mp > target.roleDataManager.maxMp){
                    //            target.roleDataManager.mp = target.roleDataManager.maxMp;
                    //        }
                    //        UiEffect.addMpOrHpParticle(target,false);
                    //    }
                    //}
                    notification.emit(notification.event.ITEM_DISAPPEAR, this);
                }, this)
            ));
        }
    }
});

DroppedItem.ItemType = {
    GoldType : 1,

    WhiteType : 2,
    GreenType : 3,
    PurpleType : 4,
    OrangeType : 5

};

DroppedItem.DropType = {
    ItemType  : 10,
    DaBaoJianType : 20
}

//var DaBaoJianLayer = ui.GuiWindowBase.extend({
//    _guiFile: "ui/DaBaoJianLayer.json",
//
//    ctor: function (closeCallFunc_,target_) {
//        this._super();
//        this._callFunc = closeCallFunc_;
//        this._target = target_;
//    },
//
//    onEnter: function () {
//        this._super();
//    },
//
//    onExit : function () {
//        this._super();
//    },
//
//    _on_btn_enter : function () {
//        //cc.director.resume();
//        notification.emit(notification.event.GAME_RESUME);
//        this.removeFromParent();
//
//        this._callFunc.apply(this._target);
//    },
//
//    _on_btn_back : function () {
//        //cc.director.resume();
//        notification.emit(notification.event.GAME_RESUME);
//        this.removeFromParent();
//        this._callFunc.apply(this._target);
//    }
//});

