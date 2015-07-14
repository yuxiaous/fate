/*
 * SFGameNativeInterface.h
 *
 *  Created on: 2014-7-28
 *      Author: wanshaofeng
 */

#ifndef SFGAMENATIVEINTERFACE_H_
#define SFGAMENATIVEINTERFACE_H_

#include <sys/types.h>

class SFNativeGameExitCallBack {
public:
	SFNativeGameExitCallBack() {};
	virtual ~SFNativeGameExitCallBack() {};
	virtual void onGameExit(bool b) = 0;
};

class SFNativeIPayResulBack {
public:
	SFNativeIPayResulBack() {};
	virtual ~SFNativeIPayResulBack() {};
	virtual void onCanceled(const char* remain) = 0;
	virtual void onFailed(const char* remain) = 0;
	virtual void onSuccess(const char* remain) = 0;
};

class SFGameNativeInterface {
public:
	//设置退出回调
	static void setSFGameExitCallBack(SFNativeGameExitCallBack* exitCallBack);
	//设置支付回调
	static void setSFIPayResulBack(SFNativeIPayResulBack* payCallBack);
	static void onDestroy();
	static void onExit();
	static void onInit();
	static void onPause();
	static void onResume();
	static bool isPaid(const char* id);
	//支付接口 id:计费点编号
	static void pay(const char* id);
	static void recharge(int price,
			const char* chargeDesc, const char* sign);
	static void setPaid(const char* id);
	//移动基地SDK，进入游戏时必须使用这个方法进行判断音乐是否开关
	static bool isMusicEnabled();
	static void viewMoreGames();
};

#endif /* SFGAMENATIVEINTERFACE_H_ */
