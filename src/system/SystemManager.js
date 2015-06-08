/**
 * Created by yuxiao on 15/5/23.
 */


var SystemManager = {
    systems: [],

    start: function() {
        LOG("SystemManager.start");
        var systems = this.systems;
        function addSubSystem(oClass) {
            systems.push(oClass);
            var sys = new oClass();
            if(sys) {
                oClass.instance = sys;
                sys.onInit();
            }
        }

        addSubSystem(PlayerSystem);
        addSubSystem(GmSystem);
        addSubSystem(MapSystem);
        addSubSystem(ShopSystem);
        addSubSystem(SkillSystem);
        addSubSystem(EquipSystem);
        addSubSystem(BagSystem);
        addSubSystem(ItemSystem);
        addSubSystem(BattleSystem);
    },

    end: function() {
        LOG("SystemManager.end");
        _.each(this._systems, function(oClass) {
            if(oClass.instance) {
                oClass.instance.onFinalize();
                oClass.instance = null;
            }
        }, this);
        this.systems.length = 0;
    }
};

