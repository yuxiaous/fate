#include "TencentMidasSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

using namespace cocos2d;


#define  CLASS_NAME "com/hdngame/fate/midas/TencentMidasSdkJni"


static TencentMidasSdk *instance = nullptr;

TencentMidasSdk::TencentMidasSdk()
{
    instance = this;
}

TencentMidasSdk *TencentMidasSdk::getInstance()
{
    return instance;
}


