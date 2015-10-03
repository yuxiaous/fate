#include "MiGameCenterSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define CLASS_NAME "com/hdngame/fate/mi/MiGameCenterSdkJni"


void MiGameCenterSdk::activityOnCreate()
{
    cocos2d::log("MiGameCenterSdk::activityOnCreate");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void MiGameCenterSdk::charge(const std::string &order, const std::string &identifier)
{
    cocos2d::log("MiGameCenterSdk::charge");
}

