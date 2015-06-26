#include "AndGameSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

using namespace cocos2d;


extern "C" {

#define  CLASS_NAME "com/fate/dev/AndGameSdkJni"


//#define AndroidClassName "org/cocos2dx/javascript/AppActivity"
//
//void Java_org_cocos2dx_javascript_AppActivity_startLevel(int nLevel)
//{
//    char _szTxt[100] = {0};
//    sprintf(_szTxt, "level_%d", nLevel);
//
//    JniMethodInfo minfo;
//    if(JniHelper::getStaticMethodInfo(minfo,AndroidClassName,"startLevel","(Ljava/lang/String;)V")) {
//        jstring stringArg = minfo.env->NewStringUTF(_szTxt);
//        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg);
//    }
//}
//
////public static native void paymentCompleted(final int id);
//void Java_org_cocos2dx_javascript_AppActivity_paymentCompleted(JNIEnv *env, jobject thiz, jint id, jint nRes)
//{
//    log("Java_org_cocos2dx_javascript_AppActivity_paymentCompleted");
//    // 	CCNotificationCenter::sharedNotificationCenter()->postNotification(payment, CCInteger::create(id));
//    int _nId = id;
//    int _nRes = nRes;
//    log("yuxiao @@@@@@@@@@@@ %d %d", _nId, _nRes);
//}


static void Java_com_fate_dev_AndGameSdkJni_init()
{
    JniMethodInfo minfo;

    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "getInstance", "()Ljava/lang/Object;")) {
        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

        if(jobj) {
            if (JniHelper::getMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
                minfo.env->CallVoidMethod(jobj, minfo.methodID);
            }
        }
    }
}

static void Java_com_fate_dev_AndGameSdkJni_buy(const char *param)
{
    cocos2d::log("Java_com_fate_dev_AndGameSdkJni_buy");
    JniMethodInfo minfo;

    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "getInstance", "()Ljava/lang/Object;")) {
        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

        if(jobj) {
            if (JniHelper::getMethodInfo(minfo, CLASS_NAME, "buy", "(Ljava/lang/String;)V")) {
                jstring jparam = minfo.env->NewStringUTF(param);

                minfo.env->CallVoidMethod(jobj, minfo.methodID, jparam);
            }
        }
    }
}

void Java_com_fate_dev_AndGameSdkJni_onBuyCallback(JNIEnv *env, jobject thiz, jstring jparam)
{
    cocos2d::log("Java_com_fate_dev_AndGameSdkJni_onBuyCallback");
    std::string param = JniHelper::jstring2string(jparam);
    AndGameSdk::getInstance()->onBuyCallback(param.c_str());
}

static bool Java_org_cocos2dx_javascript_AppActivity_isMusicEnabled()
{
//    JniMethodInfo t;
//    if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "isMusicPlay","()Z")) {
//        return t.env->CallStaticBooleanMethod(t.classID, t.methodID);
//    }
    return false;
}

}



static AndGameSdk *instance = nullptr;
AndGameSdk *AndGameSdk::getInstance()
{
    if(instance == nullptr) {
        instance = new AndGameSdk();
    }
    return instance;
}

void AndGameSdk::init()
{
    Java_com_fate_dev_AndGameSdkJni_init();
}

void AndGameSdk::buy(const std::string &param)
{
    Java_com_fate_dev_AndGameSdkJni_buy(param.c_str());
}

bool AndGameSdk::isMusicEnabled()
{
    return Java_org_cocos2dx_javascript_AppActivity_isMusicEnabled();
}
