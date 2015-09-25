#include "MMSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/mm/MMSdkJni"


//计费点代码	 商品名称
//30000913953201	1瓶回复药水	 	应用编码：	300009139532
//30000913953202	6瓶回复药水	 	app key：	BFE9123C8839FBF71862A521D6D38DB2
//30000913953203 	购买大招
//30000913953204	尼禄套装
//30000913953205	2万金币
//30000913953206	6.6万金币
//30000913953207	14.4万金币
//30000913953208	28万金币
//30000913953209	体力
//30000913953210	传奇套装礼包
//30000913953211	传说武器礼包
//30000913953212	至尊礼包
//30000913953213	VIP礼包
//30000913953214 	复活
//30000913953215	一键满级

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

    const char *appid = "300009139532";
    const char *appkey = "BFE9123C8839FBF71862A521D6D38DB2";

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jappid = minfo.env->NewStringUTF(appid);
        jstring jappkey = minfo.env->NewStringUTF(appkey);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jappid, jappkey);
        minfo.env->DeleteLocalRef(jappid);
        minfo.env->DeleteLocalRef(jappkey);
    }
}

void MMSdk::charge(const std::string &order, const std::string &key)
{
    cocos2d::log("MMSdk::charge");

    std::string identifier = getChargeIdentifier(key);
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

