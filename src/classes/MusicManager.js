/*
* shilei
* 2015/04/23
* */

var MusicManager = (function () {
    function Singleton(){
        BGM_KEY = "shilei_background_music_key";
        EFF_KEY = "shilei_effect_music_key";

        this.curPlayType = 0;

        this.setBackgroundMusicOn = function(isOn_){
            if(isOn_){
                this.setBackgroundVolumn(1);
            }
            else{
                this.setBackgroundVolumn(0);
            }
        }

        this.setEffectOn = function (isOn_) {
            if(isOn_){
                this.serEffectVolumn(1);
            }
            else{
                this.serEffectVolumn(0);
            }
        }

        /*
        *   volumn 0.0 -> 1.0
        * */
        this.setBackgroundVolumn = function(volumn_){
            cc.sys.localStorage.setItem(BGM_KEY,String(volumn_));
        }

        this.serEffectVolumn = function(volumn_){
            cc.sys.localStorage.setItem(EFF_KEY,String(volumn_));
        }

        this.getBackgroundVolume = function () {
            return Number(cc.sys.localStorage.getItem(BGM_KEY));
        }

        this.getEffectVolume = function () {
            return Number(cc.sys.localStorage.getItem(EFF_KEY));
        }
        
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
                cc.audioEngine.playMusic(musicType_,loop_);
                cc.audioEngine.setMusicVolume(this.getBackgroundVolume());
            }
        }

        this.stopBackgroundMusic = function () {
            this.curPlayType = 0;
            cc.audioEngine.stopMusic();
        }
        
        this.playEffectMusic = function (musicType_) {
            cc.audioEngine.playEffect(musicType_);
            cc.audioEngine.setEffectsVolume(this.getEffectVolume());
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