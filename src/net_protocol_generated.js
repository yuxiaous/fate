////////////////// Auto generated, DO NOT modify manually //////////////////

var net_protocol_handlers = {};

var _SendFunc = net.send.bind(net);
var _BindFunc = net.registerCallback.bind(net);

// @protocol 更新物品信息
// @param {list} items, 物品信息列表
net_protocol_handlers.CMD_SC_ITEM_INFO = 1401;
_BindFunc(1401, function(obj) {
	cc.assert(obj.items != undefined, "CMD_SC_ITEM_INFO.items is undefined.");
	net_protocol_handlers.ON_CMD_SC_ITEM_INFO(obj);
});

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

// @protocol 每日VIP奖励是否领取
// @param {uint32} get_done, 0 没有领取
net_protocol_handlers.CMD_SC_VIP_IS_GET_INFO = 1630;
_BindFunc(1630, function(obj) {
	cc.assert(obj.get_done != undefined, "CMD_SC_VIP_IS_GET_INFO.get_done is undefined.");
	net_protocol_handlers.ON_CMD_SC_VIP_IS_GET_INFO(obj);
});

// @protocol 请求每日登录奖励
// @param {uint32} player_id, 角色id
net_protocol_handlers.CMD_CS_LOGIN_REWARD_INFO = 1604;
net_protocol_handlers.SEND_CMD_CS_LOGIN_REWARD_INFO = function(obj) {
	cc.assert(obj.player_id != undefined, "CMD_CS_LOGIN_REWARD_INFO.player_id is undefined.");
	_SendFunc(1604, obj);
};

// @protocol 换装结果
// @param {uint32} result, 结果 0成功
net_protocol_handlers.CMD_SC_SKIN_CHANGE_RESULT = 1603;
_BindFunc(1603, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_SKIN_CHANGE_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_SKIN_CHANGE_RESULT(obj);
});

// @protocol 获取授权
// @param {string} token, Token
net_protocol_handlers.CMD_CS_AUTH = 504;
net_protocol_handlers.SEND_CMD_CS_AUTH = function(obj) {
	cc.assert(obj.token != undefined, "CMD_CS_AUTH.token is undefined.");
	_SendFunc(504, obj);
};

// @protocol 战斗复活
// @param {uint32} result, 0成功
net_protocol_handlers.CMD_SC_BATTLE_REVIVE = 1625;
_BindFunc(1625, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_BATTLE_REVIVE.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_BATTLE_REVIVE(obj);
});

// @protocol 五天连续登陆奖励
// @param {uint32} player_id, player ID
// @param {uint32} login_index, 当前连续登陆的天数
net_protocol_handlers.CMD_SC_LOGIN_REWARD_INFO = 1605;
_BindFunc(1605, function(obj) {
	cc.assert(obj.player_id != undefined, "CMD_SC_LOGIN_REWARD_INFO.player_id is undefined.");
	cc.assert(obj.login_index != undefined, "CMD_SC_LOGIN_REWARD_INFO.login_index is undefined.");
	net_protocol_handlers.ON_CMD_SC_LOGIN_REWARD_INFO(obj);
});

