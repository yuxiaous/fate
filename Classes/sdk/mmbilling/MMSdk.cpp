#include "MMSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

using namespace cocos2d;

#define  CLASS_NAME "com/fate/cmcc/mm.MMSdkJni"


MMSdk *MMSdk::getInstance()
{
    static MMSdk *instance = nullptr;
    if(instance == nullptr) {
        instance = new MMSdk();
    }
    return instance;
}

void MMSdk::init()
{
    const char *appid = "1111111";
    const char *appkey = "2222222";

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jappid = minfo.env->NewStringUTF(appid);
        jstring jappkey = minfo.env->NewStringUTF(appkey);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jappid, jappkey);
        minfo.env->DeleteLocalRef(jappid);
        minfo.env->DeleteLocalRef(jappkey);
    }
}

void MMSdk::charge(const std::string &order, const std::string &identifier)
{

}

