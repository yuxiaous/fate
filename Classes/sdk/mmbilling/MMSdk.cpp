#include "MMSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/mm/MMSdkJni"

static std::string g_order;
static int g_result = 0;
static bool g_confirm = false;

extern "C" {

    void Java_com_hdngame_fate_mm_MMSdkJni_onMmChargeCallback(JNIEnv *env, jobject thiz, jint result)
    {
        cocos2d::log("Java_com_hdngame_fate_mm_MMSdkJni_onMmChargeCallback");
        g_result = result;
        g_confirm = true;
//        MMSdk::getInstance()->onChargeCallback(result, order.c_str());
    }
}


static MMSdk *instance = nullptr;

MMSdk::MMSdk()
{
    instance = this;
}

MMSdk *MMSdk::getInstance()
{
    return instance;
}

void MMSdk::update(float dt)
{
    if(g_confirm) {
        onChargeCallback(g_result, g_order.c_str());
        g_result = 0;
        g_order.clear();
        g_confirm = false;
    }
}

void MMSdk::activityOnCreate()
{
    cocos2d::log("MMSdk::activityOnCreate");

    const char *appid = "300009184111";
    const char *appkey = "2847FDDE0888C26364D0D0A8FEBFC34C";

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jappid = minfo.env->NewStringUTF(appid);
        jstring jappkey = minfo.env->NewStringUTF(appkey);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jappid, jappkey);
        minfo.env->DeleteLocalRef(jappid);
        minfo.env->DeleteLocalRef(jappkey);
    }
}

void MMSdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("MMSdk::charge");

    if(order.empty() || identifier.empty()) {
        onChargeCallback(1, order);
        return;
    }

    g_order = order;

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "order", "(Ljava/lang/String;)V")) {
        jstring jidentifier = minfo.env->NewStringUTF(identifier.c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jidentifier);
        minfo.env->DeleteLocalRef(jidentifier);
    }
}

