/**
 * Created by yuxiao on 15/3/26.
 */


var DroppedItem = ui.GuiWidgetBase.extend({
    _guiFile: "ui/DroppedItem.json",

    ctor: function(id,ItemType_) {
        this._super();
        this._id = id;
        this._dropItemType = ItemType_;
    },

    onEnter: function() {
        this._super();
        this._img_icon = this.seekWidgetByName("img_icon");

        var config = configdb.item[this._id];
        if(config == undefined) {
            return;
        }

        // icon
        if(config.icon){
            this._img_icon.loadTexture(config.icon);
        }

        if(this._dropItemType == DroppedItem.ItemType.ItemType){
            this._img_icon.setVisible(false);
            var dabaojian = dragonBones.DragonBonesHelper.buildArmatureNode("dabaojian");
            dabaojian.gotoAndPlay("daiji");
            this.addChild(dabaojian);
        }
        else{
            this._iconShakeAction = this._img_icon.runAction(cc.repeatForever(cc.sequence(
                cc.moveBy(0.5, cc.p(0, 10)),
                cc.moveBy(0.5, cc.p(0, -10))
            )));

            var itemShadow = cc.Sprite.create("images/shadow1.png");
            // itemShadow.setLocalZOrder(-1);
            itemShadow.setPosition(cc.p(this._img_icon.getPosition().x,this._img_icon.getPosition().y - this._img_icon.getContentSize().height/2 - 15));
            var scaleYV = itemShadow.getContentSize().width / this._img_icon.getContentSize().width;
            //cc.log("scale yv = " + scaleYV);
            itemShadow.setScaleX(scaleYV);
            this.addChild(itemShadow);
        }
    },

    onExit: function() {
        this._img_icon = null;
        this._itemFlyAction = null;
        this._dabaojianPanel = null;
        this._super();
    },

    entranceBuyEquipSuit : function (target_,curScene_) {
        var giftId = 101002;
        if(util.getChannelId() == GameChannel.CmccMm) {
            giftId += 200000;
        }

         this._dabaojianPanel = new GiftBuyDetail(GiftSystem.GiftType.WuQi,101002, this,function () {
            curScene_._isEnteringEquipSuit = false;
            curScene_._enterDropUi = 0;
         });
        this._dabaojianPanel.pop();
        cc.director.pause();
    },

    flyToTarget: function(target) {
        if(this._iconShakeAction) {
            this._img_icon.stopAction(this._iconShakeAction);
            this._iconShakeAction = null;
        }

        if(this._itemFlyAction == null) {
            this._itemFlyAction = this.runAction(cc.sequence(
                cc.moveTo(0.1, cc.p(target.getPositionX(), target.getPositionY() + 100)),
                cc.callFunc(function() {
                    var config = configdb.item[this._id];
                    if(config && config.result_value != undefined){
                        if(this._dropItemType == DroppedItem.ItemType.BloodType){
                            var addValue = target.roleDataManager.maxHp * config.result_value;
                            addValue = Math.floor(addValue);
                            target.roleDataManager.hp += addValue;
                            if(target.roleDataManager.hp > target.roleDataManager.maxHp){
                                target.roleDataManager.hp = target.roleDataManager.maxHp;
                            }
                        }
                        else if(this._dropItemType == DroppedItem.ItemType.MagicType){
                            var addValue = target.roleDataManager.maxMp * config.result_value;
                            addValue = Math.floor(addValue);
                            target.roleDataManager.mp += addValue;
                            addValue = Math.floor(addValue);
                            if(target.roleDataManager.mp > target.roleDataManager.maxMp){
                                target.roleDataManager.mp = target.roleDataManager.maxMp;
                            }
                        }
                    }
                    notification.emit(notification.event.ITEM_DISAPPEAR, this);
                }, this)
            ));
        }
    },

    flyToTarget_particle : function (target) {
        if(this._iconShakeAction) {
            this._img_icon.stopAction(this._iconShakeAction);
            this._img_icon.setVisible(false);
            this._iconShakeAction = null;
        }

        if(this._itemFlyAction == null) {
            var energyP = cc.ParticleSystem.create("res/particles/addBloodP.plist");
            energyP.setPosition(this._img_icon.getPosition());
            this.addChild(energyP);
            var endPos = cc.p(target.getPositionX(), target.getPositionY() + 100);
            this._itemFlyAction = this.runAction(cc.Sequence.create(cc.MoveTo.create(0.5,endPos),
                            cc.CallFunc.create(function () {
                                  energyP.removeFromParent();
                                notification.emit(notification.event.ITEM_DISAPPEAR, this);
                            },this)
                            ));
        }
    }
});

DroppedItem.ItemType = {
    BloodType : 1,
    MagicType : 2,
    EquipType : 3,
    ItemType  : 4,
    DaBaoJianType : 5
};

var DaBaoJianLayer = ui.GuiWindowBase.extend({
    _guiFile: "ui/DaBaoJianLayer.json",

    ctor: function (closeCallFunc_,target_) {
        this._super();
        this._callFunc = closeCallFunc_;
        this._target = target_;
    },

    onEnter: function () {
        this._super();
    },

    onExit : function () {
        this._super();
    },

    _on_btn_enter : function () {
        cc.director.resume();
        this.removeFromParent();

        this._callFunc.apply(this._target);
    },

    _on_btn_back : function () {
        cc.director.resume();
        this.removeFromParent();
        this._callFunc.apply(this._target);
    }
});

