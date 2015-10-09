#include "TencentMidasSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#include "GameUtils.h"

using namespace cocos2d;


#define  CLASS_NAME "com/hdngame/fate/qq/TencentMidasSdkJni"

extern "C" {
    void TencentMidasSdk_init()
    {
        cocos2d::log("TencentMidasSdk_init");

        std::string offerid = "1450004328";
        std::string appkey = "OrLiuwhyCCFyPskaNF5Q8BzFboPmryNU";

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "(Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring jofferid = minfo.env->NewStringUTF(offerid.c_str());
            jstring jappkey = minfo.env->NewStringUTF(appkey.c_str());
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jofferid, jappkey);
        }
    }

    void TencentMidasSdk_pay(const std::string &order, const std::string &identifier)
    {
        cocos2d::log("TencentMidasSdk_pay order: %s, identifier: %s", order.c_str(), identifier.c_str());

//        if(order.empty() || identifier.empty()) {
//            SdkChargeProtocol::onChargeCallback(1, order);
//            return;
//        }

        std::vector<std::string> params;
        GameUtils::split(identifier, ",", params);

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "launchPayClient", "(Ljava/lang/String;Ljava/lang/String;I)V")) {
            jstring jorder = minfo.env->NewStringUTF(order.c_str());
            jstring jname = minfo.env->NewStringUTF(params[0].c_str());
            int price = atoi(params[1].c_str());
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jorder, jname, price);
        }
    }

    void Java_com_hdngame_fate_qq_TencentMidasSdkJni_onTencentMidasChargeCallback(JNIEnv *env, jobject thiz, jint result, jstring jorder)
    {
        cocos2d::log("Java_com_hdngame_fate_qq_TencentMidasSdkJni_onTencentMidasChargeCallback");

        std::string order = JniHelper::jstring2string(jorder);
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
            SdkChargeProtocol::onChargeCallback(result, order.c_str());
        });
    }
}


void TencentMidasSdk::activityOnCreate()
{
    TencentMidasSdk_init();
}

void TencentMidasSdk::charge(const std::string &order, const std::string &identifier)
{
    TencentMidasSdk_pay(order, identifier);
}