// @protocol 获取礼包倒计时时间
// @param {uint32} playid_id, 礼包类型
net_protocol_handlers.CMD_CS_GET_GIFT_TIME = 1613;
net_protocol_handlers.SEND_CMD_CS_GET_GIFT_TIME = function(obj) {
	cc.assert(obj.playid_id != undefined, "CMD_CS_GET_GIFT_TIME.playid_id is undefined.");
	_SendFunc(1613, obj);
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

// @protocol 使用识别符登录
// @param {string} identifier, 识别符
net_protocol_handlers.CMD_CS_LOGIN_WITH_IDENTIFIER = 502;
net_protocol_handlers.SEND_CMD_CS_LOGIN_WITH_IDENTIFIER = function(obj) {
	cc.assert(obj.identifier != undefined, "CMD_CS_LOGIN_WITH_IDENTIFIER.identifier is undefined.");
	_SendFunc(502, obj);
};

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
net_protocol_handlers.CMD_SC_INIT_BEGIN = 505;
_BindFunc(505, function(obj) {
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

// @protocol 恢复战斗
// @param {uint32} result, 0
net_protocol_handlers.CMD_SC_RECOVER_BATTLE = 1650;
_BindFunc(1650, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_RECOVER_BATTLE.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_RECOVER_BATTLE(obj);
});

// @protocol 购买角色大招释放数量
// @param {uint32} endless_round, 无尽模式战斗的最大回合数
net_protocol_handlers.CMD_CS_ENDLESS_MAX_ROUND = 1611;
net_protocol_handlers.SEND_CMD_CS_ENDLESS_MAX_ROUND = function(obj) {
	cc.assert(obj.endless_round != undefined, "CMD_CS_ENDLESS_MAX_ROUND.endless_round is undefined.");
	_SendFunc(1611, obj);
};

// @protocol 卸下装备结果
// @param {uint32} result, 结果 0成功
net_protocol_handlers.CMD_CS_UNEQUIP_ITEM_RESULT = 1307;
_BindFunc(1307, function(obj) {
	cc.assert(obj.result != undefined, "CMD_CS_UNEQUIP_ITEM_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_CS_UNEQUIP_ITEM_RESULT(obj);
});

// @protocol 初始化结束
net_protocol_handlers.CMD_SC_INIT_END = 506;
_BindFunc(506, function(obj) {
	net_protocol_handlers.ON_CMD_SC_INIT_END(obj);
});

// @protocol 装备槽信息
// @param {list} slots, 技能信息
net_protocol_handlers.CMD_SC_EQUIP_SLOT_INFO = 1301;
_BindFunc(1301, function(obj) {
	cc.assert(obj.slots != undefined, "CMD_SC_EQUIP_SLOT_INFO.slots is undefined.");
	net_protocol_handlers.ON_CMD_SC_EQUIP_SLOT_INFO(obj);
});

// @protocol 无尽模式结束
// @param {uint32} endless_round, 无尽模式战斗结束轮数
net_protocol_handlers.CMD_SC_ENDLESS_BATTLE_END = 1623;
_BindFunc(1623, function(obj) {
	cc.assert(obj.endless_round != undefined, "CMD_SC_ENDLESS_BATTLE_END.endless_round is undefined.");
	net_protocol_handlers.ON_CMD_SC_ENDLESS_BATTLE_END(obj);
});

// @protocol 使用角色大招次数
// @param {uint32} player_id, player ID
net_protocol_handlers.CMD_CS_USE_SUPER_SKILL = 1607;
net_protocol_handlers.SEND_CMD_CS_USE_SUPER_SKILL = function(obj) {
	cc.assert(obj.player_id != undefined, "CMD_CS_USE_SUPER_SKILL.player_id is undefined.");
	_SendFunc(1607, obj);
};

// @protocol 地图战斗
// @param {uint32} map_id, 地图点id
net_protocol_handlers.CMD_CS_BATTLE_MAP = 1501;
net_protocol_handlers.SEND_CMD_CS_BATTLE_MAP = function(obj) {
	cc.assert(obj.map_id != undefined, "CMD_CS_BATTLE_MAP.map_id is undefined.");
	_SendFunc(1501, obj);
};

// @protocol 无尽模式结束
// @param {uint32} endless_round, 无尽模式战斗结束轮数
net_protocol_handlers.CMD_CS_ENDLESS_BATTLE_END = 1622;
net_protocol_handlers.SEND_CMD_CS_ENDLESS_BATTLE_END = function(obj) {
	cc.assert(obj.endless_round != undefined, "CMD_CS_ENDLESS_BATTLE_END.endless_round is undefined.");
	_SendFunc(1622, obj);
};

// @protocol 初始化进度
// @param {uint32} percent, 初始化百分比
net_protocol_handlers.CMD_SC_INIT_PROGRESS = 507;
_BindFunc(507, function(obj) {
	cc.assert(obj.percent != undefined, "CMD_SC_INIT_PROGRESS.percent is undefined.");
	net_protocol_handlers.ON_CMD_SC_INIT_PROGRESS(obj);
});

// @protocol 登陆结果
// @param {uint32} result, 结果 成功=0
// @param {string} account, 账号唯一标识
// @param {string} token, Token
net_protocol_handlers.CMD_SC_LOGIN_RESULT = 503;
_BindFunc(503, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_LOGIN_RESULT.result is undefined.");
	cc.assert(obj.account != undefined, "CMD_SC_LOGIN_RESULT.account is undefined.");
	cc.assert(obj.token != undefined, "CMD_SC_LOGIN_RESULT.token is undefined.");
	net_protocol_handlers.ON_CMD_SC_LOGIN_RESULT(obj);
});

// @protocol 物品使用结果
// @param {uint32} result, 结果 0成功
// @param {uint32} item_type, 1加血，2加蓝，3加血加蓝
net_protocol_handlers.CMD_SC_ITEM_USE_RESULT = 1405;
_BindFunc(1405, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_ITEM_USE_RESULT.result is undefined.");
	cc.assert(obj.item_type != undefined, "CMD_SC_ITEM_USE_RESULT.item_type is undefined.");
	net_protocol_handlers.ON_CMD_SC_ITEM_USE_RESULT(obj);
});

// @protocol 装备强化（背包中）
// @param {uint32} uid, 
net_protocol_handlers.CMD_CS_EQUIP_STRENGTHEN_IN_BAG = 1310;
net_protocol_handlers.SEND_CMD_CS_EQUIP_STRENGTHEN_IN_BAG = function(obj) {
	cc.assert(obj.uid != undefined, "CMD_CS_EQUIP_STRENGTHEN_IN_BAG.uid is undefined.");
	_SendFunc(1310, obj);
};

// @protocol 战斗结束
// @param {uint32} result, 战斗结果, 1胜利，2失败
// @param {uint32} time, 战斗消耗时间，单位秒
net_protocol_handlers.CMD_CS_BATTLE_FINISH = 1503;
net_protocol_handlers.SEND_CMD_CS_BATTLE_FINISH = function(obj) {
	cc.assert(obj.result != undefined, "CMD_CS_BATTLE_FINISH.result is undefined.");
	cc.assert(obj.time != undefined, "CMD_CS_BATTLE_FINISH.time is undefined.");
	_SendFunc(1503, obj);
};

// @protocol 装备强化（已装备）
// @param {uint32} slot, 
net_protocol_handlers.CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP = 1311;
net_protocol_handlers.SEND_CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP = function(obj) {
	cc.assert(obj.slot != undefined, "CMD_CS_EQUIP_STRENGTHEN_ON_EQUIP.slot is undefined.");
	_SendFunc(1311, obj);
};

// @protocol 请求订单结果
// @param {string} order, 订单号
// @param {uint32} good_id, 商品id
net_protocol_handlers.CMD_SC_SHOP_ORDER_RESULT = 1104;
_BindFunc(1104, function(obj) {
	cc.assert(obj.order != undefined, "CMD_SC_SHOP_ORDER_RESULT.order is undefined.");
	cc.assert(obj.good_id != undefined, "CMD_SC_SHOP_ORDER_RESULT.good_id is undefined.");
	net_protocol_handlers.ON_CMD_SC_SHOP_ORDER_RESULT(obj);
});

// @protocol 换装信息
// @param {list} skins, 拥有的皮肤
// @param {uint32} use_skin, 使用的套装
net_protocol_handlers.CMD_SC_SKIN_INFO = 1601;
_BindFunc(1601, function(obj) {
	cc.assert(obj.skins != undefined, "CMD_SC_SKIN_INFO.skins is undefined.");
	cc.assert(obj.use_skin != undefined, "CMD_SC_SKIN_INFO.use_skin is undefined.");
	net_protocol_handlers.ON_CMD_SC_SKIN_INFO(obj);
});

// @protocol 地图战斗结果
// @param {uint32} result, 结果 0成功
// @param {uint32} map_id, 地图点id
net_protocol_handlers.CMD_SC_BATTLE_MAP_RESULT = 1502;
_BindFunc(1502, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_BATTLE_MAP_RESULT.result is undefined.");
	cc.assert(obj.map_id != undefined, "CMD_SC_BATTLE_MAP_RESULT.map_id is undefined.");
	net_protocol_handlers.ON_CMD_SC_BATTLE_MAP_RESULT(obj);
});

