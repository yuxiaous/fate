#include "DKSingleSdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/dksingle/DKSingleSdkJni"


void DKSingleSdk::init()
{
    cocos2d::log("DKSingleSdk::init");
}

void DKSingleSdk::activityOnCreate()
{
    cocos2d::log("DKSingleSdk::activityOnCreate");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "()V")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

