/*
 * sleifeei@163.com
 * */

var TestJS = cc.Layer.extend({
    ctor : function(){
        this._super();

        return true;
    } ,

    onEnter : function(){
        this._super();
        cc.log("test js onEnter");

        // 进入游戏
        var backItem = new cc.MenuItemFont("BACK",
            function() {
                ui.popScene();
            }, this);
        backItem.attr({
            x: 100,
            y: 100,
            fontSize: 30
        });
        var menu = new cc.Menu(backItem);
        menu.x = 0;
        menu.y = 0;
        this.addChild(menu);


        //this.testTint();
      //  this.testParticle();

        //var that = this;
        //var listener_1 = cc.EventListener.create({
        //    event : cc.EventListener.TOUCH_ONE_BY_ONE,
        //    swallowTouches: true,
        //    onTouchBegan : function(touch,event){
        //       // var target = event.getCurrentTarget();
        //        var pos = touch.getLocation();
        //        cc.log("pos.x = " + pos.x + "pos.y = " + pos.y);
        //       // that.testParticle(pos);
        //        return false;
        //    }
        //})
        //cc.eventManager.addListener(listener_1,this);

        //this.testPlayMovie();
        this.testSqlite();
    },

    onExit : function(){
        this._super();
    },


    testSqlite : function(){
        this._db = new jsb.SQLiteWrapper();
        this._dbPath = this._db.initializing("data.db","res","");
        this._isOpen = this._db.open(this._dbPath);

        cc.log("数据库打开结果 ： "+ this._isOpen ? "已打开.." : "打开失败...");

        if(this._isOpen){
            var st = this._db.statement("select * from equip");
            var ary = [];
            while(st.nextRow()){
                var equipVO = new CEquipVO();
                equipVO.wid = parseInt(st.valueString(0));
                equipVO.name = st.valueString(1);
                equipVO.desc = st.valueString(2);
                equipVO.level = st.valueString(3);
                equipVO.icon = st.valueString(4);
                equipVO.quality = st.valueString(5);
                ary.push(equipVO);
            }
            for(var vo in ary){
                cc.log("equipdata : "+ ary[vo].toString());
            }

            //this._db.directStatement("insert into equip values('88888888','test insert-1','test insert -2','test insert-3') ");
            //var insertStr = "insert into equip values('88888888','test insert-1','test insert -2','test insert-3','5','6','7','8','9','10')";
            //var st_1 = this._db.statement(insertStr);
            //st_1.execute();
            //
            //this._db.commit();

        }
    },

    testParticle :function(endPos_){
        var energyP = cc.ParticleSystem.create("res/particles/addBloodP.plist");
        energyP.attr({
            x : 200,
            y : 200
        })
        this.addChild(energyP);
        //var bezierA =cc.BezierBy.create(1.0,[energyP.getPosition(),energyP.getPosition(),cc.p(energyP.getPosition().x + 400, -100)]),

        energyP.runAction(cc.Sequence.create(cc.MoveTo.create(0.5,endPos_),
                                            cc.CallFunc.create(function () {
                                                    energyP.removeFromParent();
                                                }
                                            )));
    },

    testTint : function () {
        var spr = cc.Sprite.create("res/images/1.png");
        spr.attr = {
            x : cc.winSize.width/2,
            y : cc.winSize.height/2
        }
        this.addChild(spr);
        spr.runAction(cc.Sequence.create(
            cc.DelayTime.create(2.0),
            cc.TintBy.create(3.0,100,0,0),
            cc.TintBy.create(3.0,-100,0,0)
        ))

    },

    testPlayMovie : function(){
        //var mov = jsb.PlayMovie.create("res/movie/suu.mp4",this);
        //this.addChild(mov);
    }
});

var TestJsScene = cc.Scene.extend({
    onEnter : function(){
        this._super();
        var layer = new TestJS();
        this.addChild(layer);
    }
});

var CEquipVO = cc.Class.extend({
    wid:null,//like 10000001
    name:null,//like 银票
    level:null,//like 1
    type:null,//like 1
    price:null,//like 200
    stackCount:null,//like 99
    bind:null,//like 1
    desc:null,//like 加银两
    quality:null,//like 1
    icon:null,//like item/article/10000001.png
    toString:function(){
        return this.wid + " " + this.name + " " + this.level + " " + this.desc + " " + this.icon;
    }
});