// @protocol 更新无尽模式战斗的最大回合数
// @param {uint32} endless_round, 无尽模式战斗的最大回合数
net_protocol_handlers.CMD_SC_ENDLESS_MAX_ROUND = 1610;
_BindFunc(1610, function(obj) {
	cc.assert(obj.endless_round != undefined, "CMD_SC_ENDLESS_MAX_ROUND.endless_round is undefined.");
	net_protocol_handlers.ON_CMD_SC_ENDLESS_MAX_ROUND(obj);
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

// @protocol 更新引导数据
// @param {list} guide_info, 礼包各种类型对应的购买数量
net_protocol_handlers.CMD_SC_UPDATE_GUIDE_INFO = 1621;
_BindFunc(1621, function(obj) {
	cc.assert(obj.guide_info != undefined, "CMD_SC_UPDATE_GUIDE_INFO.guide_info is undefined.");
	net_protocol_handlers.ON_CMD_SC_UPDATE_GUIDE_INFO(obj);
});

// @protocol 购买商品结果
// @param {uint32} result, 结果 0成功
// @param {uint32} good_id, 商品id
// @param {uint32} remaining, 剩余数量
// @param {string} order, 订单id
net_protocol_handlers.CMD_SC_SHOP_BUY_RESULT = 1102;
_BindFunc(1102, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_SHOP_BUY_RESULT.result is undefined.");
	cc.assert(obj.good_id != undefined, "CMD_SC_SHOP_BUY_RESULT.good_id is undefined.");
	cc.assert(obj.remaining != undefined, "CMD_SC_SHOP_BUY_RESULT.remaining is undefined.");
	cc.assert(obj.order != undefined, "CMD_SC_SHOP_BUY_RESULT.order is undefined.");
	net_protocol_handlers.ON_CMD_SC_SHOP_BUY_RESULT(obj);
});

// @protocol 购买礼包
// @param {uint32} gift_type, 礼包类型
net_protocol_handlers.CMD_CS_BUY_GIFT = 1608;
net_protocol_handlers.SEND_CMD_CS_BUY_GIFT = function(obj) {
	cc.assert(obj.gift_type != undefined, "CMD_CS_BUY_GIFT.gift_type is undefined.");
	_SendFunc(1608, obj);
};

// @protocol 物品装备结果
// @param {uint32} result, 结果 0成功
net_protocol_handlers.CMD_CS_EQUIP_ITEM_RESULT = 1305;
_BindFunc(1305, function(obj) {
	cc.assert(obj.result != undefined, "CMD_CS_EQUIP_ITEM_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_CS_EQUIP_ITEM_RESULT(obj);
});

// @protocol 领取每日登陆奖励结果
// @param {uint32} result, 0 成功
net_protocol_handlers.CMD_SC_GET_REWARD_RESULT = 1627;
_BindFunc(1627, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_GET_REWARD_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_GET_REWARD_RESULT(obj);
});

// @protocol 购买礼包结果
// @param {uint32} result, 0成功
// @param {list} gift_type_data, 礼包各种类型对应的购买数量
net_protocol_handlers.CMD_SC_BUY_GIFT_RESULT = 1609;
_BindFunc(1609, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_BUY_GIFT_RESULT.result is undefined.");
	cc.assert(obj.gift_type_data != undefined, "CMD_SC_BUY_GIFT_RESULT.gift_type_data is undefined.");
	net_protocol_handlers.ON_CMD_SC_BUY_GIFT_RESULT(obj);
});

