#include "Qh360Sdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#include "GameUtils.h"

using namespace cocos2d;


#define  CLASS_NAME "com/hdngame/fate/qh360/Qh360SdkJni"

//appid：202702226
//appkey：f819ef3f4489f310beece90d28060c20
//appsecret：bc7fcc8a6b0e4403091a2f772141e0b5
//
//http://yunpan.cn/cdIDC4LhUa9v2  访问密码 66dd
//自检工具
//http://yunpan.cn/cd7aTX5RCK5ng  访问密码 b381


extern "C" {
    void Qh360Sdk_init()
    {
        cocos2d::log("Qh360Sdk_init");

      JniMethodInfo minfo;
      if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
          minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
      }
    }

    void Qh360Sdk_charge(const std::string &order, const std::string &identifier)
    {
        cocos2d::log("Qh360Sdk_charge order: %s, identifier: %s", order.c_str(), identifier.c_str());

//         if(order.empty() || identifier.empty()) {
//             SdkChargeProtocol::onChargeCallback(1, order);
//             return;
//         }

        std::vector<std::string> ret;
        GameUtils::split(identifier, ",", ret);

         JniMethodInfo minfo;
         if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "pay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
             jstring jorder = minfo.env->NewStringUTF(order.c_str());
             jstring jproductid = minfo.env->NewStringUTF(ret[0].c_str());
             jstring jproductname = minfo.env->NewStringUTF(ret[1].c_str());
             jstring jamount = minfo.env->NewStringUTF(ret[2].c_str());
             minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jorder, jproductid, jproductname, jamount);
         }
    }

    void Java_com_hdngame_fate_qh360_Qh360SdkJni_onQh360ChargeCallback(JNIEnv *env, jobject thiz, jint result, jstring jorder)
    {
        cocos2d::log("qh360_Qh360SdkJni_onQh360ChargeCallback");

        std::string order = JniHelper::jstring2string(jorder);
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
            SdkChargeProtocol::onChargeCallback(result, order.c_str());
        });
    }

    void Qh360Sdk_destroy()
    {
        cocos2d::log("Qh360Sdk_destroy");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "destroy", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }

    void Qh360Sdk_quit()
    {
        cocos2d::log("Qh360Sdk_quit");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "doSdkQuit", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }

    void Java_com_hdngame_fate_qh360_Qh360SdkJni_onQh360Exit(JNIEnv *env, jobject thiz)
    {
        cocos2d::log("Java_com_hdngame_fate_qh360_Qh360SdkJni_onQh360Exit");
        Director::getInstance()->end();
    }
}

void Qh360Sdk::activityOnCreate()
{
    Qh360Sdk_init();
}

void Qh360Sdk::activityOnDestroy()
{
    Qh360Sdk_destroy();
}

void Qh360Sdk::charge(const std::string &order, const std::string &identifier)
{
    Qh360Sdk_charge(order, identifier);
}

void Qh360Sdk::sdkCommand(const std::string &clazz, const std::string &method, const std::string &param)
{
    if(clazz != "Qh360"){
        return;
    }
    if(method == "exit") {
        Qh360Sdk_quit();
    }
}