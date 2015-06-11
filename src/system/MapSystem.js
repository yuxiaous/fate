/**
 * Created by yuxiao on 15/4/21.
 */


var MapSystem = SystemBase.extend({
    ctor: function () {
        this._super();

        this.max_map_id = 0;
        this.max_chapter_id = 0;
        this.maps_info = {};

        this.cur_map_pos = cc.p(0,0);
    },

    onInit: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_MAP_INFO = this.onMapInfo.bind(this);
    },

    onFinalize: function () {
        this._super();
        net_protocol_handlers.ON_CMD_SC_MAP_INFO = null;
    },

    //requestMapInfo: function() {
    //    net_protocol_handlers.SEND_CMD_CS_GET_MAP_INFO();
    //},

    onMapInfo: function(obj) {
        _.each(obj.maps, function(info) {
            this.maps_info[info.map_id] = info;

            if(info.map_id > this.max_map_id) {
                this.max_map_id = info.map_id;
            }

            var config = configdb.map[info.map_id];
            if(config && config.chapter > this.max_chapter_id) {
                this.max_chapter_id = config.chapter;
            }
        }, this);

        notification.emit(notification.event.MAP_MAP_INFO);
    },

    setGameMapPos : function (pos_) {
        if(cc.pointEqualToPoint(pos_ ,this.cur_map_pos)){
            return;
        }
        else{
            this.cur_map_pos = pos_
        }
    },

    getGameMapPos : function () {
        return this.cur_map_pos;
    },
    
    setGameMapRect : function (rect_) {
        this.cur_map_rect = rect_;
    },
    
    getGameMapRect : function () {
        return this.cur_map_rect;
    }
});