// @protocol 装备槽一键升级结果
// @param {uint32} result, 结果 0成功
net_protocol_handlers.CMD_SC_EQUIP_SLOT_UPGRADE_TOP_RESULT = 1309;
_BindFunc(1309, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_EQUIP_SLOT_UPGRADE_TOP_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_EQUIP_SLOT_UPGRADE_TOP_RESULT(obj);
});

// @protocol 使用用户名密码登录
// @param {string} username, 用户名
// @param {string} password, 密码
net_protocol_handlers.CMD_CS_LOGIN_WITH_USER_PASS = 501;
net_protocol_handlers.SEND_CMD_CS_LOGIN_WITH_USER_PASS = function(obj) {
	cc.assert(obj.username != undefined, "CMD_CS_LOGIN_WITH_USER_PASS.username is undefined.");
	cc.assert(obj.password != undefined, "CMD_CS_LOGIN_WITH_USER_PASS.password is undefined.");
	_SendFunc(501, obj);
};

// @protocol 升级技能
// @param {uint32} skill_idx, 技能索引
net_protocol_handlers.CMD_CS_SKILL_UP = 1202;
net_protocol_handlers.SEND_CMD_CS_SKILL_UP = function(obj) {
	cc.assert(obj.skill_idx != undefined, "CMD_CS_SKILL_UP.skill_idx is undefined.");
	_SendFunc(1202, obj);
};

// @protocol 购买角色大招释放数量
// @param {uint32} player_id, player ID
net_protocol_handlers.CMD_CS_BUY_SUPER_SKILL_COUNT = 1606;
net_protocol_handlers.SEND_CMD_CS_BUY_SUPER_SKILL_COUNT = function(obj) {
	cc.assert(obj.player_id != undefined, "CMD_CS_BUY_SUPER_SKILL_COUNT.player_id is undefined.");
	_SendFunc(1606, obj);
};

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

