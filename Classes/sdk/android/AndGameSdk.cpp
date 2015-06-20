#include "AndGameSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

using namespace cocos2d;

#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"
#define AndroidClassName "org/cocos2dx/javascript/AppActivity"

extern "C" {
	void Java_org_cocos2dx_javascript_AppActivity_startLevel(int nLevel)
	{
		char _szTxt[100] = {0};
    	sprintf(_szTxt, "level_%d", nLevel);

    	JniMethodInfo minfo;
    	if(JniHelper::getStaticMethodInfo(minfo,AndroidClassName,"startLevel","(Ljava/lang/String;)V")) {
    		jstring stringArg = minfo.env->NewStringUTF(_szTxt);
    		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg);
    	}
	}

    //public static native void paymentCompleted(final int id);
    void Java_org_cocos2dx_javascript_AppActivity_paymentCompleted(JNIEnv *env, jobject thiz, jint id, jint nRes)
    {
        log("Java_org_cocos2dx_javascript_AppActivity_paymentCompleted");
        // 	CCNotificationCenter::sharedNotificationCenter()->postNotification(payment, CCInteger::create(id));
        int _nId = id;
        int _nRes = nRes;
        log("yuxiao @@@@@@@@@@@@ %d %d", _nId, _nRes);
    }
}




void AndGameSdk::init()
{
    Java_org_cocos2dx_javascript_AppActivity_startLevel(112233);
}

