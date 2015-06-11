/**
 * Created by yuxiao on 15/3/19.
 */


var BattleEndPanel = ui.GuiWindowBase.extend({
    _guiFile: "ui/BattleEndPanel.json",

    ctor: function(type_) {
        this._super();

        this._battleResult = type_;
    },

    onEnter: function() {
        this._super();

        this._goldLabel = this.seekWidgetByName("lbl_jingbi");
        this._expLabel = this.seekWidgetByName("lbl_jingyan");
        this._goldLabel.setString("0");
        this._expLabel.setString("0");


        this._item_1 = this.seekWidgetByName("item_1");
        this._item_2 = this.seekWidgetByName("item_2");
        this._item_3 = this.seekWidgetByName("item_3");

        this._item_1.setVisible(false);
        this._item_2.setVisible(false);
        this._item_3.setVisible(false);

        this._victoryPanel = this.seekWidgetByName("victory_panel");
        this._failurePanel = this.seekWidgetByName("failure_panel");
        this._victoryAni = this.seekWidgetByName("victory_node");

        if(this._battleResult == BattleEndPanel.Type.Lose){
            this._failurePanel.setVisible(true);
            this._victoryPanel.setVisible(false);
        }
        else if(this._battleResult == BattleEndPanel.Type.Win){
            this._victoryPanel.setVisible(true);
            this._failurePanel.setVisible(false);

            var tmpStr = "res/images/ui/ui_10";
            var vin_ani = new cc.Sprite(tmpStr + "1.png");
            this._victoryAni.addChild(vin_ani);
            this._victoryAni.setScale(1.5);
            var animFrames = []
            for(var i = 1; i <= 8; i++){
                var strName = tmpStr + i + ".png";
                var size = cc.Sprite(strName).getContentSize();
                var frame = cc.SpriteFrame.create(strName,cc.rect(0,0,size.width,size.height));
                animFrames.push(frame);
            }
            var animation = new cc.Animation(animFrames,0.2,1);
            var animationAction = new cc.Animate(animation);
            vin_ani.runAction(animationAction);
        }
    },

    onExit: function() {
        this._super();
        this._victoryAni = null;
        this._victoryPanel = null;
        this._failurePanel = null;
    },

    setType: function(type) {

    },

    _on_btn_back: function() {
        this.close();
    },
    
    _on_btn_again: function () {
        ui.popScene();
        ui.pushScene(new BattleScene(BattleSystem.instance.cur_battle_map));
        ui.replaceScene(new BattleScene(BattleSystem.instance.cur_battle_map))
    }
});

BattleEndPanel.Type = {
    Win: 1,
    Lose: 2
}