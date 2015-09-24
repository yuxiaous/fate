#include "KuwoLoginSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/kuwo/KuwoLoginSdkJni"

extern "C" {
    void KuwoLoginSdk_enterGame(const std::string &gameid)
    {
        cocos2d::log("KuwoLoginSdk_enterGame");

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "enterGame", "(Ljava/lang/String;)V")) {
            jstring jgameid = minfo.env->NewStringUTF(gameid.c_str());
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jgameid);
        }
    }
}

void KuwoLoginSdk::activityOnCreate()
{
    KuwoLoginSdk_enterGame("10424");
}

