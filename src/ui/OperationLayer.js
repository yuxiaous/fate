/**
 * Created by yuxiao on 14/12/27.
 */


var OperationLayer = cc.Layer.extend({
    ctor: function() {
        this._super();

        var winSize = cc.director.getWinSize();
        var sprite;



        var allBtnPos = {
            left : {
                joystick   : cc.p(winSize.width - 190 , 130),
                atkBtn     : cc.p(100,95),
                skillBtn_1 : cc.p(250,95),
                skillBtn_2 : cc.p(200,200),
                skillBtn_3 : cc.p(100,250),
                skillBtn_4 : cc.p(320,195),
                skillBtn_5 : cc.p(360,95)
            },
            right : {
                joystick   : cc.p(190,130),
                atkBtn     : cc.p(winSize.width - 130, 100),
                skillBtn_1 : cc.p(winSize.width - 262, 177),
                skillBtn_2 : cc.p(winSize.width - 185, 241),
                skillBtn_3 : cc.p(winSize.width - 89, 246),
                skillBtn_4 : cc.p(winSize.width - 380, 81),
                skillBtn_5 : cc.p(winSize.width - 282, 81)
            }
        }
        var curStylePos = allBtnPos.right;
        var operStyle = cc.sys.localStorage.getItem("OperatyBtn")
        if(cc.sys.localStorage.getItem("OperatyBtn") == "LEFT"){
            curStylePos = allBtnPos.left;
        }



        // joystick
        this._joystick = this.addJoystick(
            new cc.Sprite(this.getFP("joystick2.png")),
            new cc.Sprite(this.getFP("joystick1.png")),
            new cc.Sprite(this.getFP("joystick4.png")),
            new cc.Sprite(this.getFP("joystick3.png")),
            curStylePos.joystick,
            cc.rect(-190, -120, 500, 350)
        );

        // button function

        function compoundDisableBtnSprite(resName,coverName){
            var tmpSprite = new cc.Sprite(resName);
            var covSprite = new cc.Sprite(coverName);
            var covProgress = new cc.ProgressTimer(covSprite);
            covProgress.setType(cc.ProgressTimer.TYPE_RADIAL);
            covProgress.setPercentage(100);
            var tmpSize = tmpSprite.getContentSize();
            covProgress.setPosition(cc.p(tmpSize.width/2,tmpSize.height/2));
            covProgress.setAnchorPoint(cc.p(0.5,0.5));
            covProgress.setScaleX(-1);
            tmpSprite.addChild(covProgress);
            tmpSprite.coverProgress = covProgress;
            return tmpSprite;
        }

        // attack button
        //var sprite = new cc.Sprite("res/joybutton2.png");
        //sprite.setScale(1.2);
        this._attackButton = this.addButton(
            new cc.Sprite(this.getFP("joybutton1.png")),
            sprite = new cc.Sprite(this.getFP("joybutton2.png")),
            new cc.Sprite(this.getFP("joybutton1.png")),
            curStylePos.atkBtn
        );
        sprite.setScale(1.2);

        // skill button 1
        this._skillButton1 = this.addButton(
            new cc.Sprite(this.getFP("skill1.png")),
            new cc.Sprite(this.getFP("skill1.png")),
            compoundDisableBtnSprite(this.getFP("skill1.png"),this.getFP("diableskill.png")),
            curStylePos.skillBtn_1
        );

        // skill button 2
        this._skillButton2 = this.addButton(
            new cc.Sprite(this.getFP("skill4.png")),
            new cc.Sprite(this.getFP("skill4.png")),
            compoundDisableBtnSprite(this.getFP("skill4.png"),this.getFP("diableskill.png")),
            curStylePos.skillBtn_2
        );

        // skill button 3
        this._skillButton3 = this.addButton(
            new cc.Sprite(this.getFP("skill2.png")),
            new cc.Sprite(this.getFP("skill2.png")),
            compoundDisableBtnSprite(this.getFP("skill2.png"),this.getFP("diableskill.png")),
            curStylePos.skillBtn_3
        );

        //skill button 4
        this._skillButton4 = this.addButton(
            new cc.Sprite(this.getFP("skill3.png")),
            new cc.Sprite(this.getFP("skill3.png")),
            compoundDisableBtnSprite(this.getFP("skill3.png"),this.getFP("diableskill.png")),
            curStylePos.skillBtn_4
        );

        //skill button 5
        this._skillButton5 = this.addButton(
            new cc.Sprite(this.getFP("skill5.png")),
            new cc.Sprite(this.getFP("skill5.png")),
            compoundDisableBtnSprite(this.getFP("skill5.png"),this.getFP("diableskill.png")),
            curStylePos.skillBtn_5
        );
    },

    getFP: function(name_){
        return "images/icon/skill/"+name_;
    },

    setEnable: function(enable) {
        this._joystick.setIsEnable(enable);
        this._attackButton.setIsEnable(enable);
        this._skillButton1.setIsEnable(enable);
        this._skillButton2.setIsEnable(enable);
        this._skillButton3.setIsEnable(enable);
        this._skillButton4.setIsEnable(enable);
        this._skillButton5.setIsEnable(enable);
    },

    setHide : function (isHide_) {
        this.setVisible(isHide_);
        this._joystick.setIsEnable(isHide_);

        this._curIsHide = isHide_;

        if(!this._attackButton.isCounting) this._attackButton.setIsEnable(isHide_);
        if(!this._skillButton1.isCounting) this._skillButton1.setIsEnable(isHide_);
        if(!this._skillButton2.isCounting) this._skillButton2.setIsEnable(isHide_);
        if(!this._skillButton3.isCounting) this._skillButton3.setIsEnable(isHide_);
        if(!this._skillButton4.isCounting) this._skillButton4.setIsEnable(isHide_);
        if(!this._skillButton5.isCounting) this._skillButton5.setIsEnable(isHide_);
    },

    setBtnTimingEnable : function (btnIdx_,times_) {
        switch (btnIdx_){
            case 1 :
                btnCountDown(this._skillButton1,times_);
                break;
            case 2 :
                btnCountDown(this._skillButton2,times_);
                break;
            case  3 :
                btnCountDown(this._skillButton3,times_);
                break;
            case  4 :
                btnCountDown(this._skillButton4,times_);
                break;
            case  5 :
                btnCountDown(this._skillButton5,times_);
                break;
            default :
                break;
        }

        var that = this;
        function btnCountDown(btn_,time_){
            if(time_ <= 0 || btn_.isCounting){
                return;
            }
            btn_.setIsEnable(false);
            btn_.isCounting = true;
            var tmpTime = time_ * 10;
            var label = cc.LabelTTF.create(String(tmpTime / 10));
            label.setFontSize(30);
            label.setTag(100);
            btn_.addChild(label);

            //rotate progress
            var covPro = btn_.btnSkinned.getDisabledSprite().coverProgress;
            var everyValue = 100 / tmpTime;
            function refreshLabelAnthor(){
                var curPercent = covPro.getPercentage();
                curPercent -= everyValue;
                covPro.setPercentage(curPercent);

                tmpTime -= 1;
                if(tmpTime == 0){
                    btn_.unschedule(refreshLabelAnthor);
                    btn_.isCounting = false;
                    if(that._curIsHide) btn_.setIsEnable(true);
                    covPro.setPercentage(100);
                    btn_.removeChildByTag(100);
                }
                else if(tmpTime < 10){
                    label.setString(String(tmpTime / 10));
                }
                else{
                    if(tmpTime % 10 == 0){
                        label.setString(String(tmpTime / 10));
                    }
                }
            }

            btn_.schedule(refreshLabelAnthor,0.1);
        }
    },

    setBtnMpIsNotEnough : function (btnIdx_,isEnough_) {
        switch (btnIdx_){
            case RoleAction.Type.SKILL1 :
                btnFunc(this._skillButton1,isEnough_);
                break;
            case RoleAction.Type.SKILL2 :
                btnFunc(this._skillButton2,isEnough_);
                break;
            case RoleAction.Type.SKILL3 :
                btnFunc(this._skillButton3,isEnough_);
                break;
            case RoleAction.Type.SKILL4 :
                btnFunc(this._skillButton4,isEnough_);
                break;
            case RoleAction.Type.SKILL5 :
                btnFunc(this._skillButton5,isEnough_);
                break;
            default :
                break;
        }
        function btnFunc(btn_,isE_){
            if(!btn_.isCounting){
                btn_.setIsEnable(isE_);
            }
        }
    },

    addJoystick: function(sp1, sp2, sp3, sp4, pos, area) {
        if(sp1 == null || sp3 == null)
            return null;

        var joystickBase = jsb.SneakyJoystickSkinnedBase.create();
        joystickBase.setPosition(pos);
        joystickBase.setBackgroundSprite(sp1, sp2);
        joystickBase.setThumbSprite(sp3, sp4);
        this.addChild(joystickBase);

        var joystick = jsb.SneakyJoystick.create(sp1.getContentSize(), sp3.getContentSize());
        joystick.setTouchArea(area);
        joystick.setIsConstantVelocity(true);
        joystickBase.setJoystick(joystick);
        return joystick;
    },

    addButton: function(sp1, sp2, sp3, pos) {
        if(sp1 == null)
            return null;

        var buttonBase = jsb.SneakyButtonSkinnedBase.create();
        buttonBase.setPosition(pos);
        buttonBase.setDefaultSprite(sp1);
        if(sp2) buttonBase.setPressSprite(sp2);
        if(sp3) buttonBase.setDisabledSprite(sp3);
        this.addChild(buttonBase);

        var button = jsb.SneakyButton.create(sp1.getContentSize());
        button.setIsHoldable(true);
        buttonBase.setButton(button);
        button.btnSkinned = buttonBase;
        button.isCounting = false;
        return button;
    }
});

