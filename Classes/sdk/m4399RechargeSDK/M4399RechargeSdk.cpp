#include "M4399RechargeSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#include "json/document.h"
#include "json/rapidjson.h"
#include "json/filestream.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/m4399/M4399RechargeSdkJni"

extern "C" {
    void M4399RechargeSdk_init(const std::string &gameKey, const std::string &gameName)
    {
        cocos2d::log("M4399RechargeSdk_init");

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

    void M4399RechargeSdk_charge2(const std::string &order, const std::string &key)
    {
        std::string configstr = SdkChargeProtocol::getShopConfig(key);
        if(configstr.empty()) {
            return;
        }

        rapidjson::Document json;
        json.Parse<0>(configstr.c_str());

        rapidjson::Value jcost;
        jcost = json["pay_cost"];

        rapidjson::Value jname;
        jname = json["name"];

        if(!jcost.IsInt() || !jname.IsString()) {
            return;
        }

        M4399RechargeSdk_charge(order, jname.GetString(), jcost.GetInt());
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
    M4399RechargeSdk_init("107217", "测试游戏");
}

void M4399RechargeSdk::activityOnDestroy()
{
    M4399RechargeSdk_destroy();
}

void M4399RechargeSdk::charge(const std::string &order, const std::string &key)
{
    M4399RechargeSdk_charge2(order, key);
}

