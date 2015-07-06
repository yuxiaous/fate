#include "MMSdk.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

using namespace cocos2d;

#define  CLASS_NAME "com/fate/cmcc/mm.MMSdkJni"


//应用编码：	300009139532
//app key：	BFE9123C8839FBF71862A521D6D38DB2

//计费点代码	        商品名称
//30000913953201	1瓶回复药水
//30000913953202	6瓶回复药水
//30000913953203 	30瓶回复药水
//30000913953204	尼禄套装
//30000913953205	2万金币
//30000913953206	6.6万金币
//30000913953207	14.4万金币
//30000913953208	28万金币
//30000913953209	体力
//30000913953210	传奇套装礼包
//30000913953211	传说武器礼包
//30000913953212	至尊礼包
//30000913953213	VIP礼包
//30000913953214 	复活
//30000913953215	一键满级


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
    const char *appid = "300009139532";
    const char *appkey = "BFE9123C8839FBF71862A521D6D38DB2";

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

