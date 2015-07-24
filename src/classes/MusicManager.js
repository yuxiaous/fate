/*
* shilei
* 2015/04/23
* */

var MusicManager = (function () {
    function Singleton(){
        BGM_KEY = "background_music_volume_key";
        EFF_KEY = "effect_music_volume_key";

        BGM_OPEN = "background_music_is_open_key";
        EFF_OPEN = "effect_music_is_open_key";

        FATE_SETTING = "setting.json";

        this.curPlayType = 0;

        this.setBackgroundMusicVolume = function(volume_){
            //if(isOn_){
            //    this.setBackgroundVolumn(1);
            //}
            //else{
            //    this.setBackgroundVolumn(0);
            //}
            this.setBackgroundVolumn(volume_);
        }

        this.setEffectVolume = function (volume_) {
            //if(isOn_){
            //    this.serEffectVolumn(1);
            //}
            //else{
            //    this.serEffectVolumn(0);
            //}
            this.serEffectVolumn(volume_);

        }

        /*
        *   volumn 0.0 -> 1.0
        * */
        this.setBackgroundVolumn = function(volume_){
            //cc.sys.localStorage.setItem(BGM_KEY,String(volumn_));

            jsb.JsonStorage.GetInstance(FATE_SETTING).setDoubleForKey(BGM_KEY,volume_)
            jsb.JsonStorage.GetInstance(FATE_SETTING).flush();
        }

        this.serEffectVolumn = function(volume_){
            //cc.sys.localStorage.setItem(EFF_KEY,String(volumn_));
            jsb.JsonStorage.GetInstance(FATE_SETTING).setDoubleForKey(EFF_KEY,volume_)
            jsb.JsonStorage.GetInstance(FATE_SETTING).flush();
        }

        this.getBackgroundVolume = function () {

            //return Number(cc.sys.localStorage.getItem(BGM_KEY));
            return jsb.JsonStorage.GetInstance(FATE_SETTING).getDoubleForKey(BGM_KEY);
        }

        this.getEffectVolume = function () {
            //return Number(cc.sys.localStorage.getItem(EFF_KEY));
            return jsb.JsonStorage.GetInstance(FATE_SETTING).getDoubleForKey(EFF_KEY);
        }

        this.setBackgroundMusicIsOpen = function (isOpen_) {
            jsb.JsonStorage.GetInstance(FATE_SETTING).setBoolForKey(BGM_OPEN,isOpen_);
            jsb.JsonStorage.GetInstance(FATE_SETTING).flush();
        },

        this.setEffectMusicIsOpen = function (isOpen_) {
            jsb.JsonStorage.GetInstance(FATE_SETTING).setBoolForKey(EFF_OPEN,isOpen_)
            jsb.JsonStorage.GetInstance(FATE_SETTING).flush();
        },

       this.getBackgroundIsOpen = function () {
           return jsb.JsonStorage.GetInstance(FATE_SETTING).getBoolForKey(BGM_OPEN);
       },

       this.getEffectIsOpen = function () {
           return jsb.JsonStorage.GetInstance(FATE_SETTING).getBoolForKey(EFF_OPEN);
       },

        this.playBackgroundMusic = function (musicType_,loop_) {
            if(musicType_){
                if(this.curPlayType && this.curPlayType == musicType_){
                    return;
                }
                else{
                    this.stopBackgroundMusic();
                    this.curPlayType = musicType_;
                }

                if(loop_ == undefined){
                    loop_ = true;
                }
                //LOG("mmmmmm volume = " + this.getBackgroundVolume());
                //LOG("backgroun id open = " + this.getBackgroundIsOpen());
                cc.audioEngine.playMusic(musicType_,loop_);
                if(this.getBackgroundIsOpen()){
                    cc.audioEngine.setMusicVolume(this.getBackgroundVolume());
                }
                else{
                    this.stopBackgroundMusic();
                }
            }
        }

        this.stopBackgroundMusic = function () {
            this.curPlayType = 0;
            cc.audioEngine.stopMusic();
        }
        
        this.playEffectMusic = function (musicType_) {
            cc.audioEngine.playEffect(musicType_);
            //LOG("effect music is open = " + this.getEffectIsOpen());
            if(this.getEffectIsOpen()){
                cc.audioEngine.setEffectsVolume(this.getEffectVolume());
            }
            else{
                cc.audioEngine.stopAllEffects();
            }
        }
    }

    var instance ;
    return {
      getInstance : function(){
          if(instance === undefined){
              instance = new Singleton();
          }
          return instance;
      }
    };
})();
//
//MusicManager.MType = {
//    battle :{
//        type : 1,
//        name : "sounds/forest.mp3"
//    } ,
//
//    startLayer : {
//        type : 2,
//        name : "sounds/background.mp3"
//    }
//}