// @protocol 保存当前引导类型是否结束
// @param {uint32} guideType, 引导类型
net_protocol_handlers.CMD_CS_CURRENT_GUIDE_DONE = 1620;
net_protocol_handlers.SEND_CMD_CS_CURRENT_GUIDE_DONE = function(obj) {
	cc.assert(obj.guideType != undefined, "CMD_CS_CURRENT_GUIDE_DONE.guideType is undefined.");
	_SendFunc(1620, obj);
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

// @protocol 试炼购买从最高关卡开始
// @param {uint32} result, 0
net_protocol_handlers.CMD_SC_BUY_SHILIAN_FINISH = 1640;
_BindFunc(1640, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_BUY_SHILIAN_FINISH.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_BUY_SHILIAN_FINISH(obj);
});

// @protocol 装备强化结果
// @param {uint32} result, 
net_protocol_handlers.CMD_SC_EQUIP_STRENGTHEN_RESULT = 1312;
_BindFunc(1312, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_EQUIP_STRENGTHEN_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_EQUIP_STRENGTHEN_RESULT(obj);
});

// @protocol 领取每日VIP奖励
// @param {uint32} player_id, 角色id
net_protocol_handlers.CMD_CS_GET_VIP_REWARD = 1628;
net_protocol_handlers.SEND_CMD_CS_GET_VIP_REWARD = function(obj) {
	cc.assert(obj.player_id != undefined, "CMD_CS_GET_VIP_REWARD.player_id is undefined.");
	_SendFunc(1628, obj);
};

// @protocol 装备槽一键升级到最高等级(最高只能和人物角色同级)
// @param {uint32} slot_type, 槽类型
net_protocol_handlers.CMD_CS_EQUIP_SLOT_UPGRADE_TOP = 1308;
net_protocol_handlers.SEND_CMD_CS_EQUIP_SLOT_UPGRADE_TOP = function(obj) {
	cc.assert(obj.slot_type != undefined, "CMD_CS_EQUIP_SLOT_UPGRADE_TOP.slot_type is undefined.");
	_SendFunc(1308, obj);
};

// @protocol 换装
// @param {uint32} skin_id, 套装id
net_protocol_handlers.CMD_CS_SKIN_CHANGE = 1602;
net_protocol_handlers.SEND_CMD_CS_SKIN_CHANGE = function(obj) {
	cc.assert(obj.skin_id != undefined, "CMD_CS_SKIN_CHANGE.skin_id is undefined.");
	_SendFunc(1602, obj);
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

// @protocol 战斗复活
// @param {uint32} play_id, player_id
net_protocol_handlers.CMD_CS_BATTLE_REVIVE = 1624;
net_protocol_handlers.SEND_CMD_CS_BATTLE_REVIVE = function(obj) {
	cc.assert(obj.play_id != undefined, "CMD_CS_BATTLE_REVIVE.play_id is undefined.");
	_SendFunc(1624, obj);
};

// @protocol 更新倒计时
// @param {list} gift_type_data, 礼包各种类型对应的倒计时时间
net_protocol_handlers.CMD_CS_UPDATE_GIFT_TIME = 1612;
net_protocol_handlers.SEND_CMD_CS_UPDATE_GIFT_TIME = function(obj) {
	cc.assert(obj.gift_type_data != undefined, "CMD_CS_UPDATE_GIFT_TIME.gift_type_data is undefined.");
	_SendFunc(1612, obj);
};

// @protocol 请求订单号
// @param {uint32} good_id, 商品id
net_protocol_handlers.CMD_CS_SHOP_ORDER = 1103;
net_protocol_handlers.SEND_CMD_CS_SHOP_ORDER = function(obj) {
	cc.assert(obj.good_id != undefined, "CMD_CS_SHOP_ORDER.good_id is undefined.");
	_SendFunc(1103, obj);
};

// @protocol 领取每日登录奖励
// @param {uint32} player_id, 角色id
net_protocol_handlers.CMD_CS_GET_REWARD = 1626;
net_protocol_handlers.SEND_CMD_CS_GET_REWARD = function(obj) {
	cc.assert(obj.player_id != undefined, "CMD_CS_GET_REWARD.player_id is undefined.");
	_SendFunc(1626, obj);
};

// @protocol 领取每日VIP奖励结果
// @param {uint32} result, 0 成功
net_protocol_handlers.CMD_SC_GET_VIP_REWARD_RESULT = 1629;
_BindFunc(1629, function(obj) {
	cc.assert(obj.result != undefined, "CMD_SC_GET_VIP_REWARD_RESULT.result is undefined.");
	net_protocol_handlers.ON_CMD_SC_GET_VIP_REWARD_RESULT(obj);
});

