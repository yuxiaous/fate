////////////////// Auto generated, DO NOT modify manually //////////////////

var net_protocol_handlers = {};

var _SendFunc = net.send.bind(net);
var _BindFunc = net.registerCallback.bind(net);

// @protocol 战斗过程中使用道具结果
// @param {uint32} result, 使用结果，1成功，2失败
// @param {uint32} item_type, 1加血，2加蓝，3加血加蓝
net_protocol_handlers.CMD_SC_USE_BATTLE_ITEM_RESULT = 1506;
_BindFunc(1506, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_USE_BATTLE_ITEM_RESULT.result is undefined.");
	cc.assert(obj.item_type != undefined, "CMD_SC_USE_BATTLE_ITEM_RESULT.item_type is undefined.");
	net_protocol_handlers.ON_CMD_SC_USE_BATTLE_ITEM_RESULT(obj);
});

// @protocol 错误码
// @param {uint32} code, 错误码
net_protocol_handlers.CMD_SC_ERROR_CODE = 88;
_BindFunc(88, function(obj) {
	cc.assert(obj.code != undefined, "CMD_SC_ERROR_CODE.code is undefined.");
	net_protocol_handlers.ON_CMD_SC_ERROR_CODE(obj);
});

// @protocol 技能升级结果
// @param {uint32} result, 技能升级结果 0成功
net_protocol_handlers.CMD_SC_SKILL_UP_RESULT = 1203;
_BindFunc(1203, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_SKILL_UP_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_SKILL_UP_RESULT(obj);
});

// @protocol 获取授权
// @param {uint32} token, Token
net_protocol_handlers.CMD_CS_AUTH = 500;
net_protocol_handlers.SEND_CMD_CS_AUTH = function(obj) {
	cc.assert(obj.token != undefined, "CMD_CS_AUTH.token is undefined.");
	_SendFunc(500, obj);
};

// @protocol 战斗结束返回的详细信息
// @param {uint32} result, 战斗结果，1胜利 2失败
// @param {uint32} map_id, 地图id
// @param {switch} reward, 奖励列表
net_protocol_handlers.CMD_SC_BATTLE_FINISH_RESULT = 1504;
_BindFunc(1504, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_BATTLE_FINISH_RESULT.result is undefined.");
	cc.assert(obj.map_id != undefined, "CMD_SC_BATTLE_FINISH_RESULT.map_id is undefined.");
	cc.assert(obj.reward != undefined, "CMD_SC_BATTLE_FINISH_RESULT.reward is undefined.");
	net_protocol_handlers.ON_CMD_SC_BATTLE_FINISH_RESULT(obj);
});

// @protocol 装备物品
// @param {uint32} uid, 物品uid
net_protocol_handlers.CMD_CS_EQUIP_ITEM = 1304;
net_protocol_handlers.SEND_CMD_CS_EQUIP_ITEM = function(obj) {
	cc.assert(obj.uid != undefined, "CMD_CS_EQUIP_ITEM.uid is undefined.");
	_SendFunc(1304, obj);
};

// @protocol 角色信息
// @param {switch} player, 角色信息
net_protocol_handlers.CMD_CS_PLAYER_INFO = 900;
_BindFunc(900, function(obj) {
	cc.assert(obj.player != undefined, "CMD_CS_PLAYER_INFO.player is undefined.");
	net_protocol_handlers.ON_CMD_CS_PLAYER_INFO(obj);
});

// @protocol 开始初始化
net_protocol_handlers.CMD_SC_INIT_BEGIN = 501;
_BindFunc(501, function(obj) {
	net_protocol_handlers.ON_CMD_SC_INIT_BEGIN(obj);
});

// @protocol 卖出物品
// @param {uint32} uid, 物品uid
// @param {uint32} num, 物品数量
net_protocol_handlers.CMD_CS_ITEM_SELL = 1402;
net_protocol_handlers.SEND_CMD_CS_ITEM_SELL = function(obj) {
	cc.assert(obj.uid != undefined, "CMD_CS_ITEM_SELL.uid is undefined.");
	cc.assert(obj.num != undefined, "CMD_CS_ITEM_SELL.num is undefined.");
	_SendFunc(1402, obj);
};

// @protocol 初始化结束
net_protocol_handlers.CMD_SC_INIT_END = 502;
_BindFunc(502, function(obj) {
	net_protocol_handlers.ON_CMD_SC_INIT_END(obj);
});

