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
	//�����˳��ص�
	static void setSFGameExitCallBack(SFNativeGameExitCallBack* exitCallBack);
	//����֧���ص�
	static void setSFIPayResulBack(SFNativeIPayResulBack* payCallBack);
	static void onDestroy();
	static void onExit();
	static void onInit();
	static void onPause();
	static void onResume();
	static bool isPaid(const char* id);
	//֧���ӿ� id:�Ʒѵ���
	static void pay(const char* id);
	static void recharge(int price,
			const char* chargeDesc, const char* sign);
	static void setPaid(const char* id);
	//�ƶ�����SDK��������Ϸʱ����ʹ��������������ж������Ƿ񿪹�
	static bool isMusicEnabled();
	static void viewMoreGames();
};

#endif /* SFGAMENATIVEINTERFACE_H_ */
