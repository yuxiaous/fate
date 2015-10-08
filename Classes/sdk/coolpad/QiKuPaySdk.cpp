#include "QiKuPaySdk.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
using namespace cocos2d;

#define  CLASS_NAME "com/hdngame/fate/coolpad/QiKuPaySdkJni"


//APP ID：5000001964
//平台公钥：MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCilat6uT74Rs1l39Eit5UnOH6bdtQCg78k/QuCbNDC+9pmKm2Jg7htFkqSgIZm5FPrQzQUtPP78qi/a1Lkeyig6+TeW55gesPOZ4VYydIhp/TTOfRnZPZeBURSzSoqWD159jM40U89Csgt9QWzrzRE1hv+pYCwAHBKTn3L2ClYMQIDAQAB
//应用私钥：MIICXgIBAAKBgQCaNppZGdk0IOmFFK5Ea4q03FDm8oRtZgX6/Tn034inUTrlQkiDgHpiYlAncfLAg7pRFIjdMXyycYEMcCxMTMrZub++CSbfW8yUVPm0dOPfNe8XZgkS9Y86E+uBxJ2w8eicZgopHaFn9lxBEBnWrJQGpZF/ipalJCgJDSW7iNNNkwIDAQABAoGBAIWxyvRuPWk9E1alzENS/Ki5zIW8QOTbK1oiiUlrNfzgpm+1nEota2y6EQVxe2Q9j5zVcaZaTeIiFyAia7UmakEpjH6jtjz7Y79k4BaKMhbklSvnub59H93NKvJ8M0ek3NGpaNpD8XRa0BqZRMmzqwSHS70HTjZ9N7RNWhFhxNjpAkEAx3e/rd5v7KPGDZUSJKzUsFxvfPmQgAusgHwY7nBzmLEp70rjxybcKHWR1f+wuBJkUb3s1w4bIKAumIRntLGLHwJBAMXrch7UosYVnxsggrWJRQVKfZIjaQi0S8P+gwzSpPTPQ5zU2sZJ61ipMFzrn2LQ6AibcbS2d3GirGOdcdr2Iw0CQQCZ7TD/7Z2VkbSumpELuEvRZSOr37LA/UE7TYi3yBOMi3r+7F3mO3i9yCyoZc5r3dWItvXj50DL5pDOpa6Z5EClAkEAo6VlmrBeVkKSZ6+d49Q4SYOqCCdXNWc+LjRGz1dsJS8qzIYCzmlYOtrJrkr0YpQxBszgW3dzk3XZ7BPGjDFwEQJAWa+qvxuaZ2FuLFyd0MCVGlhN5KBcIAR65ylobW2mqwj/hVg5P705A/gwogd7GtS5oZkDN/np+UwVghTkAHDaBA==
//appkey：3afe83772cbe4e508e80de3f0edc3db3

extern "C" {
    void QiKuPaySdk_init()
    {
        cocos2d::log("QiKuPaySdk_init");

        std::string appid = "5000001964";
        std::string appkey = "3afe83772cbe4e508e80de3f0edc3db3";

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "init", "(Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring jappid = minfo.env->NewStringUTF(appid.c_str());
            jstring jappkey = minfo.env->NewStringUTF(appkey.c_str());
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jappid, jappkey);
        }
    }

    void QiKuPaySdk_pay(const std::string &order, const std::string &identifier)
    {
        cocos2d::log("QiKuPaySdk_pay order: %s, identifier: %s", order.c_str(), identifier.c_str());

//        if(order.empty() || identifier.empty()) {
//            SdkChargeProtocol::onChargeCallback(1, order);
//            return;
//        }

        JniMethodInfo minfo;
        if (JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "pay", "(Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring jorder = minfo.env->NewStringUTF(order.c_str());
            jstring jidentifier = minfo.env->NewStringUTF(identifier.c_str());
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jorder, jidentifier);
        }
    }

}



void QiKuPaySdk::activityOnCreate()
{

}