// @protocol 装备槽信息
// @param {list} slots, 技能信息
net_protocol_handlers.CMD_SC_EQUIP_SLOT_INFO = 1301;
_BindFunc(1301, function(obj) {
	cc.assert(obj.slots != undefined, "CMD_SC_EQUIP_SLOT_INFO.slots is undefined.");
	net_protocol_handlers.ON_CMD_SC_EQUIP_SLOT_INFO(obj);
});

// @protocol 地图战斗
// @param {uint32} map_id, 地图点id
net_protocol_handlers.CMD_CS_BATTLE_MAP = 1501;
net_protocol_handlers.SEND_CMD_CS_BATTLE_MAP = function(obj) {
	cc.assert(obj.map_id != undefined, "CMD_CS_BATTLE_MAP.map_id is undefined.");
	_SendFunc(1501, obj);
};

// @protocol 初始化进度
// @param {uint32} percent, 初始化百分比
net_protocol_handlers.CMD_SC_INIT_PROGRESS = 503;
_BindFunc(503, function(obj) {
	cc.assert(obj.percent != undefined, "CMD_SC_INIT_PROGRESS.percent is undefined.");
	net_protocol_handlers.ON_CMD_SC_INIT_PROGRESS(obj);
});

// @protocol 升级技能
// @param {uint32} skill_id, 技能id
net_protocol_handlers.CMD_CS_SKILL_UP = 1202;
net_protocol_handlers.SEND_CMD_CS_SKILL_UP = function(obj) {
	cc.assert(obj.skill_id != undefined, "CMD_CS_SKILL_UP.skill_id is undefined.");
	_SendFunc(1202, obj);
};

// @protocol 物品使用结果
// @param {uint32} result, 结果 0成功
net_protocol_handlers.CMD_SC_ITEM_USE_RESULT = 1405;
_BindFunc(1405, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_ITEM_USE_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_ITEM_USE_RESULT(obj);
});

// @protocol 更新物品信息
// @param {list} items, 物品信息列表
net_protocol_handlers.CMD_SC_ITEM_INFO = 1401;
_BindFunc(1401, function(obj) {
	cc.assert(obj.items != undefined, "CMD_SC_ITEM_INFO.items is undefined.");
	net_protocol_handlers.ON_CMD_SC_ITEM_INFO(obj);
});

// @protocol 战斗结束
// @param {uint32} result, 战斗结果, 1胜利，2失败
// @param {uint32} time, 战斗消耗时间，单位秒
net_protocol_handlers.CMD_CS_BATTLE_FINISH = 1503;
net_protocol_handlers.SEND_CMD_CS_BATTLE_FINISH = function(obj) {
	cc.assert(obj.result != undefined, "CMD_CS_BATTLE_FINISH.result is undefined.");
	cc.assert(obj.time != undefined, "CMD_CS_BATTLE_FINISH.time is undefined.");
	_SendFunc(1503, obj);
};

// @protocol 地图战斗结果
// @param {uint32} result, 结果 0成功
// @param {uint32} map_id, 地图点id
net_protocol_handlers.CMD_SC_BATTLE_MAP_RESULT = 1502;
_BindFunc(1502, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_BATTLE_MAP_RESULT.result is undefined.");
	cc.assert(obj.map_id != undefined, "CMD_SC_BATTLE_MAP_RESULT.map_id is undefined.");
	net_protocol_handlers.ON_CMD_SC_BATTLE_MAP_RESULT(obj);
});

// @protocol 战斗过程中使用道具
// @param {uint32} uid, item uid
// @param {uing32} num, 使用数量
net_protocol_handlers.CMD_CS_USE_BATTLE_ITEM = 1505;
net_protocol_handlers.SEND_CMD_CS_USE_BATTLE_ITEM = function(obj) {
	cc.assert(obj.uid != undefined, "CMD_CS_USE_BATTLE_ITEM.uid is undefined.");
	cc.assert(obj.num != undefined, "CMD_CS_USE_BATTLE_ITEM.num is undefined.");
	_SendFunc(1505, obj);
};

// @protocol 购买商品结果
// @param {uint32} result, 结果 0成功
// @param {uint32} good_id, 商品id
// @param {uint32} remaining, 剩余数量
net_protocol_handlers.CMD_SC_SHOP_BUY_RESULT = 1102;
_BindFunc(1102, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_SHOP_BUY_RESULT.result is undefined.");
	cc.assert(obj.good_id != undefined, "CMD_SC_SHOP_BUY_RESULT.good_id is undefined.");
	cc.assert(obj.remaining != undefined, "CMD_SC_SHOP_BUY_RESULT.remaining is undefined.");
	net_protocol_handlers.ON_CMD_SC_SHOP_BUY_RESULT(obj);
});

