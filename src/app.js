
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    textField: null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();
        //this.setColor(cc.WHITE);

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size

        var size = cc.director.getWinSize();

        var bg = new cc.Sprite("res/HelloWorld.jpg");
        bg.attr({
            x: size.width / 2,
            y: size.height / 2,
            scaleX: size.width / bg.width,
            scaleY: size.height / bg.height
        });
        this.addChild(bg);

        // add a "close" icon to exit the progress. it's an autorelease object
        //var closeItem = new cc.MenuItemImage(
        //    res.CloseNormal_png,
        //    res.CloseSelected_png,
        //    function () {
        //        cc.log("Menu is clicked!");
        //    }, this);
        //closeItem.attr({
        //    x: size.width - 20,
        //    y: 20,
        //    anchorX: 0.5,
        //    anchorY: 0.5
        //});

        // 进入游戏
        var enterGame = new cc.MenuItemFont("进入游戏",
            function() {
                //crows.start();
            }, this);
        enterGame.attr({
            x: size.width / 2,
            y: size.height / 2 + 30,
            fontSize: 100
        });

        var menu = new cc.Menu(enterGame);
        if(cc.sys.platform == cc.sys.MACOS){
            // test widget
            var enterTestJS = new  cc.MenuItemFont("TEST",
                function(){
                    ui.pushScene(TestJsScene);
                },this
            );
            enterTestJS.attr({
                x : size.width / 2,
                y : size.height * 0.4,
                fontSize : 40
            })
            menu.addChild(enterTestJS);
        }
        menu.x = 0;
        menu.y = 0;
        this.addChild(menu, 1);


        jsb.fileUtils.addSearchPath("res");
        var aa = new RoleBloodBar(100, 100);
        //aa.setPosition(100, 100);
        this.addChild(aa);



        return true;
    }
});

var HelloWorldScene = cc.Scene.extend({
    //ctor: function() {
    //    this._super();
    //    this.initWithPhysics();
    //},

    onEnter:function () {
        this._super();

        //this.getPhysicsWorld().setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL);

        var layer = new HelloWorldLayer();
        this.addChild(layer);



        //cc.audioEngine.preloadMusic("res/sounds/startSceneBM.mp3");
        //cc.audioEngine.playMusic("res/sounds/startSceneBM.mp3", true);
    },

    onExit: function() {
        this._super()

        cc.audioEngine.stopMusic();
    }
});
