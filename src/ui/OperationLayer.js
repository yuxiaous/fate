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

        var isArcher = false;
        var skin = SkinSystem.instance.use_skin;
         if(skin == 103){
            isArcher = true;
        }

        if(BattleSystem.instance.curIsTryBattle()){
            var tmpHero = BattleSystem.instance.getTryBattleHero()
            if(tmpHero == Archer ){
                isArcher = true;
            }
        }

        // skill button 1
        var skill_1_str = "skill1.png";
        if(isArcher) skill_1_str = "skill1_1.png";
        this._skillButton1 = this.addButton(
            new cc.Sprite(this.getFP(skill_1_str)),
            new cc.Sprite(this.getFP(skill_1_str)),
            compoundDisableBtnSprite(this.getFP(skill_1_str),this.getFP("diableskill.png")),
            curStylePos.skillBtn_1,
            false,
            1
        );

        // skill button 2
        var skill_2_str = "skill4.png";
        if(isArcher) skill_2_str = "skill4_1.png";
        this._skillButton2 = this.addButton(
            new cc.Sprite(this.getFP(skill_2_str)),
            new cc.Sprite(this.getFP(skill_2_str)),
            compoundDisableBtnSprite(this.getFP(skill_2_str),this.getFP("diableskill.png")),
            curStylePos.skillBtn_2,
            false,
            2
        );

        // skill button 3
        var skill_3_str = "skill2.png";
        if(isArcher) skill_3_str = "skill2_1.png";
        this._skillButton3 = this.addButton(
            new cc.Sprite(this.getFP(skill_3_str)),
            new cc.Sprite(this.getFP(skill_3_str)),
            compoundDisableBtnSprite(this.getFP(skill_3_str),this.getFP("diableskill.png")),
            curStylePos.skillBtn_3,
            false,
            3
        );

        var needDisplayCount = true;
        if(BattleSystem.instance.curIsTryBattle()){
            needDisplayCount = false;
        }

        //skill button 4
        var skill_4_str = "skill3.png";
        if(isArcher) skill_4_str = "skill3_1.png";
        this._skillButton4 = this.addButton(
            new cc.Sprite(this.getFP(skill_4_str)),
            new cc.Sprite(this.getFP(skill_4_str)),
            compoundDisableBtnSprite(this.getFP(skill_4_str),this.getFP("diableskill.png")),
            curStylePos.skillBtn_4,
            needDisplayCount,
            4
        );

        //skill button 5
        this._skillButton5 = this.addButton(
            new cc.Sprite(this.getFP("skill5.png")),
            new cc.Sprite(this.getFP("skill5.png")),
            compoundDisableBtnSprite(this.getFP("skill5.png"),this.getFP("diableskill.png")),
            curStylePos.skillBtn_5,
            false,
            5
        );
    },

    onEnter : function () {
        this._super();

        this._bindings = [
            notification.createBinding(notification.event.OPERATION_TRIGGER, function (event_,data_) {
                var tmpData = data_;
                var scene = cc.director.getRunningScene();
                var curHero = scene._hero;

                var cdTime = tmpData.ActionData.cdTime;
                if(/*BattleSystem.instance.curIsTryBattle() && */tmpData.SkillType == RoleAction.Type.SKILL4){
                    cdTime = configdb.property[109].value;
                }

                scene._operator.setBtnTimingEnable(tmpData.SkillId,cdTime);

                //refresh mp
                var curCost = SkillSystem.instance.getSkillUpMpcost(tmpData.SkillType);
                curHero.roleDataManager.mp -= curCost;

                if( GuideSystem.instance.getSkillIsNotGuided(tmpData.SkillType) && BattleSystem.instance.curIsTryBattle() ){
                    var skillGuide = new SkillGuidePanel(tmpData.SkillType, function () {
                        notification.emit(notification.event.GAME_RESUME);
                        skillGuide.close();
                    },this);
                    skillGuide.pop();
                    notification.emit(notification.event.GAME_PAUSE);
                }

            },this)
        ]
    },

    onExit : function () {

        notification.removeBinding(this._bindings);
        this._super();
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

    setBtnReleaseCount : function (btnIdx_,count_) {
        switch (btnIdx_){
            case 1 :
                btnReleaseCount(this._skillButton1,count_);
                break;
            case 2 :
                btnReleaseCount(this._skillButton2,count_);
                break;
            case  3 :
                btnReleaseCount(this._skillButton3,count_);
                break;
            case  4 :
                btnReleaseCount(this._skillButton4,count_);
                break;
            case  5 :
                btnReleaseCount(this._skillButton5,count_);
                break;
            default :
                break;
        }

        function btnReleaseCount(btn_,counts_) {
            if(btn_ == undefined) {
                return;
            }
            if(!btn_.needUseCount){
                return;
            }
            btn_.releaseCount = counts_;
            //if(btn_.releaseCountLabel) {
            //    btn_.releaseCountLabel.setString(btn_.releaseCount);
            //}
            if(btn_.fontBg) {
                btn_.fontBg.setVisible(counts_ <= 0);
            }
        }
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
                //if(PlayerSystem.instance.level < 100){
                //    LOG("player system instance = " + PlayerSystem.instance.level);
                //
                //    btnDisableWithLevel(this._skillButton3);
                //}
                //else{
                //    LOG("888888");
                //
                //}
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
            var covPro =  btn_.btnSkinned.coverProgress;
            var everyValue = 100 / tmpTime;
            function refreshLabelAnthor(){
                var curPercent = covPro.getPercentage();
                curPercent -= everyValue;
                covPro.setPercentage(curPercent);

                tmpTime -= 1;
                if(tmpTime == 0){
                    btn_.unschedule(refreshLabelAnthor);
                    btn_.isCounting = false;
                    if(that._curIsHide){
                        btn_.setIsEnable(true);
                    }
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

        function btnDisableWithLevel(btn_){
            var covPro = btn_.btnSkinned.coverProgress;
            btn_.setIsEnable(false);
            covPro.setPercentage(100);
            covPro.setVisible(true);
        }

    },

    setBtnDisableWithLevel : function (btnIdx_) {
        switch (btnIdx_){
            case RoleAction.Type.SKILL1  :
                btnDisableWithLevel(this._skillButton1);
                break;
            case RoleAction.Type.SKILL2  :
                btnDisableWithLevel(this._skillButton2);
                break;
            case  RoleAction.Type.SKILL3  :
                btnDisableWithLevel(this._skillButton3);
                break;
            case  RoleAction.Type.SKILL4  :
                btnDisableWithLevel(this._skillButton4);
                break;
            case  RoleAction.Type.SKILL5  :
                btnDisableWithLevel(this._skillButton5);
                break;
            default :
                break;
        }

        function btnDisableWithLevel(btn_){
            var covPro = btn_.btnSkinned.coverProgress;
            btn_.setIsEnable(false);
            covPro.setPercentage(100);

            btn_.lockIcon.setVisible(true);

            btn_.btnSkinned.setVisible(false);
        }

    },

    setBtnTimingPause : function (btnIdx_,isPause_) {
        var btn = null;
        switch (btnIdx_){
            case 1 :
                btn = this._skillButton1;
                break;
            case 2 :
                btn = this._skillButton2;
                break;
            case  3 :
                btn = this._skillButton3;
                break;
            case  4 :
                btn = this._skillButton4;
                break;
            case  5 :
                btn = this._skillButton5;
                break;
            default :
                break;
        }

        if(btn){
            if(isPause_){
                LOG("is pause");
                btn.pause();
            }
            else{
                LOG("is resume");
                btn.resume();
            }
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

    setSkillBtnOpenEffect : function () {

        function btnOpenEffect(btn_,hadLastEffect_){
            var waitTime = 0.5;
            if(hadLastEffect_){
                waitTime = 1.0;
            }

            var btnSkin = btn_.btnSkinned;
            var pos = btnSkin.getPosition();
            var sinSize = cc.director.getWinSize();
            var startPos = cc.p(60,sinSize.height - 60);


            btnSkin.setPosition(startPos);
            btnSkin.setVisible(true);

            btnSkin.runAction(cc.Sequence.create(
                cc.DelayTime.create(waitTime),
                cc.MoveTo.create(1.0,pos),
                cc.CallFunc.create(function(){
                    UiEffect.addSkillUpdateEffect(btnSkin);
                })
            ));
        }

        var curSkillIsOpen = false;
        var roleLevel = PlayerSystem.instance.level;

        var isOpened = jsb.JsonStorage.GetInstance(LoginSystem.settingFile).getBoolForKey(GuideSystem.SkillOpen.SKILL_2);
        if(roleLevel >= configdb.property[113].value && isOpened == false){
            jsb.JsonStorage.GetInstance(LoginSystem.settingFile).setBoolForKey(GuideSystem.SkillOpen.SKILL_2,true);
            jsb.JsonStorage.GetInstance(LoginSystem.settingFile).flush();

            btnOpenEffect(this._skillButton2,curSkillIsOpen);

            curSkillIsOpen = true;
        }

        isOpened = jsb.JsonStorage.GetInstance(LoginSystem.settingFile).getBoolForKey(GuideSystem.SkillOpen.SKILL_3);

        if(roleLevel >= configdb.property[114].value && isOpened == false){
            jsb.JsonStorage.GetInstance(LoginSystem.settingFile).setBoolForKey(GuideSystem.SkillOpen.SKILL_3,true);
            jsb.JsonStorage.GetInstance(LoginSystem.settingFile).flush();

            btnOpenEffect(this._skillButton3,curSkillIsOpen);

        }






    },

    addJoystick: function(sp1, sp2, sp3, sp4, pos, area) {
        if(sp1 == null || sp3 == null)
            return null;

        //var joystickBase = jsb.SneakyJoystickSkinnedBase.create();
        //joystickBase.setPosition(pos);
        //joystickBase.setBackgroundSprite(sp1, sp2);
        //joystickBase.setThumbSprite(sp3, sp4);
        //this.addChild(joystickBase);
        //
        //var joystick = jsb.SneakyJoystick.create(sp1.getContentSize(), sp3.getContentSize());
        //joystick.setTouchArea(area);
        //joystick.setIsConstantVelocity(true);
        //joystickBase.setJoystick(joystick);

        var joystick = jsb.Joystick.create(sp1.getContentSize(), sp3.getContentSize());
        joystick.setBackgroundSprite(sp1, sp2);
        joystick.setThumbSprite(sp3, sp4);
        joystick.setTouchArea(area);
        joystick.setPosition(pos);
        this.addChild(joystick);

        return joystick;
    },

    addButton: function(sp1, sp2, sp3, pos,needUseCount_,skill_idx_) {
        if(sp1 == null)
            return null;

        var buttonBase = jsb.SneakyButtonSkinnedBase.create();
        buttonBase.setPosition(pos);
        buttonBase.setDefaultSprite(sp1);
        if(sp2) buttonBase.setPressSprite(sp2);
        if(sp3) {
            buttonBase.setDisabledSprite(sp3);
            buttonBase.coverProgress = sp3.coverProgress;
        }
        this.addChild(buttonBase);

        var button = jsb.SneakyButton.create(sp1.getContentSize());
        button.setIsHoldable(true);
        buttonBase.setButton(button);
        button.btnSkinned = buttonBase;
        button.isCounting = false;

        //var button = jsb.Joybutton.create(sp1.getContentSize());
        //button.setDefaultSprite(sp1);
        //if(sp2) button.setPressSprite(sp2);
        //if(sp3) {
        //    button.setDisabledSprite(sp3);
        //    button.coverProgress = sp3.coverProgress;
        //}
        //button.setPosition(pos);
        //this.addChild(button);
        //button.btnSkinned = button;
        //button.isCounting = false;


        var fontBg = cc.Sprite.create("images/code_ui/ui_329.png");
        button.addChild(fontBg);

        //var releaseCount = ccui.TextBMFont.create("0","res/fonts/fnt_10.fnt");
        //var buttonSize = sp1.getContentSize();
        //releaseCount.setPosition(cc.p(11,-buttonSize.height * 0.25));
        //button.addChild(releaseCount);
        button.releaseCount = 0;
        //button.releaseCountLabel = releaseCount;
        button.fontBg = fontBg;

        needUseCount_ = false || needUseCount_;
        button.needUseCount = needUseCount_;
        //button.releaseCountLabel.setVisible(button.needUseCount);
        button.fontBg.setVisible(button.needUseCount);

        var lockBg = ccui.ImageView.create("images/icon/skill/skill_lock.png");
        button.addChild(lockBg);
        lockBg.setVisible(false);
        button.lockIcon = lockBg;

        if(skill_idx_!= undefined){
            var num = 0;
            if(skill_idx_ == 2){
                num = configdb.property[113].value;
            }
            else if(skill_idx_ == 3){
                num = configdb.property[114].value;
            }
            var strLock = "等级 " + num + "开启";
        }

        lockBg.setTouchEnabled(true);
        lockBg.addTouchEventListener(function (touch,event) {
            if(event == ccui.Widget.TOUCH_ENDED){
                UiEffect.showFloatLabel(strLock);
            }
        });


        return button;
    }
});

