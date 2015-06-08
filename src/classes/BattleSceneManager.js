/**
 * Created by yuxiao on 15/3/16.
 */


var BattleSceneManager = cc.Class.extend({
    ctor: function() {
        this.reset();
    },

    reset: function() {
        this._scene = null;
        this._world = null;

        this.mainRole = null;
        this.opponents = [];
        this.items = [];
    },

    setScene: function(scene) {
        this._scene = scene;

        var street = this._scene.getChildNodeWithName("street");
        this._world = jsb.PhysicalWorld.create();
        this._world.setContentSize(street.getContentSize());
        street.addChild(this._world);

        this._uiNode = this._scene.getUINode();
        this._gameWorldNode = this._scene.getGameWorldNode();

        this._world.setShakingNode(this._gameWorldNode);
    },

    setMainRole: function(role) {
        this.mainRole = role;

        if(this._world) {
            this._world.addPhysicalNode(role);

            // camera
            var camera = this._scene.getChildNodeWithName("UntitledCamera");
            camera.setImportantAreaUnit(cc.size(0, 0));
            camera.followNode(role);
        }
    },

    addOpponent: function(role) {
        if(this._world) {
            this._world.addPhysicalNode(role);
            this.opponents.push(role);
        }
    },

    removeOpponent: function(role) {
        if(this._world) {
            this._world.removePhysicalNode(role);

            var index = _.indexOf(this.opponents, role);
            this.opponents.splice(index, 1);

            if(this.opponents.length == 0) {
                this.battleWin();
            }
        }
    },

    battleWin: function() {
        var panel = new BattleEndPanel();
        this._scene.addChild(panel, 9999);
    },

    addDroppedItem: function(item) {
        this._world.addChild(item);
        item.setLocalZOrder(-item.getPosition().y);
        this.items.push(item);
    },

    removeDroppedItem: function(item) {
        this._world.removeChild(item);

        var index = _.indexOf(this.items, item);
        this.items.splice(index, 1);
    }
});

var battleSceneManager = new BattleSceneManager();

