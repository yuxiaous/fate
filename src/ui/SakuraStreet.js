/**
 * Created by yuxiao on 15/1/14.
 */


var SakuraStreet = ui.GuiLevelHelperScene.extend({
    _guiFile: "res/scenes/sakura.lhplist",

    ctor: function() {
        this._super();
    },

    onEnter: function() {
        this._super();
        this._gameWorldNode = this.getGameWorldNode();
        this._backUiNode = this.getBackUINode();
        this._uiNode = this.getUINode();

        // operator
        this._operator = new OperationLayer();
        this._uiNode.addChild(this._operator);

        // reset button
        var size = cc.director.getWinSize();
        var resetItem = new cc.MenuItemFont("Reset", function () {
            this.resetDragonBones();
            this.testDragonBones();
        }, this);
        resetItem.setPosition(cc.p(size.width - 60, size.height - 30));
        var menu = new cc.Menu(resetItem);
        menu.x = 0;
        menu.y = 0;
        this._uiNode.addChild(menu);

        // role info panel
        //this._rolePanel = new RoleBattlePanel();
        //this._rolePanel.setPosition(0, size.height);
        //this._uiNode.addChild(this._rolePanel);

        // test dragonbones
        //jsb.DragonBonesHelper.addDragonBones("QYCCC");
        //jsb.DragonBonesHelper.addDragonBones("yaolangdajiang");
        //jsb.DragonBonesHelper.addDragonBones("qyc_effect");
        //jsb.DragonBonesHelper.addDragonBones("hurt_effect");
        this.testDragonBones();
    },

    onExit: function() {
        this._super();
    },

    testDragonBones: function() {
        LOG("testDragonBones")
        var winSize = cc.director.getWinSize();
        var street = this.getChildNodeWithName("street");

        var world = new PhysicalWorld();
        world.shakingNode = this._gameWorldNode;
        world.setContentSize(street.getContentSize());
        street.addChild(world);
        this._physicalWorld = world;

        // role1
        var role1 = new Saber();
        world.addPhysicalNode(role1);
        role1.setSpacePosition({x:400, y:200, z:0});
        role1.turn(RoleBase.Direction.Right);
        role1.setRoleAi(RoleAi.Type.Manual, {
            joystick: this._operator._joystick,
            attackButton: this._operator._attackButton,
            skillButton1: this._operator._skillButton1,
            skillButton2: this._operator._skillButton2
        });

        // role2
        var role2 = [];
        function addRole2(x, y) {
            var aaa = new SkullMan();
            world.addPhysicalNode(aaa);
            aaa.setSpacePosition({x:x, y:y, z:0});
            aaa.setRoleAi(RoleAi.Type.Stake, {
                target: role1
            });
            role2.push(aaa);
        }
        addRole2(700, 200);
        //addRole2(800, 150);
        //addRole2(900, 100);

        var camera = this.getChildNodeWithName("UntitledCamera");
        camera.followNode(role1);
        camera.setImportantAreaUnit(cc.size(0, 0));

        //this._rolePanel.setRole(role1);
    },

    resetDragonBones: function() {
        this._physicalWorld.removeFromParent();
        this._physicalWorld = null;
        //this._rolePanel.setRole(null);
    }
});

