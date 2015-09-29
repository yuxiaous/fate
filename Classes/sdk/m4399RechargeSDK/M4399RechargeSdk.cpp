#include "M4399RechargeSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#include "json/document.h"
#include "json/rapidjson.h"
#include "json/filestream.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
#include "GameUtils.h"
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/m4399/M4399RechargeSdkJni"

extern "C" {
    void M4399RechargeSdk_init()
    {
        cocos2d::log("M4399RechargeSdk_init");

        std::string gameKey = "107217";
        std::string gameName = "测试游戏";

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "(Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring jgamekey = minfo.env->NewStringUTF(gameKey.c_str());
            jstring jgamename = minfo.env->NewStringUTF(gameName.c_str());
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jgamekey, jgamename);
        }
    }

    void M4399RechargeSdk_charge(const std::string &order, const std::string &name, int cost)
    {
        cocos2d::log("M4399RechargeSdk_charge");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "charge", "(Ljava/lang/String;Ljava/lang/String;I)V")) {
            jstring jorder = minfo.env->NewStringUTF(order.c_str());
            jstring jname = minfo.env->NewStringUTF(name.c_str());
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jorder, jname, cost);
        }
    }

    void M4399RechargeSdk_charge2(const std::string &order, const std::string &identifier)
    {
        std::vector<std::string> params;
        GameUtils::split(identifier, ",", params);

        if(params.size() == 2) {
            M4399RechargeSdk_charge(order, params[0], atoi(params[1].c_str()));
        }
    }

    void Java_com_hdngame_fate_m4399_M4399RechargeSdkJni_onM4399ChargeCallback(JNIEnv *env, jobject thiz, jint result, jstring jorder)
    {
        cocos2d::log("Java_com_hdngame_fate_m4399_M4399RechargeSdkJni_onM4399ChargeCallback");

        std::string order = JniHelper::jstring2string(jorder);
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
            SdkChargeProtocol::onChargeCallback(result, order.c_str());
        });
    }

    void M4399RechargeSdk_destroy()
    {
        cocos2d::log("M4399RechargeSdk_destroy");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "destroy", "()V")) {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
    }
}

void M4399RechargeSdk::activityOnCreate()
{
    M4399RechargeSdk_init();
}

void M4399RechargeSdk::activityOnDestroy()
{
    M4399RechargeSdk_destroy();
}

void M4399RechargeSdk::charge(const std::string &order, const std::string &identifier)
{
    M4399RechargeSdk_charge2(order, identifier);
}