// @protocol 物品装备结果
// @param {uint32} result, 结果 0成功
net_protocol_handlers.CMD_CS_EQUIP_ITEM_RESULT = 1305;
_BindFunc(1305, function(obj) {
	cc.assert(obj.result != undefined, "CMD_CS_EQUIP_ITEM_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_CS_EQUIP_ITEM_RESULT(obj);
});

// @protocol 卸下装备结果
// @param {uint32} result, 结果 0成功
net_protocol_handlers.CMD_CS_UNEQUIP_ITEM_RESULT = 1307;
_BindFunc(1307, function(obj) {
	cc.assert(obj.result != undefined, "CMD_CS_UNEQUIP_ITEM_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_CS_UNEQUIP_ITEM_RESULT(obj);
});

// @protocol 技能信息
// @param {list} skills, 技能信息
net_protocol_handlers.CMD_SC_SKILL_INFO = 1201;
_BindFunc(1201, function(obj) {
	cc.assert(obj.skills != undefined, "CMD_SC_SKILL_INFO.skills is undefined.");
	net_protocol_handlers.ON_CMD_SC_SKILL_INFO(obj);
});

// @protocol GM命令
// @param {string} cmd, GM命令
net_protocol_handlers.CMD_CS_GM_CMD = 89;
net_protocol_handlers.SEND_CMD_CS_GM_CMD = function(obj) {
	cc.assert(obj.cmd != undefined, "CMD_CS_GM_CMD.cmd is undefined.");
	_SendFunc(89, obj);
};

// @protocol 装备槽升级结果
// @param {uint32} result, 结果 0成功
net_protocol_handlers.CMD_SC_EQUIP_SLOT_UPGRADE_RESULT = 1303;
_BindFunc(1303, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_EQUIP_SLOT_UPGRADE_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_EQUIP_SLOT_UPGRADE_RESULT(obj);
});

// @protocol 卖出物品结果
// @param {uint32} result, 结果 0成功
net_protocol_handlers.CMD_SC_ITEM_SELL_RESULT = 1403;
_BindFunc(1403, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_ITEM_SELL_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_ITEM_SELL_RESULT(obj);
});

// @protocol 购买商品
// @param {uint32} good_id, 商品id
// @param {uint32} count, 商品数量
net_protocol_handlers.CMD_CS_SHOP_BUY_GOODS = 1101;
net_protocol_handlers.SEND_CMD_CS_SHOP_BUY_GOODS = function(obj) {
	cc.assert(obj.good_id != undefined, "CMD_CS_SHOP_BUY_GOODS.good_id is undefined.");
	cc.assert(obj.count != undefined, "CMD_CS_SHOP_BUY_GOODS.count is undefined.");
	_SendFunc(1101, obj);
};

// @protocol 使用物品
// @param {uint32} uid, 物品uid
// @param {uint32} num, 物品数量
net_protocol_handlers.CMD_CS_ITEM_USE = 1404;
net_protocol_handlers.SEND_CMD_CS_ITEM_USE = function(obj) {
	cc.assert(obj.uid != undefined, "CMD_CS_ITEM_USE.uid is undefined.");
	cc.assert(obj.num != undefined, "CMD_CS_ITEM_USE.num is undefined.");
	_SendFunc(1404, obj);
};

// @protocol 地图信息
// @param {list} maps, 地图信息列表
net_protocol_handlers.CMD_SC_MAP_INFO = 1001;
_BindFunc(1001, function(obj) {
	cc.assert(obj.maps != undefined, "CMD_SC_MAP_INFO.maps is undefined.");
	net_protocol_handlers.ON_CMD_SC_MAP_INFO(obj);
});

// @protocol 装备槽升级
// @param {uint32} slot_type, 槽类型
net_protocol_handlers.CMD_CS_EQUIP_SLOT_UPGRADE = 1302;
net_protocol_handlers.SEND_CMD_CS_EQUIP_SLOT_UPGRADE = function(obj) {
	cc.assert(obj.slot_type != undefined, "CMD_CS_EQUIP_SLOT_UPGRADE.slot_type is undefined.");
	_SendFunc(1302, obj);
};

// @protocol 卸下装备
// @param {uint32} slot, 槽类型
net_protocol_handlers.CMD_CS_UNEQUIP_ITEM = 1306;
net_protocol_handlers.SEND_CMD_CS_UNEQUIP_ITEM = function(obj) {
	cc.assert(obj.slot != undefined, "CMD_CS_UNEQUIP_ITEM.slot is undefined.");
	_SendFunc(1306, obj);
};
