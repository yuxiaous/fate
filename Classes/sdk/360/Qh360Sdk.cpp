#include "Qh360Sdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

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

    void Qh360Sdk_destroy()
    {
        cocos2d::log("Qh360Sdk_destroy");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "destroy", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }

    void Qh360Sdk_login()
    {
        cocos2d::log("Qh360Sdk_login");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "doSdkLogin", "()V")) {
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

         JniMethodInfo minfo;
         if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "pay", "(Ljava/lang/String;Ljava/lang/String;)V")) {
             jstring jorder = minfo.env->NewStringUTF(order.c_str());
             jstring jidentifier = minfo.env->NewStringUTF(identifier.c_str());
             minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jorder, jidentifier);
         }
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

void Qh360Sdk::login()
{
    Qh360Sdk_login();
}

void Qh360Sdk::charge(const std::string &order, const std::string &identifier)
{

}
